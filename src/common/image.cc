/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "image.h"
#include "launch_exception.h"

namespace common {

  /**
   * Constructor takes the path to the resource
   * @param renderer the sdl renderer
   * @param path path to the resource
   */
  image_t::image_t(SDL_Renderer& renderer, const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
      //failed to load
      throw launch_exception("failed to load image: " + path);
    }

    //load to texture
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0,0xFF,0xFF));

    //use pixels to create texture
    this->texture = SDL_CreateTextureFromSurface(&renderer,surface);

    if (this->texture == NULL) {
      //throw an exception with sdl error detail
      throw launch_exception("could not create texture: " + std::string(SDL_GetError()));
    }

    //set the sample bounds
    this->default_sample_bounds = {0,0,surface->w,surface->h};

    //free surface
    SDL_FreeSurface(surface);
  }

  /**
   * Construct from a texture and dimensions
   * @param texture the texture (assumes ownership)
   * @param w       the texture width
   * @param h       the texture height
   */
  image_t::image_t(SDL_Texture *texture, unsigned int w, unsigned int h)
    : texture(texture),
      default_sample_bounds{0,0,(int)w,(int)h} {}

  /**
   * Copy constructor
   * @param other [description]
   */
  image_t::image_t(const image_t& other)
    : texture(other.texture),
      default_sample_bounds(other.default_sample_bounds) {}

  /**
   * Assignment operator
   */
  image_t& image_t::operator=(const image_t& other) {
    this->texture = other.texture;
    this->default_sample_bounds = other.default_sample_bounds;
    return *this;
  }

  //free the resource
  image_t::~image_t() {
    SDL_DestroyTexture(this->texture);
  }

  /**
   * Get the default sample bounds of the image
   * @return sample bounds
   */
  const SDL_Rect& image_t::default_bounds() const {
    return default_sample_bounds;
  }

  /**
   * Render the image at some position
   * @param renderer      the sdl renderer
   * @param sample_bounds the bounds to sample from the image
   * @param render_bounds the region to render to
   * @param flipped       whether to flip the image
   */
  void image_t::render_copy(SDL_Renderer& renderer,
                            const SDL_Rect& sample_bounds,
                            const SDL_Rect& render_bounds,
                            bool flipped) const {
    if (flipped) {
      SDL_RenderCopyEx(&renderer,
                       this->texture,
                       &sample_bounds,
                       &render_bounds,
                       0, NULL,
                       SDL_FLIP_HORIZONTAL);
    } else {
      SDL_RenderCopy(&renderer,
                     this->texture,
                     &sample_bounds,
                     &render_bounds);
    }
  }
}
