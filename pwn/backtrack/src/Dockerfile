FROM ubuntu:18.04
RUN apt update && apt install -y socat
EXPOSE 1337
EXPOSE 31337
COPY backtrack /chall
COPY flag.txt /flag.txt
CMD ["socat", "tcp-l:1337,reuseaddr,fork", "EXEC:/chall"]
