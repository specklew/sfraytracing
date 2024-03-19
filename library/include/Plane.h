
#ifndef SFRAYTRACING_PLANE_H
#define SFRAYTRACING_PLANE_H

#include "Vector.h"
#include "Ray.h"


class Plane {
public:
    Plane(Vector point, Vector normal);

    bool intersect(Ray &ray, Vector &v);

    [[nodiscard]] const Vector &getPoint() const;
    [[nodiscard]] const Vector &getNormal() const;

private:
    Vector Point_;
    Vector Normal_;
};

#endif //SFRAYTRACING_PLANE_H
