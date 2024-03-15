#include <iostream>
#include "library/include/Vector.h"

int main() {
    Vector vec1 = Vector(1.0f, 0.0f, 0.0f);
    Vector vec2 = Vector(0.0f, 0.0f, 1.0f);
    Vector cross = vec1.CrossProduct(vec2);

    cross *= 2;

    std::cout << "Cross product: [" << cross.X << ", " << cross.Y << ", " << cross.Z << "]" << std::endl;
    return 0;
}
