#include "Samplers/UniformDistributionSuperSampler.h"

UniformDistributionSuperSampler::UniformDistributionSuperSampler() = default;

UniformDistributionSuperSampler::UniformDistributionSuperSampler(int samplingResolution) : Sampler(samplingResolution) {}

Color UniformDistributionSuperSampler::samplePixel(int x, int y) {

    Color buffer[SamplingResolution_ * SamplingResolution_];

    Vector3 pixel_offset = upperLeftViewportCorner
                           + pixelDeltaU * (x + InvertedSamplingResolution_ * 0.5)
                           + pixelDeltaV * (y + InvertedSamplingResolution_ * 0.5);

    for(int i = 0; i < SamplingResolution_; ++i) {
        for (int j = 0; j < SamplingResolution_; ++j) {

            int sample_index = i * SamplingResolution_ + j;

            Vector3 pixel_sample_intersection = pixel_offset
                                                + pixelDeltaU * (InvertedSamplingResolution_ * i)
                                                + pixelDeltaV * (InvertedSamplingResolution_ * j);

            buffer[sample_index] = samplePoint(pixel_sample_intersection);
        }
    }

    return Color::getAverageColor(buffer, SamplingResolution_ * SamplingResolution_);
}