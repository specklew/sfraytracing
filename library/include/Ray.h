#ifndef SFRAYTRACING_RAY_H
#define SFRAYTRACING_RAY_H

#include "Vector3.h"

class Ray{
public:
    Ray();
    Ray(Vector3 origin, Vector3 direction);
    Ray(Vector3 origin, float distance);
    Ray(Vector3 origin, Vector3 direction, float distance);

    [[nodiscard]] const Vector3& getOrigin() const;
    [[nodiscard]] float getDistance() const;
    [[nodiscard]] const Vector3& getDirection() const;
    [[nodiscard]] const Vector3& getDestination() const;

    void setOrigin(const Vector3& origin);
    void setDistance(float distance);
    void setDirection(const Vector3& direction);
    void setDestination(const Vector3& destination);

    [[nodiscard]] std::string toString() const;

private:
    Vector3 Origin_{};
    Vector3 Direction_{};
    Vector3 Destination_{};
    float Distance_{};

};

#endif //SFRAYTRACING_RAY_H
