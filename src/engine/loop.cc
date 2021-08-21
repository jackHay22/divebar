/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "loop.h"
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>

namespace engine {

  /**
   * Start the game loop
   * @param  win the window
   * @param  man the state manager
   * @return     exit status
   */
  int game_loop(std::shared_ptr<window::window_t> win,
                std::shared_ptr<state::manager_t> man) {

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    SDL_Event e;

    while (true) {
      //check events
      while (SDL_PollEvent(&e) != 0) {
        //check for a quit event
        if (e.type == SDL_QUIT) {
          return EXIT_SUCCESS;
        } else {
          //handle event
          man->handle_event_manager(e);
        }
      }

      //get time since last update
      std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
      int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

      //check if tick elapsed
      if (elapsed_ms >= TICK_SLEEP) {
        //restart the timer
        start = std::chrono::steady_clock::now();
        //update the state
        man->update_manager();
      }

      //clear the screen
      win->clear_screen();

      //draw the window contents
      man->render_manager(win->get_renderer());

      //render the repaint
      win->render();

    }
    return EXIT_SUCCESS;
  }
}
