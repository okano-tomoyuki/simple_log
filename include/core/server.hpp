#ifndef SIMPLE_LOG_SERVER_HPP
#define SIMPLE_LOG_SERVER_HPP

#include <memory>
#include <vector>
#include <mutex>
#include <functional>

#include "config/config.hpp"
#include "core/queue.hpp"
#include "core/worker.hpp"
#include "core/message.hpp"
#include "sink/sink.hpp"

namespace SimpleLog
{

using ErrorCallback = std::function<void(const std::string&)>;

class Server
{
public:
    explicit Server(const Config &cfg);
    ~Server();

    void start();

    void stop();

    bool push(Message &&msg);

    void add_sink(std::unique_ptr<Sink> sink);

    void on_error(ErrorCallback cb);

    void notify_error(const std::string& msg);

    static Server &global(); 

private:
    Config config_;
    Queue queue_;
    std::vector<std::unique_ptr<Sink>> sinks_;
    Worker worker_;
    std::mutex cb_mutex_;
    ErrorCallback error_cb_;

    bool started_{false};
};

} // namespace SimpleLog

#endif // SIMPLE_LOG_SERVER_HPP