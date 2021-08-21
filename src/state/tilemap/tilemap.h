/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_TILEMAP_TILEMAP_H
#define _DIVEBAR_STATE_TILEMAP_TILEMAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "../../common/component.h"
#include "../../common/image.h"

namespace state {
namespace tilemap {

  /*
   * Tilemap
   */
  class tilemap_t : public common::component_t {
  private:
    //path to map file
    std::string map_path;
    //the tileset to use
    std::shared_ptr<common::image_t> tileset;
    //the layer indices
    std::vector<int> layers;
    //the index of the solid layer (or -1)
    int solid_idx;

    /**
     * Check if a body collides with this map
     * @param  bounds the bounds
     * @return        whether the two bounds collide
     */
    bool collides_with(const common::component_t& other) const override;

    /**
     * Check to see if the map is solid at this position
     * @param  x position x
     * @param  y position y
     * @return   whether this position is solid
     */
    bool solid_at(int x, int y) const override;

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     */
    void load(SDL_Renderer& renderer,
              const common::component_t& parent) override;

  public:
    /**
     * Constructor
     * @param map_path   path to tilemap resource
     * @param tileset    the tileset to use
     * @param layers     the layer indices to load
     * @param solid_idx  the index of the solid layer (or -1)
     */
    tilemap_t(const std::string& map_path,
              std::shared_ptr<common::image_t> tileset,
              std::vector<int>&& layers,
              int solid_idx);
    tilemap_t(const tilemap_t&) = delete;
    tilemap_t& operator=(const tilemap_t&) = delete;
  };

}}

#endif /*_DIVEBAR_STATE_TILEMAP_TILEMAP_H*/
