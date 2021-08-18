/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_IMAGE_H
#define _DIVEBAR_COMMON_IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

namespace common {

  class image_t {
  private:
    //the texture
    SDL_Texture* texture = NULL;
    //the default sample bounds
    SDL_Rect default_sample_bounds;

  public:
    /**
     * Constructor
     */
    image_t() = delete;

    /**
     * Constructor takes the path to the resource
     * @param renderer the sdl renderer
     * @param path path to the resource
     */
    image_t(SDL_Renderer& renderer, const std::string& path);

    /**
     * Construct from a texture and dimensions
     * @param texture the texture (assumes ownership)
     * @param w       the texture width
     * @param h       the texture height
     */
    image_t(SDL_Texture *texture, unsigned int w, unsigned int h);

    image_t(const image_t& other);
    image_t& operator=(const image_t& other);

    //free the resource
    ~image_t();

    /**
     * Get the default sample bounds of the image
     * @return sample bounds
     */
    const SDL_Rect& default_bounds() const;

    /**
     * Render the image at some position
     * @param renderer      the sdl renderer
     * @param sample_bounds the bounds to sample from the image
     * @param render_bounds the region to render to
     * @param flipped       whether to flip the image
     */
    void render_copy(SDL_Renderer& renderer,
                     const SDL_Rect& sample_bounds,
                     const SDL_Rect& render_bounds,
                     bool flipped=false) const;
  };
}

#endif /*_DIVEBAR_COMMON_IMAGE_H*/
