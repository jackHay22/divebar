/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "window.h"
#include "../common/launch_exception.h"
#include <iostream>
#include <exception>

namespace window {

  /**
   * Try to maximize the window scale
   * @param w pixel width
   * @param h pixel height
   * @return scale
   */
  [[nodiscard]] size_t scale_for_display(size_t w, size_t h) {
    //get the width and height of the display
    SDL_DisplayMode disp_mode;
    SDL_GetCurrentDisplayMode(0, &disp_mode);
    return std::min(disp_mode.w / w, disp_mode.h / h);
  }

  /**
   * Constructor
   * @param w window width
   * @param h window height
   * @param title the window title
   */
  window_t::window_t(const std::string& title) {

    //init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      throw common::launch_exception("failed to init sdl video: " + std::string(SDL_GetError()));
    }

    //set the render quality
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0")) {
      throw common::launch_exception("failed to set sdl render quality");
    }

    //scale the game ratio based on the display size
    size_t scale = window::scale_for_display(
      LOGICAL_W_PX,
      LOGICAL_H_PX
    );

    //create the window
    this->window = SDL_CreateWindow(
          title.c_str(),
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          LOGICAL_W_PX * scale,
          LOGICAL_H_PX * scale,
          SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

    if (this->window == NULL) {
      throw common::launch_exception("failed to init window: " + std::string(SDL_GetError()));
    }

    //initialize the renderer
    this->renderer = SDL_CreateRenderer(this->window, -1,
                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->renderer == NULL) {
      throw common::launch_exception("failed to init renderer: " + std::string(SDL_GetError()));
    }

    //set the logical size of the renderer
    SDL_RenderSetLogicalSize(this->renderer,LOGICAL_W_PX,LOGICAL_H_PX);

    //clear
    SDL_SetRenderDrawColor(this->renderer,0xFF,0xFF,0xFF,0xFF);

    int img_init_flags = IMG_INIT_PNG;

    //setup png initialization
    if (!(IMG_Init(img_init_flags) & img_init_flags)) {
      throw common::launch_exception("failed to init png load: " + std::string(IMG_GetError()));
    }

    //disable the cursor
    SDL_ShowCursor(SDL_DISABLE);
  }

  /**
   * Destructor
   */
  window_t::~window_t() {
    //free resources
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    window = NULL;
    renderer = NULL;

    //quit subsystems
    IMG_Quit();
    SDL_Quit();
  }

  /**
   * Get the renderer for the window
   * @return the renderer
   */
  SDL_Renderer& window_t::get_renderer() {
    return *renderer;
  }

  /**
   * Clear the screen
   */
  void window_t::clear_screen() {
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(renderer);
  }

  /**
   * Render the window
   */
  void window_t::render() {
    SDL_RenderPresent(renderer);
  }
}
