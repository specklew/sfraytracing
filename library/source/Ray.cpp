
#include "Ray.h"

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
