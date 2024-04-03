#ifndef SF_RAYTRACING_MATHHELPER_H
#define SF_RAYTRACING_MATHHELPER_H

#include <limits>
#include <cstdlib>

class MathHelper {
public:
    const float infinity = std::numeric_limits<float>::infinity();
    const float pi = 3.1415926535897932385f;

    [[nodiscard]] float degreesToRadians(float degrees) const;


    static float randomFloat(); // Returns a random value in [0, 1)
    static float randomFloat(float min, float max);



};

#endif //SF_RAYTRACING_MATHHELPER_H
