/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_PLAYER_H
#define _DIVEBAR_STATE_ENTITY_PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../common/component.h"
#include "../../common/image.h"
#include "entity.h"

namespace state {
namespace entity {

  /*
   * Main player in game
   */
  class player_t : public entity_t {
  private:
    //animations used by this player (shared)
    std::shared_ptr<common::image_t> anim_sheet;
    //the action to switch to once the current one is finished (or -1)
    int next_action;
    //the next direction
    bool next_direction;

    /**
     * Load actions for the player
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     */
    void load(SDL_Renderer& renderer,
              const component_t& parent) override;

    /**
     * Update the player
     */
    void update(common::component_t& parent) override;

    /**
     * Handle input events, delegate to action
     * @param parent the component parent
     * @param event the sdl event
     */
    void handle_event(component_t& parent,
                      const SDL_Event& e) override;

  public:
    /**
     * Constructor
     * @param position starting position for the player
     * @param anim_sheet the animations used by the player
     */
    player_t(SDL_Rect position,
             std::shared_ptr<common::image_t> anim_sheet);
    player_t(const player_t&) = delete;
    player_t& operator=(const player_t&) = delete;
  };

}}

#endif /*_DIVEBAR_STATE_ENTITY_PLAYER_H*/
