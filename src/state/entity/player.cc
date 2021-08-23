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

  #define ACTION_IDLE 0
  #define ACTION_WALKING 1

  /**
   * Constructor
   * @param position starting position for the player
   * @param anim_sheet the animations used by the player
   */
  player_t::player_t(SDL_Rect position,
                     std::shared_ptr<common::image_t> anim_sheet)
    : entity_t(position,100),
      anim_sheet(anim_sheet) {}

  /**
   * Load actions for the player
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   */
  void player_t::load(SDL_Renderer& renderer,
                      const component_t& parent) {
    //add idle action
    this->add_child(
      std::make_unique<actions::idle_t>(
        //the idle animation
        std::make_unique<common::anim_t>(
          anim_sheet, 32,48, 0, 12, 2
        )
      )
    );
    //add walking action
    this->add_child(
      std::make_unique<actions::walking_t>(
        //the walking flat animation
        std::make_unique<common::anim_t>(
          anim_sheet, 32,48, 1, 8, 2
        ),
        //the walking up animation
        std::make_unique<common::anim_t>(
          anim_sheet, 32,48, 2, 11, 2
        )
      )
    );
    //load the action resources
    component_t::load_children(renderer);
  }

  /**
   * Handle input events, delegate to action
   * @param parent the component parent
   * @param event the sdl event
   */
  void player_t::handle_event(component_t& parent,
                              const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {

    }
  }

}}
