#include "Materials/MetalMaterial.h"

MetalMaterial::MetalMaterial(const Color &albedo) {
    this->albedo = albedo;
}

MaterialInfo MetalMaterial::scatter(const Ray &rayIn, const HitInfo &hit) const {
    Vector3 reflected = rayIn.direction.normalized().reflect(hit.normal);

    Ray scattered = Ray(hit.point, reflected, std::numeric_limits<float>::max(), 0.001f);
    Color attenuation = albedo;

    return {true, attenuation, scattered};
}
