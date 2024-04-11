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

    virtual MaterialInfo scatter(const Ray& rayIn, const HitInfo& hit) const = 0;

    Color albedo;
};

#endif //SF_RAYTRACING_MATERIAL_H
