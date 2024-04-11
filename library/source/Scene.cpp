#include <cmath>
#include "Scene.h"
#include "Cameras/PerspectiveCamera.h"
#include "Samplers/UniformDistributionSuperSampler.h"
#include "Helpers/MathHelper.h"
#include "Materials/Material.h"

Scene::Scene() : Scene(
        new PerspectiveCamera(
        Vector3(0, 0, 0),
        Vector3(0, 0, 1),
        new UniformDistributionSuperSampler(4))){};

Scene::Scene(Camera *camera) {
    this->camera = camera;
    camera->scene = this;
}

void Scene::addObject(Geometry *object) {
    objects.push_back(object);
}

void Scene::removeObject(Geometry *object) {
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

sf::Texture Scene::renderScene(int imageWidth) const {
    return camera->renderFrame(imageWidth);
}

Scene::~Scene() {
    delete camera;
}

std::vector<Geometry*> Scene::getObjects() {
    return objects;
}

HitInfo Scene::hit(const Ray &ray) const {
    HitInfo result;
    precision min_distance = ray.distance;

    for(auto object : objects){
        if(HitInfo info = object->hit(ray); info.intersected){
            if(min_distance > info.distance) {
                min_distance = info.distance;
                result = info;
            }
        }
    }

    return result;
}

Color Scene::hitLights(const HitInfo &lastHit, const Vector3& cameraDirection) const {
    Color result(0, 0, 0);

    for(auto light : lights){

        Vector3 direction = (light->position - lastHit.point).normalized();
        Ray ray(lastHit.point, direction, infinity, minRayDistance);

        if(HitInfo hit = this->hit(ray); !hit.intersected){
            // no distinction between different lights. TODO: support other types

            precision minMaxPrecision = 0;

            Color diffuse = lastHit.material->albedo * lastHit.normal.dotProduct(direction) * lastHit.material->diffuseAmount;
            Color specular = lastHit.material->albedo * lastHit.material->specularAmount *
                             pow(std::max(lastHit.ray.direction.dotProduct(direction.reflected(lastHit.normal)), minMaxPrecision), lastHit.material->specularCoefficient);

            result += diffuse + specular;
        }

    }

    result += lastHit.material->albedo * lastHit.material->ambientAmount;


    return result;
}

void Scene::addLight(Light *light) {
    lights.push_back(light);
}

void Scene::removeLight(Light *light) {
    lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
}

std::vector<Light *> Scene::getLights() {
    return lights;
}
