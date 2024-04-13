#include "Geometry/Plane.h"

Plane::Plane(Vector3 point, Vector3 normal, const std::shared_ptr<Material>& material) {
    this->point = point;
    this->normal = normal;
    this->material = material;
}

HitInfo Plane::hit(const Ray &ray) const {
    Vector3 rayDirection = ray.direction;

    precision denominator = normal.dotProduct(rayDirection);

    if (denominator < epsilon) {
        Vector3 p = point - ray.origin;

        if (precision t = p.dotProduct(normal) / denominator; t > ray.minimalDistance && t < ray.distance) {
            Vector3 intersectionPoint = ray.origin + rayDirection.normalized() * t;
            return {true, intersectionPoint, normal, t, material, ray};
        }
    }
    return {};
}

