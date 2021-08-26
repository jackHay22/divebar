/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "shared_resources.h"

namespace common {

  /**
   * Default constructor
   * @param renderer the sdl renderer for loading images
   * @param resource_dir the base resource directory
   */
  shared_resources::shared_resources(SDL_Renderer& renderer, const std::string& resource_dir)
    : key_image(std::make_shared<image_t>(renderer, resource_dir + "tilesets/keys.png")),
      player_image(std::make_shared<image_t>(renderer, resource_dir + "animations/player.png")),
      divebar_tileset(std::make_shared<image_t>(renderer, resource_dir + "tilesets/bar.png")) {}
}
