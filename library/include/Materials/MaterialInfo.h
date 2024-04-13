#ifndef SF_RAYTRACING_MATERIALINFO_H
#define SF_RAYTRACING_MATERIALINFO_H

#include "Color.h"
#include "Ray.h"

struct MaterialInfo{
    bool wasScattered{false};
    Color attenuation{Color::Null};
    Ray scatteredRay{};
};

#endif //SF_RAYTRACING_MATERIALINFO_H
