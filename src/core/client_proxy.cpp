#include <string>
#include <chrono>
#include "core/message.hpp"
#include "core/client_proxy.hpp"
#include "core/client.hpp"

using namespace SimpleLog;

ClientProxy::ClientProxy(const Client &c)
    : client_(c)
{
}

ClientProxy& ClientProxy::sep(std::string s)
{
    override_sep_.reset(new std::string(s));
    return *this;
}

ClientProxy& ClientProxy::fmt(const FormatRules& f)
{
    override_fmt_.reset(new FormatRules(f));
    return *this;
}

ClientProxy& ClientProxy::fmt(const std::string& f)
{
    override_fmt_.reset(new FormatRules());
    return *this;
}

const FormatRules& ClientProxy::current_fmt() const
{
    return override_fmt_ ? *override_fmt_ : client_.default_fmt();
}

const std::string& ClientProxy::current_sep() const
{
    return override_sep_ ? *override_sep_ : client_.default_sep();
}

ClientProxy& ClientProxy::append(Message& msg, const FormatRules& fmt)
{ 
    return *this;
}

bool ClientProxy::commit(Message&& msg, const LogLevel& level)
{
    msg.level = level;
    msg.thread_id = std::this_thread::get_id();
    msg.tags = client_.tags();
    msg.tag_hashes = client_.tag_hashes();
    msg.separator = (override_sep_) ? *override_sep_ : client_.default_sep();
    return client_.push(std::move(msg));
}
