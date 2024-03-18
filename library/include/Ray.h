#ifndef SFRAYTRACING_RAY_H
#define SFRAYTRACING_RAY_H

#include "Vector.h"

class Ray{
public:
    Ray();
    Ray(Vector origin, Vector direction);
    Ray(Vector origin, float distance);
    Ray(Vector origin, Vector direction, float distance);

    [[nodiscard]] const Vector& getOrigin() const;
    [[nodiscard]] float getDistance() const;
    [[nodiscard]] const Vector& getDirection() const;
    [[nodiscard]] const Vector& getDestination() const;

    void setOrigin(const Vector& origin);
    void setDistance(float distance);
    void setDirection(const Vector& direction);
    void setDestination(const Vector& destination);

    std::string toString() const;

private:
    Vector Origin_;
    Vector Direction_;
    Vector Destination_;
    float Distance_;

};

#endif //SFRAYTRACING_RAY_H
