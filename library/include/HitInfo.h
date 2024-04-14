#ifndef SFRAYTRACING_HITINFO_H
#define SFRAYTRACING_HITINFO_H

#include <memory>
#include "Vector3.h"

class Material;
class Ray;

struct HitInfo {
    bool intersected{};
    bool frontFace{};
    Vector3 point{};
    Vector3 normal{};
    precision distance{};
    std::shared_ptr<Material> material{};
    Ray ray;
};

#endif //SFRAYTRACING_HITINFO_H
