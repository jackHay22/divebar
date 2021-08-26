/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_TILEMAP_VIRTUAL_TILE_H
#define _DIVEBAR_STATE_TILEMAP_VIRTUAL_TILE_H

#include <SDL2/SDL.h>
#include "../../common/component.h"
#include "../../common/shared_resources.h"

namespace state {
namespace tilemap {

  /*
   * Allows us to use and move a single object for all tiles in a layer
   */
  class virtual_tile_t : public common::component_t {
  private:
    void load(SDL_Renderer&, const common::component_t&, common::shared_resources&) override {}
  public:
    /**
     * Constructor
     */
    virtual_tile_t(int tile_dim);
    virtual_tile_t(const virtual_tile_t&) = delete;
    virtual_tile_t& operator=(const virtual_tile_t&) = delete;

    /**
     * Whether this tile collides with another component
     * @param  other the other component
     * @return       whether the two components collide
     */
    bool collides_with(const component_t& other) const override;

    /**
     * Whether this tile is currently visible to the camera
     * @return whether the component is visible
     * @param camera the current camera
     */
    bool is_visible(const SDL_Rect& camera) const override;

    /**
     * Set the position of the current tile
     * @param x position x
     * @param y position y
     */
    void move_to(int x, int y);
  };

}}

#endif /*_DIVEBAR_STATE_TILEMAP_VIRTUAL_TILE_H*/
