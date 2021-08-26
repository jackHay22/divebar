/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_MINIGAMES_POOL_H
#define _DIVEBAR_STATE_MINIGAMES_POOL_H

#include <SDL2/SDL.h>
#include "../../common/interactive_component.h"

namespace state {
namespace minigames {

  /*
   * Pool minigame
   */
  class pool_game_t : public common::interactive_component_t {
  private:

    /**
     * Load any resources for this component
     * Derived classes must call
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     */
    void load(SDL_Renderer& renderer,
              const component_t& parent) override;

    /**
     * Called when the player interacts with this game
     * @param parent the parent
     */
    void interact_entered(component_t& parent) override;

  public:
    /**
     * Default constructor
     * @param position where to position the interaction target
     */
    pool_game_t(SDL_Rect position);
    pool_game_t(const pool_game_t&) = delete;
    pool_game_t& operator=(const pool_game_t&) = delete;

  };

}}

#endif /*_DIVEBAR_STATE_MINIGAMES_POOL_H*/
