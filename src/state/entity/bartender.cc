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
      rem_idle_cycles(0),
      needs_reset(false),
      action_serve(0),
      action_walk(0),
      action_idle(0) {}

  /**
   * Constructor
   * @param position the position to trigger interaction from
   */
  bartender_t::serve_drink::serve_drink(SDL_Rect position)
    : common::interactive_component_t(
      position,
      COMPONENT_VISIBLE,
      SDLK_e, //unused
      16,
      true
    ) {}

  /**
   * Called when the player interacts with this game
   * @param parent the parent
   */
  void bartender_t::serve_drink::interact_entered(common::component_t& parent) {
    parent.get_as<bartender_t>().serve_drink_action();
  }

  /**
   * Called when the player leaves the interaction radius
   * @param parent the parent
   */
  void bartender_t::serve_drink::interact_exited(common::component_t& parent) {
    parent.get_as<bartender_t>().serve_drink_reset();
  }

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void bartender_t::load(SDL_Renderer& renderer,
                         const common::component_t& parent,
                         common::shared_resources& resources) {

    //load the animation sheet
    std::shared_ptr<common::image_t> anim_sheet =
      std::make_shared<common::image_t>(
      renderer, this->rsrc_path("animations/bartender.png")
    );

    //add serving anim
    action_serve = this->add_child(
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        0, 16, 3, true
      )
    );
    //add walking animation
    action_walk = this->add_child(
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        1, 7, 3, true
      )
    );
    //add idle anim
    action_idle = this->add_child(
      std::make_unique<common::anim_t>(
        anim_sheet, ANIM_W, ANIM_H,
        2, 12, 3
      )
    );

    //add interactive component
    this->add_child(std::make_unique<bartender_t::serve_drink>(
      this->get_bounds()
    ));

    //Set the starting action
    current_action = action_serve;

    //determine the duration of the idle cycle
    idle_cycle_duration = this->get_nth_child<common::anim_t>(action_idle).get_cycle_duration();
    rem_idle_cycles = idle_cycle_duration * IDLE_CYCLES;

    //load the action resources
    component_t::load_children(renderer,resources);
  }

  /**
   * Update the player
   */
  void bartender_t::update(common::component_t& parent) {
    if (this->get_nth_child<common::anim_t>(current_action).anim_complete()) {
      //update the current animation
      if (current_action == action_serve) {
        current_action = action_walk;
        //reset the animation
        this->get_nth_child<common::anim_t>(current_action).reset_animation();

      } else if (current_action == action_walk) {
        current_action = action_idle;
        //reset the animation
        this->get_nth_child<common::anim_t>(current_action).reset_animation();
      }
    }

    if ((current_action == action_idle) && working) {
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
    if (!working && !needs_reset) {
      //player will need to leave to trigger this again
      needs_reset = true;
      //switch to serving action
      current_action = action_serve;
      working = true;
      rem_idle_cycles = idle_cycle_duration * IDLE_CYCLES;

      //reset the serving action
      this->get_nth_child<common::anim_t>(current_action).reset_animation();
    }
  }

  /**
   * Player left, can reset
   */
  void bartender_t::serve_drink_reset() {
    needs_reset = false;
  }

}}
