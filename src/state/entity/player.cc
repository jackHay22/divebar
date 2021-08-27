/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "player.h"
#include "../../common/animation.h"
#include "../../common/image.h"
#include "actions/idle.h"
#include "actions/walking.h"

namespace state {
namespace entity {

  /**
   * Constructor
   * @param position starting position for the player
   */
  player_t::player_t(SDL_Rect position)
    : entity_t(position,100),
      next_action(-1),
      next_direction(false),
      action_idle(0),
      action_walking(0) {}

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void player_t::load(SDL_Renderer& renderer,
                      const common::component_t& parent,
                      common::shared_resources& resources) {
    //add idle action
    action_idle = this->add_child(
      std::make_unique<actions::idle_t>(
        //the idle animation
        std::make_unique<common::anim_t>(
          resources.player_image, 32,48, 0, 12, 3
        )
      )
    );

    //set the current action to idle
    current_action = action_idle;

    //add walking action
    action_walking = this->add_child(
      std::make_unique<actions::walking_t>(
        //the walking flat animation
        std::make_unique<common::anim_t>(
          resources.player_image, 32,48, 1, 8, 2
        ),
        //the walking up animation
        std::make_unique<common::anim_t>(
          resources.player_image, 32,48, 2, 11, 2, true
        ),
        //the walking down animation
        std::make_unique<common::anim_t>(
          resources.player_image, 32,48, 3, 11, 2, true
        )
      )
    );
    //load the action resources
    component_t::load_children(renderer,resources);
  }

  /**
   * Update the player
   */
  void player_t::update(common::component_t& parent) {
    //get the current action
    actions::action_t& action = this->get_nth_child<actions::action_t>(current_action);

    if ((next_action != -1) && action.action_completed()) {
      current_action = next_action;
      left = next_direction;
      //clear
      next_action = -1;
    }

    //TODO if not on solid ground switch action

    //update the current action
    common::component_t::update_child(current_action);
  }

  /**
   * Handle input events, delegate to action
   * @param parent the component parent
   * @param event the sdl event
   */
  void player_t::handle_event(component_t& parent,
                              const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_a:
          next_action = action_walking;
          next_direction = true;
          break;
        case SDLK_d:
          next_action = action_walking;
          next_direction = false;
          break;
      }

    } else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
        case SDLK_a:
          //stop walking once cycle complete
          next_action = action_idle;
          break;
        case SDLK_d:
          //stop walking once cycle complete
          next_action = action_idle;
          break;
      }
    }
  }

}}
