cmake_minimum_required(VERSION 3.10)
project(DeriBot_CPP)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(src)
include_directories(src/api)
include_directories(src/core)
include_directories(src/utils)
include_directories(src/ws)

# Source files
file(GLOB_RECURSE SOURCES
    src/main.cpp
    src/api/*.cpp
    src/core/*.cpp
    src/utils/*.cpp
    src/ws/*.cpp
)

# Output executable
add_executable(deribot ${SOURCES})

# Dependencies
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)

target_link_libraries(deribot
    Boost::system
    Boost::thread
    OpenSSL::SSL
    OpenSSL::Crypto
    pthread
)
