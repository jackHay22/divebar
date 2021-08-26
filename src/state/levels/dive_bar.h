/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_LEVELS_DIVEBAR_H
#define _DIVEBAR_STATE_LEVELS_DIVEBAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../common/component.h"
#include "../../common/image.h"
#include "level.h"

namespace state {
namespace levels {

  /*
   * Divebar level map
   */
  class dive_bar_t : public level_t {
  private:
    //Since the player can move between levels we share the image resource
    std::shared_ptr<common::image_t> player_anim_sheet;

    //the index of the player (as a child)
    int player_idx;

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
     * Optionally handle an sdl event
     * @param parent the component parent
     * @param event the sdl event
     */
    void handle_event(common::component_t& parent,
                      const SDL_Event& e) override;

  public:
    /**
     * Default constructor
     * @param player_anim_sheet the shared animations user by the player
     * (Since the player can move between levels we share the image resource)
     */
    dive_bar_t(std::shared_ptr<common::image_t> player_anim_sheet);
    dive_bar_t(const dive_bar_t&) = delete;
    dive_bar_t& operator=(const dive_bar_t&) = delete;
  };

}}

#endif /*_DIVEBAR_STATE_LEVELS_DIVEBAR_H*/
