#include "Samplers/Sampler.h"

Sampler::Sampler() : Sampler(1) {}

Sampler::Sampler(int samplingResolution) {
    center = {};
    direction = {};
    upperLeftViewportCorner = Vector3(0.0f, 0.0f, 0.0f);
    pixelDeltaU = Vector3(0.0f, 0.0f, 0.0f);
    pixelDeltaV = Vector3(0.0f, 0.0f, 0.0f);
    SamplingResolution_ = samplingResolution;
    InvertedSamplingResolution_ = static_cast<float>(1.0f / SamplingResolution_);
    ColorBuffer_ = new Color[SamplingResolution_ * SamplingResolution_];
}

Sampler::~Sampler() {
    delete[] ColorBuffer_;
}

int Sampler::GetMaximalSamplingResolution() const {
    return SamplingResolution_;
}

void Sampler::SetMaximalSamplingResolution(int maximalSamplingResolution) {
    SamplingResolution_ = maximalSamplingResolution;
    InvertedSamplingResolution_ = static_cast<float>(1.0f / SamplingResolution_);
    delete[] ColorBuffer_;
    ColorBuffer_ = new Color[SamplingResolution_ * SamplingResolution_];
}
