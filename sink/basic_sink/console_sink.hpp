#ifndef SIMPLE_LOG_CONSOLE_SINK_HPP
#define SIMPLE_LOG_CONSOLE_SINK_HPP

#include <iostream>
#include "sink/sink.hpp"

namespace SimpleLog
{

class ConsoleSink : public Sink
{
public:
    explicit ConsoleSink(const std::vector<std::string>& tags, std::unique_ptr<Formatter> fmt = std::make_unique<Formatter>())
        : Sink(tags, std::move(fmt)) 
    {}

    void write(const Message &msg) override
    {
        std::cout << formatter_->format(msg) << std::endl;
    }

    void flush() override
    {
        std::cout << std::flush;
    }
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CONSOLE_SINK_HPP