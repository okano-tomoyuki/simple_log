#pragma once
#include <atomic>
#include <vector>
#include "core/message.hpp"
#include "config/config.hpp"

namespace SimpleLog 
{

class Queue 
{
public:
    explicit Queue(std::size_t capacity, OverflowPolicy policy);

    bool push(Message&& msg);
    bool pop(Message& out);

private:
    struct Slot 
    {
        std::atomic<bool> ready{false};
        Message msg;
    };

    std::vector<Slot> buffer_;
    std::atomic<std::size_t> head_{0};
    std::atomic<std::size_t> tail_{0};
    const std::size_t capacity_;
    const OverflowPolicy policy_;
};

} // namespace SimpleLog
