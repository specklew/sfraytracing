#include "Samplers/Sampler.h"

Sampler::Sampler() {
    center = Vector3(0.0f, 0.0f, 0.0f);
    upperLeftViewportCorner = Vector3(0.0f, 0.0f, 0.0f);
    pixelDeltaU = Vector3(0.0f, 0.0f, 0.0f);
    pixelDeltaV = Vector3(0.0f, 0.0f, 0.0f);
    MaximalSamplingResolution_ = 1;
    InvertedSamplingResolution_ = static_cast<float>(1.0f / MaximalSamplingResolution_);
    ColorBuffer_ = new Color[MaximalSamplingResolution_ * MaximalSamplingResolution_];
}

Sampler::~Sampler() {
    delete[] ColorBuffer_;
}

Sampler::Sampler(Vector3 center, int samplingResolution) {
    this->center = center;
    upperLeftViewportCorner = Vector3(0.0f, 0.0f, 0.0f);
    pixelDeltaU = Vector3(0.0f, 0.0f, 0.0f);
    pixelDeltaV = Vector3(0.0f, 0.0f, 0.0f);
    MaximalSamplingResolution_ = samplingResolution;
    InvertedSamplingResolution_ = static_cast<float>(1.0f / MaximalSamplingResolution_);
    ColorBuffer_ = new Color[MaximalSamplingResolution_ * MaximalSamplingResolution_];
}

int Sampler::GetMaximalSamplingResolution() const {
    return MaximalSamplingResolution_;
}

void Sampler::SetMaximalSamplingResolution(int maximalSamplingResolution) {
    MaximalSamplingResolution_ = maximalSamplingResolution;
    InvertedSamplingResolution_ = static_cast<float>(1.0f / MaximalSamplingResolution_);
    delete[] ColorBuffer_;
    ColorBuffer_ = new Color[MaximalSamplingResolution_ * MaximalSamplingResolution_];
}
