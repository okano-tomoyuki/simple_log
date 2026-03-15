#ifndef SIMPLE_LOG_CONSOLE_SINK_HPP
#define SIMPLE_LOG_CONSOLE_SINK_HPP

#include <iostream>
#include "sink/sink.hpp"

namespace SimpleLog
{

class ConsoleSink : public Sink
{
public:
    explicit ConsoleSink()
        : Sink() 
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