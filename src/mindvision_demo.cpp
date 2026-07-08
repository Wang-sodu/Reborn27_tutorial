#include <chrono>

#include <opencv2/highgui.hpp>

#include "camera/camera.hpp"

int main()
{
  io::Camera camera(io::MindVisionParams{
    .exposure_ms = 5.0,
    .gamma = 1.0,
    .vid_pid = "f622:d13a",
  });

  while (true) {
    cv::Mat img;
    std::chrono::steady_clock::time_point timestamp;
    camera.read(img, timestamp);

    cv::imshow("mindvision_demo", img);

    int key = cv::waitKey(1);
    if (key == 'q' || key == 'Q' || key == 27) {
      break;
    }
  }

  return 0;
}
