

#include "../include/Plane.h"

Plane::Plane(Vector point, Vector normal) {
Point=point;
Normal=normal;
}

bool Plane::Intersect(Ray &ray, Vector &v) {
    Vector rayDirection=ray.getDirection();
    rayDirection.Normalize();

    float denominator = Normal.DotProduct(rayDirection);
    if (denominator != 0.0f) {
        Vector p = Point - ray.getOrigin();
        float t = p.DotProduct(Normal) / denominator;
        if (t >= 0) {
            v=ray.getOrigin() + rayDirection * t;
            return true;
        }
    }
    return false;
}

