

#include "../include/Plane.h"

Plane::Plane(Vector point, Vector normal) {
    Point_=point;
    Normal_=normal;
}

bool Plane::Intersect(Ray &ray, Vector &v) {
    Vector rayDirection=ray.getDirection();
    rayDirection.Normalize();

    float denominator = Normal_.DotProduct(rayDirection);
    if (denominator != 0.0f) {
        Vector p = Point_ - ray.getOrigin();
        float t = p.DotProduct(Normal_) / denominator;
        if (t >= 0) {
            v=ray.getOrigin() + rayDirection * t;
            return true;
        }
    }
    return false;
}

const Vector &Plane::getPoint() const {return Point_;}
const Vector &Plane::getNormal() const {return Normal_;}

