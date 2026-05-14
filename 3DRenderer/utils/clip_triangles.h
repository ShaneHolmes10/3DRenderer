#pragma once

#include "draw_triangles.h"
#include <vector>

std::vector<Triangle2> clipAndProjectTriangle(
    const Triangle3& triangle,
    float focal_length,
    float width,
    float height,
    float near_z
);
