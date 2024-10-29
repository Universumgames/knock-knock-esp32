FROM ubuntu:latest

RUN apt update
RUN apt install -y python3 python3-pip python3-venv curl bash cmake make g++ git

RUN curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
RUN python3 get-platformio.py

RUN mkdir -p /usr/local/bin
RUN ln -s ~/.platformio/penv/bin/platformio /usr/local/bin/platformio
RUN ln -s ~/.platformio/penv/bin/pio /usr/local/bin/pio
RUN ln -s ~/.platformio/penv/bin/piodebuggdb /usr/local/bin/piodebuggdb

RUN pio platform install espressif32

CMD [ "/bin/bash" ]