#include "simple_log.hpp"
#include <thread>
#include <chrono>

int main() 
{
    SimpleLog::Server server;
    server.add_sink(std::make_unique<SimpleLog::ConsoleSink>("test"));
    server.add_sink(std::make_unique<SimpleLog::FileSink>("test.log", "test"));
    server.start();

    SimpleLog::Client client(server, "test");

    client.sep(" ").info("This", "is", "an", "info", "message");
    client.warn("This is a warning message");
    client.error("This is an error message");
    client.sep(",").info(10, 1.5, "test");

    // サーバーの停止
    server.stop();

    return 0;
}