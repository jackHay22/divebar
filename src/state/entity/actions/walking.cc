/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "walking.h"
#include "../entity.h"
#include "../../levels/level.h"
#include <iostream>

namespace state {
namespace entity {
namespace actions {

  /**
   * Constructor
   * @param anim the walking animation
   * @param anim the walking up animation
   */
  walking_t::walking_t(std::unique_ptr<common::anim_t> flat_anim,
                       std::unique_ptr<common::anim_t> up_anim)
    : action_t(),
      walking_up(false),
      walking_up_frames_rem(0),
      walking_up_frames_total(0) {
    //add the animations as children of this component
    this->add_child(std::move(flat_anim));
    this->add_child(std::move(up_anim));
  }

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   */
  void walking_t::load(SDL_Renderer& renderer,
                       const common::component_t& parent) {
    component_t::load_children(renderer);

    //set size based on parent size
    const SDL_Rect& current_position = parent.get_bounds();
    this->set_size(current_position.w,current_position.h);

    //determine the length of the walking up animation
    walking_up_frames_total = this->get_nth_child<common::anim_t>(1).get_cycle_duration();
  }

  /**
   * Update if walking
   * @param parent the parent component
   * @param facing_left whether the player is facing left
   */
  void walking_t::walking_update(common::component_t& parent, bool facing_left) {
    //get the current position of the entity
    const SDL_Rect& current_position = parent.get_bounds();

    component_t *grandparent;
    if (parent.get_parent(&grandparent)) {
      //probe for opportunity to walk up
      //get the level to check if the entity can walk up something

      //x position to probe for based on direction facing
      int x_probe = facing_left ?
                      (current_position.x - 1) :
                      (current_position.x + current_position.w + 1);

      //check for solid ground below
      bool solid_below = grandparent->solid_at(
        current_position.x + (current_position.w / 2),
        current_position.y + current_position.h + 1
      );

      //solid in front of player
      bool solid_infront = grandparent->solid_at(
        x_probe,
        current_position.y + current_position.h - 1
      );

      //check for space above
      bool solid_above = grandparent->solid_at(
        x_probe,
        current_position.y + current_position.h - 9
      );

      //set the walking up flag
      walking_up = solid_infront && !solid_above && solid_below;
      //set the remaining frames
      walking_up_frames_rem = walking_up_frames_total - 1;

      //reset the walk up animation
      this->get_nth_child<common::anim_t>(1).reset_animation();
    }

    //if player not walking up, move forward
    if (!walking_up) {
      //change in x based on direction
      int dx = 1 + (-2 * facing_left);

      //inherit the parents bounds and position based on dx
      this->set_position(current_position.x + dx, current_position.y);

      //update the parent's position based on change in x
      parent.set_position(current_position.x + dx, current_position.y);
    }
  }

  /**
   * Update if walking up something
   * @param parent component
   * @param facing_left whether the player is facing left
   */
  void walking_t::climbing_update(common::component_t& parent, bool facing_left) {
    //get the current position of the entity
    const SDL_Rect& current_position = parent.get_bounds();

    walking_up_frames_rem--;

    //get the level to set the camera
    component_t *grandparent;
    if (parent.get_parent(&grandparent)) {
      //check if completed
      if (walking_up_frames_rem <= 0) {
        walking_up = false;
        //the new x position
        int new_x = facing_left ? (current_position.x - 8) : (current_position.x + 8);
        //move the player up
        this->set_position(new_x, current_position.y - 8);
        parent.set_position(new_x, current_position.y - 8);

        //TODO only do for player

        //update the camera position
        grandparent->get_as<levels::level_t>().center_camera(
          new_x, current_position.y - 8
        );

      } else {

        //TODO only do this for the player

        int dx = facing_left ? -8 : 8;
        float progress = 1.0f - ((float) walking_up_frames_rem / (float) walking_up_frames_total);
        //ease the camera
        grandparent->get_as<levels::level_t>().center_camera(
          current_position.x + (int)(dx * progress),
          current_position.y - (int)(8 * progress)
        );
      }
    }
  }

  /**
   * Update the state
   */
  void walking_t::update(common::component_t& parent) {
    //check whether the parent is facing left
    bool facing_left = parent.get_as<entity_t>().facing_left();
    //update the animation direction
    this->get_nth_child<common::anim_t>(walking_up ? 1 : 0).set_flipped(
      //flip the active animation based on the entity direction
      facing_left
    );

    //update based on walking type
    if (walking_up) {
      climbing_update(parent,facing_left);
    } else {
      walking_update(parent,facing_left);
    }

    //lock the action if walking up (action can be preempted if not walking up)
    this->set_completed(!walking_up);

    //update the current animation
    common::component_t::update_child(walking_up ? 1 : 0);
  }

  /**
   * Render this component
   * @param renderer the sdl renderer
   * @param camera   the current camera
   */
  void walking_t::render(SDL_Renderer& renderer,
                         const SDL_Rect& camera) const {
    //render the correct animation
    common::component_t::render_child(renderer,camera,walking_up ? 1 : 0);
  }

}}}
