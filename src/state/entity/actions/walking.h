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
#include "../../../common/shared_resources.h"
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
    //whether this entity is walking down
    bool walking_down;

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
     * Update if walking
     * @param parent parent component
     * @param facing_left whether the player is facing left
     */
    void walking_update(common::component_t& parent, bool facing_left);

    /**
     * Update if walking up something
     * @param parent parent component
     * @param facing_left whether the player is facing left
     */
    void climbing_update(common::component_t& parent, bool facing_left);

    /**
     * Update if walking down something
     * @param parent      the parent component
     * @param facing_left whether the entity is facing left
     */
    void descending_update(common::component_t& parent, bool facing_left);

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
     * @param flat_anim the walking animation
     * @param up_anim the walking up animation
     * @param down_anim the walking down animation
     */
    walking_t(std::unique_ptr<common::anim_t> flat_anim,
              std::unique_ptr<common::anim_t> up_anim,
              std::unique_ptr<common::anim_t> down_anim);
    walking_t(const walking_t&) = delete;
    walking_t& operator=(const walking_t&) = delete;
  };

}}}

#endif /*_DIVEBAR_STATE_ENTITY_ACTIONS_WALKING_H*/
