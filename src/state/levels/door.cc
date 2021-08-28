/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "door.h"
#include "../../common/component.h"
#include "../level_manager.h"
#include "level.h"
#include <memory>
#include <iostream>

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
    : common::component_t(
        std::move(position),
        COMPONENT_VISIBLE | COMPONENT_INTERACTIVE,
        SDLK_w
      ),
      target_index(target_index),
      target_px(target_px),
      target_py(target_py) {}

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     * @param resources the shared global resources
     */
    void door_t::load(SDL_Renderer& renderer,
                      const common::component_t& parent,
                      common::shared_resources& resources) {
      //load key (added automatically)
      component_t::load_children(renderer,resources);
    }

   /**
    * Called when the player interacts with this door
    * @param parent the parent
    * @param player the player
    */
   void door_t::interact_entered(component_t& parent,
                                 state::entity::player_t& player) {

     //TODO animate player leaving or something

     component_t *grandparent;
     if (parent.get_parent(&grandparent)) {

       //switch level
       grandparent->get_as<level_manager_t>().switch_level(
         target_index,
          target_px,
          target_py,
          player.get_attributes()
       );
     }
   }

}}
