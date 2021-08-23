/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "animation.h"
#include <iostream>

namespace common {

  /**
   * Constructor takes the path to the resource
   * @param image  the image to use (shared)
   * @param frame_width the width of a frame
   * @param frame_height the height of a frame
   * @param row_idx the row index on the sprite sheet
   * @param frames the number of frames (horizontal)
   * @param frame_delay ticks between frame updates
   */
  anim_t::anim_t(std::shared_ptr<image_t> image,
                 size_t frame_width,
                 size_t frame_height,
                 size_t row_idx,
                 size_t frames,
                 size_t frame_delay)
    : component_t({0,0,(int)frame_width,(int)frame_height},COMPONENT_VISIBLE),
      image(image),
      frame_width(frame_width),
      frame_height(frame_height),
      row_idx(row_idx),
      frames(frames),
      current_frame(0),
      frame_delay(frame_delay),
      frame_delay_counter(frame_delay),
      flipped(false) {}

  /**
   * Copy constructor
   * @param other animation to copy from (shares image)
   */
  anim_t::anim_t(const anim_t& other)
    : component_t(other),
      image(other.image),
      frame_width(other.frame_width),
      frame_height(other.frame_height),
      row_idx(other.row_idx),
      frames(other.frames),
      current_frame(other.frames),
      frame_delay(other.frame_delay),
      frame_delay_counter(other.frame_delay_counter),
      flipped(other.flipped) {}

  /**
   * Assignment operator (shares image)
   */
  anim_t& anim_t::operator=(const anim_t& other) {
    component_t::operator=(other);
    this->image = other.image;
    this->frame_width = other.frame_width;
    this->frame_height = other.frame_height;
    this->row_idx = other.row_idx;
    this->frames = other.frames;
    this->current_frame = other.current_frame;
    this->frame_delay = other.frame_delay;
    this->frame_delay_counter = other.frame_delay_counter;
    this->flipped = other.flipped;
    return *this;
  }

  /**
   * Load the animation resource
   * @param renderer the renderer
   */
  void anim_t::load(SDL_Renderer& renderer, const component_t&) {}

  /**
   * Update the animation
   * @param parent the parent of the animation
   */
  void anim_t::update(component_t& parent) {
    this->frame_delay_counter--;
    if (this->frame_delay_counter == 0) {
      this->frame_delay_counter = this->frame_delay;
      this->current_frame = (this->current_frame + 1) % this->frames;
    }

    //set position based on parent and own size
    const SDL_Rect& parent_pos = parent.get_bounds();
    const SDL_Rect& current_pos = this->get_bounds();

    //match the parent position
    this->set_position(parent_pos.x + (parent_pos.w / 2) - (current_pos.w / 2),
                       parent_pos.y + (parent_pos.h / 2) - (current_pos.h / 2));
  }

  /**
   * Render this animation
   * @param renderer the sdl renderer
   * @param camera   the current camera
   */
  void anim_t::render(SDL_Renderer& renderer,
                      const SDL_Rect& camera) const {
    //location to sample in sprite sheet
    SDL_Rect sample_bounds = {(int)(current_frame * frame_width),
                              (int)(row_idx * frame_height),
                              frame_width, frame_height};

    const SDL_Rect& current_bounds = this->get_bounds();

    //set the position to render the animation frame,
    //adjust by camera and by image size
    SDL_Rect render_bounds = {current_bounds.x - camera.x,
                              current_bounds.y - camera.y,
                              frame_width, frame_height};

    //render the current animation frame
    this->image->render_copy(renderer,sample_bounds,render_bounds,flipped);
  }

  /**
   * Set the animation flipped
   * @param  flipped flip the animation
   */
  void anim_t::set_flipped(bool flipped) {
    this->flipped = flipped;
  }
}
