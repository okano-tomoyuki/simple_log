#include "core/server.hpp"
#include "sink/basic_sink/console_sink.hpp"
#include "sink/basic_sink/file_sink.hpp"

namespace SimpleLog
{

Server::Server(const Config &cfg)
    : config_(cfg)
    , queue_(cfg.queue_size, cfg.overflow_policy)
    , worker_(queue_, sinks_, cfg.flush_interval)
{
    start();
}

Server::~Server()
{
    stop();
}

Sink* Server::add_sink(std::unique_ptr<Sink> sink)
{
    auto raw = sink.get();
    sinks_.push_back(std::move(sink));
    return raw;
}

ConsoleSink* Server::add_console_sink() 
{
    return static_cast<ConsoleSink*>(add_sink(std::unique_ptr<ConsoleSink>(new ConsoleSink())));
}

FileSink* Server::add_file_sink(const std::string& path) 
{
    return static_cast<FileSink*>(add_sink(std::unique_ptr<FileSink>(new FileSink(path))));
}

void Server::start()
{
    if (started_)
        return;
    started_ = true;
    worker_.start();
}

void Server::stop()
{
    if (!started_)
        return;
    worker_.stop();
    started_ = false;
}

bool Server::push(Message &&msg)
{
    return queue_.push(std::move(msg));
}

Server &Server::global()
{
    static Config cfg;
    static Server instance(cfg);
    return instance;
}

} // namespace SimpleLog
