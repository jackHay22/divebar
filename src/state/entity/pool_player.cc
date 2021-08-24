/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "pool_player.h"
#include "../../common/animation.h"

namespace state {
namespace entity {

  #define ACTION_SHOOTING 0
  #define ACTION_WAITING  1
  #define ACTION_PREPARE  2

  #define ANIM_W 48
  #define ANIM_H 24

  /**
   * Constructor
   * @param x position x
   * @param y position y
   */
  pool_player_t::pool_player_t(int x, int y)
    : entity_t({x,y,ANIM_W,ANIM_H},100),
      rem_frames(0),
      shooting_frames_total(0),
      idle_frames_total(0),
      prep_frames_total(0) {}

  /**
   * Load resources for the entity
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   */
  void pool_player_t::load(SDL_Renderer& renderer,
            const component_t& parent) {
    std::shared_ptr<common::image_t> anim_sheet =
      std::make_shared<common::image_t>(
      renderer, this->rsrc_path("animations/pool_player.png")
    );

    //add shotting anim
    this->add_child(
      //shooting anim
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        ACTION_SHOOTING, 12, 3, true
      )
    );
    //add idle anim
    this->add_child(
      //shooting anim
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        ACTION_WAITING, 4, 3
      )
    );
    //add prep anim
    this->add_child(
      //shooting anim
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        ACTION_PREPARE, 12, 3, true
      )
    );
    //load the action resources
    component_t::load_children(renderer);

    //set the total frames for each
    shooting_frames_total = this->get_nth_child<common::anim_t>(ACTION_SHOOTING).get_cycle_duration();
    idle_frames_total = this->get_nth_child<common::anim_t>(ACTION_WAITING).get_cycle_duration();
    prep_frames_total = this->get_nth_child<common::anim_t>(ACTION_PREPARE).get_cycle_duration();

    //calculate the total frames for shooting anim
    rem_frames = shooting_frames_total;
  }

  /**
   * Update the player
   */
  void pool_player_t::update(common::component_t& parent) {
    rem_frames--;

    if (rem_frames < 0) {
      if (current_action == ACTION_SHOOTING) {
        current_action = ACTION_WAITING;
        rem_frames = 3 * idle_frames_total;
      } else if (current_action == ACTION_WAITING) {
        current_action = ACTION_PREPARE;
        rem_frames = prep_frames_total;
      } else if (current_action == ACTION_PREPARE) {
        current_action = ACTION_SHOOTING;
        rem_frames = shooting_frames_total;
      }
      this->get_nth_child<common::anim_t>(current_action).reset_animation();
    }

    //update current
    common::component_t::update_child(current_action);
  }

}}
