#include "Geometry/Plane.h"

Plane::Plane(Vector3 point, Vector3 normal, const std::shared_ptr<Material>& material) {
    this->point = point;
    this->normal = normal;
    this->material = material;
}

HitInfo Plane::hit(const Ray &ray) const {
    Vector3 rayDirection = ray.direction;

    precision denominator = normal.dot(rayDirection);

    if (std::abs(denominator) > epsilon) {
        Vector3 p = point - ray.origin;

        if (precision t = p.dot(normal) / denominator; t > ray.minimalDistance && t < ray.distance) {
            Vector3 intersectionPoint = ray.origin + rayDirection.normalized() * t;
            return {true, denominator > 0, intersectionPoint, normal, t, material, ray};
        }
    }
    return {};
}

