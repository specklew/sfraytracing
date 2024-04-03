#include <cmath>
#include "Sphere.h"


Sphere::Sphere() = default;

Sphere::Sphere(float r){
    center = Vector3(0, 0, 0);
    radius = r;
}

Sphere::Sphere(Vector3 center, float radius){
    this->center = center;
    this->radius = radius;
}

HitInfo Sphere::hit(const Ray &ray) const {
    Vector3 rayDirection = ray.direction;
    rayDirection.normalize();

    Vector3 oc = ray.origin - center;
    float a = rayDirection.dotProduct(rayDirection);
    float half_b = oc.dotProduct(rayDirection);
    float c = oc.dotProduct(oc) - radius * radius;

    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0) return {};

    float sqrtDiscriminant = std::sqrt(discriminant);

    float t = (-half_b - sqrtDiscriminant) / a;

    if (t < ray.minimalDistance || ray.distance < t) {

        t = (-half_b + sqrtDiscriminant) / a;
        if (t < ray.minimalDistance || ray.distance < t) {
            return {};
        }
    }

    Vector3 hitPoint = ray.origin + rayDirection * t;

    return {true, hitPoint, (hitPoint - center).normalize(), t};
}

std::string Sphere::toString() const {
    return "Center: " + center.toString() + ", Radius: " + std::to_string(radius);
}



