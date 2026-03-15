#ifndef SIMPLELOG_FORMATTER_HPP
#define SIMPLELOG_FORMATTER_HPP

#include <string>
#include <vector>
#include <sstream>
#include "core/message.hpp"
#include "sink/semantic_token.hpp"

namespace SimpleLog 
{

class Formatter
{
public:
    virtual ~Formatter() = default;

    virtual FormatterOutput format(const Message& msg) const = 0;

};

} // namespace SimpleLog

#endif