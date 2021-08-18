/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "launch_exception.h"
namespace common {

  /**
   * Exception with error message
   */
  launch_exception::launch_exception(const std::string& error_msg)
    : error_msg(error_msg) {}

  /*
   * Copy constructor
   */
  launch_exception::launch_exception(const launch_exception& other) {
    this->error_msg = other.error_msg;
  }

  /**
   * Get the error message
   */
  const std::string launch_exception::trace() const throw () {
    return this->error_msg;
  }

}
