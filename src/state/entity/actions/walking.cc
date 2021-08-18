/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "walking.h"
#include "../entity.h"

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
    : common::component_t({0,0,0,0}, COMPONENT_VISIBLE),
      walking_up(false) {
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
                       const common::component_t& parent) {}

  /**
   * Update the state
   */
  void walking_t::update(common::component_t& parent) {
    //check whether the parent is facing left
    bool facing_left = parent.get_as<entity_t>().facing_left();
    //change in x based on direction
    int dx = 1 + (-2 * facing_left);

    //get the current position of the entity
    const SDL_Rect& current_position = parent.get_bounds();

    //inherit the parents bounds and position based on dx
    this->set_position(current_position.x + dx, current_position.y);
    this->set_size(current_position.w,current_position.h);

    //update the parent's position based on change in x
    parent.set_position(current_position.x + dx, current_position.y);

    //update the current animation
    common::component_t::update_child(walking_up ? 1 : 0);

    //update the animation direction
    this->get_nth_child<common::anim_t>(walking_up ? 1 : 0).set_flipped(
      //flip the active animation based on the entity direction
      facing_left
    );

    //get the level to check if the entity can walk up something
    component_t *grandparent;
    if (parent.get_parent(&grandparent)) {
      //probe to see if the entity can walk up

    }
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
