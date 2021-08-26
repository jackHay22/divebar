/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_INTERACTIVE_COMPONENT_H
#define _DIVEBAR_COMMON_INTERACTIVE_COMPONENT_H

#include "component.h"
#include "image.h"

namespace common {

  /*
   * A component that the player can interact with in some way
   */
  class interactive_component_t : public component_t {
  private:
    //the keycode that triggers the interaction
    SDL_Keycode code;
    //the text to display for the interaction prompt
    std::string display_code;
    //the proximity radius that allows the interaction
    int radius;
    //whether the interaction is triggered automatically
    bool automatic;
    //whether the component can currently be interacted with
    bool can_interact;
    //the text to show if not automatic
    std::shared_ptr<common::image_t> text;

    /**
     * Handle an sdl event
     * @param parent the component parent
     * @param event the sdl event
     */
    void handle_event(component_t& parent,
                      const SDL_Event& e) override;

    friend struct component_t;

    /**
     * The distance from the player
     * @param parent the parent of this component
     * @param x player x
     * @param y player y
     */
    void update_player_distance(component_t& parent, int x, int y);

  protected:

    /**
     * Load any resources for this component
     * Derived classes must call
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     */
    virtual void load(SDL_Renderer& renderer,
                      const component_t& parent) override;

    /**
     * Render this component (within radius)
     * Derived classes must call
     * @param renderer the sdl renderer
     * @param camera   the current camera
     */
    virtual void render(SDL_Renderer& renderer,
                        const SDL_Rect& camera) const override;

    /**
     * Called when the player interacts with this component
     * @param parent the parent
     */
    virtual void interact_entered(component_t& parent) = 0;

    /**
     * Called when the player leaves the interaction radius
     * @param parent the parent
     */
    virtual void interact_exited(component_t& parent) {}

  public:
    /**
     * Constructor
     * @param bounds the bounds of the component @see component_t
     * @param flags  attributes @see component_t
     * @param code the key that triggers the interaction
     * @param display_code the text to display for interaction
     * @param radius the distance from player that triggers the interaction
     * @param automatic the interaction is triggered by proximity
     */
    interactive_component_t(SDL_Rect bounds,
                            uint8_t flags,
                            SDL_Keycode code,
                            const std::string& display_code,
                            int radius,
                            bool automatic=false);
    interactive_component_t(const interactive_component_t&) = delete;
    interactive_component_t& operator=(const interactive_component_t&) = delete;
  };

}

#endif /*_DIVEBAR_COMMON_INTERACTIVE_COMPONENT_H*/
