#include <iostream>

#include <ekg/os/ekg_opengl.hpp>
#include <ekg/os/ekg_glfw.hpp>
#include <ekg/ekg.hpp>

int32_t main(int32_t, char**) {
  glfwInit();

  GLFWwindow *p_glfw_win {
    glfwCreateWindow(
      1280,
      720,
      "EKG-GLFW demo",
      nullptr,
      nullptr
    )
  };

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwMakeContextCurrent(p_glfw_win);

  glewExperimental = GL_TRUE;
  glewInit();

  ekg::runtime_property ekg_property {
    .p_font_path = "./whitneybook.otf",
    .p_font_path_emoji = "./openmojicolor.ttf",
    .p_gpu_api = new ekg::os::opengl(),
    .p_os_platform = new ekg::os::glfw(p_glfw_win)
  };

  ekg::runtime ekg_runtime {};
  ekg::init(&ekg_runtime, &ekg_property);

  while (!glfwWindowShouldClose(p_glfw_win)) {
    glfwSwapBuffers(p_glfw_win);
    glfwPollEvents();
  }

  glfwDestroyWindow(p_glfw_win);
  glfwTerminate();

  return 6;
}