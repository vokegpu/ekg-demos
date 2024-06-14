#include <iostream>

#include <ekg/os/ekg_opengl.hpp>
#include <ekg/os/ekg_glfw.hpp>
#include <ekg/ekg.hpp>

static void window_size_callback(GLFWwindow* p_glfw_win, int width, int height) {
  ekg::os::glfw_window_size_callback(width, height);
}

static void key_callback(GLFWwindow* p_glfw_win, int key, int scancode, int action, int mods) {
  ekg::os::glfw_key_callback(key, scancode, action, mods);
}

static void character_callback(GLFWwindow* p_glfw_win, unsigned int codepoint) {
  ekg::os::glfw_char_callback(codepoint);
}

static void cursor_position_callback(GLFWwindow* p_glfw_win, double x, double y) {
  ekg::os::glfw_cursor_pos_callback(x, y);
}

static void mouse_button_callback(GLFWwindow* p_glfw_win, int button, int action, int mods) {
  ekg::os::glfw_mouse_button_callback(button, action, mods);
}

static void scroll_callback(GLFWwindow* p_glfw_win, double dx, double dy) {
  ekg::os::glfw_scroll_callback(dx, dy);
}

int32_t main(int32_t, char**) {
  if (!glfwInit()) {
    std::cout << "MUUUUUUUUUUUUUUUUUU" << std::endl;
  }

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

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

  ekg::runtime_property ekg_property {
    .p_font_path = "./whitneybook.otf",
    .p_font_path_emoji = "./openmojicolor.ttf",
    .p_gpu_api = new ekg::os::opengl(),
    .p_os_platform = new ekg::os::glfw(p_glfw_win)
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

  ekg::frame("meow oi amo vc", {20, 20}, {400, 200})
    ->set_drag(ekg::dock::top)
    ->set_resize(ekg::dock::left | ekg::dock::bottom | ekg::dock::right);

  ekg::label("working on GLFW3", ekg::dock::fill | ekg::dock::next);
  ekg::label("very cool...", ekg::dock::fill | ekg::dock::next);
  ekg::label("meow", ekg::dock::fill | ekg::dock::next);
  ekg::button("testing button because we", ekg::dock::fill | ekg::dock::next);

  ekg::textbox("meow1", "oi eu amo gato frajola fofa perfeita eu quero casar", ekg::dock::fill | ekg::dock::next)
    ->set_scaled_height(4);

  ekg::pop_group();

  ekg::input::bind("amovc", "a");

  while (!glfwWindowShouldClose(p_glfw_win)) {
    ekg::update();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.143243f, 0.2f, 0.921721823f, 1.0f);
    glViewport(0.0f, 0.0f, ekg::ui::width, ekg::ui::height);

    if (ekg::input::action("amovc")) {
      std::cout << "Eu amo muito vc <3" << std::endl;
    }

    ekg::ui::dt = 0.016f;
    ekg::render();

    glfwSwapBuffers(p_glfw_win);
    glfwPollEvents();
  }

  glfwDestroyWindow(p_glfw_win);
  glfwTerminate();

  return 6;
}