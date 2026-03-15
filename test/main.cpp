#include "simple_log.hpp"
#include <thread>
#include <chrono>

int main() 
{
    auto& server = SimpleLog::Server::global();
    auto console = server.add_console_sink();
    console->set_tag("test");
    console->set_min_level(SimpleLog::LogLevel::DEBUG);
    auto json = console->set_json_formatter();                     
    json->set_pretty(true);      

    auto file = server.add_file_sink("test.log");
    file->set_tag("test");
    file->set_min_level(SimpleLog::LogLevel::DEBUG);
    server.start();

    auto client = SimpleLog::Client(server, "test");
    client.sep(" ").debug("This", true, "an", "info", "message");
    client.warn("This is a warning message");
    client.error("This is an error message");
    client.fatal("This is an fatal message");

    SimpleLog::FormatRules rules;
    rules.d_fmt = "%.8f";
    client.sep(" ").fmt(rules).info(10, 1.5, "test");

    server.stop();

    return 0;
}