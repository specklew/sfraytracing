#ifndef SF_RAYTRACING_MATHHELPER_H
#define SF_RAYTRACING_MATHHELPER_H

#include <limits>
#include <cstdlib>

const double infinity = std::numeric_limits<double>::infinity();
const double minRayDistance = 0.0001;
const double pi = 3.1415926535897932385;

class MathHelper {
public:
    [[nodiscard]] static double degreesToRadians(double degrees) ;


    static double randomDouble(); // Returns a random value in [0, 1)
    static double randomDouble(double min, double max);

    static double clamp(double& value, const double& min, const double& max);
    static double linearToGamma(const double& value, const double& gamma = 2.0f);



};

#endif //SF_RAYTRACING_MATHHELPER_H
