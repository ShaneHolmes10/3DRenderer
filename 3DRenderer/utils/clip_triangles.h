#pragma once

#include "draw_triangles.h"
#include <vector>

std::vector<Triangle3> clipTriangle(
    const Triangle3& triangle,
    float focal_length,
    float width,
    float height,
    float near_z
);

Triangle2 projectTriangle(
    const Triangle3& triangle,
    float focal_length,
    float width,
    float height
);
