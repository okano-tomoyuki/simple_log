#ifndef SIMPLE_LOG_CONSOLE_SINK_HPP
#define SIMPLE_LOG_CONSOLE_SINK_HPP

#include <iostream>
#include "sink/sink.hpp"
#include "sink/semantic_token.hpp"

namespace SimpleLog
{

class ConsoleSink : public Sink
{
public:
    explicit ConsoleSink()
        : Sink() 
    {}

    void write(const Message& msg) override 
    {
        FormatterOutput out = formatter_->format(msg);

        for (auto& t : out.tokens) 
        {
            apply_color(t);
            std::cout << t.text;
        }

        reset_color();
        std::cout << std::endl;
    }

    void flush() override
    {
        std::cout << std::flush;
    }

private:
    void apply_color(const SemanticToken& t) 
    {
        switch (t.type) 
        {
        case SemanticType::LEVEL_DEBUG:
            std::cout << "\033[34m"; // Blue
            break;
        case SemanticType::LEVEL_INFO:
            std::cout << "\033[32m"; // Green
            break;
        case SemanticType::LEVEL_WARN:
            std::cout << "\033[33m"; // Yellow
            break;
        case SemanticType::LEVEL_ERROR:
            std::cout << "\033[31m"; // Red
            break;
        case SemanticType::LEVEL_FATAL:
            std::cout << "\033[35m"; // Magenta
            break;
        case SemanticType::TIMESTAMP:
            std::cout << "\033[36m"; // Cyan
            break;
        case SemanticType::THREAD_ID:
            std::cout << "\033[33m"; // Yellow
            break;
        case SemanticType::PAYLOAD_STRING:
            std::cout << "\033[37m"; // White
            break;
        case SemanticType::PAYLOAD_NUMBER:
            std::cout << "\033[32m"; // Green
            break;
        case SemanticType::PAYLOAD_BOOL:
            std::cout << "\033[34m"; // Blue
            break;
        default:
            std::cout << "\033[0m"; // Reset
            break;
        }
    }

    void reset_color() 
    {
        std::cout << "\033[0m";
    }
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CONSOLE_SINK_HPP