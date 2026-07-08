#include <chrono>
#include <string>
#include <thread>
#include <vector>


#include <opencv2/highgui.hpp>

#include "camera/camera.hpp"

#include "zenoh.hxx"

int main() {
    // 1. 打开会话
    auto session = zenoh::Session::open(zenoh::Config::create_default());

    // 2. 声明发布者 (指定键)
    auto publisher = session.declare_publisher("demo/topic");
    
     io::Camera camera(io::HikRobotParams{
    .exposure_ms = 5.0,
    .gain = 16.0,
    .vid_pid = "2bdf:0001",
    .adcbitdepth = 8,
    .framerate = 265.0,
    .trigger_mode = false,
  });

    // 3. 发送数据
    while (true) {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        cv::Mat img;
        std::chrono::steady_clock::time_point timestamp;
        camera.read(img, timestamp);
       std::vector<uchar> buffer;
        std::vector<int> compression_params;
        compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
        compression_params.push_back(80);  // 质量80%
        cv::imencode(".jpg", img, buffer, compression_params);

        // 修改：发送图像数据而不是字符串
        std::string image_data(buffer.begin(), buffer.end());
            publisher.put(image_data);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
