#include "simple_log.hpp"
#include <thread>
#include <chrono>

int main() 
{
    auto& server = SimpleLog::Server::global();
    server.add_sink(std::make_unique<SimpleLog::ConsoleSink>("test"));
    server.add_sink(std::make_unique<SimpleLog::FileSink>("test.log", "test"));
    server.start();

    auto client = SimpleLog::Client(server, "test");

    client.sep(" ").info("This", true, "an", "info", "message");
    client.warn("This is a warning message");
    client.error("This is an error message");

    SimpleLog::FormatRules rules;
    rules.d_fmt = "%.3f";

    client.sep(" ").fmt(rules).info(10, 1.5, "test");

    // サーバーの停止
    server.stop();

    float a = 1.522333444f;
    std::cout << a << std::endl;

    return 0;
}