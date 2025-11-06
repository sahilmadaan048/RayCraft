/**
 * @file vec3.h
 * @brief defines the `vec3` class and related utilitty functions for 3D vector operations
 *
 * This header provides the `vec3` class, which represenrs a 3-dimensional vector and
 * includes support for common vector arithmetic, geometric operations, and random
 * vector generation used in the ray tracing applications
 */

#ifndef VEC3_H
#define VEC3_H

#include "constants.h"

/**
 * @class vec3
 * @brief Represents a 3-dimensional vector with common arithmetic and geometric operations.
 *
 * The `vec3` class is used throughout the ray tracer to represent points, directions,
 * and colors. It supports vector addition, subtraction, scalar multiplication/division,
 * dot and cross products, normalization, and random vector generation.
 *
 * Example usage:
 * @code
 * vec3 v1(1.0, 2.0, 3.0);
 * vec3 v2 = v1 * 2.0;
 * double d = dot(v1, v2);
 * vec3 n = unit_vector(v1);
 * @endcode
 */
class vec3
{
public:
    double e[3]; ///< the vector components (c, y, z)

    /** @brief default constructor initialising all components to zdero */
    vec3()
    {
        e[0] = e[1] = e[2] = 0;
    }

    /**
     * @brief constructs a vector from three component values
     * @param e0 x component
     * @param e1 y component
     * @param e2 z component
     *
     */

    vec3(double e0, double e1, double e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    /** @brief Returns the X component. */
    double x() const { return e[0]; }
    /** @brief Returns the Y component. */
    double y() const { return e[1]; }
    /** @brief Returns the Z component. */
    double z() const { return e[2]; }

    /** @brief Returns a negated copy of the vector. */
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    /** @brief Returns the component at index `i` (0 = x, 1 = y, 2 = z). */
    double operator[](int i) const { return e[i]; }

    /** @brief Returns a reference to the component at index `i` (modifiable). */
    double &operator[](int i) { return e[i]; }

    /** @brief Adds another vector to this vector (component-wise). */
    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    /** @brief Multiplies this vector component-wise by another vector. */
    vec3 &operator*=(const vec3 &v)
    {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }

    /** @brief Multiplies this vector by a scalar value. */
    vec3 &operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    /** @brief Divides this vector by a scalar value. */
    vec3 &operator/=(double t)
    {
        return *this *= 1 / t;
    }

    /** @brief Returns the Euclidean length (magnitude) of the vector. */
    double length() const
    {
        return std::sqrt(length_squared());
    }

    /** @brief Returns the squared length of the vector (avoids sqrt for efficiency). */
    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    /**
     * @brief Checks if the vector is very close to zero in all dimensions.
     * @return `true` if all components are near zero, `false` otherwise.
     */
    double near_zero() const
    {
        // return true if the vector is close to zero in all dimensions
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

    /** @brief Generates a random vector with each component in [0, 1). */
    static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    /**
     * @brief Generates a random vector with each component in [min, max).
     * @param min Lower bound for each component.
     * @param max Upper bound for each component.
     */
    static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

/// Alias for a 3D point (used interchangeably with `vec3`).
using point3 = vec3;

// ---------------------------------------------------------------------------
// Operator overloads and helper functions
// ---------------------------------------------------------------------------

/** @brief Outputs a vector to an output stream (formatted as "x y z"). */
inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

/** @brief Vector addition (component-wise). */
inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

/** @brief Vector subtraction (component-wise). */
inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

/** @brief Component-wise vector multiplication. */
inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

/** @brief Scalar multiplication from the left. */
inline vec3 operator*(double t, const vec3 &v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

/** @brief Scalar multiplication from the right. */
inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

/** @brief Scalar division. */
inline vec3 operator/(const vec3 &v, double t)
{
    return (1 / t) * v;
}

/** @brief Computes the dot product of two vectors. */
inline double dot(const vec3 &u, const vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

/** @brief Computes the cross product of two vectors. */
inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

/**
 * @brief Returns the unit (normalized) vector in the same direction as `v`.
 * @return Normalized vector or (0, 0, 0) if input has zero length.
 */
inline vec3 unit_vector(const vec3 &v)
{
    double len = v.length();
    if (len == 0)
        return vec3(0, 0, 0);
    return v / len;
}

// ---------------------------------------------------------------------------
// Random direction and reflection/refraction utilities
// ---------------------------------------------------------------------------

/** @brief Generates a random point within the unit disk (used for depth-of-field). */
inline vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
        {
            return p;
        }
    }
}

/** @brief Generates a random unit vector uniformly distributed on the sphere. */
inline vec3 random_unit_vector()
{
    while (true)
    {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1.0)
        {
            return p / sqrt(lensq);
        }
    }
}

/**
 * @brief Generates a random vector on the hemisphere oriented around a normal.
 * @param normal The reference normal vector.
 */
inline vec3 random_on_hemisphere(const vec3 &normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
    { // in the same hemisphere as the normal
        return on_unit_sphere;
    }
    else
    {
        return -on_unit_sphere;
    }
}

/**
 * @brief Reflects a vector `v` about a normal `n`.
 * @param v The incoming vector.
 * @param n The surface normal.
 * @return The reflected vector.
 */
inline vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

/**
 * @brief Refracts a vector through a surface using Snell's law.
 * @param uv The unit direction vector of the incoming ray.
 * @param n The surface normal.
 * @param etai_over_etat The ratio of refractive indices.
 * @return The refracted vector.
 */
inline vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat)
{
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif // VEC_H