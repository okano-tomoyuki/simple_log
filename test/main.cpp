#include "simple_log.hpp"
#include <thread>
#include <chrono>

int main() {
    // 設定の作成
    SimpleLog::Config config;

    // サーバーの作成
    SimpleLog::Server server(config);

    // コンソールシンクの追加
    auto console_sink = std::make_unique<SimpleLog::ConsoleSink>("test");
    server.add_sink(std::move(console_sink));

    // サーバーの開始
    server.start();

    // クライアントの作成
    SimpleLog::Client client(server, "test");

    // ログメッセージの送信
    client.info("This is an info message");
    client.warn("This is a warning message");
    client.error("This is an error message");

    // 少し待ってログが処理されるように
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // サーバーの停止
    server.stop();

    return 0;
}