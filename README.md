# fins_camera_usb — USB 相机采集插件

CameraSource 节点，OpenCV V4L2 后端读取 USB 相机，输出 cv::Mat。

## 配置

`config.h` 中的参数：

| 参数 | 默认值 | 说明 |
|------|--------|------|
| DEVICE | `/dev/video0` | `/dev/video0`、`by-id/`、`by-path/`、数字 `"0"` |
| WIDTH | 640 | 采集分辨率 |
| HEIGHT | 480 | 采集分辨率 |
| FPS | 30 | 采集帧率 |

## 输出端口

| 端口 | 类型 | 内容 |
|------|------|------|
| image | `cv::Mat` | BGR 图像帧 |

## 依赖

OpenCV (libopencv-dev)
