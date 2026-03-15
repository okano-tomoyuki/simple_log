add_executable(SimpleLogTest main.cpp)

target_link_libraries(SimpleLogTest PRIVATE SimpleLog)

target_include_directories(SimpleLogTest PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)