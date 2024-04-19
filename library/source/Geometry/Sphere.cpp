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

    Vector3 rayDirection = ray.direction.normalized();

    Vector3 oc = ray.origin - center;
    precision a = rayDirection.dot(rayDirection);
    precision half_b = oc.dot(rayDirection);
    precision c = oc.dot(oc) - radius * radius;

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
    Vector3 normal = (hitPoint - center).normalized();

    bool front_face;
    if(rayDirection.dot(normal) > 0){
        front_face = false;
        normal = -normal;
    } else {
        front_face = true;
    }

    return {true, front_face, hitPoint, normal, t, material, ray};
}

std::string Sphere::toString() const {
    return "Center: " + center.toString() + ", Radius: " + std::to_string(radius);
}



