#ifndef SF_RAYTRACING_POINTLIGHT_H
#define SF_RAYTRACING_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light{
public:
    explicit PointLight(Vector3 position, precision intensity);
    Color calculateLightColorForHit(HitInfo lastHit) override;
};

#endif //SF_RAYTRACING_POINTLIGHT_H
