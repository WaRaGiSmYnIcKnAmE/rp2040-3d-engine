#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector3.h"
#include "pico/float.h" // Для работы с углами

// Fixed-point настройки
#define FIXED_POINT_SHIFT 16
#define TO_FIXED(x) (((x) >= 0) ? ((int)((x) * (1 << FIXED_POINT_SHIFT))) : ((int)((x) * (1 << FIXED_POINT_SHIFT)))) // float -> fixed-point
#define FROM_FIXED(x) ((float)(x) / (1 << FIXED_POINT_SHIFT))                                                        // fixed-point -> float
#define MULT_FIXED(a, b) (((long long)(a) * (long long)(b)) >> FIXED_POINT_SHIFT)                                    // Умножение fixed-point

struct Matrix4
{
    int data[4][4]; // Массив для хранения матрицы в формате fixed-point

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
    static Matrix4 translation(int x, int y, int z);
    static Matrix4 scale(int sx, int sy, int sz);
    static Matrix4 rotationX(int angleFixed);
    static Matrix4 rotationY(int angleFixed);
    static Matrix4 rotationZ(int angleFixed);

    // Транспонирование матрицы
    Matrix4 transpose() const;

    static Matrix4 perspective(int fov, int aspectRatio, int near, int far);
};

#endif // MATRIX4_H
