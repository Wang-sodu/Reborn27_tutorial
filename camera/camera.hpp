#ifndef IO__CAMERA_HPP
#define IO__CAMERA_HPP

#include <chrono>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

namespace io
{
struct MindVisionParams
{
  double exposure_ms;
  double gamma;
  std::string vid_pid;
};

struct HikRobotParams
{
  double exposure_ms;
  double gain;
  std::string vid_pid;
  unsigned int adcbitdepth = 8;
  double framerate = 265.0;
  bool trigger_mode = false;
};

class CameraBase
{
public:
  virtual ~CameraBase() = default;
  virtual void read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp) = 0;
};

class Camera
{
public:
  explicit Camera(const MindVisionParams & params);
  explicit Camera(const HikRobotParams & params);
  void read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp);

private:
  std::unique_ptr<CameraBase> camera_;
};

}  // namespace io

#endif  // IO__CAMERA_HPP
