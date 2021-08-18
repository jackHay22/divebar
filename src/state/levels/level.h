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

  protected:

    /**
     * Render the current state
     */
    void render(SDL_Renderer& renderer,
                const SDL_Rect& camera) const override;

  public:
    /**
     * Default constructor
     */
    level_t();
    level_t(const level_t&) = delete;
    level_t& operator=(const level_t&) = delete;

    /**
     * Set the camera position for this level
     * @param camera the new camera position
     */
    void set_camera(SDL_Rect&& camera);
  };

}}

#endif /*_DIVEBAR_STATE_LEVELS_LEVEL_H*/
