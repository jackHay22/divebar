/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "interactive_component.h"
#include "text.h"
#include <math.h>

namespace common {

  /**
   * Constructor
   * @param bounds the bounds of the component @see component_t
   * @param flags  attributes @see component_t
   * @param code the key that triggers the interaction
   * @param display_code the text to display for interaction
   * @param radius the distance from player that triggers the interaction
   * @param automatic the interaction is triggered by proximity
   */
  interactive_component_t::interactive_component_t(SDL_Rect bounds,
                                                   uint8_t flags,
                                                   SDL_Keycode code,
                                                   const std::string& display_code,
                                                   int radius,
                                                   bool automatic)
    : component_t(std::move(bounds),flags),
      code(code),
      display_code(display_code),
      radius(radius),
      automatic(automatic),
      can_interact(false) {}

  /**
   * Load any resources for this component
   * Derived classes must call
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   */
  void interactive_component_t::load(SDL_Renderer& renderer,
                                     const component_t& parent) {
    //load the text for the code
    if (!automatic) {
     text = common::image_from_text(display_code, renderer, 255, 255, 255);
    }
  }

  /**
   * Render this component (within radius)
   * @param renderer the sdl renderer
   * @param camera   the current camera
   */
  void interactive_component_t::render(SDL_Renderer& renderer,
                                       const SDL_Rect& camera) const {
    if (can_interact && !automatic && text) {
      const SDL_Rect& curr_bounds = this->get_bounds();
      const SDL_Rect& sample_bounds = text->default_bounds();
      SDL_Rect render_bounds = {
        curr_bounds.x - camera.x,
        curr_bounds.y - camera.y,
        sample_bounds.w, sample_bounds.h
      };
      //render the image
      text->render_copy(renderer,
                        sample_bounds,
                        render_bounds);
    }
  }

  /**
   * Handle an sdl event
   * @param parent the component parent
   * @param event the sdl event
   */
  void interactive_component_t::handle_event(component_t& parent,
                                             const SDL_Event& e) {
    if ((e.type == SDL_KEYDOWN) && can_interact && !automatic && (e.key.keysym.sym == code)) {
      interact_entered(parent);
    }
  }

  /**
   * The distance from the player
   * @param parent the parent of this component
   * @param x player x
   * @param y player y
   */
  void interactive_component_t::update_player_distance(component_t& parent, int x, int y) {
    const SDL_Rect& curr_bounds = this->get_bounds();

    bool prev = can_interact;
    //calculate distance
    can_interact = radius > sqrt(pow(x - (curr_bounds.x + (curr_bounds.w / 2)), 2) +
                                 pow(y - (curr_bounds.y + (curr_bounds.h / 2)), 2));

    if (!can_interact && prev) {
      interact_exited(parent);
    }

    //do interaction if set to automatic
    if (can_interact && automatic) {
      interact_entered(parent);
    }
  }

}
