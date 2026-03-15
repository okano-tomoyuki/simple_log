#ifndef SIMPLE_LOG_SINK_HPP
#define SIMPLE_LOG_SINK_HPP

#include <memory>
#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include "core/hash.hpp"
#include "core/message.hpp"
#include "sink/formatter.hpp"

namespace SimpleLog
{

class LineFormatter;
class JsonFormatter;

class Sink
{
public:
    explicit Sink();

    Sink* set_tags(const std::vector<std::string>& tags);

    Sink* set_tag(const std::string& tag);

    Sink* set_min_level(const LogLevel& level);

    Formatter* set_formatter(std::unique_ptr<Formatter> fmt);

    JsonFormatter* set_json_formatter();

    virtual ~Sink() = default;
    
    bool should_log(const Message& msg) const;
    
    virtual void write(const Message &msg) = 0;
    virtual void flush() {}

protected:
    LogLevel min_level_;
    std::unique_ptr<Formatter> formatter_;
    std::vector<uint64_t> tag_hashes_;
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_SINK_HPP