/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_ACTIONS_IDLE_H
#define _DIVEBAR_STATE_ENTITY_ACTIONS_IDLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>
#include "../../../common/component.h"
#include "../../../common/animation.h"
#include "../../../common/shared_resources.h"
#include "action.h"

namespace state {
namespace entity {
namespace actions {

  /*
   * The idle state of an entity
   */
  class idle_t : public action_t {
  private:
    //the index of the animation
    size_t anim_child_idx;

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     * @param resources the shared global resources
     */
    void load(SDL_Renderer& renderer,
              const common::component_t& parent,
              common::shared_resources& resources) override;

    /**
     * Update the state
     */
    void update(common::component_t& parent) override;

  public:
    /**
     * Constructor
     * @param idle_anim the animation for the idle action
     */
    idle_t(std::unique_ptr<common::anim_t> idle_anim);
    idle_t(const idle_t&) = delete;
    idle_t& operator=(const idle_t&) = delete;
  };

}}}

#endif /*_DIVEBAR_STATE_ENTITY_ACTIONS_IDLE_H*/
