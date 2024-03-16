#ifndef SFRAYTRACING_RAY_H
#define SFRAYTRACING_RAY_H

#include "Vector.h"

class Ray{
public:
    Ray();
    Ray(Vector origin, Vector direction);
    Ray(Vector origin, float distance);
    Ray(Vector origin, Vector direction, float distance);

private:
    Vector mOrigin;
    Vector mDirection;
    Vector mDestination;
    float mDistance;

};

#endif //SFRAYTRACING_RAY_H
