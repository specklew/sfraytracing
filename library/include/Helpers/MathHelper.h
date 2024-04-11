#ifndef SF_RAYTRACING_MATHHELPER_H
#define SF_RAYTRACING_MATHHELPER_H

#include <limits>
#include <cstdlib>
#include "Precision.h"

const precision infinity = std::numeric_limits<precision>::infinity();
const precision minRayDistance = 0.0001;
const precision pi = 3.1415926535897932385;
const precision half360 = 180;
const precision epsilon = std::numeric_limits<precision>::epsilon();

class MathHelper {
public:
    [[nodiscard]] static precision degreesToRadians(precision degrees) ;


    static precision randomPrecision(); // Returns a random value in [0, 1)
    static precision randomPrecision(precision min, precision max);

    static precision clamp(precision& value, const precision& min, const precision& max);
    static precision linearToGamma(const precision& value, const precision& gamma = 2.0f);



};

#endif //SF_RAYTRACING_MATHHELPER_H
