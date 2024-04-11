#include <cmath>
#include "Geometry/Sphere.h"


Sphere::Sphere() = default;

Sphere::Sphere(precision r){
    center = Vector3(0, 0, 0);
    radius = r;
}

Sphere::Sphere(Vector3 center, precision radius, const std::shared_ptr<Material>& material){
    this->center = center;
    this->radius = radius;
    this->material = material;
}

HitInfo Sphere::hit(const Ray &ray) const {
    Vector3 rayDirection = ray.direction;
    rayDirection.normalize();

    Vector3 oc = ray.origin - center;
    precision a = rayDirection.dotProduct(rayDirection);
    precision half_b = oc.dotProduct(rayDirection);
    precision c = oc.dotProduct(oc) - radius * radius;

    precision discriminant = half_b * half_b - a * c;

    if (discriminant < 0) return {};

    precision sqrtDiscriminant = std::sqrt(discriminant);

    precision inv_a = 1 / a;
    precision t = (-half_b - sqrtDiscriminant) * inv_a;

    if (t < ray.minimalDistance || ray.distance < t) {

        t = (-half_b + sqrtDiscriminant) * inv_a;
        if (t < ray.minimalDistance || ray.distance < t) {
            return {};
        }
    }

    Vector3 hitPoint = ray.origin + rayDirection * t;

    return {true, hitPoint, (hitPoint - center).normalized(), t, material, ray};
}

std::string Sphere::toString() const {
    return "Center: " + center.toString() + ", Radius: " + std::to_string(radius);
}



