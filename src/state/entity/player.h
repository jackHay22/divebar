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
#include "../../common/shared_resources.h"
#include "entity.h"

namespace state {
namespace entity {

  /*
   * Main player in game
   */
  class player_t : public entity_t {
  private:
    //the action to switch to once the current one is finished (or -1)
    int next_action;
    //the next direction
    bool next_direction;

    //action children indices
    size_t action_idle;
    size_t action_walking;

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
     */
    player_t(SDL_Rect position);
    player_t(const player_t&) = delete;
    player_t& operator=(const player_t&) = delete;

    /**
     * Whether this entity controls the camera
     * @return false by default
     */
    bool controls_camera() const override { return true; }
  };

}}

#endif /*_DIVEBAR_STATE_ENTITY_PLAYER_H*/
