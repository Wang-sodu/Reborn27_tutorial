#include <cstdio>
#include <iostream>
#include <vector>


#include <opencv2/highgui.hpp>



#include "zenoh.hxx"

// 1. 定义一个回调函数，参数必须是 zenoh::Sample&
void on_data_received(zenoh::Sample& sample) {
    // 获取payload数据
    const auto& payload = sample.get_payload();
    std::string str_data = payload.as_string();
        std::vector<uchar> data(str_data.begin(), str_data.end());
    
    // 解码JPEG为图像
    cv::Mat img = cv::imdecode(data, cv::IMREAD_COLOR);
    
    if (!img.empty()) {
        // 显示图像
        cv::imshow("Camera Stream", img);
        cv::waitKey(1);
        std::cout << "收到图像，大小: " << data.size() << " bytes" << std::endl;
    } else {
        std::cerr << "解码图像失败" << std::endl;
    }
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
