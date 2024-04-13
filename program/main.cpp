#include <iostream>

#include <cfloat>
#include <cmath>
#include <vector>
#include "Vector3.h"
#include "Geometry/Sphere.h"
#include "Ray.h"
#include "Geometry/Plane.h"
#include "Geometry/Triangle.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Cameras/PerspectiveCamera.h"
#include "Scene.h"
#include "Samplers/UniformDistributionSuperSampler.h"
#include "Materials/LambertianMaterial.h"
#include "Materials/MetalMaterial.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Helpers/LoggerHelper.h"
#include "Lights/PointLight.h"

using namespace std::chrono;
using namespace std;

int main() {

    auto start = high_resolution_clock::now();

    int image_width = 1600;

    //Camera setup
    Camera* camera = new PerspectiveCamera(
            Vector3(0, 0.5, 0),
            Vector3(0, 0, -1),
            new UniformDistributionSuperSampler(4));

    // Scene setup
    Scene scene = Scene(camera);

    std::shared_ptr<Material> material = std::make_shared<LambertianMaterial>(LambertianMaterial(Color(0.5, 0.5, 0.5)));
    std::shared_ptr<Material> material1 = std::make_shared<MetalMaterial>(MetalMaterial(Color(1, 0,0)));
    std::shared_ptr<Material> material2 = std::make_shared<LambertianMaterial>(LambertianMaterial({0.5, 0.0, 0.0}));

    Sphere s1 = Sphere({-0.5, 0.5, -1}, 0.5f, material2);
    Sphere s2 = Sphere({0.5, 0.5, -1}, 0.5, material1);
    Triangle t1 = Triangle({1.25, 0, -1}, {0.25, 1, -1.5}, {0.25, -0.5, -1}, material1);

    Plane ground = Plane({0, 0, 0}, {0, 1, 0}, material);
    Plane leftWall = Plane({3,0,0}, {-1,0,0}, material);
    Plane rightWall = Plane({-3,0,0}, {1,0,0}, material);
    Plane ceiling = Plane({0,3,0}, {0,-1,0}, material);
    //Sphere ground = Sphere({0, -100.5, -1}, 100.0f, material);
    Sphere skyMirror = Sphere({0, 102, -1}, 100.0f, material1);

    scene.addObject(&s1);
    scene.addObject(&s2);
    //scene.addObject(&t1);
    scene.addObject(&ground);
    scene.addObject(&leftWall);
    scene.addObject(&rightWall);
    scene.addObject(&ceiling);
    //scene.addObject(&skyMirror);

    auto light = PointLight({2, 2, 2});

    scene.addLight(&light);

    sf::Texture rendered_image = scene.renderScene(image_width);
    rendered_image.setSmooth(false);

    sf::Sprite sprite(rendered_image);
    sprite.setOrigin(sprite.getGlobalBounds().width * 0.5f, sprite.getGlobalBounds().height * 0.5f);
    sprite.setPosition(sprite.getGlobalBounds().width * 0.5f, sprite.getGlobalBounds().height * 0.5f);

    sf::RenderWindow window(sf::VideoMode(sprite.getTextureRect().width, sprite.getTextureRect().height), "Ray Tracer");

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<milliseconds >(stop - start);

    std::string renderRecord = "Frame rendered in: " + to_string(duration.count()) + " ms.";

    cout << LoggerHelper::getLastTenRecords();
    cout << "Last record: " << renderRecord;

    LoggerHelper::addNewRecord(renderRecord);

    float zoom = 1.0f;
    float pos_x = sprite.getPosition().x;
    float pos_y = sprite.getPosition().y;
    sf::View view = window.getDefaultView();

    while(window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::NumpadPlus)){
            zoom += 0.0001f;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::NumpadMinus)) {
            zoom -= 0.0001f;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)){
            pos_x -= 0.1f / (zoom * zoom);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)){
            pos_x += 0.1f / (zoom * zoom);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)){
            pos_y -= 0.1f / (zoom * zoom);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)){
            pos_y += 0.1f / (zoom * zoom);
        }

        sprite.setScale(zoom * zoom, zoom * zoom);
        sprite.setOrigin(pos_x, pos_y);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}