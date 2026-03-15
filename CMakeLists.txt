cmake_minimum_required(VERSION 3.14)
project(SimpleLog CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SimpleLog
    core/queue.cpp
    core/server.cpp
    core/worker.cpp
    core/client/client_proxy.cpp
    core/client.cpp
)

target_include_directories(SimpleLog 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
