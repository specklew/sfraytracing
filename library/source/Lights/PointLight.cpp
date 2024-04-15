#include <cmath>
#include "Lights/PointLight.h"
#include "Helpers/MathHelper.h"
#include "Materials/Material.h"
#include "Scene.h"

PointLight::PointLight(Vector3 position, precision intensity) : Light(position, intensity) {

}

Color PointLight::calculateLightColorForHit(HitInfo lastHit) {
    Vector3 hitLightVec = position - lastHit.point;
    Vector3 direction = (hitLightVec).normalized();
    Ray ray(lastHit.point, direction, hitLightVec.length(), minRayDistance);

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
}
