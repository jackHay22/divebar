/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "pool_player.h"
#include "../../common/animation.h"

namespace state {
namespace entity {

  #define ANIM_W 48
  #define ANIM_H 24

  /**
   * Constructor
   * @param x position x
   * @param y position y
   */
  pool_player_t::pool_player_t(int x, int y)
    : entity_t({x,y,ANIM_W,ANIM_H},100),
      idle_updates_rem(0),
      idle_updates_total(0),
      action_shooting(0),
      action_waiting(0),
      action_prepare(0) {}

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void pool_player_t::load(SDL_Renderer& renderer,
                           const common::component_t& parent,
                           common::shared_resources& resources) {
    std::shared_ptr<common::image_t> anim_sheet =
      std::make_shared<common::image_t>(
      renderer, this->rsrc_path("animations/pool_player.png")
    );

    //add shooting anim
    action_shooting = this->add_child(
      //shooting anim
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        0, 12, 3, true
      )
    );
    //add idle anim
    action_waiting = this->add_child(
      //waiting anim
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        1, 4, 3
      )
    );
    //add prep anim
    action_prepare = this->add_child(
      //prep anim
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        2, 12, 3, true
      )
    );

    //set the current action
    current_action = action_waiting;

    //load the action resources
    component_t::load_children(renderer,resources);

    //determine the total cycles per idle
    idle_updates_total = this->get_nth_child<common::anim_t>(action_waiting).get_cycle_duration() * 3;
    idle_updates_rem = idle_updates_total;
  }

  /**
   * Update the player
   */
  void pool_player_t::update(common::component_t& parent) {
    if (current_action == action_waiting) {
      if (idle_updates_rem > 0) {
        idle_updates_rem--;
      } else {
        current_action = action_prepare;
        this->get_nth_child<common::anim_t>(current_action).reset_animation();
      }

    } else if (this->get_nth_child<common::anim_t>(current_action).anim_complete()) {

      if (current_action == action_shooting) {
        current_action = action_waiting;
        idle_updates_rem = idle_updates_total;

      } else if (current_action == action_prepare) {
        current_action = action_shooting;
      }

      this->get_nth_child<common::anim_t>(current_action).reset_animation();
    }

    //update current
    common::component_t::update_child(current_action);
  }

}}
