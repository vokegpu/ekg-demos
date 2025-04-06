cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
project(ekg_glfw_demo VERSION 1.0.0 DESCRIPTION "GLFW demo")

if(WIN32)
  message("--- Windows not implemented! :c")
elseif(LINUX)
  set(EXECUTABLE_OUTPUT_PATH "../../bin")
  set(CMAKE_BUILD_TYPE Debug)
  include_directories(/usr/include/freetype2)
  add_executable(ekg_glfw_demo "./src/application.cpp")
  target_link_libraries(ekg_glfw_demo ekg glfw GL GLEW freetype)
endif()

message("--- EKG GLFW demo building done!")