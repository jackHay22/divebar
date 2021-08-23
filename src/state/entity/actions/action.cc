/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "action.h"

namespace state {
namespace entity {
namespace actions {

  #define ACTION_COMPLETE   0x80 // the action can be switched out

  /**
   * Constructor
   */
  action_t::action_t()
    : common::component_t({0,0,0,0}, COMPONENT_VISIBLE),
      flags(0) {}

  /**
   * Set the action completed
   * @param completed whether the action is complete
   * and should be switched out
   */
  void action_t::set_completed(bool completed) {
    if (completed) {
      flags |= ACTION_COMPLETE;
    } else {
      flags &= ~ACTION_COMPLETE;
    }
  }

  /**
   * Whether the action is completed
   * @return the completed flag
   */
  bool action_t::action_completed() const {
    return flags & ACTION_COMPLETE;
  }
}}}
