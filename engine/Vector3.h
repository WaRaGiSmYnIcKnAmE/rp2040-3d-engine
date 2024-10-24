#ifndef VECTOR3_H
#define VECTOR3_H

#include "pico/stdlib.h"

// Фиксированное значение масштаба для преобразования в fixed-point (16 целых, 16 дробных)
#define FIXED_POINT_SHIFT 16
#define TO_FIXED(x) ((int)((x) * (1 << FIXED_POINT_SHIFT)))  // Преобразовать float в fixed-point
#define FROM_FIXED(x) ((float)(x) / (1 << FIXED_POINT_SHIFT))  // Преобразовать fixed-point в float
#define MULT_FIXED(a, b) (((a) * (b)) >> FIXED_POINT_SHIFT)  // Умножение в fixed-point

// struct for use 3D Vectors with use fixed-point
struct Vector3
{
    int x, y, z;

    Vector3() : x(0), y(0), z(0) {}

    Vector3(int x, int y, int z) : x(x), y(y), z(z) {}

    Vector3(float x, float y, float z) 
        : x(TO_FIXED(x)), y(TO_FIXED(y)), z(TO_FIXED(z)) {}
};

// Функция для сложения двух 3D векторов
Vector3 addVectors(const Vector3 &vector1, const Vector3 &vector2);

// Функция для вычитания двух 3D векторов
Vector3 subVectors(const Vector3 &vector1, const Vector3 &vector2);

// Функция для умножения 3D вектора на скаляр
Vector3 multiplyVectorByScalar(const Vector3 &v, int scalar);

// Функция для нормализации 3D вектора (делает его единичным вектором)
Vector3 normalizeVector(const Vector3 &vector);

// Функция для вычисления скалярного произведения двух 3D векторов
int scalarProduct(const Vector3 &vector1, const Vector3 &vector2);

#endif // VECTOR3_H
