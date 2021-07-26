FROM ubuntu:20.04
RUN apt update && apt install -y socat
EXPOSE 1337
COPY manager /chall
COPY flag.txt /flag.txt
CMD ["socat", "tcp-l:1337,reuseaddr,fork", "EXEC:/chall"]
