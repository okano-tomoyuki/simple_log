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
    DEBUG,
    INFO,
    WARN,
    ERROR,
};

enum class TokenType
{
    STRING,
    BOOLEAN,
    INTEGER,
    FLOATING,
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
