#include <ekg/os/ekg_opengl.hpp>
#include <ekg/os/ekg_glfw.hpp>
#include <ekg/ekg.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

static void window_size_callback(GLFWwindow* p_glfw_win, int width, int height) {
  ekg::glfw_window_size_callback(width, height);
}

static void key_callback(GLFWwindow* p_glfw_win, int key, int scancode, int action, int mods) {
  ekg::glfw_key_callback(key, scancode, action, mods);
}

static void character_callback(GLFWwindow* p_glfw_win, unsigned int codepoint) {
  ekg::glfw_char_callback(codepoint);
}

static void cursor_position_callback(GLFWwindow* p_glfw_win, double x, double y) {
  ekg::glfw_cursor_pos_callback(x, y);
}

static void mouse_button_callback(GLFWwindow* p_glfw_win, int button, int action, int mods) {
  ekg::glfw_mouse_button_callback(button, action, mods);
}

static void scroll_callback(GLFWwindow* p_glfw_win, double dx, double dy) {
  ekg::glfw_scroll_callback(dx, dy);
}

int32_t main(int32_t, char**) {
  if (!glfwInit()) {
    std::cout << "MUUUUUUUUUUUUUUUUUU" << std::endl;
  }

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  GLFWwindow *p_glfw_win {
    glfwCreateWindow(
      1280,
      720,
      "EKG-GLFW3 demo",
      nullptr,
      nullptr
    )
  };

  glfwMakeContextCurrent(p_glfw_win);

  glewExperimental = GL_TRUE;
  glewInit();

  ekg::runtime_property_t ekg_property {
    .font_path = "./whitneybook.otf",
    .font_path_emoji = "./openmojicolor.ttf",
    .p_gpu_api = new ekg::opengl("#version 400"),
    .p_os_platform = new ekg::glfw(p_glfw_win)
  };

  ekg::runtime ekg_runtime {};
  ekg::init(&ekg_runtime, &ekg_property);

  glfwSetKeyCallback(p_glfw_win, key_callback);
  glfwSetCharCallback(p_glfw_win, character_callback);
  glfwSetCursorPosCallback(p_glfw_win, cursor_position_callback);
  glfwSetMouseButtonCallback(p_glfw_win, mouse_button_callback);
  glfwSetScrollCallback(p_glfw_win, scroll_callback);
  glfwSetWindowSizeCallback(p_glfw_win, window_size_callback);
  glfwSwapInterval(1);

  ekg::make(
    ekg::frame_t {
      .tag = "first frame",
      .rect = {00.0f, 00.0f, 400.0f, 400.0f},
      .drag_dock = ekg::dock::top,
      .resize_dock = ekg::dock::left | ekg::dock::bottom | ekg::dock::right
    }
  );

  ekg::button_t button {};

  button.tag = "bt-1";
  button.text = "moo moo";
  button.text_dock = ekg::dock::left;
  button.dock = ekg::dock::left;
  button.text_font_size = ekg::font::big;
  ekg::make(button);

  button.tag = "bt-2";
  button.text = "owlf olwf";
  button.text_dock = ekg::dock::center;
  button.dock = ekg::dock::next | ekg::dock::fill;
  button.text_font_size = ekg::font::big;
  ekg::make(button);

  button.tag = "bt-3";
  button.text = "oi amo gatinhos";
  button.text_font_size = ekg::font::big;
  ekg::make(button);

  while (!glfwWindowShouldClose(p_glfw_win)) {
    //Must be before update function
    if (ekg::input("mouse-1")) {
      std::cout << "Eu amo muito vc <3" << std::endl;
    }

    ekg::update();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.143243f, 0.2f, 0.921721823f, 1.0f);
    glViewport(0.0f, 0.0f, ekg::viewport.w, ekg::viewport.h);

    ekg::render();

    glfwSwapBuffers(p_glfw_win);
    glfwPollEvents();
  }

  glfwDestroyWindow(p_glfw_win);
  glfwTerminate();

  return 6;
}