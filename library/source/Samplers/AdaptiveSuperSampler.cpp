#include <cmath>
#include <memory>
#include <unordered_map>
#include "Samplers/AdaptiveSuperSampler.h"
#include "HitInfo.h"
#include "Scene.h"

using namespace std;

AdaptiveSuperSampler::AdaptiveSuperSampler() : Sampler(4) {};

AdaptiveSuperSampler::AdaptiveSuperSampler(int samplingResolution) : Sampler(samplingResolution) {}

Color AdaptiveSuperSampler::samplePixel(int x, int y) {

    Vector3 upper_left = upperLeftViewportCorner +
                         pixelDeltaU * x +
                         pixelDeltaV * y;

    return sampleRegion(upper_left, pixelDeltaU, pixelDeltaV, 1);
}

Color AdaptiveSuperSampler::sampleIntersection(const Vector3& intersection) {
    Color color;
    Ray ray = camera->calculateRay(intersection);

    Vector3 unit_direction = ray.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    color = Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;

    float min_distance = std::numeric_limits<float>::max();

    for(auto object : camera->scene->getObjects()){
        if(HitInfo info = object->hit(ray); info.intersected){
            if(min_distance > info.distance) {
                min_distance = info.distance;

                color = Color(
                        info.hitNormal.x + 1,
                        info.hitNormal.y + 1,
                        info.hitNormal.z + 1)
                                             * 0.5f;
            }
        }
    }

    return color;
}

Color AdaptiveSuperSampler::sampleRegion(Vector3 regionLocation, Vector3 deltaX, Vector3 deltaY, int depth) {
    Color center;
    Color colors[4];

    Vector3 half_delta_x = deltaX * 0.5f;
    Vector3 half_delta_y = deltaY * 0.5f;

    center = sampleIntersection(regionLocation + half_delta_x + half_delta_y);
    colors[0] = sampleIntersection(regionLocation);
    colors[1] = sampleIntersection(regionLocation + deltaX);
    colors[2] = sampleIntersection(regionLocation + deltaY);
    colors[3] = sampleIntersection(regionLocation + deltaX + deltaY);

    if(depth >= SamplingResolution_){
        return Color::getAverageColor(colors, 4);
    }

    if(center != colors[0]) colors[0] = sampleRegion(regionLocation, deltaX * 0.5f, deltaY * 0.5f, depth + 1);
    if(center != colors[1]) colors[1] = sampleRegion(regionLocation + deltaX, deltaX * 0.5f, deltaY * 0.5f, depth + 1);
    if(center != colors[2]) colors[2] = sampleRegion(regionLocation + deltaY, deltaX * 0.5f, deltaY * 0.5f, depth + 1);
    if(center != colors[3]) colors[3] = sampleRegion(regionLocation + deltaX +deltaY, deltaX * 0.5f, deltaY * 0.5f, depth + 1);

    return Color::getAverageColor(colors, 4);

}
