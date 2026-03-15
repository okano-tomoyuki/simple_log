#ifndef SIMPLE_LOG_CORE_MESSAGE_HPP
#define SIMPLE_LOG_CORE_MESSAGE_HPP

#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdint>

namespace SimpleLog
{

enum class LogLevel
{
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
    FATAL = 4
};

enum class TokenType
{
    STRING,
    BOOLEAN,
    INTEGER,
    FLOATING,
};

struct FormatRules 
{
    std::string b_fmt = "%s";
    std::string c_fmt = "%d";
    std::string i_fmt = "%lld";
    std::string u_fmt = "%llu";
    std::string d_fmt = "%.6f";
    std::string p_fmt = "%p";
};

struct Token
{
    TokenType type;
    std::string key;
    std::string value; 
};

struct Message
{
    LogLevel level{};
    std::vector<std::string> tags;
    std::vector<uint64_t> tag_hashes;
    std::chrono::system_clock::time_point timestamp;
    std::thread::id thread_id;
    std::string separator;
    std::vector<Token> tokens;
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_CORE_MESSAGE_HPP
