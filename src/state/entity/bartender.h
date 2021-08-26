/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_ENTITY_BARTENDER_H
#define _DIVEBAR_STATE_ENTITY_BARTENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../common/component.h"
#include "../../common/interactive_component.h"
#include "../../common/image.h"
#include "entity.h"

namespace state {
namespace entity {

  /*
   * The bartender
   */
  class bartender_t : public entity_t {
  private:
    //whether the serving cycle has started
    bool working;
    //the duration of the idle cycle
    int idle_cycle_duration;
    //cool off period after working
    int rem_idle_cycles;

    //interactive component
    class serve_drink : public common::interactive_component_t {
    private:
      /**
       * Called when the player interacts with this game
       * @param parent the parent
       */
      void interact(common::component_t& parent) override;
    public:

      /**
       * Constructor
       * @param position the position to trigger interaction from
       */
      serve_drink(SDL_Rect position);
    };

    /**
     * Load resources for the entity
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     */
    void load(SDL_Renderer& renderer,
              const common::component_t& parent) override;

    /**
     * Update the player
     */
    void update(common::component_t& parent) override;

  public:
    /**
     * Constructor
     * @param x position x
     * @param y position y
     */
    bartender_t(int x, int y);
    bartender_t(const bartender_t&) = delete;
    bartender_t& operator=(const bartender_t&) = delete;

    /**
     * Bartender goes to the taps
     */
    void serve_drink_action();
  };

}}

#endif /*_DIVEBAR_STATE_ENTITY_BARTENDER_H*/
