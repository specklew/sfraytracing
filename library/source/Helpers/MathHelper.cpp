#include <random>
#include "Helpers/MathHelper.h"

inline double MathHelper::degreesToRadians(double degrees) {
    return degrees * pi / 180.0f;
}

double MathHelper::randomDouble() {
    static std::uniform_real_distribution<double> dis(0.0, 1.0);
    static std::mt19937 generator;

    return dis(generator);
}

double MathHelper::randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

double MathHelper::clamp(double &value, const double &min, const double& max) {
    if(value < min) return min;
    if(value > max) return max;
    return value;
}

double MathHelper::linearToGamma(const double& value, const double& gamma) {
    return std::pow(value, 1 / gamma);
}
