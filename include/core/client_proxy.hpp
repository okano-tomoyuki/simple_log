#ifndef SIMPLE_LOG_CLIENT_PROXY_HPP
#define SIMPLE_LOG_CLIENT_PROXY_HPP

#include <string>
#include <chrono>
#include <sstream>
#include <type_traits>
#include "core/message.hpp"

namespace SimpleLog
{

class Client;

class ClientProxy
{
public:
    ClientProxy(const Client& c);

    ClientProxy& sep(std::string s)
    {
        msg_.separator = s;
        return *this;
    }

    ClientProxy& fmt(const FormatRules& f)
    {
        rules_ = f;
        return *this;
    }

    ClientProxy& fmt(const std::string& f)
    {
        rules_ = FormatRules();
        return *this;
    }

    template<typename... Args>
    void info(const Args&... args)
    {
        msg_.level = LogLevel::INFO;
        append(args...);
        commit();
    }

    template<typename... Args>
    void debug(const Args&... args)
    {
        msg_.level = LogLevel::DEBUG;
        append(args...);
        commit();
    }

    template<typename... Args>
    void warn(const Args&... args)
    {
        msg_.level = LogLevel::WARN;
        append(args...);
        commit();
    }

    template<typename... Args>
    void error(const Args&... args)
    {
        msg_.level = LogLevel::ERROR;
        append(args...);
        commit();
    }

    ClientProxy& append();

private:
    const Client &client_;
    Message msg_;
    FormatRules rules_;

    bool commit();

    template <typename T, typename... Remain>
    ClientProxy& append(const T &value, const Remain &...remain)
    {
        append_one(value);
        return append(remain...);
    }

    template <typename T>
    typename std::enable_if<!std::is_integral<T>::value && !std::is_floating_point<T>::value && !std::is_pointer<T>::value, ClientProxy&>::type
    append_one(const T& value)
    {
        std::ostringstream oss;
        oss << value;
        Token t;
        t.type  = TokenType::STRING;
        t.value = oss.str();
        msg_.tokens.push_back(std::move(t));
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, ClientProxy&>::type
    append_one(const T& value)
    {
        char buf[64];
        std::snprintf(buf, sizeof(buf), rules_.i_fmt.c_str(), static_cast<long long>(value));
        Token t;
        t.type  = TokenType::INTEGER;
        t.value = buf;
        msg_.tokens.push_back(std::move(t));
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, ClientProxy&>::type
    append_one(const T& value)
    {
        char buf[64];
        std::snprintf(buf, sizeof(buf), rules_.d_fmt.c_str(), static_cast<double>(value));
        Token t;
        t.type  = TokenType::FLOATING;
        t.value = buf;
        msg_.tokens.push_back(std::move(t));
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value, ClientProxy&>::type
    append_one(const T& value)
    {
        char buf[64];
        std::snprintf(buf, sizeof(buf), rules_.p_fmt.c_str(), static_cast<const void*>(value));
        Token t;
        t.type  = TokenType::STRING;
        t.value = buf;
        msg_.tokens.push_back(std::move(t));
        return *this;
    }

    ClientProxy& append_one(bool value)
    {
        const bool is_str = (rules_.b_fmt == "%s");
        const std::string str = is_str ? (value ? "true" : "false") : (value ? "1" : "0");
        Token t;
        t.type  = is_str ? TokenType::BOOLEAN : TokenType::INTEGER;
        t.value = str;
        msg_.tokens.push_back(std::move(t));
        return *this;
    }

    ClientProxy& append_one(const std::string& value)
    {
        Token t;
        t.type  = TokenType::STRING;
        t.value = value;
        msg_.tokens.push_back(std::move(t));
        return *this;
    }

    ClientProxy& append_one(const char* value)
    {
        Token t;
        t.type  = TokenType::STRING;
        t.value = value;
        msg_.tokens.push_back(std::move(t));
        return *this;
    }
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CLIENT_PROXY_HPP