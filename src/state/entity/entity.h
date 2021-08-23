/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_ENTITY_H
#define _DIVEBAR_STATE_ENTITY_ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../common/component.h"

namespace state {
namespace entity {

  /*
   * Abstract entity
   * Note: abstract since it doesn't load any actions
   * and load must be defined
   */
  class entity_t : public common::component_t {
  private:
    //the health of the entity
    int health;
    //whether the entity is facing left
    bool left;

    /**
     * Update the state
     */
    void update(common::component_t& parent) override;

    /**
     * Render the current state
     */
    void render(SDL_Renderer& renderer,
                const SDL_Rect& camera) const override;

  protected:
    //the current action of the entity
    size_t current_action;

  public:
    /**
     * Constructor
     * @param position starting position
     * @param health starting health for the entity
     */
    entity_t(SDL_Rect position, int health);
    entity_t(const entity_t&) = delete;
    entity_t& operator=(const entity_t&) = delete;

    /**
     * Whether the entity is facing left
     * @return the orientation
     */
    bool facing_left() const;

    /**
     * Get the current health of this entity
     * @return the current health of the entity
     */
    int get_health() const;

    /**
     * Update the health of the entity
     * @param diff value to add to health
     */
    void update_health(int diff);
  };

}}

#endif /*_DIVEBAR_STATE_ENTITY_ENTITY_H*/
