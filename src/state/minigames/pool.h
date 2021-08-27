/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_MINIGAMES_POOL_H
#define _DIVEBAR_STATE_MINIGAMES_POOL_H

#include <SDL2/SDL.h>
#include "../../common/interactive_component.h"
#include "../../common/shared_resources.h"
#include "../entity/player.h"

namespace state {
namespace minigames {

  /*
   * Pool minigame
   */
  class pool_game_t : public common::interactive_component_t {
  private:

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
     * Called when the player interacts with this game
     * @param parent the parent
     * @param player the player
     */
    void interact_entered(component_t& parent,
                          state::entity::player_t& player) override;

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
