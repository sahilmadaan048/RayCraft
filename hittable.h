/**
 * @file hittable.h
 * @brief Defines the base interface for objects that can be intersected ("hit")
 *
 *
 * This file introduces two key releases:
 * - `bit_record`: A simple data structure to store information about a ray object intersection
 * - `hittable`: An abstract base class (interface) representing any object that can be intersected by a ray.
 *
 * Derived classes (like `sphere`, `plane`, etc) must imiplement the `hit()` method to define in future
 * how that specific geometry interacts with rays
 *
 */

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"

/**
 * @class hit-record
 * @brief Stores the details of a ray object intersection
 *
 * When a ray intersects an object., the intersection point, surface normal,
 * and ray parameter `t` are stores in this struct for later use in shading, reflection, etc
 *
 */

class hit_record
{
public:
  /** @brief the point of intersection in 3D space */
  point3 p;

  /** @brief The surface normal at the intersection point*/
  vec3 normal;

  /** @brief The ray parameter (distance along the ray) where the hit occured */
  double t;

  
  bool front_face;

  void set_face_normal(const ray &r, const vec3 &outward_normal)
  {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

/**
 * @class hittable
 * @brief Abstract base class representing any object that can be hit by a ray.
 *
 * Classes that inherit from `hittable` must implement the `hit()` function, which
 * determines if and where a given ray intersects the object.
 *
 */
class hittable
{
public:
  /** @brief virtual destructor ensures proper cleanup of derived classes */
  virtual ~hittable() = default;

  /**
   * @brief Checks whether a ray intersects the object within a given range.
   *
   * @param r The incoming ray.
   * @param ray_tmin Minimum valid `t` value along the ray (closest distance).
   * @param ray_tmax Maximum valid `t` value along the ray (farthest distance).
   * @param rec Output parameter that will be filled with intersection data if a hit occurs.
   * @return `true` if the ray intersects the object; otherwise `false`.
   *
   * @note This is a pure virtual function and must be overridden in all derived classes.
   */
  virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};

#endif