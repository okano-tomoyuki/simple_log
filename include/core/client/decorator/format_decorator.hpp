#ifndef SIMPLE_LOG_FORMAT_DECORATOR_HPP
#define SIMPLE_LOG_FORMAT_DECORATOR_HPP

#include <string>
#include "core/client/client_proxy.hpp"
#include "core/client/decorator.hpp"

namespace SimpleLog
{

class FormatDecorator : public Decorator 
{
public:
    FormatDecorator(const Client& c, const std::string& fmt);

protected:
    ClientProxy build_proxy(LogLevel lvl) const override;

private:
    std::string fmt_;
};

} // SimpleLog

#endif // SIMPLE_LOG_FORMAT_DECORATOR_HPP