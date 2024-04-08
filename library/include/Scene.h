#ifndef SF_RAYTRACING_SCENE_H
#define SF_RAYTRACING_SCENE_H

#include <vector>
#include "Geometry/Geometry.h"
#include "SFML/Graphics/Texture.hpp"
#include "Cameras/Camera.h"
#include "Lights/Light.h"

class Scene{
public:
    Scene();
    explicit Scene(Camera* camera);

    ~Scene();

    Camera *camera{};

    void addObject(Geometry *object);
    void removeObject(Geometry *object);
    std::vector<Geometry*> getObjects();

    void addLight(Light *light);
    void removeLight(Light *light);
    std::vector<Light*> getLights();

    [[nodiscard]] HitInfo hit(const Ray& ray) const;
    [[nodiscard]] Color hitLights(const HitInfo &lastHit) const;

    [[nodiscard]] sf::Texture renderScene(int width) const;

private:
    std::vector<Geometry*> objects;
    std::vector<Light*> lights;
};

#endif //SF_RAYTRACING_SCENE_H
