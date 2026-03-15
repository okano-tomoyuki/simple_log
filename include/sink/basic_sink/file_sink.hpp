#ifndef SIMPLE_LOG_FILE_SINK_HPP
#define SIMPLE_LOG_FILE_SINK_HPP

#include <fstream>
#include "sink/sink.hpp"

namespace SimpleLog
{

class FileSink : public Sink
{
public:
    FileSink(const std::string &path)
        : Sink()
        , file_(path, std::ios::out | std::ios::app)
    {}

    void write(const Message &msg) override
    {
        if (file_.is_open())
        {
            file_ << formatter_->format(msg) << '\n';
        }
    }

    void flush() override
    {
        if (file_.is_open())
        {
            file_.flush();
        }
    }

private:
    std::ofstream file_;
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_FILE_SINK_HPP