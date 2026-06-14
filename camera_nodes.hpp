/*******************************************************************************
 * camera_nodes.hpp — CameraSource (USB cam → cv::Mat)
 ******************************************************************************/

#pragma once

#include <atomic>
#include <chrono>
#include <thread>

#include <fins/node.hpp>
#include <opencv2/opencv.hpp>

#include "config.h"

class CameraSource : public fins::Node {
public:
  void define() override {
    set_name("USBCameraSource");
    set_description("USB 相机图像采集，输出 cv::Mat");
    set_category("Camera");
    register_output<cv::Mat>("image");
  }
  void initialize() override {
    logger->info("CameraSource 初始化.");
    running_ = false;
  }
  void run() override {
    if (running_) return;
    running_ = true;

    if (!open_camera()) {
      logger->warn("相机打开失败: {}", config::DEVICE);
      running_ = false;
      return;
    }
    logger->info("CameraSource 开始采集 {}x{} @{}fps", config::WIDTH, config::HEIGHT, config::FPS);

    worker_ = std::thread([this]() {
      cv::Mat frame;
      auto interval = std::chrono::milliseconds(1000 / config::FPS);
      auto next = std::chrono::steady_clock::now() + interval;

      while (running_) {
        if (!cap_.read(frame)) {
          logger->warn("读帧失败，尝试重连...");
          cap_.release();
          std::this_thread::sleep_for(std::chrono::seconds(1));
          if (!open_camera()) continue;
        }

        if (!frame.empty()) send("image", frame);

        std::this_thread::sleep_until(next);
        next += interval;
      }
    });
  }
  void pause() override {
    running_ = false;
    if (worker_.joinable()) worker_.join();
    cap_.release();
    logger->info("CameraSource 已暂停.");
  }
  void reset() override { logger->info("CameraSource 重置."); }

private:
  cv::VideoCapture cap_;
  std::thread worker_;
  std::atomic<bool> running_{false};

  bool open_camera() {
    std::string dev = config::DEVICE;
    if (dev.size() == 1 && std::isdigit(dev[0]))
      return cap_.open(std::stoi(dev));
    return cap_.open(dev, cv::CAP_V4L2);
  }
};
EXPORT_NODE(CameraSource)
