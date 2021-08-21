/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "dive_bar.h"
#include "../tilemap/tilemap.h"
#include "../../common/image.h"
#include "../../window/window.h"

namespace state {
namespace levels {

  /**
   * Default constructor
   */
  dive_bar_t::dive_bar_t() : level_t() {}

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
        this->rsrc_path("tilesets/divebar.png")
      );

    //add background map layers
    this->add_child(std::make_unique<tilemap::tilemap_t>(
      this->rsrc_path("maps/divebar.txt"),
      tileset, std::vector<int>{2,3,4},
      -1
    ));

    //load entities


    //load the foreground map layers (includes ground)
    this->add_child(std::make_unique<tilemap::tilemap_t>(
      this->rsrc_path("maps/divebar.txt"),
      tileset, std::vector<int>{0,1},
      1 // second layer is solid
    ));
  }

  /**
   * Update the state
   */
  void dive_bar_t::update(common::component_t& parent) {

    //TODO center the camera on the player
    //parent.get_as<level_t>().set_camera({});

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
