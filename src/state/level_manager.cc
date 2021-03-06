/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "level_manager.h"
#include <memory>
#include "levels/dive_bar.h"
#include "levels/exterior.h"
#include "../common/image.h"

namespace state {

  /**
   * Manage different levels
   */
  level_manager_t::level_manager_t()
    : common::component_t({0,0,0,0},COMPONENT_ALWAYS_VISIBLE),
      current_map_location(0) {}

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     * @param resources the shared global resources
     */
    void level_manager_t::load(SDL_Renderer& renderer,
                                const common::component_t& parent,
                                common::shared_resources& resources) {
    //load the different map regions
    this->add_child(std::make_unique<levels::dive_bar_t>());
    this->add_child(std::make_unique<levels::exterior_t>());

    //load child resources
    component_t::load_children(renderer,resources);
  }

  /**
   * Update the state
   */
  void level_manager_t::update(common::component_t& parent) {
    //update the current level
    common::component_t::update_child(current_map_location);
  }

  /**
   * Render the current state
   */
  void level_manager_t::render(SDL_Renderer& renderer,
                               const SDL_Rect& camera) const {
    //render the active region
    common::component_t::render_child(renderer,camera,current_map_location);
    common::component_t::render_fg_child(renderer,camera,current_map_location);
  }

  /**
   * Handle an sdl event
   * @param parent the component parent
   * @param event the sdl event
   */
  void level_manager_t::handle_event(common::component_t& parent,
                                     const SDL_Event& e) {
    //let the current region handle the event
    common::component_t::child_handle_event(e,current_map_location);
  }

  /**
   * Switch to a different level
   * @param level_idx the level index
   * @param player_x  the new player position x
   * @param player_y  the new player position y
   * @param player_attributes the attributes of the player to update in the new level
   */
  void level_manager_t::switch_level(int level_idx,
                                     int player_x,
                                     int player_y,
                                     const entity::entity_attributes_t& player_attributes) {
    //set the new map location
    current_map_location = level_idx;
    //update the player in the new location
    this->get_nth_child<levels::level_t>(current_map_location).update_player(
      player_x, player_y, player_attributes
    );
  }
}
