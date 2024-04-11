#ifndef SFRAYTRACING_RAY_H
#define SFRAYTRACING_RAY_H

#include "Vector3.h"
#include "Helpers/MathHelper.h"

class Ray{
public:

    Vector3 origin{};
    Vector3 direction{};
    Vector3 destination{};
    precision distance{infinity};
    precision minimalDistance{minRayDistance};

    Ray();
    Ray(Vector3 origin, Vector3 direction);
    Ray(Vector3 origin, Vector3 direction, precision distance, precision minimalDistance = minRayDistance);

    [[nodiscard]] std::string toString() const;

private:


};

#endif //SFRAYTRACING_RAY_H
