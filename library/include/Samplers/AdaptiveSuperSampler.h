#ifndef SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H
#define SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H

#include "Sampler.h"

class AdaptiveSuperSampler : public Sampler {
public:
    Color samplePixel(int x, int y) override;
};

#endif //SF_RAYTRACING_ADAPTIVESUPERSAMPLER_H
