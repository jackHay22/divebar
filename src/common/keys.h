/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_KEYS_H
#define _DIVEBAR_COMMON_KEYS_H

#include <SDL2/SDL.h>
#include <memory>
#include "component.h"
#include "image.h"
#include "shared_resources.h"

namespace common {

  /*
   *  Display a keyboard key prompt
   */
  class keys_t : public component_t {
  private:
    //the key to display
    char key;
    //the images for all keys
    std::shared_ptr<image_t> key_sheet;
    //the sample bounds from the key sheet
    SDL_Rect sample_bounds;

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
     * Render the key
     * @param renderer the sdl renderer
     * @param camera   the current camera
     */
    void render_fg(SDL_Renderer& renderer,
                   const SDL_Rect& camera) const override;

  public:
    /**
     * Default constructor
     * @param key the key to display
     */
    keys_t(char key);
    keys_t(const keys_t&) = delete;
    keys_t& operator=(const keys_t&) = delete;
  };

}

#endif /*_DIVEBAR_COMMON_KEYS_H*/
