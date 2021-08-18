/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include "window/window.h"
#include "engine/loop.h"
#include "state/manager.h"
#include "common/launch_exception.h"

/**
 * Load resources, start
 */
int start(const std::string& rsrc_path) {
  //create a new window
  std::shared_ptr<window::window_t> window =
    std::make_shared<window::window_t>(window::DEFAULT_TITLE);

  //create a new game manager
  std::shared_ptr<state::manager_t> manager =
    std::make_shared<state::manager_t>(window->get_renderer(),rsrc_path);

  //start the engine game loop
  return engine::game_loop(window,manager);
}

/**
 * Entrypoint
 */
int main(int argc, char **argv) {
  std::string rsrc_path = "resources/";
  try {
    return start(rsrc_path);
  } catch (const common::launch_exception& e) {
    std::cerr << e.trace() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
