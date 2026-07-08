#include <chrono>
#include <string>
#include <thread>

#include "zenoh.hxx"

int main() {
    // 1. 打开会话
    auto session = zenoh::Session::open(zenoh::Config::create_default());

    // 2. 声明发布者 (指定键)
    auto publisher = session.declare_publisher("demo/topic");

    // 3. 发送数据
    while (true) {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        std::string message = "hello from " + std::to_string(ms);
        publisher.put(message);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
