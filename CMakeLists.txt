cmake_minimum_required(VERSION 3.16)

project(reborn27_camera_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找依赖包
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(zenohc REQUIRED)
find_package(zenohcxx REQUIRED)

# 打印OpenCV信息
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

# 创建io库（相机相关）
add_library(io STATIC
  camera/hikrobot/hikrobot.cpp
  camera/mindvision/mindvision.cpp
  camera/camera.cpp
  tools/logger.cpp
)

target_include_directories(io PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${OpenCV_INCLUDE_DIRS}
  camera/hikrobot/include
  camera/mindvision/include
)

# 根据架构设置库路径
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
  target_link_directories(io PUBLIC
    ${PROJECT_SOURCE_DIR}/camera/hikrobot/lib/amd64
    ${PROJECT_SOURCE_DIR}/camera/mindvision/lib/amd64
  )
  set(IO_RPATH
    ${PROJECT_SOURCE_DIR}/camera/hikrobot/lib/amd64
    ${PROJECT_SOURCE_DIR}/camera/mindvision/lib/amd64
  )
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
  target_link_directories(io PUBLIC
    ${PROJECT_SOURCE_DIR}/camera/hikrobot/lib/arm64
    ${PROJECT_SOURCE_DIR}/camera/mindvision/lib/arm64
  )
  set(IO_RPATH
    ${PROJECT_SOURCE_DIR}/camera/hikrobot/lib/arm64
    ${PROJECT_SOURCE_DIR}/camera/mindvision/lib/arm64
  )
else()
  message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}!")
endif()

target_link_libraries(io PUBLIC
  ${OpenCV_LIBS}
  Threads::Threads
  spdlog::spdlog
  fmt::fmt
  MvCameraControl
  MVSDK
  usb-1.0
)

set_target_properties(io PROPERTIES
  BUILD_RPATH "${IO_RPATH}"
)

# mindvision_demo
add_executable(mindvision_demo src/mindvision_demo.cpp)
target_link_libraries(mindvision_demo PRIVATE io)
set_target_properties(mindvision_demo PROPERTIES BUILD_RPATH "${IO_RPATH}")

# hikrobot_demo
add_executable(hikrobot_demo src/hikrobot_demo.cpp)
target_link_libraries(hikrobot_demo PRIVATE io)
set_target_properties(hikrobot_demo PROPERTIES BUILD_RPATH "${IO_RPATH}")

# publisher - 需要相机和zenoh
add_executable(publisher src/publisher.cpp)
target_link_libraries(publisher PRIVATE 
    io                                    # 相机库
    zenohcxx::zenohc                      # zenoh
)
set_target_properties(publisher PROPERTIES 
    BUILD_RPATH "${IO_RPATH}"
)

# subscriber - 只需要zenoh和OpenCV（不需要相机）
add_executable(subscriber src/subscriber.cpp)
target_link_libraries(subscriber PRIVATE 
    zenohcxx::zenohc                      # zenoh
    ${OpenCV_LIBS}                        # OpenCV显示图像
)
target_include_directories(subscriber PRIVATE
    ${OpenCV_INCLUDE_DIRS}                # OpenCV头文件
)