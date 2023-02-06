FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update

RUN apt-get install -y vim git gcc curl wget make net-tools build-essential nasm
# RUN apt-get install -y check libbz2-dev libcurl4-openssl-dev libjson-c-dev libmilter-dev
# RUN apt-get install -y python3 python3-pip python3-pytest 
# RUN apt-get install -y libncurses5-dev libpcre2-dev libssl-dev zlib1g-dev
# RUN apt-get install -y pkg-config valgrind libxml2-dev

# RUN python3 -m pip install cmake
# RUN apt-get install -y cargo rustc

# RUN wget https://www.clamav.net/downloads/production/clamav-0.105.1-3.tar.gz && tar xf clamav-0.105.1-3.tar.gz && cd clamav-0.105.1

# RUN mkdir -p /clamav-0.105.1/build && cd /clamav-0.105.1/build
# RUN cmake .. 
# RUN cmake --build .
# RUN ctest
# RUN cmake --build . --target install

FROM ubuntu:20.04

RUN apt-get update && apt-get install -y wget

RUN groupadd clamav && useradd -g clamav -s /bin/false -c "Clam Antivirus" clamav

RUN wget http://www.clamav.net/downloads/production/clamav-1.0.0.linux.x86_64.deb
RUN dpkg -i clamav-1.0.0.linux.x86_64.deb

RUN mv /usr/local/etc/clamd.conf.sample  /usr/local/etc/clamd.conf
RUN mv /usr/local/etc/freshclam.conf.sample  /usr/local/etc/freshclam.conf

RUN sed -i 's/Example/#Example/' /usr/local/etc/clamd.conf
RUN sed -i 's/Example/#Example/' /usr/local/etc/freshclam.conf

RUN echo "LocalSocket /tmp/clamd.socket" >> /usr/local/etc/clamd.conf && echo "LocalSocketMode 660" >> /usr/local/etc/clamd.conf

RUN /usr/local/bin/freshclam
