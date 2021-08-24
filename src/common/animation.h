/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_ANIMATION_H
#define _DIVEBAR_COMMON_ANIMATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include "component.h"
#include "image.h"

namespace common {

  //defines an animation row of a sprite sheet
  class anim_t : public component_t {
  private:
    //the animation set (can be shared between animations)
    std::shared_ptr<image_t> image;
    //the width of a frame
    int frame_width;
    //the height of a frame
    int frame_height;
    //the row index on the sprite sheet
    size_t row_idx;

    //the total number of frames (not necessarily the full row)
    int frames;
    //the current frame
    int current_frame;
    //the delay in ticks between frames
    int frame_delay;
    //the current counter for frame delay
    int frame_delay_counter;

    //whether the image is flipped
    bool flipped;
    //play the animation once, pause until reset
    bool once;

    /**
     * Update the animation
     * @param parent the parent of the animation
     */
    void update(component_t& parent) override;

    /**
     * Load the animation resource
     * @param renderer the renderer
     */
    void load(SDL_Renderer& renderer, const component_t&) override;

    /**
     * Render this animation
     * @param renderer the sdl renderer
     * @param camera   the current camera
     */
    void render(SDL_Renderer& renderer,
                const SDL_Rect& camera) const override;

  public:
    /**
     * Constructor
     */
    anim_t() = delete;

    /**
     * Constructor takes the path to the resource
     * @param image  the image to use (shared)
     * @param frame_width the width of a frame
     * @param frame_height the height of a frame
     * @param row_idx     the row index on the sprite sheet
     * @param frames the number of frames (horizontal)
     * @param frame_delay ticks between frame updates
     * @param once        play the animation once until reset
     */
    anim_t(std::shared_ptr<image_t> image,
           size_t frame_width,
           size_t frame_height,
           size_t row_idx,
           int frames,
           int frame_delay,
           bool once=false);

    /**
     * Copy constructor
     * @param other animation to copy from (shares image)
     */
    anim_t(const anim_t& other);

    /**
     * Assignment operator (shares image)
     */
    anim_t& operator=(const anim_t& other);

    /**
     * Set the animation flipped
     * @param  flipped flip the animation
     */
    void set_flipped(bool flipped=true);

    /**
     * Get the duration of the animation un update cycles
     * @return duration
     */
    int get_cycle_duration() const;

    /**
     * Reset the animation
     */
    void reset_animation();

    /**
     * Whether the current animation cycle is complete
     * @return whether the cycle is complete
     */
    bool anim_complete() const;

    /**
     * The remaining update cycles in the animation
     * @return the number of update calls left in the cycle
     */
    int cycle_duration_remaining() const;
  };
}

#endif /*_DIVEBAR_COMMON_ANIMATION_H*/
