/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_SHARED_RESOURCES_H
#define _DIVEBAR_COMMON_SHARED_RESOURCES_H

#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include "image.h"

namespace common {

  /*
   * Shared resources available to
   * components
   */
  struct shared_resources {
  public:
    //resources that can be accessed by other components
    std::shared_ptr<image_t> key_image;
    std::shared_ptr<image_t> player_image;
    std::shared_ptr<image_t> divebar_tileset;
    std::shared_ptr<image_t> exterior_tileset;

    /**
     * Default constructor
     * @param renderer the sdl renderer for loading images
     * @param resource_dir the base resource directory
     */
    shared_resources(SDL_Renderer& renderer, const std::string& resource_dir);
    shared_resources(const shared_resources&) = delete;
    shared_resources& operator=(const shared_resources&) = delete;
  };

}

#endif /*_DIVEBAR_COMMON_SHARED_RESOURCES_H*/
