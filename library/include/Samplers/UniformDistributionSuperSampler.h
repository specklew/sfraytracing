#ifndef SF_RAYTRACING_UNIFORMDISTRIBUTIONSUPERSAMPLER_H
#define SF_RAYTRACING_UNIFORMDISTRIBUTIONSUPERSAMPLER_H

#include "Sampler.h"

class UniformDistributionSuperSampler : public Sampler {
public:
    UniformDistributionSuperSampler();
    explicit UniformDistributionSuperSampler(int samplingResolution);

    Color samplePixel(int x, int y) override;
};

#endif //SF_RAYTRACING_UNIFORMDISTRIBUTIONSUPERSAMPLER_H
