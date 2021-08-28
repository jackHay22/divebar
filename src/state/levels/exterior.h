/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_LEVELS_EXTERIOR_H
#define _DIVEBAR_STATE_LEVELS_EXTERIOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../common/component.h"
#include "../../common/shared_resources.h"
#include "level.h"

namespace state {
namespace levels {

  /*
   * Exterior map
   */
  class exterior_t : public level_t {
  private:
    //the index of the player (as a child)
    size_t player_idx;

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     * @param resources the shared global resources
     */
    void load(SDL_Renderer& renderer,
              const common::component_t& parent,
              common::shared_resources& resources) override;

    /**
     * Update the state
     */
    void update(common::component_t& parent) override;

  public:
    /**
     * Default constructor
     */
    exterior_t();
    exterior_t(const exterior_t&) = delete;
    exterior_t& operator=(const exterior_t&) = delete;

    /**
     * Move the player to some position in this level
     * @param x new player position x
     * @param y new player position y
     * @param player_attributes the attributes of the player to update
     */
    void update_player(int x, int y,
                       const entity::entity_attributes_t& player_attributes) override;
  };

}}

#endif /*_DIVEBAR_STATE_LEVELS_EXTERIOR_H*/
