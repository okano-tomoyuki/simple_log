#include <string>
#include <vector>
#include <cstdint>
#include "core/hash.hpp"
#include "core/server.hpp"
#include "core/message.hpp"
#include "core/client_proxy.hpp"
#include "core/client.hpp"

using namespace SimpleLog;

Client::Client(Server& s, const std::string& tag)
    : server_(&s)
    , sep_(" ")
    , tags_({tag})
    , tag_hashes_({hash64(tag)})
    , rules_(FormatRules())
{}

Client::Client(Server& s, const std::vector<std::string>& tags)
    : server_(&s)
    , sep_(" ")
    , tags_(tags)
    , tag_hashes_(hash64(tags))
    , rules_(FormatRules())
{}

Client::Client(const Client& other)
    : server_(other.server_)
    , sep_(other.sep_)
    , tags_(other.tags_)
    , tag_hashes_(other.tag_hashes_)
    , rules_(FormatRules())
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
    rules_ = FormatRules();
}

void Client::default_fmt(const FormatRules& rules)
{
    rules_ = rules;
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

const FormatRules& Client::default_fmt() const 
{ 
    return rules_; 
}

ClientProxy Client::sep(const std::string& s) const
{
    ClientProxy p(*this);
    p.sep(s);
    return p;
}

ClientProxy Client::fmt(const std::string& f) const
{
    ClientProxy p(*this);
    p.fmt(f);
    return p;
}

ClientProxy Client::fmt(const FormatRules& rules) const
{
    ClientProxy p(*this);
    p.fmt(rules);
    return p;
}

bool Client::push(Message&& msg) const 
{
    return server_->push(std::move(msg));
}