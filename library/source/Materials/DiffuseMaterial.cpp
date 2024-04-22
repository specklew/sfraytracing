#include "Materials/DiffuseMaterial.h"
#include "Helpers/MathHelper.h"

DiffuseMaterial::DiffuseMaterial(const Color &albedo) {
    this->color = albedo;
    this->diffuseAmount = 0.7;
    this->ambientAmount = 0.05;
    this->specularAmount = 0.2;
    this->specularCoefficient = 2;
    this->anisotropy = 0.0;
}

DiffuseMaterial::DiffuseMaterial(const Color &albedo, precision roughness, precision metallic,
                                 precision ambientOcclusion, precision anisotropy) {

    this->color = albedo;
    this->roughness = roughness;
    this->metallic = metallic;
    this->ambientOcclusion = ambientOcclusion;
    this->anisotropy = anisotropy;
}

MaterialInfo DiffuseMaterial::scatter(const Ray &rayIn, const HitInfo &hit) const {
    return {false, color};
}
