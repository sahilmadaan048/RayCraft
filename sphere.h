/**
 * @file sphere.h
 * @brief Defines the Sphere class, a hittable object representing a 3D sphere
 *
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "constants.h"

/**
 * @class sphere
 * @brief Represents a sphere that can be intersected by rays
 *
 * Inherits from `hittable` and implements the `hit()` function
 *
 * Inherits from `hittbale` and implements the `hit()` function
 * to check for ray-sphere intersections
 *
 */

class sphere : public hittable
{
public:
  /**
   * @brief Constructs a sphere with the given center ans radius
   * @param center - center of the sphere
   * @param radius - radius of the sphere
   *
   */
  sphere(const point3 &center, double radius) : center(center), radius(std::fmax(0, radius)) {}

  /**
   * @brief Determines if a ray hits the sphere within a valid range
   * @param r the input ray
   * @param ray_tmin Minimum ray distance to check
   * @param ray_tmax Maximum ray distance to check
   * @param rec Stores intersection details if a hit occurs
   * @return True of the ray intersects the sphere, false otherwise
   *
   */

  bool hit(const ray &r, interval ray_t, hit_record &rec) const override
  {
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
      return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root))
    {
      root = (h + sqrtd) / a;
      if (!ray_t.surrounds(root))
        return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    // rec.mat = mat;

    return true;
  }

private:
  point3 center; // <- the center of the sphere
  double radius; // <- the radius of the sphere
};

#endif