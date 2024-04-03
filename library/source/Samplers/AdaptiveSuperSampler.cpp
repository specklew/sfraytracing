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
    /*
    int colors_accumulated = 0;
    int samples_to_iterate = 0;
    int new_samples_to_iterate = 0;
    Color colors[2 ^ SamplingResolution_];

    Vector3 upper_left = upperLeftViewportCorner +
                         pixelDeltaU * x +
                         pixelDeltaV * y;

    Vector3 lower_right = upperLeftViewportCorner +
                          pixelDeltaU * (x + 1) +
                          pixelDeltaV * (y * 1);

    Vector3 first_center = upperLeftViewportCorner +
                           pixelDeltaU * (x + 0.5f) +
                           pixelDeltaV * (y + 0.5f);

    // MAX NUMBER WITH CACHING - TODO: IMPLEMENT CACHING
    int max_num_of_samples = pow(4, SamplingResolution_ - 1) + pow(pow(2, SamplingResolution_ - 1) + 1 , 2);

    unordered_map<Vector3, Color> points_colors = {};
    points_colors.reserve(max_num_of_samples);

    Vector3 points[max_num_of_samples * 2];
    Vector3 new_points[max_num_of_samples * 2];

    points[0] = first_center;
    points[1] = upper_left;
    points[3] = upper_left + pixelDeltaU;
    points[2] = upper_left + pixelDeltaV;
    points[4] = lower_right;

    samples_to_iterate = 5;

    for(int depth = 1; depth <= SamplingResolution_; ++depth){

        // Find colors for each new point to sample.
        for(auto point : points){
            if(points_colors[point] != Color::Null) continue;
            points_colors[point] = sampleIntersection(point);
        }

        for(int i = 0; i < samples_to_iterate * 0.2; ++i){
            for(int j = i + 1; j < i + 5; ++j){

                if(points_colors[points[i]] == points_colors[points[j]] || depth == SamplingResolution_){
                    colors[colors_accumulated++] = points_colors[points[i]] * pow(4, SamplingResolution_ - depth);
                    continue;
                }

                Vector3 delta = points[j] - points[i];

                new_points[new_samples_to_iterate] = points[i] + delta * 0.5f;
                new_points[new_samples_to_iterate + 1] = points[i];
                new_points[new_samples_to_iterate + 2] = points[i + 1];
                new_points[new_samples_to_iterate + 3] = points[i] + Vector3(delta.x, 0, 0);
                new_points[new_samples_to_iterate + 4] = points[i] + Vector3(0, delta.y, 0);

                new_samples_to_iterate += 5;

            }
        }

        for(int i = 0; i < new_samples_to_iterate; ++i){
            points[i] = new_points[i];
        }

        samples_to_iterate = new_samples_to_iterate;
        new_samples_to_iterate = 0;
    }

    return Color::getAverageColor(colors, pow(4, SamplingResolution_));
}*/

/*
        for(auto section : sampled){

            for(int i = 0; i < 4; ++i){
                if(section[0].second == section[i + 1].second){
                    colors[colors_accumulated++] = section[0].second;
                    continue;
                }

                std::pair<Vector3, Color> new_section[5];

                auto new_center = std::pair<Vector3, Color>();
                auto new_p1 = std::pair<Vector3, Color>();
                auto new_p2 = std::pair<Vector3, Color>();

                Vector3 delta = section[i + 1].first - section[0].first;

                new_center.first = section[0].first + delta  * 0.5f;
                new_p1.first = section[0].first + Vector3(delta.x, 0, 0);
                new_p2.first = section[0].first + Vector3(0, delta.y, 0);

                new_section[0] = new_center;
                new_section[1] = section[0];
                new_section[2] = section[i+1];
                new_section[3] = new_p1;
                new_section[4] = new_p2;

                sampled.push_back(new_section);
            }

            sampled.erase(std::remove(sampled.begin(), sampled.end(), section), sampled.end());
            delete[] section;
        }

        depth++;
    }

    for(auto section : sampled){
        colors[colors_accumulated++] = section[1].second;
    }*/

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
