#ifndef SF_RAYTRACING_LIGHT_H
#define SF_RAYTRACING_LIGHT_H

#include "Color.h"
#include "Vector3.h"

class Scene;
struct HitInfo;

class Light{
public:
    explicit Light(Vector3 position, precision intensity);
    Scene *scene;
    Vector3 position;

    precision intensity;
    Color color;

    virtual Color calculateLightColorForHit(HitInfo lastHit) = 0;
};

#endif //SF_RAYTRACING_LIGHT_H
