cmake_minimum_required(VERSION 2.8.3)
project(test)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/module/)
message("---" ${CMAKE_MODULE_PATH})

# OpenCV依赖
find_package( OpenCV REQUIRED )

# OpenGL
find_package(OpenGL REQUIRED)

# GLUT
find_package(GLUT REQUIRED)

# Glew
find_package(Glew REQUIRED)

# SiftGPU：手动设置其头文件与库文件所在位置
include_directories("/home/dxq/code_ws/SiftGPU/src/SiftGPU/" ${OpenGL_INCLUDE_DIR})
set(SIFTGPU_LIBS "/home/dxq/code_ws/SiftGPU/bin/libsiftgpu.so")

add_executable( testSIFTGPU src/testGPUSift.cpp )

target_link_libraries( testSIFTGPU
    ${OpenCV_LIBS}
    ${SIFTGPU_LIBS}
    ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES}
)