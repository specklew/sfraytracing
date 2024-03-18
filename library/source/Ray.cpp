
#include "../include/Ray.h"
#include <limits>


Ray::Ray() {
    Origin_ = {0, 0, 0};
    Direction_ = {0, 0, 0};
    Distance_ = std::numeric_limits<float>::max();
}

Ray::Ray(Vector origin, Vector direction) {
    Origin_ = origin;
    Direction_ = direction;
    Distance_ = std::numeric_limits<float>::max();
}

Ray::Ray(Vector origin, float distance) {
    Origin_ = origin;
    Distance_ = distance;
}

Ray::Ray(Vector origin, Vector direction, float distance) {
    Origin_ = origin;
    Direction_ = direction;
    Distance_ = distance;
}

const Vector &Ray::getOrigin() const {return Origin_;}
const Vector &Ray::getDirection() const {return Direction_;}
const Vector &Ray::getDestination() const {return Destination_;}
float Ray::getDistance() const {return Distance_;}


void Ray::setOrigin(const Vector& origin) { Origin_ = origin; }
void Ray::setDirection(const Vector& direction) { Direction_ = direction; }
void Ray::setDestination(const Vector& destination) { Destination_ = destination; }
void Ray::setDistance(float distance) { Distance_ = distance; }

std::string Ray::toString() const {
    return "{" + Origin_.toString() + ", " + Direction_.toString() + "}";
}






