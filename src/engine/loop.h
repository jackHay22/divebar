/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_ENGINE_LOOP_H
#define _DIVEBAR_ENGINE_LOOP_H

#include <memory>
#include "../window/window.h"
#include "../state/manager.h"

namespace engine {

  //ms per tick
  const int TICK_SLEEP = 50;

  /**
   * Start the game loop
   * @param  win the window
   * @param  man the state manager
   * @return     exit status
   */
  int game_loop(std::shared_ptr<window::window_t> win,
                std::shared_ptr<state::manager_t> man);
}

#endif /*_DIVEBAR_ENGINE_LOOP_H*/
