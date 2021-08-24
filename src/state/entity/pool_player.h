/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_POOL_PLAYER_H
#define _DIVEBAR_STATE_ENTITY_POOL_PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../common/component.h"
#include "../../common/image.h"
#include "entity.h"

namespace state {
namespace entity {

  /*
   * Static pool player
   */
  class pool_player_t : public entity_t {
  private:
    //the frames left for each animation component
    int rem_frames;
    //the total for each
    int shooting_frames_total;
    int idle_frames_total;
    int prep_frames_total;

    /**
     * Load resources for the entity
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     */
    void load(SDL_Renderer& renderer,
              const component_t& parent) override;

    /**
     * Update the player
     */
    void update(common::component_t& parent) override;

  public:
    /**
     * Constructor
     * @param x position x
     * @param y position y
     */
    pool_player_t(int x, int y);
    pool_player_t(const pool_player_t&) = delete;
    pool_player_t& operator=(const pool_player_t&) = delete;
  };

}}

#endif /*_DIVEBAR_STATE_ENTITY_POOL_PLAYER_H*/
