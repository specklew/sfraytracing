#include "Materials/LambertianMaterial.h"

LambertianMaterial::LambertianMaterial(const Color &albedo) {
    this->albedo = albedo;
}

MaterialInfo LambertianMaterial::scatter(const Ray &rayIn, const HitInfo &hit) const {
    Vector3 scatter_direction = hit.normal + Vector3::randomInUnitSphere();

    if(scatter_direction.isNearZero()){
        scatter_direction = hit.normal;
    }

    Ray scattered = Ray(hit.point, scatter_direction, std::numeric_limits<float>::max(), 0.001f);
    Color attenuation = albedo;

    return {true, attenuation, scattered};
}
