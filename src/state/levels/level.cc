/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "level.h"
#include "../../window/window.h"

namespace state {
namespace levels {

  /**
   * Default constructor
   */
  level_t::level_t()
    : common::component_t({0,0,0,0}, COMPONENT_VISIBLE),
      level_camera({0,0,window::LOGICAL_W_PX,window::LOGICAL_H_PX}) {}

  /**
   * Render the current state
   */
  void level_t::render(SDL_Renderer& renderer, const SDL_Rect&) const {
    //render everything in the level using this camera
    component_t::render_children(renderer,level_camera);
  }

  /**
   * Set the camera position for this level
   * @param camera the new camera position
   */
  void level_t::set_camera(SDL_Rect&& camera) {
    this->level_camera = camera;
  }

}}
