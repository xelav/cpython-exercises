FROM gcc:latest

COPY --from=ghcr.io/astral-sh/uv:latest /uv /usr/local/bin/uv

RUN apt-get update && apt-get install -y \
    gdb \
    make \
    cmake \
    valgrind \
    python3.13-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace