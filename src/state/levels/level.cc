/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "level.h"
#include "../../window/window.h"
#include <algorithm>

namespace state {
namespace levels {

  /**
   * Default constructor
   */
  level_t::level_t()
    : common::component_t({0,0,0,0}, COMPONENT_ALWAYS_VISIBLE),
      level_camera({0,0,window::LOGICAL_W_PX,window::LOGICAL_H_PX}),
      max_width(0),
      max_height(0) {}

  /**
   * Render the current state
   */
  void level_t::render(SDL_Renderer& renderer, const SDL_Rect&) const {
    //render everything in the level using this camera
    component_t::render(renderer,level_camera);
  }

  /**
   * Center the camera at some position
   * @param x position x
   * @param y position y
   */
  void level_t::center_camera(int x, int y) {
    //set the x and y (bound by map size)
    level_camera.x = std::min(std::max(x - (level_camera.w / 2), 0), max_width - level_camera.w);
    level_camera.y = std::min(std::max(y - (level_camera.h / 2), 0), max_height - level_camera.h);
  }

  /**
   * Set the max dimensions of the level
   * @param max_width  the max level width
   * @param max_height the max level height
   */
  void level_t::set_max_bounds(int max_width, int max_height) {
    this->max_width = max_width;
    this->max_height = max_height;
  }

}}
