#ifndef VECTOR3_H
#define VECTOR3_H

#include "pico/stdlib.h"
#include "pico/float.h"

#define FIXED_POINT_SHIFT 16

// struct for use 3D Vectors with use fixed-point
struct Vector3
{
    int32_t x, y, z;

    Vector3() : x(0), y(0), z(0) {}

    Vector3(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}

    Vector3(float fx, float fy, float fz)
        : x(float2fix(fx, FIXED_POINT_SHIFT)),
          y(float2fix(fy, FIXED_POINT_SHIFT)),
          z(float2fix(fz, FIXED_POINT_SHIFT)) {}

    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(const int32_t scalar) const
    {
        return Vector3((x * scalar),
                       (y * scalar),
                       (z * scalar));
    }

    Vector3 &operator*=(int32_t scalar)
    {
        x = (x * scalar);
        y = (y * scalar);
        z = (z * scalar);
        return *this;
    }

    Vector3 operator*(const Vector3 vector) const
    {
        return Vector3(
            ((y * vector.z) - (z * vector.y)),
            -((x * vector.z) - (z * vector.x)),
            ((x * vector.y) - (y * vector.x)));
    }

    Vector3 &operator*=(Vector3 vector)
    {
        x = ((y * vector.z) - (z * vector.y));
        y = ((z * vector.x) - (x * vector.z));
        z = ((x * vector.y) - (y * vector.x));
        return *this;
    }

    // Преобразование в float для использования в выводе или дальнейших вычислениях
    void toFloat(float &outX, float &outY, float &outZ) const
    {
        outX = fix2float(x, FIXED_POINT_SHIFT);
        outY = fix2float(y, FIXED_POINT_SHIFT);
        outZ = fix2float(z, FIXED_POINT_SHIFT);
    }

    // Dot product
    int32_t dot(const Vector3 &other) const
    {
        return ((x * other.x)) +
               ((y * other.y)) +
               ((z * other.z));
    }
};

// Пример дополнительных функций для операций над векторами

// Сложение векторов
Vector3 addVectors(const Vector3 &vector1, const Vector3 &vector2);

// Вычитание векторов
Vector3 subVectors(const Vector3 &vector1, const Vector3 &vector2);

// Умножение на скаляр
Vector3 multiplyVectorByScalar(const Vector3 &v, int32_t scalar);

// Нормализация вектора (делает его единичным вектором)
Vector3 normalizeVector(const Vector3 &vector);

// Скалярное произведение двух векторов
int32_t scalarProduct(const Vector3 &vector1, const Vector3 &vector2);

#endif // VECTOR3_H
