#ifndef SF_RAYTRACING_LIGHT_H
#define SF_RAYTRACING_LIGHT_H

#include "Color.h"
#include "Vector3.h"

class Scene;

class Light{
public:
    explicit Light(Vector3 position);
    Vector3 position;

    float intensity;
    Color color;
};

#endif //SF_RAYTRACING_LIGHT_H
