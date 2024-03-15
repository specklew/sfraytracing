#ifndef SFRAYTRACING_VECTOR_H
#define SFRAYTRACING_VECTOR_H


class Vector{
public:
    Vector();
    float X{};
    float Y{};
    float Z{};
    
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    float DotProduct(const Vector& other) const;
    Vector CrossProduct(const Vector& other) const;
};

#endif //SFRAYTRACING_VECTOR_H