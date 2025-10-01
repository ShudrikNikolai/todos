FROM drogonframework/drogon:latest

RUN apt-get update && apt-get install -y \
    git \
    libjsoncpp-dev \
    libssl-dev \
    libyaml-cpp-dev \
    zlib1g-dev \
    libpq-dev \
    postgresql-all \
    curl \
    vim \
    && rm -rf /var/lib/apt/lists/*


#RUN git clone https://github.com/Thalhammer/jwt-cpp.git external/jwt-cpp && \
#    git clone https://github.com/trusch/libbcrypt.git external/libbcrypt
# RUN ls -la

COPY . /app

# RUN if [ ! -f "/app/config.yaml" ]; then \
#         echo "Error: config.yaml not found!" && exit 1; \
#     fi &&\
#     cat /app/config.yaml \

RUN rm -rf build && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 4000

# CMD ["sh", "-c", "if [ -f \"/app/config.yaml\" ]; then \
#         echo \"Config file found, starting application...\"; \
#         ./build/todo_backend; \
#     else \
#         echo \"Error: Config file not found at /app/config.yaml\"; \
#         exit 1; \
#     fi"]

CMD ["./build/todo_backend"]