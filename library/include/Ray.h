#ifndef SFRAYTRACING_RAY_H
#define SFRAYTRACING_RAY_H

#include "Vector.h"

class Ray{
public:
    Ray();
    Ray(Vector origin, Vector direction);
    Ray(Vector origin, float distance);
    Ray(Vector origin, Vector direction, float distance);

    const Vector &getOrigin() const;
    float getDistance() const;
    const Vector &getDirection() const;
    const Vector &getDestination() const;

    void setOrigin(const Vector &mOrigin);
    void setDistance(float mDistance);
    void setDirection(const Vector &mDirection);
    void setDestination(const Vector &mDestination);

private:
    Vector mOrigin;
    Vector mDirection;
    Vector mDestination;
    float mDistance;

};

#endif //SFRAYTRACING_RAY_H
