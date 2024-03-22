#include "Samplers/UniformDistributionSuperSampler.h"
#include "Ray.h"
#include "HitInfo.h"
#include "Sphere.h"

UniformDistributionSuperSampler::UniformDistributionSuperSampler() = default;

UniformDistributionSuperSampler::UniformDistributionSuperSampler(Vector3 center, int samplingResolution) : Sampler(center, samplingResolution) {}

Color UniformDistributionSuperSampler::Sample(int x, int y) {

    Sphere sphere = Sphere(Vector3(0, 0, 1), 0.5f);

/*    Vector3 pixel_center = upperLeftViewportCorner
            + pixelDeltaU * (x + 0.5f)
            + pixelDeltaV * (y + 0.5f);

    Vector3 rayDirection = pixel_center - center;

    Ray ray = Ray(center, rayDirection);

    if(HitInfo info = sphere.hit(ray); info.intersected) {
        return Color(info.hitNormal.x + 1, info.hitNormal.y + 1, info.hitNormal.z + 1) * 0.5f;
    } else {
        // For sake of testing:
        Vector3 unit_direction = ray.direction.normalized();
        float t = 0.5f * (unit_direction.y + 1.0f);
        return Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;
    }*/

    Vector3 pixel_offset = upperLeftViewportCorner
            + pixelDeltaU * (x + InvertedSamplingResolution_ * 0.5f)
            + pixelDeltaV * (y + InvertedSamplingResolution_ * 0.5f);

    for(int i = 0; i < MaximalSamplingResolution_; ++i){
        for(int j = 0; j < MaximalSamplingResolution_; ++j) {

            Vector3 pixel_sample_intersection = pixel_offset
                    + pixelDeltaU * (InvertedSamplingResolution_ * i)
                    + pixelDeltaV * (InvertedSamplingResolution_ * j);

            Vector3 rayDirection = pixel_sample_intersection - center;

            Ray ray = Ray(center, rayDirection);

            if(HitInfo info = sphere.hit(ray); info.intersected) {
                ColorBuffer_[i * MaximalSamplingResolution_ + j] =
                        Color(info.hitNormal.x + 1, info.hitNormal.y + 1, info.hitNormal.z + 1) * 0.5f;
            } else {
                // For sake of testing:
                Vector3 unit_direction = ray.direction.normalized();
                float t = 0.5f * (unit_direction.y + 1.0f);
                ColorBuffer_[i * MaximalSamplingResolution_ + j] =
                        Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;
            }

        }
    }

    return Color::GetAverageColor(ColorBuffer_, MaximalSamplingResolution_ * MaximalSamplingResolution_);
}