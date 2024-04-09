#include <cmath>
#include "Geometry/Sphere.h"


Sphere::Sphere() = default;

Sphere::Sphere(float r){
    center = Vector3(0, 0, 0);
    radius = r;
}

Sphere::Sphere(Vector3 center, float radius, const std::shared_ptr<Material>& material){
    this->center = center;
    this->radius = radius;
    this->material = material;
}

HitInfo Sphere::hit(const Ray &ray) const {
    Vector3 rayDirection = ray.direction;
    rayDirection.normalize();

    Vector3 oc = ray.origin - center;
    double a = rayDirection.dotProduct(rayDirection);
    double half_b = oc.dotProduct(rayDirection);
    double c = oc.dotProduct(oc) - radius * radius;

    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0) return {};

    double sqrtDiscriminant = std::sqrt(discriminant);

    double inv_a = 1 / a;
    double t = (-half_b - sqrtDiscriminant) * inv_a;

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



