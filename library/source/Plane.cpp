

#include "../include/Plane.h"

Plane::Plane(Vector3 point, Vector3 normal) {
    Point_=point;
    Normal_=normal;
}

bool Plane::intersect(Ray &ray, Vector3 &v) {
    Vector3 rayDirection=ray.getDirection();
    rayDirection.normalize();

    float denominator = Normal_.dotProduct(rayDirection);
    if (denominator != 0.0f) {
        Vector3 p = Point_ - ray.getOrigin();
        float t = p.dotProduct(Normal_) / denominator;
        if (t >= 0) {
            v=ray.getOrigin() + rayDirection * t;
            return true;
        }
    }
    return false;
}

const Vector3 &Plane::getPoint() const {return Point_;}
const Vector3 &Plane::getNormal() const {return Normal_;}

