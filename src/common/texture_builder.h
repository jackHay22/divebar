/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_TEXTURE_BUILDER_H
#define _DIVEBAR_COMMON_TEXTURE_BUILDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "image.h"

namespace common {

  //allows the construction of textures pixel by pixel
  class texture_builder_t {
  private:
    //buffer size
    unsigned int width;
    unsigned int height;

    //sdl surface
    SDL_Surface *surface;

    //the buffer of pixels
    uint32_t **buffer;

  public:
    /**
     * Constructor
     */
    texture_builder_t() = delete;

    /**
     * Constructor takes the path to the resource
     * @param w the width of the texture
     * @param h the height of the texture
     */
    texture_builder_t(unsigned int w, unsigned int h);

    texture_builder_t(const texture_builder_t&) = delete;
    texture_builder_t& operator=(const texture_builder_t&) = delete;

    /**
     * Destructor
     */
    ~texture_builder_t();

    /**
     * Set the pixel color at some position
     * @param x position x
     * @param y position y
     * @param r color channel r
     * @param g color channel g
     * @param b color channel b
     */
    void set_px_color(int x, int y,
                      unsigned int r,
                      unsigned int g,
                      unsigned int b);

    /**
     * Convert to an image
     * @param renderer the sdl renderer
     * @return the image
     */
    std::shared_ptr<common::image_t> to_image(SDL_Renderer& renderer);
  };
}

#endif /*_DIVEBAR_COMMON_TEXTURE_BUILDER_H*/
