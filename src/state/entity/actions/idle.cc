/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "idle.h"
#include "../entity.h"

namespace state {
namespace entity {
namespace actions {

  /**
   * Constructor
   * @param idle_anim the animation for the idle action
   */
  idle_t::idle_t(std::unique_ptr<common::anim_t> idle_anim)
    : action_t(),
      anim_child_idx(0) {
    anim_child_idx = this->add_child(std::move(idle_anim));
  }

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void idle_t::load(SDL_Renderer& renderer,
                    const common::component_t& parent,
                    common::shared_resources& resources) {
    this->set_completed(true); //can always toggle action off
    component_t::load_children(renderer,resources);
  }

  /**
   * Update the state
   */
  void idle_t::update(common::component_t& parent) {
    //get the current position of the entity
    const SDL_Rect& current_position = parent.get_bounds();
    //inherit the parents bounds and position based on dx
    this->set_position(current_position.x,current_position.y);
    this->set_size(current_position.w,current_position.h);

    //update the current animation
    common::component_t::update(parent);

    //update the animation direction
    this->get_nth_child<common::anim_t>(anim_child_idx).set_flipped(
      //flip the active animation based on the entity direction
      parent.get_as<entity_t>().facing_left()
    );
  }

}}}
