

#include "Color.h"

Color::Color() = default;

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(const Color& color){
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
}

Color Color::operator+(const Color &color) const {
    return {static_cast<unsigned char>(r + color.r),
            static_cast<unsigned char>(g + color.g),
            static_cast<unsigned char>(b + color.b)};
}

Color Color::operator-(const Color &color) const {
    return {static_cast<unsigned char>(r - color.r),
            static_cast<unsigned char>(g - color.g),
            static_cast<unsigned char>(b - color.b)};
}

Color Color::operator*(const Color &color) const {
    return {static_cast<unsigned char>(r * color.r),
            static_cast<unsigned char>(g * color.g),
            static_cast<unsigned char>(b * color.b)};
}

Color Color::operator*(float scalar) const {
    return {static_cast<unsigned char>(r * scalar),
            static_cast<unsigned char>(g * scalar),
            static_cast<unsigned char>(b * scalar)};
}

Color Color::operator/(float scalar) const {
    return {static_cast<unsigned char>(r / scalar),
            static_cast<unsigned char>(g / scalar),
            static_cast<unsigned char>(b / scalar)};
}

Color &Color::operator+=(const Color &color) {
    *this = *this + color;
}

Color &Color::operator-=(const Color &color) {
    *this = *this - color;
}

Color &Color::operator*=(const Color &color) {
    *this = *this * color;
}

Color &Color::operator*=(float scalar) {
    *this = *this * scalar;
}

Color &Color::operator/=(float scalar) {
    *this = *this / scalar;
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

