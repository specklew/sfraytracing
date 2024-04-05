#ifndef SF_RAYTRACING_METALMATERIAL_H
#define SF_RAYTRACING_METALMATERIAL_H

#include "Material.h"

class MetalMaterial : public Material{
public:
    MetalMaterial(const Color& albedo);
    [[nodiscard]] MaterialInfo scatter(const Ray &rayIn, const HitInfo &hit) const override;
};

#endif //SF_RAYTRACING_METALMATERIAL_H
