#ifndef SF_RAYTRACING_MATERIAL_H
#define SF_RAYTRACING_MATERIAL_H

#include "Color.h"
#include "MaterialInfo.h"
#include "HitInfo.h"

class Material{
public:
    virtual ~Material() = default;

    float diffuseAmount = 0.7f;

    float ambientAmount = 0.1f;

    float specularAmount = 1.0f;
    float specularCoefficient = 20.0f;
    float reflectFraction;

    virtual MaterialInfo scatter(const Ray& rayIn, const HitInfo& hit) const = 0;

    Color albedo;
};

#endif //SF_RAYTRACING_MATERIAL_H
