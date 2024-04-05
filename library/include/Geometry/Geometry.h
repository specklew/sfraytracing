#ifndef SFRAYTRACING_GEOMETRY_H
#define SFRAYTRACING_GEOMETRY_H

#include "Ray.h"
#include "HitInfo.h"

class Geometry {
public:
    virtual ~Geometry() = default;

    [[nodiscard]] virtual HitInfo hit(const Ray &ray) const = 0;

protected:
    std::shared_ptr<Material> material;
};

#endif //SFRAYTRACING_GEOMETRY_H
