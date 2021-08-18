/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "texture_builder.h"
#include "launch_exception.h"

namespace common {

  #define ALPHA_CHAN 255

  /**
   * Constructor takes the path to the resource
   * @param w the width of the texture
   * @param h the height of the texture
   */
  texture_builder_t::texture_builder_t(unsigned int w, unsigned int h)
    : width(w),
      height(h){
    //r, g, b, alpha masks
    Uint32 rmask, gmask, bmask, amask;

    //https://wiki.libsdl.org/SDL_CreateRGBSurface

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    //create the surface (adjust height based on the min y, min x values, number of animation frames)
    surface = SDL_CreateRGBSurface(0,
                                   this->width,
                                   this->height,
                                   32,
                                   rmask,
                                   gmask,
                                   bmask,
                                   amask);
    if (surface == NULL) {
      throw launch_exception("failed to create surface for texture builder");
    }

    //allocate buffer space
    this->buffer = (uint32_t**) malloc(sizeof(uint32_t*) * height);
    for (unsigned int i=0; i<height; i++) {
      this->buffer[i] = (uint32_t*) malloc(sizeof(uint32_t) * width);

      //note: representing pure black as empty
      memset(this->buffer[i],0,sizeof(uint32_t) * width);
    }
  }

  /**
   * Destructor
   */
  texture_builder_t::~texture_builder_t() {
    //free the buffer
    for (unsigned int i=0; i<this->height; i++) {
      free(this->buffer[i]);
    }
    free(this->buffer);
    SDL_FreeSurface(this->surface);
  }

  /**
   * Set the pixel color at some position
   * @param x position x
   * @param y position y
   * @param r color channel r
   * @param g color channel g
   * @param b color channel b
   */
  void texture_builder_t::set_px_color(int x, int y,
                                       unsigned int r,
                                       unsigned int g,
                                       unsigned int b) {
    this->buffer[y][x] = SDL_MapRGBA(surface->format,r,g,b,ALPHA_CHAN);
  }

  /**
   * Convert to an image
   * @param renderer the sdl renderer
   * @return the image
   */
  std::shared_ptr<common::image_t> texture_builder_t::to_image(SDL_Renderer& renderer) {
    SDL_LockSurface(this->surface);

    //set pixels
    for (unsigned int y=0; y<this->height; y++) {
      for (unsigned int x=0; x<this->width; x++) {

        if (this->buffer[y][x]) {
          uint8_t *surface_pixel = (uint8_t*)this->surface->pixels;
          surface_pixel += (y * this->surface->pitch) +
                           (x * sizeof(uint32_t));
          *((uint32_t*)surface_pixel) = this->buffer[y][x];
        }
      }
    }

    SDL_UnlockSurface(this->surface);

    //create a new texture from the surface
    return std::make_shared<image_t>(SDL_CreateTextureFromSurface(&renderer,this->surface), width,height);
  }
}
