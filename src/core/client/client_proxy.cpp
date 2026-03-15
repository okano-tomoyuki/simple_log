#include <string>
#include <chrono>
#include "core/message.hpp"
#include "core/client.hpp"

using namespace SimpleLog;

ClientProxy::ClientProxy(const Client &c, LogLevel lvl)
    : client_(c)
{
    msg_.level = lvl;
    msg_.tags = c.tags();
    msg_.tag_hashes = c.tag_hashes();
}

ClientProxy& ClientProxy::append() 
{ 
    return *this; 
}

void ClientProxy::set_separator(const std::string &s) 
{ 
    msg_.separator = s; 
}

void ClientProxy::set_format(const std::string &f) 
{ 
    format_ = f; 
}

bool ClientProxy::commit()
{
    return client_.push(std::move(msg_));
}
