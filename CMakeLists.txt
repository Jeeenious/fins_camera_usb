cmake_minimum_required(VERSION 3.16)

project(fins_camera_usb LANGUAGES CXX)

find_package(OpenCV REQUIRED)

fins_add_node(${PROJECT_NAME}
  nodes.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
