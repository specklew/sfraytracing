
#include "../include/Ray.h"



Ray::Ray() = default;

Ray::Ray(Vector3 origin, Vector3 direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray::Ray(Vector3 origin, Vector3 direction, float distance) {
    this->origin = origin;
    this->direction = direction;
    this->distance = distance;
    this->destination = origin + direction * distance;
}


std::string Ray::toString() const {
    return "{" + origin.toString() + ", " + direction.toString() + "}";
}






