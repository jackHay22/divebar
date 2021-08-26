/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "bartender.h"
#include <memory>
#include "../../common/animation.h"

namespace state {
namespace entity {

  #define ACTION_SERVE 0
  #define ACTION_WALK 1
  #define ACTION_IDLE 2
  #define ANIM_W 40
  #define ANIM_H 32
  #define IDLE_CYCLES 3

  /**
   * Constructor
   * @param x position x
   * @param y position y
   */
  bartender_t::bartender_t(int x, int y)
    : entity_t({x,y,ANIM_W,ANIM_H},100),
      working(false),
      idle_cycle_duration(0),
      rem_idle_cycles(0) {}

  /**
   * Constructor
   * @param position the position to trigger interaction from
   */
  bartender_t::serve_drink::serve_drink(SDL_Rect position)
    : common::interactive_component_t(
      position,
      COMPONENT_ALWAYS_VISIBLE,
      SDLK_e, //unused
      "",
      16,
      true
    ) {}

  /**
   * Serve drink interaction triggered by player proximity
   * @param parent the parent
   */
  void bartender_t::serve_drink::interact(common::component_t& parent) {
    parent.get_as<bartender_t>().serve_drink_action();
  }

  /**
   * Load resources for the entity
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   */
  void bartender_t::load(SDL_Renderer& renderer,
                         const component_t& parent) {

    //load the animation sheet
    std::shared_ptr<common::image_t> anim_sheet =
      std::make_shared<common::image_t>(
      renderer, this->rsrc_path("animations/bartender.png")
    );

    //add serving anim
    this->add_child(
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        ACTION_SERVE, 16, 3, true
      )
    );
    //add walking animation
    this->add_child(
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        ACTION_WALK, 7, 3, true
      )
    );
    //add idle anim
    this->add_child(
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        ACTION_IDLE, 12, 3
      )
    );

    //add interactive component
    this->add_child(std::make_unique<bartender_t::serve_drink>(
      this->get_bounds()
    ));

    //Set the starting action
    current_action = ACTION_SERVE;

    //determine the duration of the idle cycle
    idle_cycle_duration = this->get_nth_child<common::anim_t>(ACTION_IDLE).get_cycle_duration();
    rem_idle_cycles = idle_cycle_duration * IDLE_CYCLES;

    //load the action resources
    component_t::load_children(renderer);
  }

  /**
   * Update the player
   */
  void bartender_t::update(common::component_t& parent) {
    if (this->get_nth_child<common::anim_t>(current_action).anim_complete()) {
      //update the current animation
      if (current_action == ACTION_SERVE) {
        current_action = ACTION_WALK;
        //reset the animation
        this->get_nth_child<common::anim_t>(current_action).reset_animation();

      } else if (current_action == ACTION_WALK) {
        current_action = ACTION_IDLE;
        //reset the animation
        this->get_nth_child<common::anim_t>(current_action).reset_animation();
      }
    }

    if ((current_action == ACTION_IDLE) && working) {
      rem_idle_cycles--;
      working = rem_idle_cycles > 0;
    }

    //update current
    common::component_t::update_child(current_action);
  }

  /**
   * Bartender goes to the taps
   */
  void bartender_t::serve_drink_action() {
    if (!working) {
      //switch to serving action
      current_action = ACTION_SERVE;
      working = true;
      rem_idle_cycles = idle_cycle_duration * IDLE_CYCLES;

      //reset the serving action
      this->get_nth_child<common::anim_t>(current_action).reset_animation();
    }
  }

}}
