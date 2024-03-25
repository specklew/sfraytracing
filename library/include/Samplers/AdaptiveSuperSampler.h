#ifndef SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H
#define SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H

#include "Sampler.h"

class AdaptiveSuperSampler : public Sampler {
public:
    AdaptiveSuperSampler();
    AdaptiveSuperSampler(Vector3 center, Vector3 direction, int samplingResolution);
    Color samplePixel(int x, int y) override;

private:
    Color sampleSection(Vector3 p1, Vector3 p2, Vector3 deltaX, Vector3 deltaY, int depth);

    Color sampleRay(const Ray &ray);
};

#endif //SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H
