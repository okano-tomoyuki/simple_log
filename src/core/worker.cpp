#include "core/worker.hpp"

namespace SimpleLog
{

Worker::Worker(
    Queue &queue,
    std::vector<std::unique_ptr<Sink>> &sinks,
    std::chrono::milliseconds flush_interval
)   : queue_(queue)
    , sinks_(sinks)
    , flush_interval_(flush_interval) 
{}

void Worker::start()
{
    if (running_.exchange(true))
        return;
    worker_ = std::thread(&Worker::run, this);
}

void Worker::stop()
{
    if (!running_.exchange(false))
        return;

    if (worker_.joinable())
    {
        worker_.join();
    }
}

void Worker::run()
{
    using namespace std::chrono;
    auto next_flush = steady_clock::now() + flush_interval_;

    while (running_.load())
    {
        Message msg;
        if (queue_.pop(msg))
        {
            for (auto &s : sinks_)
            {
                if (s->should_log(msg))
                {
                    s->write(msg);
                }
            }
        }
        else
        {
            std::this_thread::sleep_for(1ms);
        }

        const auto now = steady_clock::now();
        if (now >= next_flush)
        {
            for (auto &s : sinks_)
            {
                s->flush();
            }
            next_flush = now + flush_interval_;
        }
    }

    // drain
    Message msg;
    while (queue_.pop(msg))
    {
        for (auto &s : sinks_)
        {
            if (s->should_log(msg))
            {
                s->write(msg);
            }
        }
    }

    for (auto &s : sinks_)
    {
        s->flush();
    }
}

} // namespace SimpleLog
