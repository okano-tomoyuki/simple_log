#include <string>
#include <chrono>
#include "core/message.hpp"
#include "core/client_proxy.hpp"
#include "core/client.hpp"

using namespace SimpleLog;

ClientProxy::ClientProxy(const Client &c)
    : client_(c)
{
    msg_.tags = c.tags();
    msg_.tag_hashes = c.tag_hashes();
}

ClientProxy& ClientProxy::append()
{ 
    return *this;
}

bool ClientProxy::commit()
{
    msg_.thread_id = std::this_thread::get_id();
    return client_.push(std::move(msg_));
}
