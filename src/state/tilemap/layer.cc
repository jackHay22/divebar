/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "layer.h"
#include "../../common/launch_exception.h"
#include <utility>
#include "virtual_tile.h"

namespace state {
namespace tilemap {

  #define COMMA ','
  #define SPACE ' '
  #define LAYER "layer"
  #define TILE_WIDTH "tilewidth"
  #define TILES_HIGH "tileshigh"

  /**
   * Parse a labeled number
   * @param  line the line ('label value')
   * @return      the parsed number (or throws)
   */
  int parse_labeled_number(const std::string& line) {
    //parse tile dimension
    std::stringstream s_stream(line);

    bool first = true;

    //get each value
    while (s_stream.good()) {
      std::string substr;
      std::getline(s_stream, substr, SPACE);

      if (!first) {
        try {
          return std::stoi(substr);
        } catch (...) {
          throw common::launch_exception("failed to parse number from line in map file: " + line);
        }
      }
      first = false;
    }
    throw common::launch_exception("failed to parse number from line in map file: " + line);
    return 0;
  }

  /**
   * Check if a string starts with some prefix
   * @param  str    the string
   * @param  prefix the prefix
   * @return        whether str starts with prefix
   */
  bool startswith(const std::string& str, const std::string& prefix) {
    return str.rfind(prefix, 0) == 0;
  }

  /**
   * Constructor
   * @param path the path to the layer file
   * @param tileset the tileset to use
   * @param idx  the index of this layer in the map file
   * @param solid whether this layer is solid
   */
  layer_t::layer_t(const std::string& path,
                  std::shared_ptr<common::image_t> tileset,
                  size_t idx,
                  bool solid)
    : common::component_t({0,0,0,0},
                          solid ? (COMPONENT_COLLIDABLE
                                 | COMPONENT_SOLID
                                 | COMPONENT_ALWAYS_VISIBLE) :
                                  COMPONENT_ALWAYS_VISIBLE),
      path(path),
      tileset(tileset),
      idx(idx),
      contents(),
      tile_dim(8) {}

  /**
   * Check if a position is within the bounds of the layer
   * @param  x position x
   * @param  y position y
   * @return   whether this point is in bounds
   */
  bool layer_t::in_bounds(int x, int y) const {
    int idx_x = x / tile_dim;
    int idx_y = y / tile_dim;

    //check bounds and get the type of the tile
    return (idx_x >= 0) && (idx_y >= 0) &&
           (idx_y < (int)this->contents.size()) &&
           (idx_x < (int)this->contents.at(idx_y).size());
  }

  /**
   * Determine whether a solid map layer collides with a component
   * @param  other the other component
   * @return       whether the two collide
   */
  bool layer_t::collides_with(const component_t& other) const {
    //optimization: only check for solid layers
    if (this->is_solid()) {
      const SDL_Rect& other_bounds = other.get_bounds();

      //create a virtual tile to compare with the other body
      virtual_tile_t current_tile(tile_dim);

      //generate positions that might intersect
      for (int i=(other_bounds.x - tile_dim); i<((other_bounds.x + other_bounds.w) + tile_dim); i+=(tile_dim / 2)) {
        for (int j=(other_bounds.y - tile_dim); j<((other_bounds.y + other_bounds.h) + tile_dim); j+=(tile_dim / 2)) {
          //check if the generated position is in bounds
          if (in_bounds(i,j)) {
            //determine indices of tile
            int idx_x = i / tile_dim;
            int idx_y = j / tile_dim;

            //set position
            current_tile.move_to(idx_x * tile_dim, idx_y * tile_dim);

            //check if solid and collided
            if ((this->contents.at(idx_y).at(idx_x) >= 0) &&
                other.collides_with(current_tile)) {
              return true;
            }
          }
        }
      }
    }

    //didn't collide or not a solid layer
    return false;
  }

  /**
   * Check to see if the map is solid at this position
   * @param  x position x
   * @param  y position y
   * @return   whether this position is solid
   */
  bool layer_t::solid_at(int x, int y) const {
    return in_bounds(x,y) &&
           (this->contents.at(y / tile_dim).at(x / tile_dim) >= 0);
  }

  /**
   * Parse map contents into buffer
   * @param file the file
   */
  void layer_t::parse_map_lines(std::ifstream& file, int max_height) {
    std::string line;
    int x = 0;
    int y = 0;

    while (std::getline(file, line)) {
      //check if the section end reached
      if (line.empty()) {
        return;
      }

      if (y >= max_height) {
        return;
      }

      //split line by commas
      this->contents.emplace_back();
      std::stringstream s_stream(line);

      //get each value
      while (s_stream.good()) {
         std::string substr;
         std::getline(s_stream, substr, COMMA);

         if (!substr.empty()) {
           //attempt to parse value
           try {
             int type = std::stoi(substr);

             if (type != -1) {
               //add the tile to the map contents
               this->contents.back().push_back(type);
             } else {
               this->contents.back().push_back(-1);
             }

           } catch (...) {
             throw common::launch_exception("failed to read from map file: " +
              path + ", layer " + std::to_string(idx));
           }
           x++;
         }
      }
      y++;
    }
  }

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void layer_t::load(SDL_Renderer& renderer,
                     const common::component_t& parent,
                     common::shared_resources& resources) {
    //clear any existing contents
    contents.clear();

    int layer = -1; //the current layer
    int max_height = 0; //the height to parse for any given layer
    std::string line; //the line read from the file

    try {
      std::ifstream layer_file(path);

      while (std::getline(layer_file, line)) {
        if (!line.empty()) {
          if (startswith(line,TILES_HIGH)) {
            max_height = parse_labeled_number(line);

          } else if (startswith(line,TILE_WIDTH)) {
            this->tile_dim = parse_labeled_number(line);

          } else if (startswith(line,LAYER)) {
            //get the current layer number
            layer = parse_labeled_number(line);
            if (layer == (int)this->idx) {
              //parse this layer
              parse_map_lines(layer_file,max_height);
              return; //done
            }
          }
        }
      }

    } catch (...) {
      throw common::launch_exception("failed to read from map file: " +
        path + ", layer " + std::to_string(idx));
    }

    if (contents.empty()) {
      throw common::launch_exception("failed to read from map file: " +
        path + ", layer " + std::to_string(idx) + " (nothing loaded)");
    }

    component_t::load_children(renderer,resources);
  }

  /**
   * Render the current state
   */
  void layer_t::render(SDL_Renderer& renderer,
                       const SDL_Rect& camera) const {
    //create a virtual tile to compare with the other body
    virtual_tile_t current_tile(tile_dim);
    SDL_Rect sample_bounds = {0,0,tile_dim,tile_dim};
    SDL_Rect render_bounds = {0,0,tile_dim,tile_dim};

    //get the image dimensions
    const SDL_Rect& tileset_dim = tileset->default_bounds();
    int tiles_per_row = tileset_dim.w / tile_dim;

    //render tiles in layer
    for (size_t i=0; i<contents.size(); i++) {
      for (size_t j=0; j<contents.at(i).size(); j++) {
        //the index of the current tile
        int tile_idx = contents.at(i).at(j);

        //check if tile visible at all
        if (tile_idx > -1) {
          //set position of collision body
          current_tile.move_to(j * tile_dim, i * tile_dim);

          //set the sample region within the tileset
          sample_bounds.x = tile_dim * (tile_idx % tiles_per_row);
          sample_bounds.y = tile_dim * (tile_idx / tiles_per_row);

          //set the position to render the tileset sample
          render_bounds.x = (tile_dim * j) - camera.x;
          render_bounds.y = (tile_dim * i) - camera.y;

          //check if visible to camera
          if (current_tile.is_visible(camera)) {
            //render using tileset
            this->tileset->render_copy(
              renderer,
              sample_bounds,
              render_bounds
            );
          }
        }
      }
    }
  }

  /**
   * Get the width of this layer
   * @return layer width
   */
  int layer_t::get_layer_width() const {
    return contents.at(0).size() * tile_dim;
  }

  /**
   * Get the height of this layer
   * @return layer height
   */
  int layer_t::get_layer_height() const {
    return contents.size() * tile_dim;
  }

}}
