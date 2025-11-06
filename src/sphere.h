/**
 * @file sphere.h
 * @brief Defines the `sphere` class, a hittable object representing a 3D sphere
 *  
 * The `sphere` class models a sphere that can intersected bu rays in a ray tracing
 * environment. It implements the `hit()` fcuntion from the `hittable` interface to 
 * determine whether a ray intersects the sphere and to compute intersection details
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "constants.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"

/**
 * @class sphere
 * @brief Represents a sphere that can be intersected by rays
 *  
 * The `sphere` class inherits from `the `hittble` and implements the `hit()` function 
 * to check for intersections between a given ray and the sphere
 * 
 * This class encapsulates:
 *  - the center posistion of the sphere
 *  - the radius of the sphere
 *  - the material pointer associated with the sphere
 * 
 * Example usage:
 * @code
 * auto mat = make_shared<lambertian>(color(0.7, 0.3, 0.3))
 * sphere s(point3(0, 0, -1), 0.5, mat)
 * @endcode
 */

class sphere : public hittable
{
public:
  /**
   * @brief constructs a asphere with the given coloe, radius,  and material
   * 
   * @param center The 3D coordinates of the sphere's cdnter
   * @param radius The radius of th sphere, Negative values are clamped to zero
   * @param mat A shared pointer to the sphere;s material
   * 
   */
  sphere(const point3 &center, double radius, shared_ptr<material> mat)
      : center(center), radius(std::fmax(0, radius)), mat(mat) {}
      
  /**
   * @brief Determines whether a ray intersects the sphere within a valid range.
   *
   * This function solves the quadratic equation for the intersection of a ray with
   * a sphere and checks if a valid intersection occurs within the range specified
   * by `ray_t`. If an intersection is found, it fills the `hit_record` with
   * intersection details such as point, normal, and material.
   *
   * @param r The input ray.
   * @param ray_t The valid range of distances along the ray to consider.
   * @param rec A reference to a `hit_record` object that stores intersection data.
   * @return `true` if the ray intersects the sphere, otherwise `false`.
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
    rec.mat = mat;

    return true;
  }

private:
  point3 center;                   // <- the center of the sphere
  double radius;                   // <- the radius of the sphere
  shared_ptr<material> mat;        // <- the material associated with the sphere
};

#endif