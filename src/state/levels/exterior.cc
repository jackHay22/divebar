/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "exterior.h"
#include "door.h"
#include "../tilemap/tilemap.h"
#include "../entity/player.h"
#include "../entity/entity.h"
#include "../../common/image.h"
#include "../../window/window.h"

namespace state {
namespace levels {

  /**
   * Default constructor
   */
  exterior_t::exterior_t()
    : level_t(),
      player_idx(0) {}

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   * @param resources the shared global resources
   */
  void exterior_t::load(SDL_Renderer& renderer,
                        const common::component_t& parent,
                        common::shared_resources& resources) {
    //add background map layers
    this->add_child(std::make_unique<tilemap::tilemap_t>(
      this->rsrc_path("maps/exterior.txt"),
      resources.exterior_tileset,
      std::vector<int>{0,1},
      -1
    ));

    //load the player
    player_idx = this->add_child(std::make_unique<entity::player_t>(
      SDL_Rect{160,80,8,24}
    ));

    //load the foreground map layers (includes ground)
    size_t fg_idx = this->add_child(std::make_unique<tilemap::tilemap_t>(
      this->rsrc_path("maps/exterior.txt"),
      resources.exterior_tileset,
      std::vector<int>{2,3},
      0 // index of solid layer
    ));

    //add the door to inside
    this->add_child(std::make_unique<door_t>(
      SDL_Rect{144,32,8,24},
      0, 272, 80
    ));

    //load children
    component_t::load_children(renderer,resources);

    //tilemap now loaded, get dimensions
    const tilemap::tilemap_t& solid_layer = get_nth_child<tilemap::tilemap_t>(fg_idx);
    //set the max bounds for camera lock
    this->set_max_bounds(solid_layer.get_map_width(), solid_layer.get_map_height());
  }

  /**
   * Update the state
   */
  void exterior_t::update(common::component_t& parent) {
    //get the player position
    const SDL_Rect& player_bounds = this->get_nth_child(player_idx).get_bounds();

    //center the camera
    this->center_camera(player_bounds.x, player_bounds.y);

    //update components in level
    component_t::update(parent);
  }

  /**
   * Move the player to some position in this level
   * @param x new player position x
   * @param y new player position y
   * @param player_attributes the attributes of the player to update
   */
  void exterior_t::update_player(int x, int y,
                                 const entity::entity_attributes_t& player_attributes) {
    this->get_nth_child(player_idx).set_position(x,y);
    this->get_nth_child<entity::entity_t>(player_idx).get_attributes().update_attrs(player_attributes);
  }
}}
