/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "pool.h"
#include <memory>
#include <iostream>

namespace state {
namespace minigames {

  /**
   * Default constructor
   */
  pool_game_t::pool_game_t(SDL_Rect position)
    : common::component_t(std::move(position), COMPONENT_VISIBLE | COMPONENT_INTERACTIVE) {}

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void pool_game_t::load(SDL_Renderer& renderer,
                          const common::component_t& parent,
                          common::shared_resources& resources) {
    //load game resources


    //load any children (including key)
    component_t::load_children(renderer,resources);
  }

  /**
   * Called when the player interacts with this component
   * @param parent the parent
   * @param player the player
   */
  void pool_game_t::interact_entered(component_t& parent,
                        state::entity::player_t& player) {
    std::cout << "pool game entered" << std::endl;
  }
}}
