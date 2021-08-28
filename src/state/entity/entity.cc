/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "entity.h"
#include <memory>

namespace state {
namespace entity {

  /**
   * Constructor
   * @param position starting position
   * @param health starting health for the entity
   */
  entity_t::entity_t(SDL_Rect position, int health, uint8_t flags)
    : common::component_t(std::move(position), COMPONENT_VISIBLE |
                                               COMPONENT_COLLIDABLE |
                                               COMPONENT_GRAVITY | flags),
      health(health),
      attributes_idx(0),
      current_action(0),
      left(false) {
    //add the entity attributes
    attributes_idx = this->add_child(
      std::make_unique<entity_attributes_t>()
    );
  }

  /**
   * Update the state
   */
  void entity_t::update(common::component_t& parent) {
    //update the current action child
    common::component_t::update_child(current_action);
  }

  /**
   * Render the current state
   */
  void entity_t::render(SDL_Renderer& renderer,
                        const SDL_Rect& camera) const {
    // //TEMP
    // debug_render_bounds(renderer,camera);
    //render the current action child
    common::component_t::render_child(renderer,
                                      camera,
                                      current_action);
  }

  /**
   * Whether the entity is facing left
   * @return the orientation
   */
  bool entity_t::facing_left() const {
    return left;
  }

  /**
   * Get the current health of this entity
   * @return the current health of the entity
   */
  int entity_t::get_health() const {
    return health;
  }

  /**
   * Update the health of the entity
   * @param diff value to add to health
   */
  void entity_t::update_health(int diff) {
    health += diff;
  }

  /**
   * Get the attributes of this entity
   * @return entity attributes
   */
  entity_attributes_t& entity_t::get_attributes() {
    return this->get_nth_child<entity_attributes_t>(attributes_idx);
  }

}}
