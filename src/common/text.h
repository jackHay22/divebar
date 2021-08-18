/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_TEXT_H
#define _DIVEBAR_COMMON_TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common/image.h"
#include <string>
#include <memory>

namespace common {

  /**
   * Generate an image from text
   * @param str      the text
   * @param renderer the sdl renderer
   * @param r        color channel r
   * @param g        color channel g
   * @param b        color channel b
   */
  std::shared_ptr<common::image_t> image_from_text(const std::string& str,
                                                   SDL_Renderer& renderer,
                                                   unsigned int r,
                                                   unsigned int g,
                                                   unsigned int b);

}

#endif /*_DIVEBAR_COMMON_TEXT_H*/
