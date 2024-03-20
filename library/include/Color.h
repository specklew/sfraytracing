#ifndef SFRAYTRACING_COLOR_H
#define SFRAYTRACING_COLOR_H

#include <string>

class Color {
public:
    unsigned char r{};
    unsigned char g{};
    unsigned char b{};

    Color();

    Color(unsigned char r, unsigned char g, unsigned char b);

    Color(const Color &color);

    [[nodiscard]] Color operator+(const Color &color) const;

    [[nodiscard]] Color operator-(const Color &color) const;

    [[nodiscard]] Color operator*(const Color &color) const;

    [[nodiscard]] Color operator*(float scalar) const;

    [[nodiscard]] Color operator/(float scalar) const;

    Color &operator+=(const Color &color);

    Color &operator-=(const Color &color);

    Color &operator*=(const Color &color);

    Color &operator*=(float scalar);

    Color &operator/=(float scalar);

    [[nodiscard]] bool operator==(const Color &color) const;

    [[nodiscard]] bool operator!=(const Color &color) const;

    [[nodiscard]] std::string toString() const;

};

#endif //SFRAYTRACING_COLOR_H