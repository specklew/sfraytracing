#include "Geometry/Plane.h"

Plane::Plane(Vector3 point, Vector3 normal) {
    this->point = point;
    this->normal = normal;
}

HitInfo Plane::hit(const Ray &ray) const {
    Vector3 rayDirection=ray.direction;
    rayDirection.normalize();

    float denominator = normal.dotProduct(rayDirection);

    if (denominator != 0.0f) {
        Vector3 p = point - ray.origin;

        if (float t = p.dotProduct(normal) / denominator >= 0) {
            Vector3 intersectionPoint = ray.origin + rayDirection * t;
            return {true, intersectionPoint, normal, t};
        }
    }
    return {};
}

