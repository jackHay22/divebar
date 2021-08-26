/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "keys.h"

namespace common {

  #define KEY_W 9
  #define KEY_H 9
  #define KEY_MARGIN 4

  /**
   * Default constructor
   * @param key the key to display
   * @param key_sheet the key images
   */
  keys_t::keys_t(char key)
    : component_t({0,0,0,0}, COMPONENT_ALWAYS_VISIBLE),
      key(key),
      sample_bounds({0,0,0,0}) {}

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void keys_t::load(SDL_Renderer& renderer,
                    const common::component_t& parent,
                    common::shared_resources& resources) {
    int offset = 0;
    if (key == 'W') {
      offset = KEY_W * 1;
    } else if (key == 'A') {
      offset = KEY_W * 2;
    } else if (key == 'S') {
      offset = KEY_W * 3;
    } else if (key == 'D') {
      offset = KEY_W * 4;
    }
    //keys in image are: E,W,A,S,D
    sample_bounds = {offset,0,KEY_W,KEY_H};

    this->key_sheet = resources.key_image;
  }

  /**
   * Render the key
   * @param renderer the sdl renderer
   * @param camera   the current camera
   */
  void keys_t::render_fg(SDL_Renderer& renderer,
                         const SDL_Rect& camera) const {
    SDL_Rect render_bounds = {
      KEY_MARGIN,
      camera.h - KEY_MARGIN - KEY_H,
      KEY_W, KEY_H
    };
    //render in bottom left
    key_sheet->render_copy(renderer,
                           sample_bounds,
                           render_bounds);
  }
}
