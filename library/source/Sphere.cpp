
#include "../include/Sphere.h"
#include "../include/Vector3.h"
#include <cmath>


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
    Vector3 rayDirection = ray.getDirection();
    rayDirection.normalize();

    Vector3 oc = ray.getOrigin() - center;
    float a = rayDirection.dotProduct(rayDirection);
    float b = oc.dotProduct(rayDirection);
    float c = oc.dotProduct(oc) - radius * radius;
    float discriminant = b * b - a * c;

    bool hit = false;

    if (discriminant >= 0) {

        float t1 = (-b - std::sqrt(discriminant)) /  a;
        float t2 = (-b + std::sqrt(discriminant)) /  a;

        if (t1 >= 0) {

            Vector3 hitPoint1 = ray.getOrigin() + rayDirection * t1;
            hit = true;
        }

        if (t2 >= 0 && t1 != t2) {
            Vector3 hitPoint2 = ray.getOrigin() + rayDirection * t2;

            hit = true;
        }

    }
    return hit;
}

std::string Sphere::toString() const {
    return "Center: " + center.toString() + ", Radius: " + std::to_string(radius);
}

void Sphere::printIntersectionPoints(std::vector<Vector3> &iPoints) {
    if (!iPoints.empty()){
        for (Vector3 v : iPoints) {
            std::cout << v.toString() << "   ";
        }
    }
    else{
        std::cout << "No intersections." << std::endl;
    }
}



