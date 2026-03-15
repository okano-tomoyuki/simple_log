#include "core/queue.hpp"

namespace SimpleLog
{

Queue::Queue(std::size_t capacity, OverflowPolicy policy)
    : buffer_(capacity)
    , capacity_(capacity)
    , policy_(policy)
{
}

bool Queue::push(Message &&msg)
{
    auto pos = tail_.fetch_add(1, std::memory_order_acq_rel);
    auto idx = pos % capacity_;
    auto &slot = buffer_[idx];

    bool expected = false;
    if (!slot.ready.compare_exchange_strong(expected, true, std::memory_order_acq_rel, std::memory_order_acquire))
    {
        // すでに ready == true
        if (policy_ == OverflowPolicy::DROP_NEW)
        {
            // 新しいメッセージを捨てる
            return false;
        }
        // Overwrite の場合は上書き
    }

    slot.msg = std::move(msg);
    // ready はすでに true
    return true;
}

bool Queue::pop(Message &out)
{
    auto pos = head_.load(std::memory_order_acquire);
    auto idx = pos % capacity_;
    auto &slot = buffer_[idx];

    if (!slot.ready.load(std::memory_order_acquire))
    {
        return false;
    }

    out = std::move(slot.msg);
    slot.ready.store(false, std::memory_order_release);
    head_.store(pos + 1, std::memory_order_release);
    return true;
}

} // namespace SimpleLog
