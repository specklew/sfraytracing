#include "Ray.h"

Ray::Ray() = default;

Ray::Ray(Vector3 origin, Vector3 direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray::Ray(Vector3 origin, Vector3 direction, double distance, double minimalDistance) {
    this->origin = origin;
    this->direction = direction;
    this->distance = distance;
    this->minimalDistance = minimalDistance;
    this->destination = origin + direction * distance;
}


std::string Ray::toString() const {
    return "{" + origin.toString() + ", " + direction.toString() + "}";
}






