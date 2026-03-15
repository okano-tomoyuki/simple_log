#ifndef SIMPLELOG_SEMANTIC_TOKEN_HPP
#define SIMPLELOG_SEMANTIC_TOKEN_HPP

#include <string>
#include <vector>

namespace SimpleLog 
{

enum class SemanticType 
{
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_FATAL,
    TIMESTAMP,
    THREAD_ID,
    TAG,
    PAYLOAD_STRING,
    PAYLOAD_NUMBER,
    PAYLOAD_BOOL,
    SEPARATOR,

    JSON_BEGIN_OBJECT,
    JSON_END_OBJECT,
    JSON_BEGIN_ARRAY,
    JSON_END_ARRAY,
    JSON_KEY,
    JSON_VALUE,

    UNKNOWN
};

struct SemanticToken 
{
    SemanticType type;
    std::string text;
    int depth = 0; // JSON の階層構造用（Pretty Print に使える）
};

struct FormatterOutput 
{
    std::vector<SemanticToken> tokens;
};

} // namespace SimpleLog

#endif
