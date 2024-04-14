#include <cmath>
#include <cfloat>
#include "Color.h"
#include "Helpers/MathHelper.h"

const Color Color::Null = {-1, -1, -1};
const Color Color::Black = {0, 0, 0};
const Color Color::White = {1, 1, 1};

const precision Color::min{0};
const precision Color::max{1};

Color::Color() : Color(Null){}

Color::Color(const Color& color) : Color(color.r, color.g, color.b){}

Color::Color(precision r, precision g, precision b) {
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

Color Color::operator*(precision scalar) const {
    return {r * scalar, g * scalar, b * scalar};
}

Color Color::operator/(precision scalar) const {
    return {r / scalar, g / scalar, b / scalar};
}

Color &Color::operator+=(const Color &color) {
    this->r += color.r;
    this->g += color.g;
    this->b += color.b;

    return *this;
}

Color &Color::operator-=(const Color &color) {
    this->r -= color.r;
    this->g -= color.g;
    this->b -= color.b;
    return *this;
}

Color &Color::operator*=(const Color &color) {
    this->r *= color.r;
    this->g *= color.g;
    this->b *= color.b;
    return *this;
}

Color &Color::operator*=(precision scalar) {
    this->r *= scalar;
    this->g *= scalar;
    this->b *= scalar;
    return *this;
}

Color &Color::operator/=(precision scalar) {
    this->r /= scalar;
    this->g /= scalar;
    this->b /= scalar;
    return *this;
}

bool Color::operator==(const Color &other) const {
    return std::fabs(r - other.r) <= 0.02 &&
            std::fabs(g - other.r) <= 0.02 &&
            std::fabs(b - other.b) <= 0.02;
}

bool Color::operator!=(const Color &color) const {
    return !(*this==color);
}

std::string Color::toString() const {
    return "Color(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}

Color Color::getAverageColor(const Color *colors, int size) {

    precision invSize = 1.0 / size;

    precision r = 0;
    precision g = 0;
    precision b = 0;

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

Color Color::clamp() {
    MathHelper::clamp(r, Color::min, Color::max);
    MathHelper::clamp(g, Color::min, Color::max);
    MathHelper::clamp(b, Color::min, Color::max);
    return *this;
}

Color Color::linearToGamma(const precision& gamma) {
    r = MathHelper::linearToGamma(r, gamma);
    g = MathHelper::linearToGamma(g, gamma);
    b = MathHelper::linearToGamma(b, gamma);

    return *this;
}

Color Color::operator+(precision scalar) const {
    return {r + scalar, g + scalar, b + scalar};
}

Color Color::operator-(precision scalar) const {
    return {r - scalar, g - scalar, b - scalar};
}

Color &Color::operator+=(precision scalar) {
    r += scalar;
    g += scalar;
    b += scalar;
    return *this;
}

Color &Color::operator-=(precision scalar) {
    r -= scalar;
    g -= scalar;
    b -= scalar;
    return *this;
}

Color::Color(precision intensity) {
    r = intensity;
    g = intensity;
    b = intensity;
}

