#ifndef VECTOR3_H
#define VECTOR3_H

#include "pico/stdlib.h"
#include "FixedPoint.h"

// Структура Vector3 для работы с 3D векторами с использованием fixed-point
struct Vector3
{
    FixedPoint x, y, z;

    // Конструктор для любых значений с преобразованием в FixedPoint
    Vector3(FixedPoint x, FixedPoint y, FixedPoint z) : x(x), y(y), z(z) {}

    // Универсальный конструктор для int и float значений
    template <typename T>
    Vector3(T x, T y, T z) : x(FixedPoint(x)), y(FixedPoint(y)), z(FixedPoint(z)) {}

    // Перегрузка оператора + для сложения
    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3((x + other.x).getRawValue(), (y + other.y).getRawValue(), (z + other.z).getRawValue());
    }

    // Перегрузка оператора - для вычитания
    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3((x - other.x).getRawValue(), (y - other.y).getRawValue(), (z - other.z).getRawValue());
    }

    // Перегрузка оператора * для умножения на скаляр
    Vector3 operator*(const FixedPoint &scalar) const
    {
        return Vector3((x * scalar).getRawValue(), (y * scalar).getRawValue(), (z * scalar).getRawValue());
    }

    // Перегрузка оператора *= для умножения на скаляр с присвоением
    Vector3 &operator*=(const FixedPoint &scalar)
    {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;
        return *this;
    }
};

// Функция для сложения двух 3D векторов
Vector3 addVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return vector1 + vector2;
}

// Функция для вычитания двух 3D векторов
Vector3 subVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return vector1 - vector2;
}

// Функция для умножения 3D вектора на скаляр
Vector3 multiplyVectorByScalar(const Vector3 &v, int scalar)
{
    return v * FixedPoint::fromInt(scalar);
}

// Функция для нормализации 3D вектора (делает его единичным вектором)
Vector3 normalizeVector(const Vector3 &vector)
{
    FixedPoint magnitude = FixedPoint::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    return Vector3((vector.x / magnitude).getRawValue(), (vector.y / magnitude).getRawValue(), (vector.z / magnitude).getRawValue());
}

// Функция для вычисления скалярного произведения двух 3D векторов
FixedPoint scalarProduct(const Vector3 &vector1, const Vector3 &vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

#endif // VECTOR3_H