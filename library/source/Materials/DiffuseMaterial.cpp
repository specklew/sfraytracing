#include "Materials/DiffuseMaterial.h"
#include "Helpers/MathHelper.h"

DiffuseMaterial::DiffuseMaterial(const Color &albedo) {
    this->albedo = albedo;
    this->diffuseAmount = 0.7;
    this->ambientAmount = 0.05;
    this->specularAmount = 0.2;
    this->specularCoefficient = 2;
}

MaterialInfo DiffuseMaterial::scatter(const Ray &rayIn, const HitInfo &hit) const {
/*
    Vector3 scatter_direction = hit.normal + Vector3::randomInUnitSphere();

    if(scatter_direction.isNearZero()){
        scatter_direction = hit.normal;
    }

    Ray scattered = Ray(hit.point, scatter_direction, infinity, minRayDistance);
    Color attenuation = albedo;
*/

    return {false, albedo};
}
