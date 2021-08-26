/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "tilemap.h"
#include "layer.h"

namespace state {
namespace tilemap {

  /**
   * Constructor
   * @param map_path   path to tilemap resource
   * @param tileset    the tileset to use
   * @param layers     the layer indices to load
   * @param solid_idx  the index of the solid layer (or -1)
   */
  tilemap_t::tilemap_t(const std::string& map_path,
                      std::shared_ptr<common::image_t> tileset,
                      std::vector<int>&& layers,
                      int solid_idx)
    : component_t({0,0,0,0}, COMPONENT_COLLIDABLE
                           | COMPONENT_SOLID
                           | COMPONENT_ALWAYS_VISIBLE),
      map_path(map_path),
      tileset(tileset),
      layers(layers),
      solid_idx(solid_idx) {}

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     * @param resources the shared global resources
     */
    void tilemap_t::load(SDL_Renderer& renderer,
                         const common::component_t& parent,
                         common::shared_resources& resources) {
    //add map layers
    for (size_t i=0; i<layers.size(); i++) {
      component_t::add_child(
        std::make_unique<layer_t>(map_path,
                                  tileset,
                                  layers.at(i),
                                  (int)i==solid_idx));
    }

    //load child resources
    component_t::load_children(renderer,resources);
  }

  /**
   * Check if a body collides with this map
   * @param  bounds the bounds
   * @return        whether the two bounds collide
   */
  bool tilemap_t::collides_with(const common::component_t& other) const {
    if (solid_idx > -1) {
      return this->get_nth_child<common::component_t>(solid_idx).collides_with(other);
    }
    return false;
  }

  /**
   * Check to see if the map is solid at this position
   * @param  x position x
   * @param  y position y
   * @return   whether this position is solid
   */
  bool tilemap_t::solid_at(int x, int y) const {
    if (solid_idx > -1) {
      return this->get_nth_child<common::component_t>(solid_idx).solid_at(x,y);
    }
    return false;
  }

  /**
   * Compute the width of the map
   * @return map width
   */
  int tilemap_t::get_map_width() const {
    if (solid_idx > -1) {
      return this->get_nth_child<layer_t>(solid_idx).get_layer_width();
    } else {
      return this->get_nth_child<layer_t>(0).get_layer_width();
    }
  }

  /**
   * Compute the width of the map
   * @return map width
   */
  int tilemap_t::get_map_height() const {
    if (solid_idx > -1) {
      return this->get_nth_child<layer_t>(solid_idx).get_layer_height();
    } else {
      return this->get_nth_child<layer_t>(0).get_layer_height();
    }
  }

}}
