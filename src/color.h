/**
 * @file color.h
 * @brief Defines the color type and functions for outputting color values in the ray tracer.
 *
 * The color is represented as a 3D vector (r, g, b), where each component is in the range [0, 1].
 * This header provides gamma correction and utilities for converting these color values
 * to byte values suitable for image output (e.g., in PPM format).
 */

#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;  ///< Represents an RGB color using a 3D vector structure.

// ---------------------------------------------------------
// Gamma Correction
// ---------------------------------------------------------

/**
 * @brief Converts a linear color component to gamma-corrected form.
 * 
 * Applies gamma correction (γ = 2.0), which compensates for monitor brightness
 * and human visual response.  
 * 
 * @param linear_component The linear color component in the range [0, 1].
 * @return Gamma-corrected component.
 */
inline double linear_to_gamma(double linear_component)
{
    return (linear_component > 0) ? std::sqrt(linear_component) : 0;
}

// ---------------------------------------------------------
// Color Output
// ---------------------------------------------------------

/**
 * @brief Writes the given color to the output stream in integer RGB format.
 * 
 * Each color component is clamped to [0, 1), scaled to [0, 255],
 * and written as three space-separated integers (for PPM image output).
 *
 * @param out Output stream (typically an image file or console).
 * @param pixel_color The color to write, represented as (r, g, b).
 */
inline void write_color(std::ostream &out, const color &pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Clamp and convert [0,1) -> [0,255]
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // Output as "r g b"
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
