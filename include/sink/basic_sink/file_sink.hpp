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
            const auto& tokens = formatter_->format(msg).tokens;
            for (const auto& t : tokens)
            {
                file_ << t.text;
            }
            file_ << '\n';
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