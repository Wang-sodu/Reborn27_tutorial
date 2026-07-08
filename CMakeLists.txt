# 1. 指定需要的 CMake 最低版本
cmake_minimum_required(VERSION 3.10)
# 2. 声明项⽬名称及使⽤的语⾔
project(opencv_test VERSION 1.0 LANGUAGES CXX)
# 3. 设置 C++ 标准（等同于 g++ 的 -std=c++17）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 4. 查找OpenCV库
find_package(OpenCV REQUIRED)
# 5. 指定OpenCV头⽂件搜索路径
include_directories(${OpenCV_INCLUDE_DIRS})
# 6. 创建主程序
add_executable(main_app opencv_test.cpp)
# 7. 将 OpenCV 库链接到主程序
target_link_libraries(main_app ${OpenCV_LIBS})