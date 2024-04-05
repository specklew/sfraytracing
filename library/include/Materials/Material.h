#ifndef SF_RAYTRACING_MATERIAL_H
#define SF_RAYTRACING_MATERIAL_H

#include "Color.h"
#include "MaterialInfo.h"
#include "HitInfo.h"

class Material{
public:
    virtual ~Material() = default;

    float specularAmount;
    float specularCoefficient;
    float reflectFraction;

    virtual MaterialInfo scatter(const Ray& rayIn, const HitInfo& hit) const = 0;

protected:
    Color albedo;
};

#endif //SF_RAYTRACING_MATERIAL_H
