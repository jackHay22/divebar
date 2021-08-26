/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#ifndef _DIVEBAR_COMMON_COMPONENT_H
#define _DIVEBAR_COMMON_COMPONENT_H

#include <memory>
#include <vector>
#include <string>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "shared_resources.h"

namespace common {

  //flags
  #define COMPONENT_COLLIDABLE     0x80 // a physical component in the map (can collide with solid components)
  #define COMPONENT_SOLID          0x40 // Other components cannot move through this one
  #define COMPONENT_VISIBLE        0x20 // Component should be rendered when the camera can see it
  #define COMPONENT_GRAVITY        0x10 // This component is effected by gravity
  #define COMPONENT_REMOVE         0x08 // this component should be removed
  #define COMPONENT_ALWAYS_VISIBLE 0x04 // this component should always be rendererd (regardless of camera position)

  #define GRAVITY_PER_TICK 2

  //Updatable, renderable component
  struct component_t {
  private:
    //the parent of this component
    component_t* parent;
    //the children of this component
    std::vector<std::unique_ptr<component_t>> children;
    //the bounds and position of this component
    SDL_Rect bounds;
    //the flags for this component
    uint8_t flags;
    //directory to prefix paths to load resources from
    std::string resource_dir_prefix;

    /**
     * Calculate collisions for a child
     * @param idx the child to check
     * @return whether the child collided with a solid component
     */
    bool check_child_collisions(size_t idx) const;

    /**
     * Call update on an interactive components close enough to the provided location
     * @param center_x the location x
     * @param center_y the location y
     */
    void update_interactive_components(int center_x, int center_y);

  protected:
    /**
     * Add a child to this component (assumes ownership)
     * @param c the child
     * @return the index of the child
     */
    int add_child(std::unique_ptr<component_t> c);

    /**
     * Get the nth child, cast to type
     * @param  i index of the child
     * @return   a const reference to the child (throws exception if cast fails)
     */
    template <typename T>
    const T& get_nth_child(size_t i) const {
      return dynamic_cast<const T&>(*this->children.at(i));
    }

    /**
     * Get the nth child, cast to type NON CONST
     * @param  i index of the child
     * @return   a const reference to the child (throws exception if cast fails)
     */
    template <typename T>
    T& get_nth_child(size_t i) {
      return dynamic_cast<T&>(*this->children.at(i));
    }

    /**
     * Get the nth child as a component
     * @param  i child index
     * @return   the child
     */
    component_t& get_nth_child(size_t i) {
      return *this->children.at(i);
    }

    /**
     * Update this component, takes mutable reference to
     * parent (can update --i.e. environmental interation)
     * Implemented by the concrete type
     * (By default updates children)
     * @param parent the parent component
     */
    virtual void update(component_t& parent);

    /**
     * Update a single child
     * @param idx the index of the child
     */
    void update_child(size_t idx);

    /**
     * Optionally handle an sdl event
     * @param parent the component parent
     * @param event the sdl event
     */
    virtual void handle_event(component_t& parent,
                              const SDL_Event& e);

    /**
     * Let a single child handle the event
     * @param e   the event
     * @param idx the child index
     */
    void child_handle_event(const SDL_Event& e, size_t idx);

    /**
     * Render this component
     * (By default renders children)
     * Implemented by the concrete type
     * @param renderer the sdl renderer
     * @param camera   the current camera
     */
    virtual void render(SDL_Renderer& renderer,
                        const SDL_Rect& camera) const;

    /**
     * Render any foreground elements for this component (i.e. ui components)
     * (By default renders children)
     * @param renderer the sdl renderer
     * @param camera   the current camera
     */
    virtual void render_fg(SDL_Renderer& renderer,
                           const SDL_Rect& camera) const;

    /**
     * Render a single child
     * @param renderer the sdl renderer
     * @param camera   the camera
     * @param idx      the child to render
     */
    void render_child(SDL_Renderer& renderer,
                      const SDL_Rect& camera,
                      size_t idx) const;


    /**
     * Render a single child fg components
     * @param renderer the sdl renderer
     * @param camera   the camera
     * @param idx      the child to render
     */
    void render_fg_child(SDL_Renderer& renderer,
                         const SDL_Rect& camera,
                         size_t idx) const;

    /**
     * Load resources for registered children
     * @param  renderer the sdl renderer for loading images
     * @param  resources shared resources
     */
    void load_children(SDL_Renderer& renderer,
                       shared_resources& resources);

    /**
     * Load any resources for this component
     * @param renderer the sdl renderer for loading images
     * @param parent   the parent of this component
     * @param resources shared resources available to all components
     */
    virtual void load(SDL_Renderer& renderer,
                      const component_t& parent,
                      shared_resources& resources) = 0;

    /**
     * Render the bounds of this component for debugging
     * @param renderer the sdl renderer
     * @param camera   the camera to render with
     */
    void debug_render_bounds(SDL_Renderer& renderer,
                             const SDL_Rect& camera) const;

  public:
    /**
     * Constructor
     * @param bounds the bounds of the component
     * @param flags  attributes
     * @param resource_dir_prefix a prefix to add to resource load paths
     */
    component_t(SDL_Rect&& bounds,
                uint8_t flags,
                const std::string& resource_dir_prefix="");

    /**
     * Copy constructor
     * (Doesn't copy children)
     * @param other component to copy from
     */
    component_t(const component_t& other);

    /**
     * Assignment operator
     * @param other component to copy from
     */
    component_t& operator=(const component_t& other);

    //no default construction
    component_t() = delete;

    //Virtual destructor
    virtual ~component_t();

    /**
     * Get the parent of this component
     * @param  parent the parent of this component
     * @return        whether this component has a parent
     */
    bool get_parent(component_t** parent);

    template <typename T>
    T& get_as() {
      return dynamic_cast<T&>(*this);
    }

    /**
     * Get the bounds of the component
     * @return the component bounds
     */
    const SDL_Rect& get_bounds() const { return bounds; }

    /**
     * Whether this component is currently visible to the camera
     * @return whether the component is visible
     * @param camera the current camera
     */
    virtual bool is_visible(const SDL_Rect& camera) const;

    /**
     * Set the position of the current object
     * @param x position x
     * @param y position y
     */
    component_t& set_position(int x, int y);

    /**
     * Set the width and height of the object
     * @param w the new width
     * @param h the new height
     */
    component_t& set_size(int w, int h);

    /**
     * Mark this component for removal
     */
    void mark_for_removal();

    /**
     * Get the full path to a resource
     * @param  path the local path for the resource
     * @return      the full path to load from
     */
    std::string rsrc_path(const std::string& path) const;

    /**
     * Whether this component collides with another component
     * @param  other the other component
     * @return       whether the two components collide
     */
    virtual bool collides_with(const component_t& other) const;

    /**
     * Whether the component is collidable
     * @return whether the component is collidable
     */
    virtual bool is_solid() const;

    /**
     * Check if this component is solid at some position
     * @param x position x
     * @param y position y
     * @return whether this position is solid
     */
    virtual bool solid_at(int x, int y) const;
  };
}

#endif /*_DIVEBAR_COMMON_COMPONENT_H*/
