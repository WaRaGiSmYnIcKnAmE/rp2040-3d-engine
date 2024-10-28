#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector3.h"
#include "pico/float.h" // Для работы с углами

#define FIXED_POINT_SHIFT 16

struct Matrix4
{
    int32_t data[4][4]; // Массив для хранения матрицы в формате fixed-point

    // Конструктор по умолчанию
    Matrix4();

    // Создание единичной матрицы
    static Matrix4 identity();

    // Умножение матрицы на другую матрицу
    Matrix4 multiply(const Matrix4 &other) const;

    // Умножение матрицы на вектор
    Vector3 multiply(const Vector3 &vec) const;

    // Перегрузка операторов для умножения матриц
    Matrix4 operator*(const Matrix4 &other) const; // Умножение матриц
    Matrix4 &operator*=(const Matrix4 &other);     // Умножение и присвоение

    // Функции для трансформаций (перемещение, масштабирование, поворот)
    static Matrix4 translation(int32_t x, int32_t y, int32_t z);
    static Matrix4 scale(int32_t sx, int32_t sy, int32_t sz);
    static Matrix4 rotationX(int32_t angleFixed);
    static Matrix4 rotationY(int32_t angleFixed);
    static Matrix4 rotationZ(int32_t angleFixed);

    // Транспонирование матрицы
    Matrix4 transpose() const;

    static Matrix4 perspective(int32_t fov, int32_t aspectRatio, int32_t near, int32_t far);
};

#endif // MATRIX4_H
