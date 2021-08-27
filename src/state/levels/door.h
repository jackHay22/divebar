/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_LEVELS_DOOR_H
#define _DIVEBAR_STATE_LEVELS_DOOR_H

#include <SDL2/SDL.h>
#include "../../common/interactive_component.h"
#include "../../common/shared_resources.h"

namespace state {
namespace levels {

  /*
   * Defines a door between different areas
   */
  class door_t : public common::interactive_component_t {
  private:
    //the level to switch to
    int target_index;
    //the location to put the player x
    int target_px;
    //the location to put the player y
    int target_py;

    /**
     * Called when the player interacts with this door
     * @param parent the parent
     */
    void interact_entered(component_t& parent) override;

  public:
    /**
     * Constructor
     * @param position
     * @param target_index
     * @param target_px the location to put the player x
     * @param target_py the location to put the player y
     */
    door_t(SDL_Rect position,
           int target_index,
           int target_px,
           int target_py);
    door_t(const door_t&) = delete;
    door_t& operator=(door_t&) = delete;

  };

}}

#endif /*_DIVEBAR_STATE_LEVELS_DOOR_H*/
