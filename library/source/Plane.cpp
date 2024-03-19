

#include "../include/Plane.h"

Plane::Plane(Vector point, Vector normal) {
    Point_=point;
    Normal_=normal;
}

bool Plane::intersect(Ray &ray, Vector &v) {
    Vector rayDirection=ray.getDirection();
    rayDirection.normalize();

    float denominator = Normal_.dotProduct(rayDirection);
    if (denominator != 0.0f) {
        Vector p = Point_ - ray.getOrigin();
        float t = p.dotProduct(Normal_) / denominator;
        if (t >= 0) {
            v=ray.getOrigin() + rayDirection * t;
            return true;
        }
    }
    return false;
}

const Vector &Plane::getPoint() const {return Point_;}
const Vector &Plane::getNormal() const {return Normal_;}

