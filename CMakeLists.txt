cmake_minimum_required(VERSION 3.9)
project(contrast_chroma)

set(CMAKE_CXX_STANDARD 11)

add_executable(contrast_chroma main.cpp)

find_package( OpenCV REQUIRED )

target_link_libraries(contrast_chroma ${OpenCV_LIBS})