#ifndef SIMPLE_LOG_LINE_FORMATTER_HPP
#define SIMPLE_LOG_LINE_FORMATTER_HPP

#include <string>
#include <vector>
#include <sstream>
#include "core/message.hpp"
#include "sink/semantic_token.hpp"
#include "sink/formatter.hpp"

namespace SimpleLog 
{

class LineFormatter : public Formatter
{
public:
    FormatterOutput format(const Message& msg) const 
    {
        FormatterOutput out;

        std::ostringstream oss;
        oss << msg.thread_id;

        // [LEVEL]
        out.tokens.push_back(create_level_token(msg.level));

        // [thread_id]
        out.tokens.push_back({SemanticType::THREAD_ID, "[" + oss.str() + "]", 0});

        // payload tokens
        for (size_t i = 0; i < msg.tokens.size(); ++i) 
        {
            const auto& t = msg.tokens[i];

            SemanticType type = classify_token(t);

            out.tokens.push_back({type, t.value, 0});

            // separator（最後以外）
            if (i + 1 < msg.tokens.size()) 
            {
                out.tokens.push_back({SemanticType::SEPARATOR, msg.separator, 0});
            }
        }

        return out;
    }

private:
    SemanticToken create_level_token(LogLevel lvl) const 
    {
        switch (lvl) 
        {
        case LogLevel::DEBUG: return {SemanticType::LEVEL_DEBUG, "[DEBUG]", 0};
        case LogLevel::INFO:  return {SemanticType::LEVEL_INFO, "[INFO]", 0};
        case LogLevel::WARN:  return {SemanticType::LEVEL_WARN, "[WARN]", 0};
        case LogLevel::ERROR: return {SemanticType::LEVEL_ERROR, "[ERROR]", 0};
        case LogLevel::FATAL: return {SemanticType::LEVEL_FATAL, "[FATAL]", 0};
        }
        return {SemanticType::UNKNOWN, "[UNKNOWN]", 0};
    }

    SemanticType classify_token(const Token& t) const 
    {
        if (t.type == TokenType::INTEGER || t.type == TokenType::FLOATING) return SemanticType::PAYLOAD_NUMBER;
        if (t.type == TokenType::BOOLEAN)   return SemanticType::PAYLOAD_BOOL;
        return SemanticType::PAYLOAD_STRING;
    }
};

} // namespace SimpleLog

#endif