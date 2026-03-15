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
    explicit Sink(const std::string& tag, std::unique_ptr<Formatter> fmt)
        : tag_hashes_({hash64(tag)})
        , formatter_(std::move(fmt))
    {}

    explicit Sink(const std::vector<std::string>& tags, std::unique_ptr<Formatter> fmt)
        : tag_hashes_(hash64(tags))
        , formatter_(std::move(fmt))
    {}

    virtual ~Sink() = default;
    
    inline bool should_log(const Message& msg) const
    { 
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
    std::unique_ptr<Formatter> formatter_;
    std::vector<uint64_t> tag_hashes_;
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_SINK_HPP