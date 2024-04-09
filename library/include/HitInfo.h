#ifndef SFRAYTRACING_HITINFO_H
#define SFRAYTRACING_HITINFO_H

#include <memory>
#include "Vector3.h"

class Material;
class Ray;

struct HitInfo {
    bool intersected{};
    Vector3 point{};
    Vector3 normal{};
    double distance{};
    std::shared_ptr<Material> material{};
    Ray ray;
};

#endif //SFRAYTRACING_HITINFO_H
