#ifndef SF_RAYTRACING_SAMPLER_H
#define SF_RAYTRACING_SAMPLER_H

#include "Color.h"
#include "Vector3.h"
#include "Ray.h"
#include "vector"

class Camera;

class Sampler{
public:
    virtual ~Sampler();
    Sampler();
    explicit Sampler(int samplingResolution);

    Vector3 upperLeftViewportCorner;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;

    Camera* camera;

    virtual Color samplePixel(int x, int y) = 0;

protected:
    int SamplingResolution_;
    double InvertedSamplingResolution_;
    Color *ColorBuffer_;

    virtual Color samplePoint(const Vector3& point);
};


#endif //SF_RAYTRACING_SAMPLER_H
