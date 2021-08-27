/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_ENTITY_ATTRIBUTES_H
#define _DIVEBAR_STATE_ENTITY_ENTITY_ATTRIBUTES_H

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
  class entity_attributes_t : public common::component_t {
  private:
    //TODO the attributes

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     * @param resources the shared global resources
     */
    void load(SDL_Renderer& renderer,
              const common::component_t& parent,
              common::shared_resources& resources) override {}

  public:
    /**
     * Constructor
     * @param position starting position
     * @param health starting health for the entity
     */
    entity_attributes_t();
    entity_attributes_t(const entity_attributes_t&) = delete;
    entity_attributes_t& operator=(const entity_attributes_t&) = delete;

    /**
     * Update these attributes based on others
     * @param other the other attributes
     */
    void update(const entity_attributes_t& other);
  };

}}

#endif /*_DIVEBAR_STATE_ENTITY_ENTITY_ATTRIBUTES_H*/
