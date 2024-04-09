#include "Materials/LambertianMaterial.h"
#include "Helpers/MathHelper.h"

LambertianMaterial::LambertianMaterial(const Color &albedo) {
    this->albedo = albedo;
    this->diffuseAmount = 0.7f;
    this->ambientAmount = 0.05f;
    this->specularAmount = 0.1f;
    this->specularCoefficient = 0.5f;
}

MaterialInfo LambertianMaterial::scatter(const Ray &rayIn, const HitInfo &hit) const {
    Vector3 scatter_direction = hit.normal + Vector3::randomInUnitSphere();

    if(scatter_direction.isNearZero()){
        scatter_direction = hit.normal;
    }

    Ray scattered = Ray(hit.point, scatter_direction, infinity, minimalDistance);
    Color attenuation = albedo;

    return {true, attenuation, scattered};
}
