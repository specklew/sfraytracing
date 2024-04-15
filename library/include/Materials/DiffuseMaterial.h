#ifndef SF_RAYTRACING_DIFFUSEMATERIAL_H
#define SF_RAYTRACING_DIFFUSEMATERIAL_H

#include "Material.h"

class DiffuseMaterial : public Material{
public:
    DiffuseMaterial(const Color& albedo);
    [[nodiscard]] MaterialInfo scatter(const Ray &rayIn, const HitInfo &hit) const override;
};

#endif //SF_RAYTRACING_DIFFUSEMATERIAL_H
