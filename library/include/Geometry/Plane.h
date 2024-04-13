
#ifndef SFRAYTRACING_PLANE_H
#define SFRAYTRACING_PLANE_H

#include "Vector3.h"
#include "Ray.h"
#include "HitInfo.h"
#include "Geometry.h"


class Plane : public Geometry {
public:

    Vector3 point;
    Vector3 normal;

    Plane(Vector3 point, Vector3 normal, const std::shared_ptr<Material>& material);

    [[nodiscard]] HitInfo hit(const Ray &ray) const override;
};

#endif //SFRAYTRACING_PLANE_H
