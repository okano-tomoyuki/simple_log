#include <string>
#include "core/client/client_proxy.hpp"
#include "core/client/decorator.hpp"
#include "core/client/decorator/format_decorator.hpp"

using namespace SimpleLog;

FormatDecorator::FormatDecorator(const Client& c, const std::string& fmt)
    : Decorator(c)
    , fmt_(fmt) 
{}

ClientProxy FormatDecorator::build_proxy(LogLevel lvl) const
{
    ClientProxy p(client_, lvl);
    p.set_format(fmt_);
    return p;
}
