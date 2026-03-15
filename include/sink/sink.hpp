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

class Sink
{
public:
    explicit Sink()
        : min_level_(LogLevel::INFO)
        , formatter_(std::unique_ptr<Formatter>(new Formatter()))
    {}

    void set_tags(const std::vector<std::string>& tags)
    {
        tag_hashes_ = hash64(tags);
    }

    void set_tag(const std::string& tag)
    {
        tag_hashes_ = {hash64(tag)};
    }

    void set_min_level(const LogLevel& level)
    {
        min_level_ = level;
    }

    void set_formatter(std::unique_ptr<Formatter> fmt) 
    {
        formatter_ = std::move(fmt);
    }

    virtual ~Sink() = default;
    
    inline bool should_log(const Message& msg) const
    {
        if (msg.level < min_level_)
        {
            return false;
        }

        for (const auto& t : msg.tag_hashes)
        {
            if (std::find(tag_hashes_.begin(), tag_hashes_.end(), t) != tag_hashes_.end())
            {
                return true;
            }
        }

        return false;
    }
    
    virtual void write(const Message &msg) = 0;
    virtual void flush() {}

protected:
    LogLevel min_level_;
    std::unique_ptr<Formatter> formatter_;
    std::vector<uint64_t> tag_hashes_;
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_SINK_HPP