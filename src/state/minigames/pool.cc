/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "pool.h"
#include <iostream>

namespace state {
namespace minigames {

  /**
   * Default constructor
   */
  pool_game_t::pool_game_t(SDL_Rect position)
    : common::interactive_component_t(
        position,
        COMPONENT_ALWAYS_VISIBLE,
        SDLK_e,
        "Press [E] to play",
        16
      ) {}

  /**
   * Load any resources for this component
   * Derived classes must call
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   */
  void pool_game_t::load(SDL_Renderer& renderer,
                         const component_t& parent) {
    interactive_component_t::load(renderer,parent);

    //TODO
  }

  /**
   * Called when the player interacts with this game
   * @param parent the parent
   */
  void pool_game_t::interact_entered(component_t& parent) {
    std::cout << "interaction handler for pool called" << std::endl;
  }
}}
