#include <cmath>
#include <cfloat>
#include "Color.h"
#include "Helpers/MathHelper.h"

const Color Color::Null = {-1, -1, -1};
const double Color::min = {0};
const double Color::max = {1};

Color::Color() : Color(Null){}

Color::Color(const Color& color) : Color(color.r, color.g, color.b){}

Color::Color(double r, double g, double b) {
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

Color Color::operator*(double scalar) const {
    return {r * scalar, g * scalar, b * scalar};
}

Color Color::operator/(double scalar) const {
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

Color &Color::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

Color &Color::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}

bool Color::operator==(const Color &other) const {
    return std::fabs(r - other.r) <= DBL_EPSILON &&
            std::fabs(g - other.r) <= DBL_EPSILON &&
            std::fabs(b - other.b) <= DBL_EPSILON;
}

bool Color::operator!=(const Color &color) const {
    return r != color.r && g != color.g && b != color.b;
}

std::string Color::toString() const {
    return "Color(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}

Color Color::getAverageColor(const Color *colors, int size) {

    double invSize = 1.0 / size;

    double r = 0;
    double g = 0;
    double b = 0;

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

Color Color::linearToGamma(const double& gamma) {
    r = MathHelper::linearToGamma(r, gamma);
    g = MathHelper::linearToGamma(g, gamma);
    b = MathHelper::linearToGamma(b, gamma);

    return *this;
}

