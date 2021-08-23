/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "entity.h"

namespace state {
namespace entity {

  /**
   * Constructor
   * @param position starting position
   * @param health starting health for the entity
   */
  entity_t::entity_t(SDL_Rect position, int health)
    : common::component_t(std::move(position), COMPONENT_VISIBLE |
                                               COMPONENT_COLLIDABLE |
                                               COMPONENT_GRAVITY),
      health(health),
      left(false),
      current_action(0) {}

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
    //TEMP
    debug_render_bounds(renderer,camera);
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

}}
