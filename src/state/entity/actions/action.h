/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_ACTIONS_ACTION_H
#define _DIVEBAR_STATE_ENTITY_ACTIONS_ACTION_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include "../../../common/component.h"

namespace state {
namespace entity {
namespace actions {

  /*
   * Abstract action type
   */
  class action_t : public common::component_t {
  private:
    //flags on this action
    uint8_t flags;

  protected:
    
    /**
     * Set the action completed
     * @param completed whether the action is complete
     * and should be switched out
     */
    void set_completed(bool completed);

  public:
    /**
     * Constructor
     */
    action_t();
    action_t(const action_t&) = delete;
    action_t& operator=(const action_t&) = delete;

    /**
     * Whether the action is completed
     * @return the completed flag
     */
    bool action_completed() const;
  };

}}}

#endif /*_DIVEBAR_STATE_ENTITY_ACTIONS_ACTION_H*/
