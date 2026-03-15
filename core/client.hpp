#ifndef SIMPLE_LOG_CLIENT_HPP
#define SIMPLE_LOG_CLIENT_HPP

#include <string>
#include <vector>
#include <cstdint>
#include "core/hash.hpp"
#include "core/server.hpp"
#include "core/message.hpp"
#include "core/client/decorator.hpp"
#include "core/client/decorator/separator_decorator.hpp"
#include "core/client/decorator/format_decorator.hpp"

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

    const std::vector<std::string>& tags() const;

    const std::string& default_sep() const;
    
    const std::string& default_fmt() const;

    SeparatorDecorator sep(const std::string& s) const;

    FormatDecorator fmt(const std::string& f) const;

    bool push(Message&& msg) const;

    template<typename... Args>
    void info(const Args&... args) const 
    {
        ClientProxy p(*this, LogLevel::INFO);
        p.append(args...);
        p.commit();
    }

    template<typename... Args>
    void debug(const Args&... args) const 
    {
        ClientProxy p(*this, LogLevel::DEBUG);
        p.append(args...);
        p.commit();
    }

    template<typename... Args>
    void warn(const Args&... args) const 
    {
        ClientProxy p(*this, LogLevel::WARN);
        p.append(args...);
        p.commit();
    }

    template<typename... Args>
    void error(const Args&... args) const 
    {
        ClientProxy p(*this, LogLevel::ERROR);
        p.append(args...);
        p.commit();
    }

private:
    Server* server_; 
    std::vector<std::string> tags_;
    std::vector<uint64_t> tag_hashes_;
    std::string sep_;
    std::string fmt_;
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CLIENT_HPP