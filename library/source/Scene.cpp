#include "Scene.h"
#include "Cameras/PerspectiveCamera.h"
#include "Samplers/UniformDistributionSuperSampler.h"

Scene::Scene(){
    camera = new PerspectiveCamera(
            Vector3(0, 0, 0),
            Vector3(0, 0, 1),
            new UniformDistributionSuperSampler(Vector3(0,0,0), 16));
};

void Scene::AddObject(Geometry *object) {
    objects.push_back(object);
}

void Scene::RemoveObject(Geometry *object) {
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

sf::Texture Scene::RenderScene() const {
    return camera->RenderFrame(1600);
}

Scene::~Scene() {
    for (auto object : objects) {
        delete object;
    }

    delete camera;
}
