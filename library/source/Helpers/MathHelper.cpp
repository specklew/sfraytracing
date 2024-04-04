#include <random>
#include "Helpers/MathHelper.h"

inline float MathHelper::degreesToRadians(float degrees) const {
    return degrees * pi / 180.0f;
}

float MathHelper::randomFloat() {
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    static std::mt19937 generator;

    return dis(generator);
}

float MathHelper::randomFloat(float min, float max) {
    return min + (max - min) * randomFloat();
}

float MathHelper::clampFloat(float &value, const float &min, const float& max) {
    if(value < min) return min;
    if(value > max) return max;
    return value;
}

float MathHelper::linearToGamma(const float& value, const float& gamma) {
    return std::pow(value, 1 / gamma);
}
