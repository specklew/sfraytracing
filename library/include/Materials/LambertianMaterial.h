#ifndef SF_RAYTRACING_LAMBERTIANMATERIAL_H
#define SF_RAYTRACING_LAMBERTIANMATERIAL_H

#include "Material.h"

class LambertianMaterial : public Material{
public:
    LambertianMaterial(const Color& albedo);
    [[nodiscard]] MaterialInfo scatter(const Ray &rayIn, const HitInfo &hit) const override;
};

#endif //SF_RAYTRACING_LAMBERTIANMATERIAL_H
