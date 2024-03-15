#include <iostream>
#include "library/include/Vector.h"

int main() {
    Vector vector;
    vector.X = 10.0f;
    vector.Y = 11.0f;
    std::cout << "X = " << vector.X << " Y = " << vector.Y << std::endl;
    return 0;
}
