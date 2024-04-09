#include "Materials/MetalMaterial.h"
#include "Helpers/MathHelper.h"

MetalMaterial::MetalMaterial(const Color &albedo) {
    this->albedo = albedo;
    this->diffuseAmount = 0.3;
    this->ambientAmount = 0.1;
    this->specularAmount = 0.5;
    this->specularCoefficient = 10.0;
}

MaterialInfo MetalMaterial::scatter(const Ray &rayIn, const HitInfo &hit) const {
    Vector3 reflected = rayIn.direction.normalized().reflect(hit.normal);

    Ray scattered = Ray(hit.point, reflected, infinity, minRayDistance);
    Color attenuation = albedo;

    return {true, attenuation, scattered};
}
