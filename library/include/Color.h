#ifndef SFRAYTRACING_COLOR_H
#define SFRAYTRACING_COLOR_H

#include <string>
#include "Precision.h"

class Color {
public:
    static const Color Null;
    static const Color Black;
    static const Color White;

    precision r;
    precision g;
    precision b;

    Color();

    Color(const Color &color);

    Color(precision r, precision g, precision b);

    [[nodiscard]] Color operator+(const Color &color) const;

    [[nodiscard]] Color operator-(const Color &color) const;

    [[nodiscard]] Color operator*(const Color &color) const;

    [[nodiscard]] Color operator*(precision scalar) const;

    [[nodiscard]] Color operator/(precision scalar) const;

    Color &operator+=(const Color &color);

    Color &operator-=(const Color &color);

    Color &operator*=(const Color &color);

    Color &operator*=(precision scalar);

    Color &operator/=(precision scalar);

    [[nodiscard]] bool operator==(const Color &other) const;

    [[nodiscard]] bool operator!=(const Color &color) const;

    Color clamp();
    Color linearToGamma(const precision& gamma);

    static Color getAverageColor(const Color *colors, int size);

    static bool areAllColorsEqual(const Color *colors, int size);

    [[nodiscard]] std::string toString() const;

private:
    static const precision min;
    static const precision max;

};

#endif //SFRAYTRACING_COLOR_H
