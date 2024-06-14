#include <ekg/ekg.hpp>
#include <ekg/os/ekg_sdl.hpp>
#include <ekg/os/ekg_opengl.hpp>

int32_t main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
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

  ekg::runtime_property ekg_runtime_property {
    .p_font_path = "./whitneybook.otf",
    .p_font_path_emoji = "./openmojicolor.ttf",
    .p_gpu_api = new ekg::os::opengl(),
    .p_os_platform = new ekg::os::sdl(p_sdl_win)
  };

  ekg::runtime ekg {};
  ekg::init(&ekg, &ekg_runtime_property);

  ekg::frame("meow oi amo vc", {20, 20}, {400, 200})
    ->set_drag(ekg::dock::top)
    ->set_resize(ekg::dock::left | ekg::dock::bottom | ekg::dock::right);

  ekg::label("working on SDL2", ekg::dock::fill | ekg::dock::next);
  ekg::label("very cool...", ekg::dock::fill | ekg::dock::next);
  ekg::label("meow", ekg::dock::fill | ekg::dock::next);
  ekg::button("testing button because we", ekg::dock::fill | ekg::dock::next);

  ekg::textbox("meow1", "oi eu amo gato frajola fofa perfeita eu quero casar", ekg::dock::fill | ekg::dock::next)
    ->set_scaled_height(4);

  ekg::pop_group();

  SDL_Event sdl_event {};
  bool running {true};

  while (running) {
    while (SDL_PollEvent(&sdl_event)) {
      ekg::os::sdl_poll_event(sdl_event);

      if (sdl_event.type == SDL_QUIT) {
        running = false;
      }
    }

    ekg::update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glViewport(0.0f, 0.0f, ekg::ui::width, ekg::ui::height);

    ekg::render();

    SDL_GL_SwapWindow(p_sdl_win);
    SDL_Delay(16);
  }

  return 666;
}