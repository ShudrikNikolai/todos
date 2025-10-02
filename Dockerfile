FROM ubuntu:24.04

RUN apt-get update && apt-get install -y tzdata

ENV TZ=Europe/Moscow

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    cmake \
    git \
    pkg-config \
    curl \
    wget \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y \
    libjsoncpp-dev \
    libssl-dev \
    uuid-dev \
    zlib1g-dev \
    libsqlite3-dev \
    libpq-dev \
    libbrotli-dev \
    libzstd-dev \
    libyaml-cpp-dev \
    postgresql-client \
    netcat-traditional \
    && rm -rf /var/lib/apt/lists/*

RUN echo "=== Cloning Drogon ===" && \
    git clone https://github.com/drogonframework/drogon /tmp/drogon

RUN echo "=== Submodule init ===" && \
    cd /tmp/drogon && \
    git submodule update --init && \
    ls -la

RUN echo "=== Creating build directory ===" && \
    cd /tmp/drogon && \
    mkdir build && \
    ls -la

RUN echo "=== Configuring CMake ===" && \
    cd /tmp/drogon/build && \
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_CXX_STANDARD=20 \
          -DBUILD_DOC=OFF \
          -DBUILD_EXAMPLES=OFF \
          .. 2>&1 | tee /tmp/cmake_output.log || \
    (echo "CMake failed. Output:" && cat /tmp/cmake_output.log && exit 1)

RUN echo "=== Checking if Makefile exists ===" && \
    cd /tmp/drogon/build && \
    ls -la | head -10

RUN echo "=== Building Drogon ===" && \
    cd /tmp/drogon/build && \
    make && make install

RUN echo "=== Cleaning up ===" && \
    rm -rf /tmp/drogon

RUN echo "=== Drogon Installation Check ===" && \
    echo "CMake files:" && \
    find /usr -name "*Drogon*" -type f 2>/dev/null | grep -i cmake || cat /tmp/drogon/build/CMakeFiles/CMakeError.log && \
    echo "Library files:" && \
    find /usr -name "*drogon*" -type f 2>/dev/null | head -5 || echo "No Drogon library files found" && \
    echo "Header files:" && \
    find /usr -name "drogon.h" -type f 2>/dev/null || echo "Drogon headers not found"

WORKDIR /app

COPY . .

COPY docker-start.sh /app/docker-start.sh
RUN chmod +x /app/docker-start.sh

EXPOSE 4000

CMD ["/app/docker-start.sh"]