# 🏗️ Base image with C++ and dependencies
FROM ubuntu:22.04

# 🛠️ Install tools and libraries
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    libssl-dev \
    libboost-all-dev \
    libwebsocketpp-dev \
    nlohmann-json3-dev \
    libasio-dev \
    && rm -rf /var/lib/apt/lists/*

# 📁 Create and set working directory
WORKDIR /app

# 📦 Copy the source code into the container
COPY . .

# 🔨 Build the app using CMake
RUN mkdir -p build && cd build && \
    cmake .. && \
    make -j$(nproc)

# 🚪 Expose WebSocket server port
EXPOSE 9002

# ▶️ Default command
CMD ["./build/deribot"]
// Placeholder for Dockerfile
