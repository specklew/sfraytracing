#include "Scene.h"
#include "Cameras/PerspectiveCamera.h"
#include "Samplers/UniformDistributionSuperSampler.h"
#include "Cameras/OrthographicCamera.h"

Scene::Scene(){
    camera = new OrthographicCamera(
            Vector3(0, 0, 0),
            Vector3(0, 0, 1),
            new UniformDistributionSuperSampler({0,0,0}, {0,0,1}, 4));
};

void Scene::addObject(Geometry *object) {
    objects.push_back(object);
}

void Scene::removeObject(Geometry *object) {
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

sf::Texture Scene::renderScene() const {
    return camera->renderFrame(1600);
}

Scene::~Scene() {
    delete camera;
}

std::vector<Geometry*> Scene::getObjects() {
    return objects;
}
