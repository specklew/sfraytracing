#ifndef SFRAYTRACING_COLOR_H
#define SFRAYTRACING_COLOR_H

#include <string>

class Color {
public:
    static const Color Null;

    float r{};
    float g{};
    float b{};

    Color();

    Color(const Color &color);

    Color(float r, float g, float b);

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

    static Color getAverageColor(const Color *colors, int size);

    static bool areAllColorsEqual(const Color *colors, int size);

    [[nodiscard]] std::string toString() const;

};

#endif //SFRAYTRACING_COLOR_H
