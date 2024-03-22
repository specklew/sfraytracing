#ifndef SF_RAYTRACING_SAMPLER_H
#define SF_RAYTRACING_SAMPLER_H

#include "Color.h"
#include "Vector3.h"

class Sampler{
public:
    virtual ~Sampler();
    Sampler();
    Sampler(Vector3 center, int samplingResolution);

    Vector3 center;
    Vector3 upperLeftViewportCorner;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;

    [[nodiscard]] int GetMaximalSamplingResolution() const;
    void SetMaximalSamplingResolution(int maximalSamplingResolution);

    virtual Color Sample(int x, int y) = 0;

protected:
    int MaximalSamplingResolution_;
    float InvertedSamplingResolution_;
    Color *ColorBuffer_;
};


#endif //SF_RAYTRACING_SAMPLER_H
