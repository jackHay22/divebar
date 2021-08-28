/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_LEVELS_DOOR_H
#define _DIVEBAR_STATE_LEVELS_DOOR_H

#include <SDL2/SDL.h>
#include "../../common/component.h"
#include "../../common/shared_resources.h"
#include "../entity/player.h"

namespace state {
namespace levels {

  /*
   * Defines a door between different areas
   */
  class door_t : public common::component_t {
  private:
    //the level to switch to
    int target_index;
    //the location to put the player x
    int target_px;
    //the location to put the player y
    int target_py;

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
     * Called when the player interacts with this door
     * @param parent the parent
     * @param player the player
     */
    void interact_entered(component_t& parent,
                          state::entity::player_t& player) override;

  public:
    /**
     * Constructor
     * @param position
     * @param target_index
     * @param target_px the location to put the player x
     * @param target_py the location to put the player y
     */
    door_t(SDL_Rect position,
           int target_index,
           int target_px,
           int target_py);
    door_t(const door_t&) = delete;
    door_t& operator=(door_t&) = delete;

  };

}}

#endif /*_DIVEBAR_STATE_LEVELS_DOOR_H*/
