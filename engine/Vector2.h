#ifndef VECTOR2_H
#define VECTOR2_H

#include "pico/stdlib.h"

// Фиксированное значение масштаба для преобразования в fixed-point (16 целых, 16 дробных)
#define FIXED_POINT_SHIFT 16
#define TO_FIXED(x) ((int)((x) * (1 << FIXED_POINT_SHIFT)))   // Преобразовать float в fixed-point
#define FROM_FIXED(x) ((float)(x) / (1 << FIXED_POINT_SHIFT)) // Преобразовать fixed-point в float
#define MULT_FIXED(a, b) (((a) * (b)) >> FIXED_POINT_SHIFT)   // Умножение в fixed-point

// struct for use 2D Vectors with use fixed-point
struct Vector2
{
    int x, y;

    Vector2() : x(0), y(0) {}

    Vector2(int x, int y) : x(x), y(y) {}

    Vector2(float x, float y, float z)
        : x(TO_FIXED(x)), y(TO_FIXED(y)) {}

    // Перегрузка оператора +
    Vector2 operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    // Перегрузка оператора -
    Vector2 operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    // Перегрузка оператора * для умножения на скаляр
    Vector2 operator*(int scalar) const
    {
        return Vector2(MULT_FIXED(x, scalar), MULT_FIXED(y, scalar));
    }

    // Перегрузка оператора *= для умножения на скаляр с присвоением
    Vector2 &operator*=(int scalar)
    {
        x = MULT_FIXED(x, scalar);
        y = MULT_FIXED(y, scalar);
        return *this;
    }
};

// Function for addition two 2D Vectors
Vector2 addVectors(const Vector2 &vector1, const Vector2 &vector2);

// Function for subtraction two 2D Vectors
Vector2 subVectors(const Vector2 &vector1, const Vector2 &vector2);

// Function for alculating the product of a 2D Vector by a scalar
Vector2 multiplyVectorByScalar(const Vector2 &v, float scalar);

// Аunction for 2D Vector normalization
Vector2 normalizeVector(const Vector2 &vector);

// Function for alculating the scalar product of 2D Vector by a 3D Vector
int scalarProduct(const Vector2 &vector1, const Vector2 &vector2);

#endif // VECTOR_H