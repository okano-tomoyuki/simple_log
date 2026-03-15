#ifndef SIMPLE_LOG_JSON_FORMATTER_HPP
#define SIMPLE_LOG_JSON_FORMATTER_HPP

#include <string>
#include <vector>
#include <sstream>
#include "core/message.hpp"
#include "sink/semantic_token.hpp"
#include "sink/formatter.hpp"

namespace SimpleLog
{

class JsonFormatter : public Formatter
{
public:
    JsonFormatter *set_indent(int n)
    {
        indent_ = n;
        return this;
    }

    JsonFormatter *set_pretty(bool b)
    {
        pretty_ = b;
        return this;
    }

    FormatterOutput format(const Message &msg) const override
    {
        FormatterOutput out;

        // {
        out.tokens.push_back({SemanticType::JSON_BEGIN_OBJECT, "{", 0});

        // "level": "DEBUG",
        out.tokens.push_back({SemanticType::JSON_KEY, "\"level\": ", 1});

        switch (msg.level)
        {
        case LogLevel::DEBUG:
            out.tokens.push_back({SemanticType::LEVEL_DEBUG, "\"DEBUG\"", 1});
            break;
        case LogLevel::INFO:
            out.tokens.push_back({SemanticType::LEVEL_INFO, "\"INFO\"", 1});
            break;
        case LogLevel::WARN:
            out.tokens.push_back({SemanticType::LEVEL_WARN, "\"WARN\"", 1});
            break;
        case LogLevel::ERROR:
            out.tokens.push_back({SemanticType::LEVEL_ERROR, "\"ERROR\"", 1});
            break;
        case LogLevel::FATAL:
            out.tokens.push_back({SemanticType::LEVEL_FATAL, "\"FATAL\"", 1});
            break;
        }
        out.tokens.push_back({SemanticType::SEPARATOR, ", ", 1});

        // "timestamp": "...",
        // add_key_value(out, "timestamp", msg.timestamp, 1);

        // "thread_id": 123,
        std::ostringstream oss;
        oss << msg.thread_id;
        out.tokens.push_back({SemanticType::JSON_KEY, "\"thread_id\": ", 1});
        out.tokens.push_back({SemanticType::PAYLOAD_NUMBER, oss.str(), 1});
        out.tokens.push_back({SemanticType::SEPARATOR, ", ", 1});

        // "payload": [...]
        out.tokens.push_back({SemanticType::JSON_KEY, "\"payload\": ", 1});

        if (join_)
        {
            std::string joined;
            for (size_t i = 0; i < msg.tokens.size(); ++i)
            {
                joined += msg.tokens[i].value;
                if (i + 1 < msg.tokens.size())
                    joined += msg.separator;
            }
            out.tokens.push_back({SemanticType::SEPARATOR, "\"" + joined + "\"", 2});
        }
        else
        {
            out.tokens.push_back({SemanticType::JSON_BEGIN_ARRAY, "[", 1});
            for (size_t i = 0; i < msg.tokens.size(); ++i)
            {
                const auto &t = msg.tokens[i];

                if (t.type == TokenType::BOOLEAN)
                    out.tokens.push_back({SemanticType::PAYLOAD_BOOL, t.value, 2});
                else if (t.type == TokenType::INTEGER || t.type == TokenType::FLOATING)
                    out.tokens.push_back({SemanticType::PAYLOAD_NUMBER, t.value, 2});
                else
                    out.tokens.push_back({SemanticType::PAYLOAD_STRING, "\"" + t.value + "\"", 2});

                if (i + 1 < msg.tokens.size())
                    out.tokens.push_back({SemanticType::SEPARATOR, ", ", 2});
            }
            out.tokens.push_back({SemanticType::JSON_END_ARRAY, "]", 1});
        }

        // }
        out.tokens.push_back({SemanticType::JSON_END_OBJECT, "}", 0});

        return out;
    }

private:
    int indent_ = 2;
    bool pretty_ = false;
    bool join_ = true;
};

} // namespace SimpleLog

#endif
