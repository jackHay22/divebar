/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_LEVELS_LEVEL_H
#define _DIVEBAR_STATE_LEVELS_LEVEL_H

#include <SDL2/SDL.h>
#include "../../common/component.h"

namespace state {
namespace levels {

  /*
   * Defines a map with a camera specific to the map
   */
  class level_t : public common::component_t {
  private:
    //level maintains its own camera
    SDL_Rect level_camera;
    //the max width and max height of the level
    int max_width;
    int max_height;

  protected:

    /**
     * Render the current state
     */
    void render(SDL_Renderer& renderer,
                const SDL_Rect& camera) const override;

    /**
     * Center the camera at some position
     * @param x position x
     * @param y position y
     */
    void center_camera(int x, int y);

    /**
     * Set the max dimensions of the level
     * @param max_width  the max level width
     * @param max_height the max level height
     */
    void set_max_bounds(int max_width, int max_height);

  public:
    /**
     * Default constructor
     */
    level_t();
    level_t(const level_t&) = delete;
    level_t& operator=(const level_t&) = delete;

  };

}}

#endif /*_DIVEBAR_STATE_LEVELS_LEVEL_H*/
