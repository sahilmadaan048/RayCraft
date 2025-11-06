/**
 * @file constants.h
 * @brief Defines global constants, utility functions, and common includes for the ray tracer.
 *
 * This header provides mathematical constants, random number utilities, and includes
 * frequently used components such as `vec3`, `ray`, and `camera`.
 * It serves as a centralized dependency header for the entire rendering system.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <limits>
#include <memory>

// C++ standard usings
using std::make_shared;
using std::shared_ptr;

// ---------------------------------------------------------
// Constants
// ---------------------------------------------------------

const double infinity = std::numeric_limits<double>::infinity();  ///< Represents positive infinity
const double pi = 3.1415926535897932385;                          ///< Mathematical constant π

// ---------------------------------------------------------
// Utility Functions
// ---------------------------------------------------------

/**
 * @brief Converts degrees to radians.
 * @param degrees Angle in degrees.
 * @return Angle in radians.
 */
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

/**
 * @brief Returns a random real number in the range [0, 1).
 * @return Random double between 0 (inclusive) and 1 (exclusive).
 */
inline double random_double()
{
    return std::rand() / (RAND_MAX + 1.0);
}

/**
 * @brief Returns a random real number in the range [min, max].
 * @param min Lower bound of the range.
 * @param max Upper bound of the range.
 * @return Random double between min and max.
 */
inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

// ---------------------------------------------------------
// Common Headers
// ---------------------------------------------------------
// These are included last to ensure inline functions defined above
// are recognized by the files that depend on them.

#include "camera.h"
#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
