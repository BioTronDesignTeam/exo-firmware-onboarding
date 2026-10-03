FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    openocd \
    git \
    udev \
    && rm -rf /var/lib/apt/lists/*
