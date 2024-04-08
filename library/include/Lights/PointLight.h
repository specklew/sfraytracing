#ifndef SF_RAYTRACING_POINTLIGHT_H
#define SF_RAYTRACING_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light{
public:
    PointLight(Vector3 position);
};

#endif //SF_RAYTRACING_POINTLIGHT_H
