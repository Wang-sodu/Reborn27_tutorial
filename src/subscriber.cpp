#include <cstdio>
#include <iostream>

#include "zenoh.hxx"

// 1. 定义一个回调函数，参数必须是 zenoh::Sample&
void on_data_received(zenoh::Sample& sample) {
    std::cout << sample.get_payload().as_string() << std::endl;
}

int main() {
    // 2. 打开会话
    auto session = zenoh::Session::open(zenoh::Config::create_default());

    // 3. 声明订阅者，直接传入函数名 `on_data_received`
    auto subscriber = session.declare_subscriber(
        "demo/topic", [](zenoh::Sample& sample) { on_data_received(sample); }, [] {});

    // 4. 阻塞程序，防止立刻退出
    std::getchar(); 

    return 0;
}
