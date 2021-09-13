FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update
RUN apt-get install -y xinetd
RUN apt-get install -y libglib2.0-0

RUN useradd -m spim_panel

RUN mkdir /home/spim_panel/usr
RUN cp -R /lib* /home/spim_panel
RUN cp -R /usr/lib* /home/spim_panel/usr

RUN mkdir /home/spim_panel/bin && \
    cp /bin/* /home/spim_panel/bin

RUN mkdir /home/spim_panel/dev && \
    mknod /home/spim_panel/dev/null c 1 3 && \
    mknod /home/spim_panel/dev/zero c 1 5 && \
    mknod /home/spim_panel/dev/random c 1 8 && \
    mknod /home/spim_panel/dev/urandom c 1 9 && \
    chmod 666 /home/spim_panel/dev/*

COPY ./challenge.xinetd /etc/xinetd.d/challenge
COPY ./start.sh /start.sh
RUN echo "Quit Spamming..." > /etc/banner_fail

RUN chmod +x /start.sh

COPY ./bin/ /home/spim_panel/
RUN chown -R root:spim_panel /home/spim_panel && \
    chmod -R 750 /home/spim_panel && \
    chmod 740 /home/spim_panel/flag.txt

CMD ["/start.sh"]

EXPOSE 1337