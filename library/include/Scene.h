#ifndef SF_RAYTRACING_SCENE_H
#define SF_RAYTRACING_SCENE_H

#include <vector>
#include "Geometry.h"
#include "SFML/Graphics/Texture.hpp"
#include "Cameras/Camera.h"

class Scene{
public:
    Scene();
    ~Scene();

    Camera *camera{};

    void AddObject(Geometry *object);
    void RemoveObject(Geometry *object);

    sf::Texture RenderScene() const;

private:
    std::vector<Geometry*> objects;
};

#endif //SF_RAYTRACING_SCENE_H
