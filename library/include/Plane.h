
#ifndef SFRAYTRACING_PLANE_H
#define SFRAYTRACING_PLANE_H

#include "Vector3.h"
#include "Ray.h"


class Plane {
public:
    Plane(Vector3 point, Vector3 normal);

    bool intersect(Ray &ray, Vector3 &v);

    [[nodiscard]] const Vector3 &getPoint() const;
    [[nodiscard]] const Vector3 &getNormal() const;

private:
    Vector3 Point_;
    Vector3 Normal_;
};

#endif //SFRAYTRACING_PLANE_H
