#include <iostream>
#include "library/include/Vector.h"

int main() {

    std::cout << std::endl << "---- Assignments ----" << std::endl << std::endl;

    Vector v1 = {0, 3, 0};
    Vector v2 = {5, 5, 0};
    std::cout << "Angle between vector " << v1.toString() << " and " << v2.toString() << " = " << v1.Angle(v2) << std::endl;

    std::cout << std::endl;

    v1 = {4,5,1};
    v2 = {4,1,3};

    Vector perpendicular = v1.CrossProduct(v2);
    std::cout << "Vector perpendicular to: " << std::endl << "v1 = " << v1.toString() << std::endl << "v2 = " << v2.toString() << std::endl;
    std::cout << "Is " << perpendicular.toString() << std::endl;
    std::cout << "Its angles with v1 and v2 are " << v1.Angle(perpendicular) << " and " << v2.Angle(perpendicular) << std::endl;
    std::cout << "Normalized perpendicular vector is " << perpendicular.Normalize().toString() << " with length = " << perpendicular.Length();

    std::cout << std::endl;


    return 0;
}
