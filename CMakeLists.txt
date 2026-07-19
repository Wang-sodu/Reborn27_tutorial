cmake_minimum_required(VERSION 3.10)
project(LightDetector)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCES
    src/ArmorDetector.cpp
    src/drewPicture.cpp
    src/main.cpp
)
find_package(OpenCV REQUIRED)
add_executable(light_detector ${SOURCES})
target_link_libraries(light_detector ${OpenCV_LIBS})
target_include_directories(light_detector PRIVATE ${OpenCV_INCLUDE_DIRS})