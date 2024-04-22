#include <cmath>
#include "Lights/PointLight.h"
#include "Helpers/MathHelper.h"
#include "Materials/Material.h"
#include "Scene.h"
#include "PBR.h"

#define PBRShading true

PointLight::PointLight(Vector3 position, precision intensity) : Light(position, intensity) {

}

Color PointLight::calculateLightColorForHit(HitInfo hit) {
#if PBRShading

    Color ambient = Color(0.03) * hit.material->color * (1.0 - hit.material->ambientOcclusion);
    //Average F0 for dielectric materials
    Color F0 = Color(0.04);
    // Get Proper F0 if material is not dielectric
    F0 = mix(F0, hit.material->color, hit.material->metallic);
    Vector3 N = hit.normal.normalized();
    Vector3 Ve = (hit.ray.origin - hit.point).normalized();

    Vector3 hit_light_segment = position - hit.point;

    precision l_dist = hit_light_segment.lengthSquared();
    precision light_intensity = intensity / l_dist;

    Vector3 l_dir = hit_light_segment.normalized();
    Vector3 H = (Ve + l_dir).normalized();
    return ambient + computeReflectance(N, Ve, F0, hit.material->color, l_dir, H, color, light_intensity, hit.material->metallic, hit.material->roughness, hit.material->anisotropy);

#elif

    Vector3 hit_light_segment = position - hit.point;
    Vector3 direction = hit_light_segment.normalized();
    Ray ray = Ray(hit.point, direction, hit_light_segment.length(), minRayDistance);

    Color ambient = hit.material->ambientAmount;

    if(HitInfo hit = scene->hit(ray); hit.intersected){
        return ambient;
    }

    float distanceSquared = hit_light_segment.lengthSquared();

    Color diffuse = color * direction.dotProduct(hit.normal) * hit.material->diffuseAmount;
    Color specular = color * hit.material->specularAmount *
            std::pow(std::max(hit.ray.direction.dotProduct(direction.reflected(hit.normal)), precision(0)), hit.material->specularCoefficient);

    Color result = diffuse + specular;

    return result * light_intensity / distanceSquared + ambient;

#endif
}
