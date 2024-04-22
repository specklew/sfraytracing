#ifndef SF_RAYTRACING_MATERIAL_H
#define SF_RAYTRACING_MATERIAL_H

#include "Color.h"
#include "MaterialInfo.h"
#include "HitInfo.h"

class Material{
public:
    virtual ~Material() = default;

    precision diffuseAmount = 0.7;

    precision ambientAmount = 0.1;

    precision specularAmount = 0.3;
    precision specularCoefficient = 2.0;
    precision reflectFraction;

    precision roughness = 0.8;
    precision metallic = 0.2;
    precision ambientOcclusion = 0.4;
    precision anisotropy = 0.5;

    virtual MaterialInfo scatter(const Ray& rayIn, const HitInfo& hit) const = 0;

    Color color;
};

#endif //SF_RAYTRACING_MATERIAL_H
