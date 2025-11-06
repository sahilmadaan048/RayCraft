/**
 * @file interval.h
 * @brief Defines the `interval` class used to represent numerical ranges.
 *
 * The interval class provides a convenient way to express and check 
 * if values lie within given numerical bounds — commonly used for 
 * ray intersection ranges (e.g., valid `t` values along a ray).
 */

#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

/**
 * @class interval
 * @brief Represents a continuous range of real numbers [min, max].
 *
 * Provides methods to check containment, clamping, and range relationships.
 * Also includes two special static intervals:
 *  - `interval::empty` → represents an invalid or empty range.
 *  - `interval::universe` → represents the full range (-∞, +∞).
 */
class interval
{
public:
    double min; ///< Lower bound of the interval
    double max; ///< Upper bound of the interval

    /**
     * @brief Default constructor.
     * Initializes an empty interval (min = +∞, max = -∞).
     */
    interval() : min(+infinity), max(-infinity) {}

    /**
     * @brief Constructs an interval from given bounds.
     * @param min Lower bound.
     * @param max Upper bound.
     */
    interval(double min, double max) : min(min), max(max) {}

    /**
     * @brief Returns the size (width) of the interval.
     * @return max - min
     */
    double size() const { return max - min; }

    /**
     * @brief Checks if a value lies within or on the interval.
     * @param x Value to test.
     * @return True if min ≤ x ≤ max.
     */
    bool contains(double x) const { return min <= x && x <= max; }

    /**
     * @brief Checks if a value lies strictly within the interval.
     * @param x Value to test.
     * @return True if min < x < max.
     */
    bool surrounds(double x) const { return min < x && x < max; }

    /**
     * @brief Clamps a value to stay within [min, max].
     * @param x Value to clamp.
     * @return Clamped value.
     */
    double clamp(double x) const
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty;     ///< Represents no valid range (min > max)
    static const interval universe;  ///< Represents full numeric range (-∞, +∞)
};

// Static interval definitions
const interval interval::empty    = interval(+infinity, -infinity);  // ∅
const interval interval::universe = interval(-infinity, +infinity);  // (-∞, +∞)

#endif
