#include <cmath>
#include "Lights/PointLight.h"
#include "Helpers/MathHelper.h"
#include "Materials/Material.h"
#include "Scene.h"

#define PBRShading true

PointLight::PointLight(Vector3 position, precision intensity) : Light(position, intensity) {

}

Color PointLight::calculateLightColorForHit(HitInfo lastHit) {
#if PBRShading

    Color ambient = Color(0.03) * lastHit.material->albedo * (1.0 - lastHit.material->ao);
    //Average F0 for dielectric materials
    Color F0 = Color(0.04);
    // Get Proper F0 if material is not dielectric
    F0 = mix(F0, lastHit.material->albedo, lastHit.material->metallic);
    Vector3 N = lastHit.normal.normalized();
    Vector3 Ve = (lastHit.ray.origin - lastHit.point).normalized();

    float intensity = 1.0f;
    if(l.type == 1)
    {
        float l_dist = lightDist(hit.hit_point,l);
        intensity = l.intensity/(l_dist*l_dist);
    }
    vec3 l_dir = lightRay(hit.hit_point,l).rd;
    vec3 H = normalize(Ve + l_dir);
    return ambient + computeReflectance(N,Ve,F0,hit.material.color,l_dir,H,l.color,intensity,hit.material.metallic,hit.material.roughness);

#elif

    Vector3 hitLightVec = position - lastHit.point;
    Vector3 direction = hitLightVec.normalized();
    Ray ray = Ray(lastHit.point, direction, hitLightVec.length(), minRayDistance);

    Color ambient = lastHit.material->ambientAmount;

    if(HitInfo hit = scene->hit(ray); hit.intersected){
        return ambient;
    }

    float distanceSquared = hitLightVec.lengthSquared();

    Color diffuse = color * direction.dotProduct(lastHit.normal) * lastHit.material->diffuseAmount;
    Color specular = color * lastHit.material->specularAmount *
            std::pow(std::max(lastHit.ray.direction.dotProduct(direction.reflected(lastHit.normal)), precision(0)), lastHit.material->specularCoefficient);

    Color result = diffuse + specular;

    return result * intensity / distanceSquared + ambient;

#endif
}
