#include <string>
#include "core/client/client_proxy.hpp"
#include "core/client/decorator.hpp"
#include "core/client/decorator/format_decorator.hpp"

using namespace SimpleLog;

FormatDecorator::FormatDecorator(const Client& c, const FormatRules& rules)
    : Decorator(c)
    , rules_(rules) 
{}

ClientProxy FormatDecorator::build_proxy(LogLevel lvl) const
{
    ClientProxy p(client_, lvl);
    p.set_format(rules_);
    return p;
}
