#ifndef SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H
#define SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H

#include "Sampler.h"

class AdaptiveSuperSampler : public Sampler {
public:
    AdaptiveSuperSampler();
    AdaptiveSuperSampler(int samplingResolution);
    Color samplePixel(int x, int y) override;

private:

    Color sampleRegion(Vector3 regionLocation, Vector3 deltaX, Vector3 deltaY, int depth);
    Color sampleIntersection(const Vector3& intersection);
};

#endif //SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H
