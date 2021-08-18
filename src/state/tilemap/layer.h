/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_STATE_TILEMAP_LAYER_H
#define _DIVEBAR_STATE_TILEMAP_LAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../../common/component.h"
#include "../../common/image.h"

namespace state {
namespace tilemap {

  /*
   * Tilemap layer
   */
  class layer_t : public common::component_t {
  private:
    //the layer file path
    std::string path;
    //the tileset to use (inherit from parent)
    std::shared_ptr<common::image_t> tileset;
    //layer index
    size_t idx;
    //the contents of the layer
    std::vector<std::vector<int>> contents;
    //tile dimension
    int tile_dim;

    /**
     * Parse map contents into buffer
     * @param file the file
     * @param max_height the maximum height that should be read
     */
    void parse_map_lines(std::ifstream& file, int max_height);

    /**
     * Check if a position is within the bounds of the layer
     * @param  x position x
     * @param  y position y
     * @return   whether this point is in bounds
     */
    bool in_bounds(int x, int y) const;

    /**
     * Determine whether a solid map layer collides with a component
     * @param  other the other component
     * @return       whether the two collide
     */
    bool collides_with(const common::component_t& other) const;

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

    /**
     * Render the current state
     */
    void render(SDL_Renderer& renderer,
                const SDL_Rect& camera) const override;

  public:
    /**
     * Constructor
     * @param path the path to the layer file
     * @param tileset the tileset to use
     * @param idx  the index of this layer in the map file
     * @param solid whether this layer is solid
     */
    layer_t(const std::string& path,
            std::shared_ptr<common::image_t> tileset,
            size_t idx,
            bool solid);
    layer_t(const layer_t&) = delete;
    layer_t& operator=(const layer_t&) = delete;
  };

}}

#endif /*_DIVEBAR_STATE_TILEMAP_LAYER_H*/
