/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "interactive_component.h"
#include "keys.h"
#include <math.h>

namespace common {

  /**
   * Constructor
   * @param bounds the bounds of the component @see component_t
   * @param flags  attributes @see component_t
   * @param code the key that triggers the interaction
   * @param radius the distance from player that triggers the interaction
   * @param automatic the interaction is triggered by proximity
   */
  interactive_component_t::interactive_component_t(SDL_Rect bounds,
                                                  uint8_t flags,
                                                  SDL_Keycode code,
                                                  int radius,
                                                  bool automatic)
    : component_t(std::move(bounds),flags),
      code(code),
      radius(radius),
      automatic(automatic),
      can_interact(false) {

    if (!automatic) {
      char key = 'E';
      if (code == SDLK_w) {
        key = 'W';
      } else if (code == SDLK_a) {
        key = 'A';
      } else if (code == SDLK_s) {
        key = 'S';
      } else if (code == SDLK_d) {
        key = 'D';
      }
      //add the key
      this->add_child(std::make_unique<keys_t>(key));
    }
  }

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void interactive_component_t::load(SDL_Renderer& renderer,
                                     const component_t& parent,
                                     shared_resources& resources) {
    component_t::load_children(renderer,resources);
  }

  /**
   * Handle an sdl event
   * @param parent the component parent
   * @param event the sdl event
   * @param player the player
   */
  void interactive_component_t::handle_event_player(component_t& parent,
                                                    const SDL_Event& e,
                                                    state::entity::player_t& player) {
    if ((e.type == SDL_KEYDOWN) && can_interact && !automatic && (e.key.keysym.sym == code)) {
      interact_entered(parent,player);
    }
  }

  /**
   * Render key when enabled
   * @param renderer the sdl renderer
   * @param camera   the current camera
   */
  void interactive_component_t::render_fg(SDL_Renderer& renderer,
                                          const SDL_Rect& camera) const {
    if (can_interact && !automatic) {
      component_t::render_fg(renderer,camera);
    }
  }

  /**
   * The distance from the player
   * @param parent the parent of this component
   * @param player the player
   */
  void interactive_component_t::update_player_distance(component_t& parent,
                                                       state::entity::player_t& player) {
    const SDL_Rect& curr_bounds = this->get_bounds();
    const SDL_Rect& player_bounds = player.get_bounds();

    bool prev = can_interact;
    //calculate distance
    can_interact = radius > sqrt(pow((player_bounds.x + (player_bounds.w / 2)) -
                                     (curr_bounds.x + (curr_bounds.w / 2)), 2) +
                                 pow((player_bounds.y + (player_bounds.h / 2)) -
                                     (curr_bounds.y + (curr_bounds.h / 2)), 2));

    if (!can_interact && prev) {
      interact_exited(parent,player);
    }

    //do interaction if set to automatic
    if (can_interact && automatic) {
      interact_entered(parent,player);
    }
  }

}
