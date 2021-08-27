/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_INTERACTIVE_COMPONENT_H
#define _DIVEBAR_COMMON_INTERACTIVE_COMPONENT_H

#include "component.h"
#include "shared_resources.h"
#include "../state/entity/player.h"

namespace common {

  /*
   * A component that the player can interact with in some way
   */
  class interactive_component_t : public component_t {
  private:
    //the keycode that triggers the interaction
    SDL_Keycode code;
    //the proximity radius that allows the interaction
    int radius;
    //whether the interaction is triggered automatically
    bool automatic;
    //whether the component can currently be interacted with
    bool can_interact;

    /**
     * Handle an sdl event
     * @param parent the component parent
     * @param event the sdl event
     * @param player the player
     */
    void handle_event_player(component_t& parent,
                             const SDL_Event& e,
                             state::entity::player_t& player);

    /**
     * Render key when enabled
     * @param renderer the sdl renderer
     * @param camera   the current camera
     */
    void render_fg(SDL_Renderer& renderer,
                   const SDL_Rect& camera) const override;

    friend struct component_t;

    /**
     * The distance from the player
     * @param parent the parent of this component
     * @param player the player
     */
    void update_player_distance(component_t& parent, state::entity::player_t& player);

  protected:

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     * @param resources the shared global resources
     */
    virtual void load(SDL_Renderer& renderer,
                      const component_t& parent,
                      shared_resources& resources) override;

    /**
     * Called when the player interacts with this component
     * @param parent the parent
     * @param player the player
     */
    virtual void interact_entered(component_t& parent,
                                  state::entity::player_t& player) = 0;

    /**
     * Called when the player leaves the interaction radius
     * @param parent the parent
     * @param player the player
     */
    virtual void interact_exited(component_t& parent,
                                 state::entity::player_t& player) {}

  public:
    /**
     * Constructor
     * @param bounds the bounds of the component @see component_t
     * @param flags  attributes @see component_t
     * @param code the key that triggers the interaction
     * @param radius the distance from player that triggers the interaction
     * @param automatic the interaction is triggered by proximity
     */
    interactive_component_t(SDL_Rect bounds,
                            uint8_t flags,
                            SDL_Keycode code,
                            int radius,
                            bool automatic=false);
    interactive_component_t(const interactive_component_t&) = delete;
    interactive_component_t& operator=(const interactive_component_t&) = delete;
  };

}

#endif /*_DIVEBAR_COMMON_INTERACTIVE_COMPONENT_H*/
