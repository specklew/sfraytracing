#include "Materials/LambertianMaterial.h"
#include "Helpers/MathHelper.h"

LambertianMaterial::LambertianMaterial(const Color &albedo) {
    this->albedo = albedo;
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
