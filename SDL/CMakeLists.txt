cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
project(ekg_sdl_demo VERSION 1.0.0 DESCRIPTION "SDL demo")

if (WIN32)
  message("--- Windows not implemented! :c")
elseif(LINUX)
  set(EXECUTABLE_OUTPUT_PATH "../../bin")
  include_directories(/usr/include/freetype2)
  add_executable(ekg_sdl_demo "./src/application.cpp")
  target_link_libraries(ekg_sdl_demo ekg SDL2main SDL2 GL GLEW freetype)
endif()

message("--- EKG SDL demo building done!")