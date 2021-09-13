#include <cstdio>
#include <vector>
#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <csignal>
#include <netinet/in.h>

void listen_loop();
void do_reads();
void memory_loop();
unsigned int get_index();
void list_clients();
std::vector<int> fds;
std::vector<char*> buffers;

void sigpipe_handler(int){}
char target[] = "This is my super secret string";


void menu() {
    int result = -1;
    puts("0) List connected clients\n1) Remove clients\n2) Read client buffer\n3) Exit\n=> ");
    std::cin >> result;
    unsigned int index;
    switch (result) {
        case 0:
            list_clients();
            break;
        case 1:
            index = get_index();
            if (index != 0x31337) {
                fds[index] = -1;
            }
            break;
        case 2:
            index = get_index();
            if (index != 0x31337) {
                puts(buffers[index]);
            }  
            break;
        case 3:
            system("echo 'bye!'");
            exit(0);
        default:
            puts("Bad option");
    }
}

void list_clients() {
    for (int i = 0; i < fds.size(); i++) {
        if (fds[i] != -1)
            printf("%d => Client<%d>\n", i, fds[i]);
    }
}

unsigned int get_index() {
    puts("Enter index of client to act upon => ");
    unsigned int index;
    std::cin >> index;
    if (index < fds.size() && fds[index] != -1)
        return index;
    else {
        puts("Bad index");
        return 0x31337;
    }
}

int main() {
    signal(SIGPIPE,sigpipe_handler);
    std::thread listener(listen_loop);
    listener.detach();
    std::thread reader(do_reads);
    reader.detach();
    std::thread memory(memory_loop);
    memory.detach();
    while (true) {
        menu();
    }
}

void do_reads() {
    while (true) {
        std::vector<char*> valid_buf;
        std::vector<int> valid_fd;
        for (int i = 0; i < fds.size(); i++) {
            if (fds[i] != -1 && buffers[i] != nullptr) {
                valid_fd.push_back(fds[i]);
                valid_buf.push_back(buffers[i]);
            }
        }
        sleep(1);
        for (int i = 0; i < valid_fd.size(); i++) {
            int res = recv(valid_fd[i], valid_buf[i], 0x40, MSG_DONTWAIT);
        }
    }
}

void listen_loop() {
    int server_fd;
    struct sockaddr_in address{};
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(31337);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0) {
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        exit(EXIT_FAILURE);
    }

    while (true) {
        int sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (sock > 0) {
            fds.push_back(sock);
            buffers.push_back(nullptr);
        }
    }
}

void memory_loop() {
    while (true) {
        for (int i = 0; i < buffers.size(); i++) {
            if (buffers[i] == nullptr && fds[i] != -1) {
                buffers[i] = new char[0x40];
            } else if (fds[i] == -1 && buffers[i] != nullptr) {
                delete[] buffers[i];
                buffers[i] = nullptr;
            }
        }
        usleep(1000);
    }
}