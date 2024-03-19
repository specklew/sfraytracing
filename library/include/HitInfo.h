#ifndef SFRAYTRACING_HITINFO_H
#define SFRAYTRACING_HITINFO_H

#include "Vector3.h"

struct HitInfo {
    bool hit{};
    Vector3 hitPoint{};
    Vector3 hitNormal{};
    float distance{};
};

#endif //SFRAYTRACING_HITINFO_H
