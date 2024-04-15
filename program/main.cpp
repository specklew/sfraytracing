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
#include "Samplers/AdaptiveSuperSampler.h"
#include "Materials/DiffuseMaterial.h"
#include "Materials/MetalMaterial.h"
#include "Materials/DielectricMaterial.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Helpers/LoggerHelper.h"
#include "Lights/PointLight.h"

using namespace std::chrono;
using namespace std;

int main() {

    auto start = high_resolution_clock::now();

    //Camera setup
    Camera* camera = new PerspectiveCamera(
            Vector3(0, 1, 1),
            Vector3(0, 0, -1),
            new UniformDistributionSuperSampler(4));

    // Scene setup
    Scene scene = Scene(camera);

    std::shared_ptr<Material> diffuseWhite = std::make_shared<DiffuseMaterial>(DiffuseMaterial(Color(0.7, 0.7, 0.7)));
    std::shared_ptr<Material> diffuseRed = std::make_shared<DiffuseMaterial>(DiffuseMaterial({0.7, 0.0, 0.0}));
    std::shared_ptr<Material> diffuseBlue = std::make_shared<DiffuseMaterial>(DiffuseMaterial({0.0, 0.0, 0.7}));
    std::shared_ptr<Material> mirror = std::make_shared<MetalMaterial>(MetalMaterial(Color(1, 1, 1)));
    std::shared_ptr<Material> glass = std::make_shared<DielectricMaterial>(DielectricMaterial({1,1,1}, 1.6));

    std::shared_ptr<Material> glossyMagenta = std::make_shared<DiffuseMaterial>(DiffuseMaterial({0.7, 0.0, 0.7}));
    glossyMagenta->specularAmount = 2;
    glossyMagenta->diffuseAmount = 0.2;
    glossyMagenta->specularCoefficient = 15;

    Sphere s1 = Sphere({1, 0.5, -1.5}, 0.5f, glossyMagenta);
    Sphere s2 = Sphere({-1, 0.5, -1.5}, 0.5f, diffuseWhite);
    Sphere s3 = Sphere({0, 0.5, -1.5}, 0.5, glass);
    Triangle t1 = Triangle({1.25, 0, -1}, {0.25, 1, -1.5}, {0.25, -0.5, -1}, mirror);

    Plane ground = Plane({0, 0, 0}, {0, 1, 0}, diffuseWhite);
    Plane leftWall = Plane({2,0,0}, {-1,0,0}, diffuseRed);
    Plane rightWall = Plane({-2,0,0}, {1,0,0}, diffuseBlue);
    Plane ceiling = Plane({0,3,0}, {0,-1,0}, diffuseWhite);
    Plane backWall = Plane({0, 0, -3}, {0,0,1}, diffuseWhite);
    //Sphere ground = Sphere({0, -100, -1}, 100.0f, diffuseWhite);

    scene.addObject(&s1);
    scene.addObject(&s2);
    scene.addObject(&s3);
    //scene.addObject(&t1);
    scene.addObject(&ground);
    scene.addObject(&leftWall);
    scene.addObject(&rightWall);
    scene.addObject(&ceiling);
    scene.addObject(&backWall);

    auto light = PointLight({0, 2, -1.5}, 3);

    scene.addLight(&light);

    sf::Texture rendered_image = scene.renderScene();
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