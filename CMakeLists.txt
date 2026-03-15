cmake_minimum_required(VERSION 3.14)
project(SimpleLog CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SimpleLog
    src/core/queue.cpp
    src/core/server.cpp
    src/core/worker.cpp
    src/core/client_proxy.cpp
    src/core/client.cpp
    src/sink/sink.cpp
)

target_include_directories(SimpleLog
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(test)
