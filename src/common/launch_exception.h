/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_LAUNCH_EXCEPTION_H
#define _DIVEBAR_COMMON_LAUNCH_EXCEPTION_H

#include <exception>
#include <string>

namespace common {

  struct launch_exception : std::exception {
  private:
    //the error message
    std::string error_msg;

  public:
    /**
     * Exception with error message
     */
    launch_exception(const std::string& error_msg);
    launch_exception(const launch_exception& other);
    launch_exception& operator=(const launch_exception&) = delete;

    /**
     * Get the error message
     */
    const std::string trace() const throw ();
  };

}

#endif /*_DIVEBAR_COMMON_LAUNCH_EXCEPTION_H*/
