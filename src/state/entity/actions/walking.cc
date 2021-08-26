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

  #define WALKING_ANIM  0
  #define CLIMBING_ANIM 1
  #define CLIMBING_DOWN_ANIM 2

  /**
   * Constructor
   * @param flat_anim the walking animation
   * @param up_anim the walking up animation
   * @param down_anim the walking down animation
   */
  walking_t::walking_t(std::unique_ptr<common::anim_t> flat_anim,
                       std::unique_ptr<common::anim_t> up_anim,
                       std::unique_ptr<common::anim_t> down_anim)
    : action_t(),
      walking_up(false),
      walking_down(false) {
    //add the animations as children of this component
    this->add_child(std::move(flat_anim));
    this->add_child(std::move(up_anim));
    this->add_child(std::move(down_anim));
  }

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void walking_t::load(SDL_Renderer& renderer,
                       const common::component_t& parent,
                       common::shared_resources& resources) {
    //load animation resources as necessary
    component_t::load_children(renderer,resources);

    //set size based on parent size
    const SDL_Rect& current_position = parent.get_bounds();
    this->set_size(current_position.w,current_position.h);
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
      //probe for opportunity to walk up/down
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

      //whether the level goes down next
      bool solid_down_front = grandparent->solid_at(
        x_probe,
        current_position.y + current_position.h + 1
      );

      //set the walking up flag
      walking_up = solid_infront && !solid_above && solid_below;
      if (!walking_up) {
        walking_down = !solid_infront && !solid_down_front && solid_below;

        if (walking_down) {
          //reset the walk down animation
          this->get_nth_child<common::anim_t>(CLIMBING_DOWN_ANIM).reset_animation();
        }
      } else {
        //reset the walk up animation
        this->get_nth_child<common::anim_t>(CLIMBING_ANIM).reset_animation();
      }
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

    //get the climbing animation
    const common::anim_t& climbing_anim = this->get_nth_child<common::anim_t>(CLIMBING_ANIM);

    //get the level to set the camera
    component_t *grandparent;
    if (parent.get_parent(&grandparent)) {
      //check if completed
      if (climbing_anim.anim_complete()) {
        walking_up = false;

        //this mutates current_position
        parent.set_position(
          facing_left ? (current_position.x - 8) : (current_position.x + 8),
          current_position.y - 8
        );

        if (parent.get_as<entity_t>().controls_camera()) {
          grandparent->get_as<levels::level_t>().center_camera(
            current_position.x,
            current_position.y
          );
        }

        //move the action position to match
        this->set_position(current_position.x, current_position.y);

      } else {
        int dx = facing_left ? -8 : 8;
        float progress = 1.0f - ((float) climbing_anim.cycle_duration_remaining() /
                                 (float) climbing_anim.get_cycle_duration());

        if (parent.get_as<entity_t>().controls_camera()) {
          //ease the camera
          grandparent->get_as<levels::level_t>().center_camera(
            current_position.x + (int)(dx * progress),
            current_position.y - (int)(8 * progress)
          );
        }
      }
    }
  }

  /**
   * Update if walking down something
   * @param parent      the parent component
   * @param facing_left whether the entity is facing left
   */
  void walking_t::descending_update(common::component_t& parent, bool facing_left) {
    //get the current position of the entity
    const SDL_Rect& current_position = parent.get_bounds();

    //get the climbing animation
    const common::anim_t& climbing_anim = this->get_nth_child<common::anim_t>(CLIMBING_DOWN_ANIM);

    //get the level to set the camera
    component_t *grandparent;
    if (parent.get_parent(&grandparent)) {
      if (climbing_anim.anim_complete()) {
        walking_down = false;

        //this mutates current_position
        parent.set_position(
          facing_left ? (current_position.x - 8) : (current_position.x + 8),
          current_position.y + 8
        );

        if (parent.get_as<entity_t>().controls_camera()) {
          grandparent->get_as<levels::level_t>().center_camera(
            current_position.x,
            current_position.y
          );
        }

        //move the action position to match
        this->set_position(current_position.x, current_position.y);

      } else {
        int dx = facing_left ? -8 : 8;
        float progress = 1.0f - ((float) climbing_anim.cycle_duration_remaining() /
                                 (float) climbing_anim.get_cycle_duration());

        if (parent.get_as<entity_t>().controls_camera()) {
          //ease the camera
          grandparent->get_as<levels::level_t>().center_camera(
            current_position.x + (int)(dx * progress),
            current_position.y + (int)(8 * progress)
          );
        }
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
    this->get_nth_child<common::anim_t>(walking_up ? CLIMBING_ANIM : (walking_down ? CLIMBING_DOWN_ANIM : WALKING_ANIM)).set_flipped(
      //flip the active animation based on the entity direction
      facing_left
    );

    //update based on walking type
    if (walking_up) {
      climbing_update(parent,facing_left);
      //check if switched
      if (!walking_up) {
        walking_update(parent,facing_left);
      }
    } else if (walking_down) {
      descending_update(parent,facing_left);
      //check if switched
      if (!walking_down) {
        walking_update(parent,facing_left);
      }
    } else {
      walking_update(parent,facing_left);
    }

    //update the current animation
    common::component_t::update_child(walking_up ? CLIMBING_ANIM : (walking_down ? CLIMBING_DOWN_ANIM : WALKING_ANIM));

    //lock the action if walking up (action can be preempted if not walking up)
    this->set_completed(!walking_up);
  }

  /**
   * Render this component
   * @param renderer the sdl renderer
   * @param camera   the current camera
   */
  void walking_t::render(SDL_Renderer& renderer,
                         const SDL_Rect& camera) const {
    //render the correct animation
    common::component_t::render_child(renderer,camera,
      walking_up ? CLIMBING_ANIM : (walking_down ? CLIMBING_DOWN_ANIM : WALKING_ANIM));
  }

}}}
