/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_ACTIONS_WALKING_H
#define _DIVEBAR_STATE_ENTITY_ACTIONS_WALKING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>
#include "../../../common/component.h"
#include "../../../common/animation.h"
#include "action.h"

namespace state {
namespace entity {
namespace actions {

  /*
   * A walking state for an entity
   */
  class walking_t : public action_t {
  private:
    //whether this entity is walking up
    bool walking_up;

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     */
    void load(SDL_Renderer& renderer,
              const common::component_t& parent) override;

    /**
     * Update the state
     */
    void update(common::component_t& parent) override;

    /**
     * Render this component
     * @param renderer the sdl renderer
     * @param camera   the current camera
     */
    void render(SDL_Renderer& renderer,
                const SDL_Rect& camera) const override;

  public:
    /**
     * Constructor
     * @param anim the walking animation
     * @param anim the walking up animation
     */
    walking_t(std::unique_ptr<common::anim_t> flat_anim,
              std::unique_ptr<common::anim_t> up_anim);
    walking_t(const walking_t&) = delete;
    walking_t& operator=(const walking_t&) = delete;
  };

}}}

#endif /*_DIVEBAR_STATE_ENTITY_ACTIONS_WALKING_H*/
