#include "Samplers/Sampler.h"
#include "HitInfo.h"
#include "Scene.h"

Sampler::Sampler() : Sampler(1) {}

Sampler::Sampler(int samplingResolution) {
    upperLeftViewportCorner = Vector3(0, 0, 0);
    pixelDeltaU = Vector3(0, 0, 0);
    pixelDeltaV = Vector3(0, 0, 0);
    SamplingResolution_ = samplingResolution;
    InvertedSamplingResolution_ = static_cast<precision>(1.0 / SamplingResolution_);
    ColorBuffer_ = new Color[SamplingResolution_ * SamplingResolution_];
}

Sampler::~Sampler() {
    delete[] ColorBuffer_;
}

Color Sampler::samplePoint(const Vector3& point) {

    Ray ray = camera->calculateRay(point);
    return camera->rayColor(ray);
}
