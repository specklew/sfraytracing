#ifndef SF_RAYTRACING_SCENE_H
#define SF_RAYTRACING_SCENE_H

#include <vector>
#include "Geometry.h"
#include "SFML/Graphics/Texture.hpp"
#include "Cameras/Camera.h"

class Scene{
public:
    static Scene& getInstance(){
        static Scene instance;
        return instance;
    }

    Scene(Scene const&) = delete;
    void operator=(Scene const&) = delete;

    Camera *camera{};

    void addObject(Geometry *object);
    void removeObject(Geometry *object);
    std::vector<Geometry*> getObjects();

    [[nodiscard]] sf::Texture renderScene() const;

private:
    Scene();
    ~Scene();

    std::vector<Geometry*> objects;
};

#endif //SF_RAYTRACING_SCENE_H
