/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_WINDOW_WINDOW_H
#define _DIVEBAR_WINDOW_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

namespace window {

  //constants
  const std::string DEFAULT_TITLE = "Dive Bar";
  const size_t LOGICAL_W_PX = 128;
  const size_t LOGICAL_H_PX = 64;

  /*
   * Main game window
   */
  class window_t {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;

  public:
    /**
     * Constructor
     * @param title the window title
     */
    window_t(const std::string& title);
    window_t(const window_t&) = delete;
    window_t& operator=(const window_t&) = delete;

    //free sdl resources
    ~window_t();

    /**
     * Get the renderer for the window
     * @return the renderer
     */
    SDL_Renderer& get_renderer();

    /**
     * Clear the screen
     */
    void clear_screen();

    /**
     * Render the window
     */
    void render();
  };

}

#endif /*_DIVEBAR_WINDOW_WINDOW_H*/
