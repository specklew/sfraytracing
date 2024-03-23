#include "Samplers/UniformDistributionSuperSampler.h"
#include "HitInfo.h"
#include "Sphere.h"
#include "Scene.h"

UniformDistributionSuperSampler::UniformDistributionSuperSampler() = default;

UniformDistributionSuperSampler::UniformDistributionSuperSampler(Vector3 center,
                                                                 Vector3 direction,
                                                                 int samplingResolution) :
                                                                 Sampler(center, direction, samplingResolution) {}

Color UniformDistributionSuperSampler::sample(std::vector<Ray> scanlines){

    for(int i = 0; i < scanlines.size(); ++i){

        // Background gradient:
        Vector3 unit_direction = scanlines[i].direction.normalized();
        float t = 0.5f * (unit_direction.y + 1.0f);
        ColorBuffer_[i] =
                Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;

        float min_distance = std::numeric_limits<float>::max();

        for(auto object : camera->scene->getObjects()){
            if(HitInfo info = object->hit(scanlines[i]); info.intersected){
                if(min_distance > info.distance) {
                    min_distance = info.distance;

                    ColorBuffer_[i] = Color(
                            info.hitNormal.x + 1,
                            info.hitNormal.y + 1,
                            info.hitNormal.z + 1)
                                      * 0.5f;
                }
            }
        }
    }

    return Color::getAverageColor(ColorBuffer_, SamplingResolution_ * SamplingResolution_);
}

std::vector<Vector3> UniformDistributionSuperSampler::calculateSamplePoints(int x, int y) {

    std::vector<Vector3> points;

    Vector3 pixel_offset = upperLeftViewportCorner
                           + pixelDeltaU * (x + InvertedSamplingResolution_ * 0.5f)
                           + pixelDeltaV * (y + InvertedSamplingResolution_ * 0.5f);

    for(int i = 0; i < SamplingResolution_; ++i) {
        for (int j = 0; j < SamplingResolution_; ++j) {

            Vector3 pixel_sample_intersection = pixel_offset
                                                + pixelDeltaU * (InvertedSamplingResolution_ * i)
                                                + pixelDeltaV * (InvertedSamplingResolution_ * j);

            points.push_back(pixel_sample_intersection);
        }
    }

    return points;
}
