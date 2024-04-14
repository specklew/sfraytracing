#ifndef SF_RAYTRACING_DIELECTRICMATERIAL_H
#define SF_RAYTRACING_DIELECTRICMATERIAL_H

#include "Material.h"

class DielectricMaterial : public Material{
public:
    DielectricMaterial(const Color& albedo, precision refractionIndex);

    precision refractionIndex;
    MaterialInfo scatter(const Ray &rayIn, const HitInfo &hit) const override;
};

#endif //SF_RAYTRACING_DIELECTRICMATERIAL_H
