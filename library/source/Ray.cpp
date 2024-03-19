
#include "../include/Ray.h"
#include <limits>


Ray::Ray() {
    Distance_ = std::numeric_limits<float>::max();
}

Ray::Ray(Vector3 origin, Vector3 direction) {
    Origin_ = origin;
    Direction_ = direction;
    Distance_ = std::numeric_limits<float>::max();
}

Ray::Ray(Vector3 origin, float distance) {
    Origin_ = origin;
    Distance_ = distance;
}

Ray::Ray(Vector3 origin, Vector3 direction, float distance) {
    Origin_ = origin;
    Direction_ = direction;
    Distance_ = distance;
}

const Vector3 &Ray::getOrigin() const {return Origin_;}
const Vector3 &Ray::getDirection() const {return Direction_;}
const Vector3 &Ray::getDestination() const {return Destination_;}
float Ray::getDistance() const {return Distance_;}


void Ray::setOrigin(const Vector3& origin) { Origin_ = origin; }
void Ray::setDirection(const Vector3& direction) { Direction_ = direction; }
void Ray::setDestination(const Vector3& destination) { Destination_ = destination; }
void Ray::setDistance(float distance) { Distance_ = distance; }

std::string Ray::toString() const {
    return "{" + Origin_.toString() + ", " + Direction_.toString() + "}";
}






