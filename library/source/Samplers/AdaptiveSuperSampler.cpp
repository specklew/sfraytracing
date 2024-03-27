#include <cmath>
#include <memory>
#include "Samplers/AdaptiveSuperSampler.h"
#include "HitInfo.h"
#include "Scene.h"

AdaptiveSuperSampler::AdaptiveSuperSampler() : Sampler(4) {};


AdaptiveSuperSampler::AdaptiveSuperSampler(int samplingResolution) : Sampler(samplingResolution) {}

Color AdaptiveSuperSampler::samplePixel(int x, int y) {

    int depth = 0;
    int colors_accumulated = 0;
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

    std::vector<std::shared_ptr<std::pair<Vector3, Color>>> sampled;

    std::shared_ptr<std::pair<Vector3, Color>> pc = std::make_shared<std::pair<Vector3, Color>>();
    std::shared_ptr<std::pair<Vector3, Color>> p1 = std::make_shared<std::pair<Vector3, Color>>();
    std::shared_ptr<std::pair<Vector3, Color>> p2 = std::make_shared<std::pair<Vector3, Color>>();
    std::shared_ptr<std::pair<Vector3, Color>> p3 = std::make_shared<std::pair<Vector3, Color>>();
    std::shared_ptr<std::pair<Vector3, Color>> p4 = std::make_shared<std::pair<Vector3, Color>>();

    pc->first = first_center;
    p1->first = upper_left;
    p2->first = upper_left + pixelDeltaU;
    p3->first = upper_left + pixelDeltaV;
    p4->first = lower_right;

    sampled.push_back(pc);
    sampled.push_back(p1);
    sampled.push_back(p2);
    sampled.push_back(p3);
    sampled.push_back(p4);

    while (depth < SamplingResolution_ && !sampled.empty()) {

        auto it = sampled.begin();

        do {
            if ((*it)->second != Color::Null) continue;
            (*it)->second = sampleIntersection((*it)->first);
        } while (++it != sampled.end());

        it = sampled.begin();

        do {
            std::shared_ptr<std::pair<Vector3, Color>> center = *it;

            for (int i = 1; i < 5; ++i) {
                std::shared_ptr<std::pair<Vector3, Color>> &current_point = *(it + i);

                if (current_point->second == center->second) {
                    colors[colors_accumulated++] = center->second;
                    continue;
                }

                auto new_p1 = center;
                auto new_p2 = current_point;

                auto new_center = std::make_shared<std::pair<Vector3, Color>>();
                auto new_p3 = std::make_shared<std::pair<Vector3, Color>>();
                auto new_p4 = std::make_shared<std::pair<Vector3, Color>>();

                Vector3 delta = new_p2->first - new_p1->first;

                new_center->first = new_p1->first + delta * 0.5f;
                new_p3->first = new_p1->first + Vector3(delta.x, 0, 0);
                new_p4->first = new_p1->first + Vector3(0, delta.y, 0);

                sampled.push_back(new_center);
                sampled.push_back(new_p1);
                sampled.push_back(new_p2);
                sampled.push_back(new_p3);
                sampled.push_back(new_p4);

            }

            sampled.erase(it, it + 5);
        } while ((it += 5) != sampled.end());

        depth++;
    }

    auto it = sampled.begin();
    while(it != sampled.end()){
        colors[colors_accumulated++] = (*(it+1))->second;
        it+=5;
    }

    return Color::getAverageColor(colors, colors_accumulated);
}

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
