#ifndef VECTOR2_H
#define VECTOR2_H

#include "pico/stdlib.h"
#include "pico/float.h"

#define FIXED_POINT_SHIFT 16

// struct for use 2D Vectors with use fixed-point
struct Vector2
{
    int32_t x, y;

    Vector2() : x(0), y(0) {}

    Vector2(int32_t x, int32_t y) : x(x), y(y) {}

    Vector2(float x, float y, float z)
        : x(float2fix(x, FIXED_POINT_SHIFT)),
          y(float2fix(y, FIXED_POINT_SHIFT)) {}

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
        return Vector2((x * scalar) >> FIXED_POINT_SHIFT,
                       (y * scalar) >> FIXED_POINT_SHIFT);
    }

    // Перегрузка оператора *= для умножения на скаляр с присвоением
    Vector2 &operator*=(int scalar)
    {
        x = (x * scalar) >> FIXED_POINT_SHIFT;
        y = (y * scalar) >> FIXED_POINT_SHIFT;
        return *this;
    }

    // Преобразование в float для использования в выводе или дальнейших вычислениях
    void toFloat(float &outX, float &outY) const
    {
        outX = fix2float(x, FIXED_POINT_SHIFT);
        outY = fix2float(y, FIXED_POINT_SHIFT);
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
int32_t scalarProduct(const Vector2 &vector1, const Vector2 &vector2);

#endif // VECTOR_H