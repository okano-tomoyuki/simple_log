#include <string>
#include "core/client/client_proxy.hpp"
#include "core/client/decorator.hpp"
#include "core/client/decorator/separator_decorator.hpp"

using namespace SimpleLog;

SeparatorDecorator::SeparatorDecorator(const Client &c, const std::string &sep)
    : Decorator(c)
    , sep_(sep) 
{}

ClientProxy SeparatorDecorator::build_proxy(LogLevel lvl) const
{
    ClientProxy p(client_, lvl);
    p.set_separator(sep_);
    return p;
}