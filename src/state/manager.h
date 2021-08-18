/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_MANAGER_H
#define _DIVEBAR_STATE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common/component.h"

namespace state {

  #define MANAGER_TITLE_STATE 0
  #define MANAGER_PAUSE_STATE 1
  #define MANAGER_GAME_STATE 2
  #define MANAGER_OPTIONS_STATE 3

  /*
   * Main game state manager
   */
  class manager_t : public common::component_t {
  private:
    //the current state
    size_t current_state;
    //the camera
    SDL_Rect camera;

    //unused (no parent)
    void load(SDL_Renderer& renderer, const common::component_t& parent) override {}

    /**
     * Manager always visible (need this to render children)
     * @param  camera the camera
     * @return        whether the manager is visible
     */
    bool is_visible(const SDL_Rect& camera) const override { return true; }

  public:
    /**
     * Constructor
     * Takes renderer to load resources, resource directory
     */
    manager_t(SDL_Renderer& renderer, const std::string& resource_dir);
    manager_t(const manager_t&) = delete;
    manager_t& operator=(const manager_t&) = delete;

    /**
     * Update the state
     */
    void update();

    /**
     * Handle an sdl event
     * @param e the sdl event
     */
    void handle_event(const SDL_Event& e);

    /**
     * Render the current state
     */
    void render(SDL_Renderer& renderer) const;

    /**
     * Set the current state
     * @param state the new current state
     */
    void set_current_state(size_t state);
  };

}

#endif /*_DIVEBAR_STATE_MANAGER_H*/
