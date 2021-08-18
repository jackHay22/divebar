/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "virtual_tile.h"

namespace state {
namespace tilemap {

  /**
   * Constructor
   */
  virtual_tile_t::virtual_tile_t(int tile_dim)
    : common::component_t({0,0,tile_dim,tile_dim},COMPONENT_VISIBLE) {}

  /**
   * Whether this tile collides with another component
   * @param  other the other component
   * @return       whether the two components collide
   */
  bool virtual_tile_t::collides_with(const component_t& other) const {
    return common::component_t::collides_with(other);
  }

  /**
   * Whether this tile is currently visible to the camera
   * @return whether the component is visible
   * @param camera the current camera
   */
  bool virtual_tile_t::is_visible(const SDL_Rect& camera) const {
    return common::component_t::is_visible(camera);
  }

  /**
   * Set the position of the current tile
   * @param x position x
   * @param y position y
   */
  void virtual_tile_t::move_to(int x, int y) {
    common::component_t::set_position(x,y);
  }

}}
