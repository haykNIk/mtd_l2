# @Author: hayknik

FROM debian:bookworm-slim

RUN apt-get update \
 && apt-get install -y --no-install-recommends g++ cmake make \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY src/CMakeLists.txt ./src/CMakeLists.txt
COPY src/Form.h src/Form.cpp src/main.cpp ./src/

RUN cmake -S src -B build && cmake --build build

CMD ["./build/main"]
