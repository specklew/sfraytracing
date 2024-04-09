#ifndef SFRAYTRACING_COLOR_H
#define SFRAYTRACING_COLOR_H

#include <string>

class Color {
public:
    static const Color Null;

    double r;
    double g;
    double b;

    Color();

    Color(const Color &color);

    Color(double r, double g, double b);

    [[nodiscard]] Color operator+(const Color &color) const;

    [[nodiscard]] Color operator-(const Color &color) const;

    [[nodiscard]] Color operator*(const Color &color) const;

    [[nodiscard]] Color operator*(double scalar) const;

    [[nodiscard]] Color operator/(double scalar) const;

    Color &operator+=(const Color &color);

    Color &operator-=(const Color &color);

    Color &operator*=(const Color &color);

    Color &operator*=(double scalar);

    Color &operator/=(double scalar);

    [[nodiscard]] bool operator==(const Color &other) const;

    [[nodiscard]] bool operator!=(const Color &color) const;

    Color clamp();
    Color linearToGamma(const double& gamma);

    static Color getAverageColor(const Color *colors, int size);

    static bool areAllColorsEqual(const Color *colors, int size);

    [[nodiscard]] std::string toString() const;

private:
    static const double min;
    static const double max;

};

#endif //SFRAYTRACING_COLOR_H
