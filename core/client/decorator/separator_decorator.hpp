#ifndef SIMPLE_LOG_SEPARATOR_DECORATOR_HPP
#define SIMPLE_LOG_SEPARATOR_DECORATOR_HPP

#include <string>
#include "core/client/client_proxy.hpp"
#include "core/client/decorator.hpp"

namespace SimpleLog
{

class SeparatorDecorator : public Decorator
{
public:
    SeparatorDecorator(const Client &c, const std::string &sep)
        : Decorator(c)
        , sep_(sep) 
    {}

protected:
    ClientProxy build_proxy(LogLevel lvl) const override
    {
        ClientProxy p(client_, lvl);
        p.set_separator(sep_);
        return p;
    }

private:
    std::string sep_;
};

} // SimpleLog

#endif // SIMPLE_LOG_SEPARATOR_DECORATOR_HPP