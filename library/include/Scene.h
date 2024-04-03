#ifndef SF_RAYTRACING_SCENE_H
#define SF_RAYTRACING_SCENE_H

#include <vector>
#include "Geometry.h"
#include "SFML/Graphics/Texture.hpp"
#include "Cameras/Camera.h"

class Scene{
public:
    Scene();
    explicit Scene(Camera* camera);

    ~Scene();

    Camera *camera{};

    void addObject(Geometry *object);
    void removeObject(Geometry *object);
    std::vector<Geometry*> getObjects();

    HitInfo hit(const Ray& ray) const;

    [[nodiscard]] sf::Texture renderScene(int width) const;

private:
    std::vector<Geometry*> objects;
};

#endif //SF_RAYTRACING_SCENE_H
