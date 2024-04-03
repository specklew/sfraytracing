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
    Sampler(int samplingResolution);

    Vector3 center;
    Vector3 direction;
    Vector3 upperLeftViewportCorner;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;

    Camera* camera;

    [[nodiscard]] int GetMaximalSamplingResolution() const;
    void SetMaximalSamplingResolution(int maximalSamplingResolution);

    virtual Color samplePixel(int x, int y) = 0;

protected:
    int SamplingResolution_;
    float InvertedSamplingResolution_;
    Color *ColorBuffer_;

    virtual Color samplePoint(const Vector3& point);
};


#endif //SF_RAYTRACING_SAMPLER_H
