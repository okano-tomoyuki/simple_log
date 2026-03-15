#ifndef SIMPLE_LOG_DECORATOR_HPP
#define SIMPLE_LOG_DECORATOR_HPP

#include "core/message.hpp"
#include "core/client/client_proxy.hpp"

namespace SimpleLog
{

class Client;

class Decorator
{
public:
    Decorator(const Client &c) 
        : client_(c) 
    {}

    template <typename... Args>
    void info(const Args &...args) const
    {
        ClientProxy p = build_proxy(LogLevel::INFO);
        p.append(args...);
        p.commit();
    }

    template <typename... Args>
    void debug(const Args &...args) const
    {
        ClientProxy p = build_proxy(LogLevel::DEBUG);
        p.append(args...);
        p.commit();
    }

    template <typename... Args>
    void warn(const Args &...args) const
    {
        ClientProxy p = build_proxy(LogLevel::WARN);
        p.append(args...);
        p.commit();
    }

    template <typename... Args>
    void error(const Args &...args) const
    {
        ClientProxy p = build_proxy(LogLevel::ERROR);
        p.append(args...);
        p.commit();
    }

protected:
    virtual ClientProxy build_proxy(LogLevel lvl) const = 0;

    const Client &client_;
};

} // SimpleLog

#endif // SIMPLE_LOG_DECORATOR_HPP