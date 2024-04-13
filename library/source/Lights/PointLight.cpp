#include "Lights/PointLight.h"
#include "Helpers/MathHelper.h"
#include "Scene.h"

PointLight::PointLight(Vector3 position) : Light(position) {

}

Color PointLight::calculateLightColorForHit(HitInfo lastHit) {
    Vector3 hitLightVec = position - lastHit.point;
    Vector3 direction = (hitLightVec).normalized();
    Ray ray(lastHit.point, direction, hitLightVec.length(), minRayDistance);

    if(HitInfo hit = scene->hit(ray); hit.intersected){
        return Color::Black;
    }

    float distanceSquared = hitLightVec.lengthSquared();

    return color * intensity / distanceSquared;
}
