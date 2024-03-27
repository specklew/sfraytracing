#ifndef SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H
#define SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H

#include "Sampler.h"

class AdaptiveSuperSampler : public Sampler {
public:
    AdaptiveSuperSampler();
    AdaptiveSuperSampler(int samplingResolution);
    Color samplePixel(int x, int y) override;

private:

    Color sampleIntersection(const Vector3& intersection);
};

#endif //SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H
