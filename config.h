/*******************************************************************************
 * config.h — USB 相机参数
 ******************************************************************************/
#pragma once

#include <string>

namespace config {

// 支持: "/dev/video0", "/dev/v4l/by-id/...", "/dev/v4l/by-path/...", "0" 四种写法
inline const std::string DEVICE = "/dev/video0";
inline constexpr int WIDTH  = 640;
inline constexpr int HEIGHT = 480;
inline constexpr int FPS    = 30;

}  // namespace config
