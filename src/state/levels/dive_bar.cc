/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "dive_bar.h"
#include "../tilemap/tilemap.h"
#include "../entity/player.h"
#include "../../common/image.h"
#include "../../window/window.h"

namespace state {
namespace levels {

  /**
   * Default constructor
   * @param player_anim_sheet the shared animations user by the player
   * (Since the player can move between levels we share the image resource)
   */
  dive_bar_t::dive_bar_t(std::shared_ptr<common::image_t> player_anim_sheet)
    : level_t(),
      player_anim_sheet(player_anim_sheet) {}

  /**
   * Load any resources for this component
   * @param renderer the sdl renderer for loading images
   * @param parent   the parent of this component
   */
  void dive_bar_t::load(SDL_Renderer& renderer,
                        const common::component_t& parent) {
    //load the tileset
    std::shared_ptr<common::image_t> tileset =
      std::make_shared<common::image_t>(
        renderer,
        this->rsrc_path("tilesets/bar.png")
      );

    //add background map layers
    this->add_child(std::make_unique<tilemap::tilemap_t>(
      this->rsrc_path("maps/bar.txt"),
      tileset, std::vector<int>{0,1,2},
      -1
    ));

    //load the player
    this->add_child(std::make_unique<entity::player_t>(
      SDL_Rect{24,16,8,24},
      player_anim_sheet
    ));

    //load the foreground map layers (includes ground)
    this->add_child(std::make_unique<tilemap::tilemap_t>(
      this->rsrc_path("maps/bar.txt"),
      tileset, std::vector<int>{3,4},
      0 // index of solid layer
    ));

    //load children
    component_t::load_children(renderer);

    //tilemap now loaded, get dimensions
    const tilemap::tilemap_t& solid_layer = get_nth_child<tilemap::tilemap_t>(2);
    //set the max bounds for camera lock
    this->set_max_bounds(solid_layer.get_map_width(), solid_layer.get_map_height());
  }

  /**
   * Update the state
   */
  void dive_bar_t::update(common::component_t& parent) {
    //get the player position
    const SDL_Rect& player_bounds = this->get_nth_child(1).get_bounds();

    //center the camera
    this->center_camera(player_bounds.x, player_bounds.y);

    //update components in level
    component_t::update_children();
  }

  /**
   * Optionally handle an sdl event
   * @param parent the component parent
   * @param event the sdl event
   */
  void dive_bar_t::handle_event(common::component_t& parent,
                                 const SDL_Event& e) {

    //children will handle event
    common::component_t::children_handle_event(e);
  }
}}
