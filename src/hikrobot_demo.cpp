#include <chrono>

#include <opencv2/highgui.hpp>

#include "camera/camera.hpp"

int main()
{
  io::Camera camera(io::HikRobotParams{
    .exposure_ms = 5.0,
    .gain = 16.0,
    .vid_pid = "2bdf:0001",
    .adcbitdepth = 8,
    .framerate = 265.0,
    .trigger_mode = false,
  });

  while (true) {
    cv::Mat img;
    std::chrono::steady_clock::time_point timestamp;
    camera.read(img, timestamp);

    cv::imshow("hikrobot_demo", img);

    int key = cv::waitKey(1);
    if (key == 'q' || key == 'Q' || key == 27) {
      break;
    }
  }

  return 0;
}
