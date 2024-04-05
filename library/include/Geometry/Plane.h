
#ifndef SFRAYTRACING_PLANE_H
#define SFRAYTRACING_PLANE_H

#include "Vector3.h"
#include "Ray.h"
#include "HitInfo.h"
#include "Geometry.h"


class Plane : Geometry {
public:

    Vector3 point;
    Vector3 normal;

    Plane(Vector3 point, Vector3 normal);

    [[nodiscard]] HitInfo hit(const Ray &ray) const override;
};

#endif //SFRAYTRACING_PLANE_H
