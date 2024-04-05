#ifndef SFRAYTRACING_HITINFO_H
#define SFRAYTRACING_HITINFO_H

#include <memory>
#include "Vector3.h"

class Material;

struct HitInfo {
    bool intersected{};
    Vector3 point{};
    Vector3 normal{};
    float distance{};
    std::shared_ptr<Material> material{};
};

#endif //SFRAYTRACING_HITINFO_H
