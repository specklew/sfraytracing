#include "Scene.h"
#include "Cameras/PerspectiveCamera.h"
#include "Samplers/UniformDistributionSuperSampler.h"
#include "Cameras/OrthographicCamera.h"

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
