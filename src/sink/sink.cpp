#include <memory>
#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include "core/hash.hpp"
#include "core/message.hpp"
#include "sink/formatter.hpp"
#include "sink/basic_formatter/line_formatter.hpp"
#include "sink/basic_formatter/json_formatter.hpp"
#include "sink/sink.hpp"

using namespace SimpleLog;

Sink::Sink()
    : min_level_(LogLevel::INFO)
    , formatter_(std::unique_ptr<Formatter>(new LineFormatter()))
{}

Sink* Sink::set_tags(const std::vector<std::string>& tags)
{
    tag_hashes_ = hash64(tags);
    return this;
}

Sink* Sink::set_tag(const std::string& tag)
{
    tag_hashes_ = {hash64(tag)};
    return this;
}

Sink* Sink::set_min_level(const LogLevel& level)
{
    min_level_ = level;
    return this;
}

Formatter* Sink::set_formatter(std::unique_ptr<Formatter> fmt) 
{
    formatter_ = std::move(fmt);
    return formatter_.get();
}

JsonFormatter* Sink::set_json_formatter() 
{
    formatter_ = std::unique_ptr<JsonFormatter>(new JsonFormatter());
    return static_cast<JsonFormatter*>(formatter_.get());
}

bool Sink::should_log(const Message& msg) const
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