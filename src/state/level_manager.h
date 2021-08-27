/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_LEVEL_MANAGER_H
#define _DIVEBAR_STATE_LEVEL_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common/component.h"
#include "../common/shared_resources.h"
#include "entity/entity_attributes.h"

namespace state {

  #define LEVEL_REGION_BAR 0

  /*
   * Manages different areas within the game
   */
  class level_manager_t : public common::component_t {
  private:
    //the current location of the player within all of the map regions
    size_t current_map_location;

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

    /**
     * Render the current state
     */
    void render(SDL_Renderer& renderer,
                const SDL_Rect& camera) const override;

    /**
     * Handle an sdl event
     * @param parent the component parent
     * @param event the sdl event
     */
    void handle_event(common::component_t& parent,
                      const SDL_Event& e) override;

  public:
    /**
     * Manage different levels
     */
    level_manager_t();
    level_manager_t(const level_manager_t&) = delete;
    level_manager_t& operator=(const level_manager_t&) = delete;

    /**
     * Switch to a different level
     * @param level_idx the level index
     * @param player_x  the new player position x
     * @param player_y  the new player position y
     * @param player_attributes the attributes of the player to update in the new level
     */
    void switch_level(int level_idx,
                      int player_x,
                      int player_y,
                      const entity::entity_attributes_t& player_attributes);
  };

}

#endif /*_DIVEBAR_STATE_LEVEL_MANAGER_H*/
