#include <cmath>
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#include "Sphere.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Camera::Camera() {
    position = Vector3(0, 0, 0);
    direction = Vector3(0, 0, 1);
    up = Vector3(0, 1, 0);
    fov = 60.0f;
    aspectRatio = 16.0f / 9.0f;
    nearPlane = 0.1f;
    farPlane = 1000.0f;
}

Camera::Camera(const Vector3 &position, const Vector3 &direction) {
    this->position = position;
    this->direction = direction;
    up = Vector3(0, 1, 0);
    fov = 60;
    aspectRatio = 16.0f / 9.0f;
    nearPlane = 0.1f;
    farPlane = 1000.0f;
}

void Camera::Render(int imageWidth) {

    int image_height = static_cast<int>(imageWidth / aspectRatio);

    // SFML Setup
    auto* pixels = new sf::Uint8[imageWidth * image_height * 4];

    sf::RenderWindow window(sf::VideoMode(imageWidth, image_height), "Ray Tracer");
    sf::Texture buffer;
    buffer.create(imageWidth, image_height);
    sf::Sprite sprite(buffer);

    // Camera Setup

    float theta = fov * M_PI / 180.0f;
    float h = std::tan(theta / 2.0f);

    float viewport_height = 2.0 * h;
    float viewport_width = viewport_height * (static_cast<float>(imageWidth) / image_height);

    Vector3 viewport_u = Vector3(viewport_width, 0,0);
    Vector3 viewport_v = Vector3(0, -viewport_height, 0);

    Vector3 pixel_delta_u = viewport_u / static_cast<float>(imageWidth);
    Vector3 pixel_delta_v = viewport_v / static_cast<float>(image_height);

    Vector3 viewport_upper_left = position - viewport_u / 2.0f - viewport_v / 2.0f + Vector3(0, 0, 1.0f);
    Vector3 first_pixel_pos = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5f;

    // Scene

    Sphere sphere = Sphere(Vector3(0, 0, 2), 0.5f);

    // Scanlines

    for(int j = 0; j < image_height; ++j){
        for(int i = 0; i < imageWidth; ++i){
            Vector3 pixel_center = first_pixel_pos + (pixel_delta_u * i) + (pixel_delta_v * j);
            Vector3 ray_direction = pixel_center - position; // Faster than with normalization.

            Ray ray = Ray(position, ray_direction);
            Color pixel_color;

            if(HitInfo info = sphere.hit(ray); info.intersected) {

                pixel_color = Color(info.hitNormal.x + 1, info.hitNormal.y + 1, info.hitNormal.z + 1) * 0.5f;

            } else {

                // For sake of testing:
                Vector3 unit_direction = ray.direction.normalized();
                float t = 0.5f * (unit_direction.y + 1.0f);
                pixel_color = Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;

            }


            pixels[(j * imageWidth + i) * 4 + 0] = pixel_color.r * 255;
            pixels[(j * imageWidth + i) * 4 + 1] = pixel_color.g * 255;
            pixels[(j * imageWidth + i) * 4 + 2] = pixel_color.b * 255;
            pixels[(j * imageWidth + i) * 4 + 3] = 255;
        }
    }

    buffer.update(pixels);

    // Opening window

    while(window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }

    // Cleanup

    delete(&pixels);
}
