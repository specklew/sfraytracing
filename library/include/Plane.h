
#ifndef SFRAYTRACING_PLANE_H
#define SFRAYTRACING_PLANE_H

#include "Vector.h"
#include "Ray.h"


class Plane {
public:
    Plane(Vector point, Vector normal);

    Vector Point;
    Vector Normal;

    bool Intersect(Ray &ray, Vector &v);
};

#endif //SFRAYTRACING_PLANE_H
