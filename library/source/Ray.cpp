
#include "../include/Ray.h"


Ray::Ray() {
    mOrigin = {0,0,0};
    mDirection = {0,0,0};
}

Ray::Ray(Vector origin, Vector direction) {
    mOrigin = origin;
    mDirection = direction;
}

Ray::Ray(Vector origin, float distance) {
    mOrigin = origin;
    mDistance = distance;
}

Ray::Ray(Vector origin, Vector direction, float distance) {
    mOrigin = origin;
    mDirection = direction;
    mDistance = distance;

}

const Vector &Ray::getOrigin() const {
    return mOrigin;
}
const Vector &Ray::getDirection() const {
    return mDirection;
}
const Vector &Ray::getDestination() const {
    return mDestination;
}
float Ray::getDistance() const {
    return mDistance;
}




void Ray::setOrigin(const Vector &mOrigin) {
    Ray::mOrigin = mOrigin;
}
void Ray::setDirection(const Vector &mDirection) {
    Ray::mDirection = mDirection;
}
void Ray::setDestination(const Vector &mDestination) {
    Ray::mDestination = mDestination;
}
void Ray::setDistance(float mDistance) {
    Ray::mDistance = mDistance;
}






