#include "simple_log.hpp"
#include <thread>
#include <chrono>

int main() 
{
    auto& server = SimpleLog::Server::global();
    auto console_sink = server.add_console_sink();
    console_sink->set_tag("test");
    console_sink->set_min_level(SimpleLog::LogLevel::DEBUG);
    auto file_sink = server.add_file_sink("test.log");
    file_sink->set_tag("test");
    file_sink->set_min_level(SimpleLog::LogLevel::FATAL);

    server.start();

    auto client = SimpleLog::Client(server, "test");
    client.sep(" ").debug("This", true, "an", "info", "message");
    client.warn("This is a warning message");
    client.error("This is an error message");

    SimpleLog::FormatRules rules;
    rules.d_fmt = "%.8f";
    client.sep(" ").fmt(rules).info(10, 1.5, "test");

    server.stop();

    return 0;
}