#ifndef SIMPLE_LOG_CLIENT_PROXY_HPP
#define SIMPLE_LOG_CLIENT_PROXY_HPP

#include <string>
#include <chrono>
#include <sstream>
#include <type_traits>
#include <memory>
#include "core/message.hpp"

namespace SimpleLog
{

class Client;

class ClientProxy
{
public:
    ClientProxy(const Client& c);

    ClientProxy& sep(std::string s);

    ClientProxy& fmt(const FormatRules& f);

    ClientProxy& fmt(const std::string& f);

    template<typename... Args>
    void info(const Args&... args)
    {
        Message msg;
        append(msg, current_fmt(), args...);
        commit(std::move(msg), LogLevel::INFO);
    }

    template<typename... Args>
    void debug(const Args&... args)
    {
        Message msg;
        append(msg, current_fmt(), args...);
        commit(std::move(msg), LogLevel::DEBUG);
    }

    template<typename... Args>
    void warn(const Args&... args)
    {
        Message msg;
        append(msg, current_fmt(), args...);
        commit(std::move(msg), LogLevel::WARN);
    }

    template<typename... Args>
    void error(const Args&... args)
    {
        Message msg;
        append(msg, current_fmt(), args...);
        commit(std::move(msg), LogLevel::ERROR);
    }

private:
    const Client &client_;
    std::unique_ptr<FormatRules> override_fmt_;
    std::unique_ptr<std::string> override_sep_;

    bool commit(Message&& message, const LogLevel& level);

    const FormatRules& current_fmt() const;

    const std::string& current_sep() const;

    ClientProxy& append(Message& msg, const FormatRules& fmt);

    template <typename T, typename... Remain>
    ClientProxy& append(Message& msg, const FormatRules& fmt, const T &value, const Remain &...remain)
    {
        append_one(msg, fmt, value);
        return append(msg, fmt, remain...);
    }

    template <typename T>
    typename std::enable_if<!std::is_integral<T>::value && !std::is_floating_point<T>::value && !std::is_pointer<T>::value, ClientProxy&>::type
    append_one(Message& msg, const FormatRules& fmt, const T& value)
    {
        std::ostringstream oss;
        oss << value;
        msg.tokens.push_back(std::move(Token{TokenType::STRING, "", oss.str()}));
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value, ClientProxy&>::type
    append_one(Message& msg, const FormatRules& fmt, const T& value)
    {
        char buf[64];
        std::snprintf(buf, sizeof(buf), fmt.i_fmt.c_str(), static_cast<long long>(value));
        msg.tokens.push_back(std::move(Token{TokenType::INTEGER, "", buf}));
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value && std::is_unsigned<T>::value, ClientProxy&>::type
    append_one(Message& msg, const FormatRules& fmt, const T& value)
    {
        char buf[64];
        std::snprintf(buf, sizeof(buf), fmt.u_fmt.c_str(), static_cast<unsigned long long>(value));
        msg.tokens.push_back(std::move(Token{TokenType::INTEGER, "", buf}));
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, ClientProxy&>::type
    append_one(Message& msg, const FormatRules& fmt, const T& value)
    {
        char buf[64];
        std::snprintf(buf, sizeof(buf), fmt.d_fmt.c_str(), static_cast<double>(value));
        msg.tokens.push_back(std::move(Token{TokenType::FLOATING, "", buf}));
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value, ClientProxy&>::type
    append_one(Message& msg, const FormatRules& fmt, const T& value)
    {
        char buf[64];
        std::snprintf(buf, sizeof(buf), fmt.p_fmt.c_str(), static_cast<const void*>(value));
        msg.tokens.push_back(std::move(Token{TokenType::INTEGER, "", buf}));
        return *this;
    }

    ClientProxy& append_one(Message& msg, const FormatRules& fmt, bool value)
    {
        const bool is_str = (fmt.b_fmt == "%s");
        const std::string str = is_str ? (value ? "true" : "false") : (value ? "1" : "0");
        msg.tokens.push_back(std::move(Token{is_str ? TokenType::BOOLEAN : TokenType::INTEGER, "", str}));
        return *this;
    }

    ClientProxy& append_one(Message& msg, const FormatRules& fmt, const std::string& value)
    {
        msg.tokens.push_back(std::move(Token{TokenType::STRING, "", value}));
        return *this;
    }

    ClientProxy& append_one(Message& msg, const FormatRules& fmt, const char* value)
    {
        msg.tokens.push_back(std::move(Token{TokenType::STRING, "", value}));
        return *this;
    }
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CLIENT_PROXY_HPP