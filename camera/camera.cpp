#include "camera.hpp"

#include "hikrobot/hikrobot.hpp"
#include "mindvision/mindvision.hpp"

namespace io
{
Camera::Camera(const MindVisionParams & params)
{
  camera_ = std::make_unique<MindVision>(params.exposure_ms, params.gamma, params.vid_pid);
}

Camera::Camera(const HikRobotParams & params)
{
  camera_ = std::make_unique<HikRobot>(
    params.exposure_ms, params.gain, params.vid_pid, params.adcbitdepth, params.framerate,
    params.trigger_mode);
}

void Camera::read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp)
{
  camera_->read(img, timestamp);
}

}  // namespace io
