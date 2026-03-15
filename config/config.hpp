#pragma once
#include <chrono>

namespace SimpleLog 
{

enum class OverflowPolicy 
{
    OVERWRITE,
    DROP_NEW,
};

struct Config 
{
    std::size_t queue_size = 8192;
    std::chrono::milliseconds flush_interval{50};
    OverflowPolicy overflow_policy = OverflowPolicy::OVERWRITE;
};

} // namespace SimpleLog
