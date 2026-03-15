#ifndef SIMPLE_LOG_CLIENT_HPP
#define SIMPLE_LOG_CLIENT_HPP

#include <string>
#include <vector>
#include <cstdint>
#include "core/hash.hpp"
#include "core/server.hpp"
#include "core/message.hpp"
#include "core/client_proxy.hpp"

namespace SimpleLog
{

class Client 
{

public:
    Client(Server& s, const std::string& tag);

    Client(Server& s, const std::vector<std::string>& tags);

    Client(const Client& other);

    void add_tag(const std::string& tag); 

    void tags(const std::vector<std::string>& tags);

    void default_sep(const std::string& sep);
    
    void default_fmt(const std::string& fmt);

    void default_fmt(const FormatRules& rules);

    const std::vector<std::string>& tags() const;

    const std::vector<uint64_t>& tag_hashes() const;

    const std::string& default_sep() const;
    
    const FormatRules& default_fmt() const;

    ClientProxy sep(const std::string& s) const;

    ClientProxy fmt(const std::string& f) const;

    ClientProxy fmt(const FormatRules& rules) const;

    bool push(Message&& msg) const;

    template<typename... Args>
    void info(const Args&... args) const 
    {
        ClientProxy(*this).info(args...);
    }

    template<typename... Args>
    void debug(const Args&... args) const 
    {
        ClientProxy(*this).debug(args...);
    }

    template<typename... Args>
    void warn(const Args&... args) const 
    {
        ClientProxy(*this).warn(args...);
    }

    template<typename... Args>
    void error(const Args&... args) const 
    {
        ClientProxy(*this).error(args...);
    }

    template<typename... Args>
    void fatal(const Args&... args) const 
    {
        ClientProxy(*this).fatal(args...);
    }

private:
    Server* server_; 
    std::vector<std::string> tags_;
    std::vector<uint64_t> tag_hashes_;
    std::string sep_;
    FormatRules rules_;
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CLIENT_HPP