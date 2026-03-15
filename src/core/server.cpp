#include "core/server.hpp"

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

void Server::add_sink(std::unique_ptr<Sink> sink)
{
    sinks_.push_back(std::move(sink));
}

Server &Server::global()
{
    static Config cfg;
    static Server instance(cfg);
    return instance;
}

} // namespace SimpleLog
