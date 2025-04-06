#include <ekg/os/ekg_opengl.hpp>
#include <ekg/os/ekg_sdl.hpp>
#include <ekg/ekg.hpp>

#include <iostream>

int32_t main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetSwapInterval(1);

  SDL_Window *p_sdl_win {
    SDL_CreateWindow(
      "EKG-SDL2 demo",
      10,
      10,
      1280,
      720,
      SDL_WINDOW_OPENGL
    )
  };

  SDL_GLContext sdl_gl_context {SDL_GL_CreateContext(p_sdl_win)};

  glewExperimental = GL_TRUE;
  glewInit();

  ekg::runtime_property_t ekg_property {
    .font_path = "./whitneybook.otf",
    .font_path_emoji = "./openmojicolor.ttf",
    .p_gpu_api = new ekg::opengl("#version 400"),
    .p_os_platform = new ekg::sdl(p_sdl_win)
  };

  ekg::runtime ekg_runtime {};
  ekg::init(&ekg_runtime, &ekg_property);

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

  SDL_Event sdl_event {};
  bool running {true};

  while (running) {
    while (SDL_PollEvent(&sdl_event)) {
      ekg::sdl_poll_event(sdl_event);

      if (sdl_event.type == SDL_QUIT) {
        running = false;
      }
    }
    //Must be before update function
    if (ekg::input("mouse-1")) {
      std::cout << "Eu amo muito vc <3" << std::endl;
    }

    ekg::update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glViewport(0.0f, 0.0f, ekg::viewport.w, ekg::viewport.h);

    ekg::render();

    SDL_GL_SwapWindow(p_sdl_win);
    SDL_Delay(16);
  }

  return 666;
}