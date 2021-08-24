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
    //the total number of idle cycles
    int idle_updates_rem;
    //number of idle cycles remaining
    int idle_updates_total;

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
