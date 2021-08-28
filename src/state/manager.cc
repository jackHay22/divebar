/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "manager.h"
#include "level_manager.h"
#include "../window/window.h"
#include "../common/shared_resources.h"
#include <memory>

namespace state {

  /**
   * Constructor
   */
  manager_t::manager_t(SDL_Renderer& renderer, const std::string& resource_dir)
    : component_t({0,0,0,0},COMPONENT_ALWAYS_VISIBLE,SDLK_e,resource_dir),
      current_state(0),
      camera({0,0,window::LOGICAL_W_PX,window::LOGICAL_H_PX}) {
    //load child states

    //add the title manager
    //TODO

    //add the level manager
    this->add_child(std::make_unique<level_manager_t>());

    //create shared resources
    std::shared_ptr<common::shared_resources> shared_resources =
      std::make_shared<common::shared_resources>(renderer, resource_dir);

    //load resources for children
    component_t::load_children(renderer,*shared_resources);
  }

  /**
   * Update this component
   * @param parent the parent component
   */
  void manager_t::update_manager() {
    //update the current component
    common::component_t::update_child(current_state);
  }

  /**
   * Handle an sdl event
   * @param e the sdl event
   */
  void manager_t::handle_event_manager(const SDL_Event& e) {
    //let the current component handle the event
    common::component_t::child_handle_event(e,current_state);
  }

  /**
   * Render the current state
   */
  void manager_t::render_manager(SDL_Renderer& renderer) const {
    //render the active state
    common::component_t::render_child(renderer,camera,current_state);
  }

  /**
   * Set the current state
   * @param state the new current state
   */
  void manager_t::set_current_state(size_t state) {
    current_state = state;
  }

}
