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
#include "level.h"

namespace state {
namespace levels {

  /*
   * Divebar level map
   */
  class dive_bar_t : public level_t {
  private:

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
     */
    dive_bar_t();
    dive_bar_t(const dive_bar_t&) = delete;
    dive_bar_t& operator=(const dive_bar_t&) = delete;
  };

}}

#endif /*_DIVEBAR_STATE_LEVELS_DIVEBAR_H*/
