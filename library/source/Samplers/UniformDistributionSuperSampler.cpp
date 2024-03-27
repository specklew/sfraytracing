#include "Samplers/UniformDistributionSuperSampler.h"
#include "HitInfo.h"
#include "Scene.h"

UniformDistributionSuperSampler::UniformDistributionSuperSampler() = default;

UniformDistributionSuperSampler::UniformDistributionSuperSampler(int samplingResolution) : Sampler(samplingResolution) {}

Color UniformDistributionSuperSampler::samplePixel(int x, int y) {

    Vector3 pixel_offset = upperLeftViewportCorner
                           + pixelDeltaU * (x + InvertedSamplingResolution_ * 0.5f)
                           + pixelDeltaV * (y + InvertedSamplingResolution_ * 0.5f);

    for(int i = 0; i < SamplingResolution_; ++i) {
        for (int j = 0; j < SamplingResolution_; ++j) {

            int sample_index = i * SamplingResolution_ + j;

            Vector3 pixel_sample_intersection = pixel_offset
                                                + pixelDeltaU * (InvertedSamplingResolution_ * i)
                                                + pixelDeltaV * (InvertedSamplingResolution_ * j);

            Ray ray = camera->calculateRay(pixel_sample_intersection);

            Vector3 unit_direction = ray.direction.normalized();
            float t = 0.5f * (unit_direction.y + 1.0f);
            ColorBuffer_[sample_index] =
                    Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;

            float min_distance = std::numeric_limits<float>::max();

            for(auto object : camera->scene->getObjects()){
                if(HitInfo info = object->hit(ray); info.intersected){
                    if(min_distance > info.distance) {
                        min_distance = info.distance;

                        ColorBuffer_[sample_index] = Color(
                                info.hitNormal.x + 1,
                                info.hitNormal.y + 1,
                                info.hitNormal.z + 1)
                                          * 0.5f;
                    }
                }
            }
        }
    }

    return Color::getAverageColor(ColorBuffer_, SamplingResolution_ * SamplingResolution_);
}