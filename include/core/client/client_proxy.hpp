#ifndef SIMPLE_LOG_CLIENT_PROXY_HPP
#define SIMPLE_LOG_CLIENT_PROXY_HPP

#include <string>
#include <chrono>
#include <sstream>
#include "core/message.hpp"

namespace SimpleLog
{

class Client;

class ClientProxy
{
public:
    ClientProxy(const Client &c, LogLevel lvl);

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

    template <typename T>
    ClientProxy& append_one(const T &value)
    {
        std::ostringstream oss;
        oss << value;
        Token token;
        token.type  = TokenType::STRING;
        token.key   = "";
        token.value = oss.str();
        msg_.tokens.push_back(token);
        return *this;
    }

};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CLIENT_PROXY_HPP