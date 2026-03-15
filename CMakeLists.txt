cmake_minimum_required(VERSION 3.14)
project(SimpleLog CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SimpleLog
    src/core/queue.cpp
    src/core/server.cpp
    src/core/worker.cpp
    src/core/client/client_proxy.cpp
    src/core/client/decorator/format_decorator.cpp
    src/core/client/decorator/separator_decorator.cpp
    src/core/client.cpp
)

target_include_directories(SimpleLog
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(test)
