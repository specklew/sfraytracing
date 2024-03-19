#ifndef SFRAYTRACING_GEOMETRY_H
#define SFRAYTRACING_GEOMETRY_H

#include "Ray.h"
#include "HitInfo.h"

class Geometry {
public:
    [[nodiscard]] virtual HitInfo hit(const Ray &ray) const = 0;
};

#endif //SFRAYTRACING_GEOMETRY_H
