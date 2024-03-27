#include "Color.h"

const Color Color::Null = {-1, -1, -1};

Color::Color() : Color(Null){}

Color::Color(const Color& color) : Color(color.r, color.g, color.b){}

Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color Color::operator+(const Color &color) const {
    return {r + color.r, g + color.g, b + color.b};
}

Color Color::operator-(const Color &color) const {
    return {r - color.r, g - color.g, b - color.b};
}

Color Color::operator*(const Color &color) const {
    return {r * color.r, g * color.g, b * color.b};
}

Color Color::operator*(float scalar) const {
    return {r * scalar, g * scalar, b * scalar};
}

Color Color::operator/(float scalar) const {
    return {r / scalar, g / scalar, b / scalar};
}

Color &Color::operator+=(const Color &color) {
    *this = *this + color;
    return *this;
}

Color &Color::operator-=(const Color &color) {
    *this = *this - color;
    return *this;
}

Color &Color::operator*=(const Color &color) {
    *this = *this * color;
    return *this;
}

Color &Color::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

Color &Color::operator/=(float scalar) {
    *this = *this / scalar;
    return *this;
}

bool Color::operator==(const Color &color) const {
    return r == color.r && g == color.g && b == color.b;
}

bool Color::operator!=(const Color &color) const {
    return r != color.r && g != color.g && b != color.b;
}

std::string Color::toString() const {
    return "Color(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}

Color Color::getAverageColor(const Color *colors, int size) {

    float invSize = 1.0f / size;

    float r = 0;
    float g = 0;
    float b = 0;

    for(int i = 0; i < size; ++i){
        Color color = colors[i];
        r += color.r;
        g += color.g;
        b += color.b;
    }

    r *= invSize;
    g *= invSize;
    b *= invSize;

    return {r, g, b};
}

bool Color::areAllColorsEqual(const Color *colors, int size) {
    for(int i = 1; i < size; ++i){
        if(colors[i] != colors[0]){
            return false;
        }
    }
    return true;
}

