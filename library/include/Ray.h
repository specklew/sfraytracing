#ifndef SFRAYTRACING_RAY_H
#define SFRAYTRACING_RAY_H

#include "Vector3.h"
#include <limits>

class Ray{
public:

    Vector3 origin{};
    Vector3 direction{};
    Vector3 destination{};
    float distance{std::numeric_limits<float>::max()};

    Ray();
    Ray(Vector3 origin, Vector3 direction);
    Ray(Vector3 origin, Vector3 direction, float distance);

    [[nodiscard]] std::string toString() const;

private:


};

#endif //SFRAYTRACING_RAY_H
