/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "component.h"
#ifndef __APPLE__
#include <filesystem>
#endif

namespace common {

  /**
   * Constructor
   * @param bounds the bounds of the component
   * @param flags  attributes
   */
  component_t::component_t(SDL_Rect&& bounds,
                           uint8_t flags,
                           const std::string& resource_dir_prefix)
    : parent(nullptr),
      children(),
      bounds(bounds),
      flags(flags),
      resource_dir_prefix(resource_dir_prefix) {}

  /**
   * Copy constructor
   * @param other component to copy from
   */
  component_t::component_t(const component_t& other)
    : parent(other.parent),
      children(),
      bounds(other.bounds),
      flags(other.flags),
      resource_dir_prefix(other.resource_dir_prefix) {}

  /**
   * Assignment operator
   * @param other component to copy from
   */
  component_t& component_t::operator=(const component_t& other) {
    this->parent = other.parent;
    this->bounds = other.bounds;
    this->flags = other.flags;
    this->resource_dir_prefix = other.resource_dir_prefix;
    return *this;
  }

  //Virtual destructor
  component_t::~component_t() {
    children.clear();
  }

  /**
   * Calculate collisions for a child
   * @param idx the child to check
   * @return whether the child collided with a solid component
   */
  bool component_t::check_child_collisions(size_t idx) const {
    if (children.at(idx)->flags & COMPONENT_COLLIDABLE) {
      //resolve collisions
      for (size_t i=0; i<children.size(); i++) {
        //check for a collision
        if ((i != idx) &&
            children.at(i)->is_solid() &&
            children.at(i)->collides_with(*children.at(idx))) {
          //collision
          return true;
        }
      }
    }
    return false;
  }

  /**
   * Add a child to this component (assumes ownership)
   * @param c the child
   */
  void component_t::add_child(std::unique_ptr<component_t> c) {
    //set the parent of the child
    c->parent = this;
    //inherit resource location
    c->resource_dir_prefix = this->resource_dir_prefix;
    children.push_back(std::move(c));
  }

  /**
   * Get the parent of this component
   * @param  parent the parent of this component
   * @return        whether this component has a parent
   */
  bool component_t::get_parent(component_t** parent) {
    *parent = this->parent;
    return this->parent != nullptr;
  }

  /**
   * Update this component, takes mutable reference to
   * parent (can update --i.e. environmental interation)
   * Implemented by the concrete type
   * (By default updates children)
   * @param parent the parent component
   */
  void component_t::update(component_t& parent) {
    this->update_children();
  }

  /**
   * Update all child components
   */
  void component_t::update_children() {
    //update each in the x direction
    for (size_t i=0; i<children.size(); i++) {
      update_child(i);
    }
  }

  /**
   * Updater a single child
   * @param idx the index of the child
   */
  void component_t::update_child(size_t idx) {
    //TODO remove components marked

    SDL_Rect old_position = children.at(idx)->bounds;

    //update the component
    children.at(idx)->update(*this);

    //check if the component collided
    if (check_child_collisions(idx)) {
      //reset
      children.at(idx)->bounds = old_position;
    }

    //get the new old position
    old_position = children.at(idx)->bounds;

    //update is effected by gravity
    if (children.at(idx)->flags & COMPONENT_GRAVITY) {
      //update y position
      children.at(idx)->bounds.y += GRAVITY_PER_TICK;

      //check collision
      if (check_child_collisions(idx)) {
        //reset
        children.at(idx)->bounds = old_position;
      }
    }
  }

  /**
   * Optionally handle an sdl event
   * @param parent the component parent
   * @param event the sdl event
   */
  void component_t::handle_event(component_t& parent,
                                 const SDL_Event& e) {
    //pass to children by default
    children_handle_event(e);
  }

  /**
   * Pass event to children if not handled at this level
   * @param e the sdl event
   */
  void component_t::children_handle_event(const SDL_Event& e) {
    for (size_t i=0; i<children.size(); i++) {
      children.at(i)->handle_event(*this,e);
    }
  }

  /**
   * Let a single child handle the event
   * @param e   the event
   * @param idx the child index
   */
  void component_t::child_handle_event(const SDL_Event& e, size_t idx) {
    children.at(idx)->handle_event(*this,e);
  }

  /**
   * Render children
   * @param renderer the sdl renderer
   * @param camera   the current camera
   */
  void component_t::render_children(SDL_Renderer& renderer,
                                    const SDL_Rect& camera) const {
    for (size_t i=0; i<children.size(); i++) {
      render_child(renderer,camera,i);
    }
  }

  /**
   * Render a single child
   * @param renderer the sdl renderer
   * @param camera   the camera
   * @param idx      the child to render
   */
  void component_t::render_child(SDL_Renderer& renderer,
                                 const SDL_Rect& camera,
                                 size_t idx) const {
    if (children.at(idx)->is_visible(camera)) {
      children.at(idx)->render(renderer,camera);
    }
  }

  /**
   * Render this component
   * (By default renders children)
   * Implemented by the concrete type
   * @param renderer the sdl renderer
   * @param camera   the current camera
   */
  void component_t::render(SDL_Renderer& renderer,
                           const SDL_Rect& camera) const {
    this->render_children(renderer,camera);
  }

  /**
   * Load resources for registered children
   * @param  renderer the sdl renderer for loading images
   */
  void component_t::load_children(SDL_Renderer& renderer) {
    for (size_t i=0; i<children.size(); i++) {
      children.at(i)->load(renderer, *this);
    }
  }

  /**
   * Whether this component is currently visible to the camera
   * @return whether the component is visible
   * @param camera the current camera
   */
  bool component_t::is_visible(const SDL_Rect& camera) const {
    return (flags & COMPONENT_VISIBLE) &&
            ((bounds.x < (camera.x + camera.w)) &&
            ((bounds.x + bounds.w) > camera.x) &&
            (bounds.y < (camera.y + camera.h)) &&
            ((bounds.y + bounds.h) > camera.y));
  }

  /**
   * Whether this component collides with another component
   * @param  other the other component
   * @return       whether the two components collide
   */
  bool component_t::collides_with(const component_t& other) const {
    return (flags & COMPONENT_COLLIDABLE) &&
            ((bounds.x < (other.bounds.x + other.bounds.w)) &&
            ((bounds.x + bounds.w) > other.bounds.x) &&
            (bounds.y < (other.bounds.y + other.bounds.h)) &&
            ((bounds.y + bounds.h) > other.bounds.y));
  }

  /**
   * Set the position of the current object
   * @param x position x
   * @param y position y
   */
  component_t& component_t::set_position(int x, int y) {
    this->bounds = { x, y, bounds.w, bounds.h };
    return *this;
  }

  /**
   * Set the width and height of the object
   * @param w the new width
   * @param h the new height
   */
  component_t& component_t::set_size(int w, int h) {
    this->bounds = { bounds.x, bounds.y, w, h };
    return *this;
  }

  /**
   * Whether the component is collidable
   * @return whether the component is collidable
   */
  bool component_t::is_solid() const {
    return flags & COMPONENT_SOLID;
  }

  /**
   * Check if this component is solid at some position
   * @param x position x
   * @param y position y
   * @return whether this position is solid
   */
  bool component_t::solid_at(int x, int y) const {
    if (is_solid() &&
        (x > bounds.x) &&
        (x < (bounds.x + bounds.w)) &&
        (y > bounds.y) &&
        (y < (bounds.y + bounds.h))) {
      return true;
    }
    //check children
    for (size_t i=0; i<children.size(); i++) {
      if (children.at(i)->solid_at(x,y)) {
        return true;
      }
    }
    return false;
  }

  /**
   * Mark this component for removal
   */
  void component_t::mark_for_removal() {
    flags |= COMPONENT_REMOVE;
  }

  /**
   * Get the full path to a resource
   * @param  path the local path for the resource
   * @return      the full path to load from
   */
  std::string component_t::rsrc_path(const std::string& path) const {
#ifndef __APPLE__
    std::filesystem::path dir(resource_dir_prefix);
    std::filesystem::path rsrc(path);

    std::filesystem::path full_path = dir / rsrc;

    return full_path.string();
#else
    if ((resource_dir_prefix.size() > 0) &&
        (resource_dir_prefix.back() == '/')) {
      return resource_dir_prefix + path;
    }
    return resource_dir_prefix + "/" + path;
#endif
  }
}
