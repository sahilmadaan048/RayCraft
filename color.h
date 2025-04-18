#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>
#include <cmath> 

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    int rbyte = static_cast<int>(std::round(255.999 * r)); 
    int gbyte = static_cast<int>(std::round(255.999 * g)); 
    int bbyte = static_cast<int>(std::round(255.999 * b)); 

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
