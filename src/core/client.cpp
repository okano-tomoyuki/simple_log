#include <string>
#include <vector>
#include <cstdint>
#include "core/hash.hpp"
#include "core/server.hpp"
#include "core/message.hpp"
#include "core/client/client_proxy.hpp"
#include "core/client/decorator.hpp"
#include "core/client/decorator/separator_decorator.hpp"
#include "core/client/decorator/format_decorator.hpp"
#include "core/client.hpp"

using namespace SimpleLog;

Client::Client(Server& s, const std::string& tag)
    : server_(&s)
    , sep_(" ")
    , tags_({tag})
    , tag_hashes_({hash64(tag)})
    , fmt_()
{}

Client::Client(Server& s, const std::vector<std::string>& tags)
    : server_(&s)
    , sep_(" ")
    , tags_(tags)
    , tag_hashes_(hash64(tags))
    , fmt_()
{}

Client::Client(const Client& other)
    : server_(other.server_)
    , sep_(other.sep_)
    , tags_(other.tags_)
    , tag_hashes_(other.tag_hashes_)
    , fmt_(other.fmt_)
{}

void Client::add_tag(const std::string& tag) 
{ 
    tags_.push_back(tag);
    tag_hashes_.push_back(hash64(tag));
}

void Client::tags(const std::vector<std::string>& tags) 
{ 
    tags_ = tags;
    tag_hashes_ = hash64(tags);
}

void Client::default_sep(const std::string& sep) 
{ 
    sep_ = sep; 
}

void Client::default_fmt(const std::string& fmt) 
{ 
    fmt_ = fmt; 
}

const std::vector<std::string>& Client::tags() const 
{ 
    return tags_; 
}

const std::vector<uint64_t>& Client::tag_hashes() const 
{ 
    return tag_hashes_; 
}

const std::string& Client::default_sep() const 
{ 
    return sep_; 
}

const std::string& Client::default_fmt() const 
{ 
    return fmt_; 
}

SeparatorDecorator Client::sep(const std::string& s) const
{
    return SeparatorDecorator(*this, s);
}

FormatDecorator Client::fmt(const std::string& f) const
{
    return FormatDecorator(*this, f);
}

bool Client::push(Message&& msg) const 
{
    return server_->push(std::move(msg));
}