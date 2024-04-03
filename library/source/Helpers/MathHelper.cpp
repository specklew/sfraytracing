#include "Helpers/MathHelper.h"

inline float MathHelper::degreesToRadians(float degrees) const {
    return degrees * pi / 180.0f;
}

float MathHelper::randomFloat() {
    return rand() / (RAND_MAX + 1.0);
}

float MathHelper::randomFloat(float min, float max) {
    return min + (max - min) * randomFloat();
}
