/**
 * @file ray.h
 * @brief Defines the `ray` class representing a 3D geometric ray.
 *
 * A ray is defined by an origin point and a direction vector. It is used
 * to trace paths through a 3D scene, where each ray can test for intersections
 * with objects such as spheres or planes.
 */

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/**
 * @class ray
 * @brief Represents a mathematical ray in 3D space.
 *
 * A ray is defined by the equation:
 *    P(t) = origin + t * direction
 *
 * where:
 * - `origin` is the starting point of the ray.
 * - `direction` is the vector indicating its direction.
 * - `t` is a scalar parameter determining how far along the ray to move.
 *
 * Example:
 * @code
 * ray r(point3(0, 0, 0), vec3(1, 0, 0));
 * point3 p = r.at(2.5); // Returns (2.5, 0, 0)
 * @endcode
 */
class ray
{
private:
  point3 orig; ///< The origin point of the ray.
  vec3 dir;    ///< The direction vector of the ray.

public:
  /** @brief Default constructor initializing an empty ray. */
  ray() {}

  /**
   * @brief Constructs a ray with a given origin and direction.
   * @param origin The starting point of the ray.
   * @param direction The direction vector of the ray.
   */
  ray(const point3 &origin, const vec3 &direction)
      : orig(origin), dir(direction) {}

  /** @brief Returns the origin of the ray. */
  const point3 &origin() const { return orig; }

  /** @brief Returns the direction of the ray. */
  const vec3 &direction() const { return dir; }

  /**
   * @brief Returns the point at distance `t` along the ray.
   *
   * The point is calculated as:
   *    P(t) = origin + t * direction
   *
   * @param t Distance parameter along the ray.
   * @return The point `P(t)` on the ray.
   */
  point3 at(double t) const { return orig + t * dir; }
};

#endif // RAY_H
