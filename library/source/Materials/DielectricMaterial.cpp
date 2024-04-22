#include <cmath>
#include "Materials/DielectricMaterial.h"

DielectricMaterial::DielectricMaterial(const Color &albedo, precision refractionIndex) {
    this->color = albedo;
    this->refractionIndex = refractionIndex;
}

MaterialInfo DielectricMaterial::scatter(const Ray &rayIn, const HitInfo &hit) const {
    Color attenuation(1,1,1);
    precision one = 1;
    precision ri = hit.frontFace ? (one / refractionIndex) : refractionIndex;

    Vector3 unit_dir = rayIn.direction.normalized();
    Vector3 refracted = unit_dir.refracted(hit.normal, ri).normalized();

    return {true, attenuation, {hit.point, refracted}};
}
