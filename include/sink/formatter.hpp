#ifndef SIMPLE_SINK_FORMATTER_HPP
#define SIMPLE_SINK_FORMATTER_HPP

#include <string>
#include <sstream>
#include "core/message.hpp"

namespace SimpleLog
{

class Formatter
{
public:
    virtual ~Formatter() = default;
    virtual std::string format(const Message &msg) const
    {
        std::ostringstream oss;
        oss << "["
            << std::this_thread::get_id()
            << "] ";

        switch (msg.level)
        {
        case LogLevel::DEBUG:
            oss << "DEBUG";
            break;
        case LogLevel::INFO:
            oss << "INFO";
            break;
        case LogLevel::WARN:
            oss << "WARN";
            break;
        case LogLevel::ERROR:
            oss << "ERROR";
            break;
        }

        return oss.str();
    }
};

} // namespace SimpleLog

#endif // SIMPLE_SINK_FORMATTER_HPP