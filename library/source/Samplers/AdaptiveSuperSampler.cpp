#include <memory>
#include "Samplers/AdaptiveSuperSampler.h"
#include "HitInfo.h"
#include "Scene.h"

AdaptiveSuperSampler::AdaptiveSuperSampler() : Sampler({}, {}, 4) {};


AdaptiveSuperSampler::AdaptiveSuperSampler(Vector3 center, Vector3 direction, int samplingResolution) : Sampler(center,
                                                                                                                direction,
                                                                                                                4^samplingResolution) {}

Color AdaptiveSuperSampler::samplePixel(int x, int y) {

    auto center = std::make_shared<Vector3>(upperLeftViewportCorner + pixelDeltaU * (x + 0.5f)+ pixelDeltaV * (y + 0.5f));

    auto center_col = std::make_shared<Color>(sampleRay(camera->calculateRay(*center)));

    int depth = 1;
    int colors_accumulated = 0;

    std::vector<std::pair<std::shared_ptr<Vector3>, std::shared_ptr<Color>>*> sections;

    auto *first_section = new std::pair<std::shared_ptr<Vector3>, std::shared_ptr<Color>>[5];

    auto p1 = std::make_shared<Vector3>();
    auto p2 = std::make_shared<Vector3>();
    auto p3 = std::make_shared<Vector3>();
    auto p4 = std::make_shared<Vector3>();

    *p1 = upperLeftViewportCorner + pixelDeltaU * x + pixelDeltaV * y;
    *p2 = upperLeftViewportCorner + pixelDeltaU * (x + 1) + pixelDeltaV;
    *p3 = upperLeftViewportCorner + pixelDeltaU * x + pixelDeltaV * (y + 1);
    *p4 = upperLeftViewportCorner + pixelDeltaU * (x + 1) + pixelDeltaV * (y + 1);

    first_section[0] = {center, center_col};
    first_section[1] = {p1, nullptr};
    first_section[2] = {p2, nullptr};
    first_section[3] = {p3, nullptr};
    first_section[4] = {p4, nullptr};

    sections.push_back(first_section);

    while(depth < SamplingResolution_ && !sections.empty()){

        for(auto section : sections){

            for(int i = 0; i < 5; ++i){
                if(section[i].second == nullptr){
                    auto color = std::make_shared<Color>();
                    *color = sampleRay(camera->calculateRay(*section[i].first));
                    section[i].second = color;
                }

                if(i == 0){
                    continue;
                }

                if(*section[0].second != *section[i].second){

                    float dX = section[i].first->x - section[0].first->x;
                    float dY = section[i].first->y - section[0].first->y;

                    Vector3 deltaX = Vector3(dX, 0, 0);
                    Vector3 deltaY = Vector3(0, dY, 0);

                    auto new_center = std::make_shared<Vector3>(*section[0].first - (deltaX + deltaY) * 0.5);

                    auto *new_section = new std::pair<std::shared_ptr<Vector3>, std::shared_ptr<Color>>[5];

                    auto new_p1 = std::make_shared<Vector3>(*section[0].first - deltaY);
                    auto new_p4 = std::make_shared<Vector3>(*section[0].first - deltaX);

                    new_section[0] = {new_center, nullptr};
                    new_section[1] = {new_p1, nullptr};
                    new_section[2] = {section[i].first, section[i].second};
                    new_section[3] = {section[0].first, section[0].second};
                    new_section[4] = {new_p4, nullptr};

                    sections.push_back(new_section);
                } else {
                    ColorBuffer_[colors_accumulated++] = *section[0].second;
                }
            }

            sections.erase(std::remove(sections.begin(), sections.end(), section), sections.end());
            delete[] section;
        }

        depth++;
    }

    for(auto section : sections){
        for(int i = 0; i < 5; ++i){
            if(section[i].second != nullptr){
                ColorBuffer_[colors_accumulated++] = *section[i].second;
                sections.erase(std::remove(sections.begin(), sections.end(), section), sections.end());
                break;
            }
        }
        delete[] section;
    }


    return Color::getAverageColor(ColorBuffer_, colors_accumulated);
}

Color AdaptiveSuperSampler::sampleSection(Vector3 p1, Vector3 p2, Vector3 deltaX, Vector3 deltaY, int depth) {
    Vector3 points[4];

    points[0] = p1;
    points[1] = p1 + deltaX;
    points[2] = p2;
    points[3] = p1 + deltaY;

    Vector3 center = p1 + ((deltaX + deltaY) * 0.5);
    Ray ray = camera->calculateRay(center);

    Color colors[5];
    colors[0] = sampleRay(ray);

    if(depth >= SamplingResolution_){
        return colors[0];
    }

    for(int i = 0; i < 4; ++i){
        ray = camera->calculateRay(points[i]);
        Color c = sampleRay(ray);

        if(colors[0] != c){
            Vector3 new_deltaX = deltaX * 0.5;
            Vector3 new_deltaY = deltaY * 0.5;

            if(Vector3 cp = points[i] - center; (cp.x > 0 && cp.y > 0) || (cp.x < 0 && cp.y < 0)){
                new_deltaX = -new_deltaX;
            }

            if(center.x > points[i].x){
                colors[i + 1] = sampleSection(center, points[i], new_deltaX, new_deltaY, depth + 1);
            }else{
                colors[i + 1] = sampleSection(points[i], center, new_deltaX, new_deltaY, depth + 1);
            }

        }
    }

    return Color::getAverageColor(colors, 5);
}

Color AdaptiveSuperSampler::sampleRay(const Ray &ray) {
    Vector3 unit_direction = ray.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    Color c = Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;

    float min_distance = std::numeric_limits<float>::max();

    for(auto object : camera->scene->getObjects()){
        if(HitInfo info = object->hit(ray); info.intersected){
            if(min_distance > info.distance) {
                min_distance = info.distance;

                c = Color(
                        info.hitNormal.x + 1,
                        info.hitNormal.y + 1,
                        info.hitNormal.z + 1)
                    * 0.5f;
            }
        }
    }
    return c;
}
