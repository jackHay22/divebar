/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "door.h"
#include "../../common/component.h"
#include "../level_manager.h"
#include "level.h"

namespace state {
namespace levels {

  /**
   * Constructor
   * @param position
   * @param target_index
   * @param target_px the location to put the player x
   * @param target_py the location to put the player y
   */
  door_t::door_t(SDL_Rect position,
                 int target_index,
                 int target_px,
                 int target_py)
    : common::interactive_component_t(
        position,
        COMPONENT_VISIBLE,
        SDLK_e, 8
      ),
      target_index(target_index),
      target_px(target_px),
      target_py(target_py) {}

   /**
    * Called when the player interacts with this door
    * @param parent the parent
    */
   void door_t::interact_entered(component_t& parent) {
     //get the player attributes to switch over
     const entity::entity_attributes_t& attrs = parent.get_as<level_t>().get_player_attrs();

     component_t *grandparent;
     if (parent.get_parent(&grandparent)) {

       //switch level
       grandparent->get_as<level_manager_t>().switch_level(
         target_index,
          target_px,
          target_py,
          attrs
       );
     }
   }

}}
