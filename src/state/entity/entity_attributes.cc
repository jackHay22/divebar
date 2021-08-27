/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "entity_attributes.h"

namespace state {
namespace entity {

  /**
   * Constructor
   * @param position starting position
   * @param health starting health for the entity
   */
  entity_attributes_t::entity_attributes_t()
    : common::component_t({0,0,0,0}, 0) {}

  /**
   * Update these attributes based on others
   * @param other the other attributes
   */
  void entity_attributes_t::update(const entity_attributes_t& other) {
    //TODO
  }

}}
