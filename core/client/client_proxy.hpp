#ifndef SIMPLE_LOG_CLIENT_PROXY_HPP
#define SIMPLE_LOG_CLIENT_PROXY_HPP

#include "core/message.hpp"
#include <string>
#include <chrono>

namespace SimpleLog
{

class Client;

class ClientProxy
{
public:
    ClientProxy(const Client &c, LogLevel lvl);

    template <typename T>
    ClientProxy& append_one(const T &value)
    {
        return *this;
    }

    template <typename T, typename... Remain>
    ClientProxy& append(const T &value, const Remain &...remain)
    {
        append_one(value);
        return append(remain...);
    }

    ClientProxy& append();

    void set_separator(const std::string &s);
    
    void set_format(const std::string &f);

    bool commit();

private:
    const Client &client_;
    Message msg_;
    std::string format_; 
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CLIENT_PROXY_HPP