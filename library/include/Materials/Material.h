#ifndef SF_RAYTRACING_MATERIAL_H
#define SF_RAYTRACING_MATERIAL_H

#include "Color.h"
#include "MaterialInfo.h"
#include "HitInfo.h"

class Material{
public:
    virtual ~Material() = default;

    double diffuseAmount = 0.7;

    double ambientAmount = 0.1;

    double specularAmount = 0.3;
    double specularCoefficient = 2.0;
    double reflectFraction;

    virtual MaterialInfo scatter(const Ray& rayIn, const HitInfo& hit) const = 0;

    Color albedo;
};

#endif //SF_RAYTRACING_MATERIAL_H
