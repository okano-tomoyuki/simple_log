#pragma once
#include <atomic>
#include <thread>
#include <vector>
#include "core/queue.hpp"
#include "sink/sink.hpp"
#include "config/config.hpp"

namespace SimpleLog 
{

class Worker
{
public:
    Worker(Queue& queue,
           std::vector<std::unique_ptr<Sink>>& sinks,
           std::chrono::milliseconds flush_interval);

    void start();
    void stop();

private:
    void run();

    Queue& queue_;
    std::vector<std::unique_ptr<Sink>>& sinks_;
    std::chrono::milliseconds flush_interval_;
    std::atomic<bool> running_{false};
    std::thread worker_;
};

} // namespace SimpleLog
