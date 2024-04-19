#include <random>
#include "Helpers/MathHelper.h"

inline precision MathHelper::degreesToRadians(precision degrees) {
    return degrees * pi / half360;
}

precision MathHelper::randomPrecision() {
    static std::uniform_real_distribution<precision> dis(0.0, 1.0);
    static std::mt19937 generator;

    return dis(generator);
}

precision MathHelper::randomPrecision(precision min, precision max) {
    return min + (max - min) * randomPrecision();
}

precision MathHelper::clamp(precision &value, const precision &min, const precision &max) {
    if(value < min) return (value = min);
    if(value > max) return (value = max);
    return value;
}

precision MathHelper::linearToGamma(const precision &value, const precision& gamma) {
    return std::pow(value, 1 / gamma);
}

precision MathHelper::lerp(const precision &from, const precision &to, const precision &t) {
    return from * (1 - t) + to * t;
}
