/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_BARTENDER_H
#define _DIVEBAR_STATE_ENTITY_BARTENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../common/component.h"
#include "../../common/shared_resources.h"
#include "../../common/image.h"
#include "player.h"
#include "entity.h"

namespace state {
namespace entity {

  /*
   * The bartender
   */
  class bartender_t : public entity_t {
  private:
    //whether the serving cycle has started
    bool working;
    //the duration of the idle cycle
    int idle_cycle_duration;
    //cool off period after working
    int rem_idle_cycles;
    //whether the player needs to enter and leave the area
    bool needs_reset;

    //action children indices
    size_t action_serve;
    size_t action_walk;
    size_t action_idle;

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
     * Update the player
     */
    void update(common::component_t& parent) override;

    /**
     * Called when the player interacts with this component
     * @param parent the parent
     * @param player the player
     */
    void interact_entered(component_t& parent,
                           state::entity::player_t& player) override;

    /**
     * Called when the player leaves the interaction radius
     * @param parent the parent
     * @param player the player
     */
    void interact_exited(component_t& parent,
                         state::entity::player_t& player) override;

  public:
    /**
     * Constructor
     * @param x position x
     * @param y position y
     * @param key_sheet images for key interaction
     */
    bartender_t(int x, int y);
    bartender_t(const bartender_t&) = delete;
    bartender_t& operator=(const bartender_t&) = delete;
  };

}}

#endif /*_DIVEBAR_STATE_ENTITY_BARTENDER_H*/
