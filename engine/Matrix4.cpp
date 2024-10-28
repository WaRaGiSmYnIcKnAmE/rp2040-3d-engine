#include "Matrix4.h"
#include "pico/float.h"

// Конструктор по умолчанию: все элементы матрицы равны нулю
Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            data[i][j] = 0;
}

// Создание единичной матрицы
Matrix4 Matrix4::identity()
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
        result.data[i][i] = float2fix(1.0f, FIXED_POINT_SHIFT);
    return result;
}

// Умножение матрицы на другую матрицу
Matrix4 Matrix4::multiply(const Matrix4 &other) const
{
    Matrix4 result;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            int sum = 0;
            for (int k = 0; k < 4; ++k)
            {
                sum += float2fix(fix2float(data[i][k], FIXED_POINT_SHIFT) * fix2float(other.data[k][j], FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

// Умножение матрицы на вектор
Vector3 Matrix4::multiply(const Vector3 &vec) const
{
    Vector3 result;
    result.x = float2fix(
        (fix2float(data[0][0], FIXED_POINT_SHIFT) * fix2float(vec.x, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            (fix2float(data[0][1], FIXED_POINT_SHIFT) * fix2float(vec.y, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            (fix2float(data[0][2], FIXED_POINT_SHIFT) * fix2float(vec.z, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            fix2float(data[0][3], FIXED_POINT_SHIFT),
        FIXED_POINT_SHIFT);
    result.y = float2fix(
        (fix2float(data[1][0], FIXED_POINT_SHIFT) * fix2float(vec.x, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            (fix2float(data[1][1], FIXED_POINT_SHIFT) * fix2float(vec.y, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            (fix2float(data[1][2], FIXED_POINT_SHIFT) * fix2float(vec.z, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            fix2float(data[1][3], FIXED_POINT_SHIFT),
        FIXED_POINT_SHIFT);
    result.z = float2fix(
        (fix2float(data[2][0], FIXED_POINT_SHIFT) * fix2float(vec.x, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            (fix2float(data[2][1], FIXED_POINT_SHIFT) * fix2float(vec.y, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            (fix2float(data[2][2], FIXED_POINT_SHIFT) * fix2float(vec.z, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT) +
            fix2float(data[2][3], FIXED_POINT_SHIFT),
        FIXED_POINT_SHIFT);
    return result;
}

// Функции трансформации (перевод в fixed-point)

// Перемещение
Matrix4 Matrix4::translation(int32_t x, int32_t y, int32_t z)
{
    Matrix4 result = Matrix4::identity();
    result.data[0][3] = x;
    result.data[1][3] = y;
    result.data[2][3] = z;
    return result;
}

// Масштабирование
Matrix4 Matrix4::scale(int32_t sx, int32_t sy, int32_t sz)
{
    Matrix4 result = Matrix4::identity();
    result.data[0][0] = sx;
    result.data[1][1] = sy;
    result.data[2][2] = sz;
    return result;
}

// Поворот вокруг оси X
Matrix4 Matrix4::rotationX(int32_t angleFixed)
{
    Matrix4 result = Matrix4::identity();
    int32_t cosA = float2fix(cosf(int2float(angleFixed)), FIXED_POINT_SHIFT);
    int32_t sinA = float2fix(sinf(int2float(angleFixed)), FIXED_POINT_SHIFT);
    result.data[1][1] = cosA;
    result.data[1][2] = -sinA;
    result.data[2][1] = sinA;
    result.data[2][2] = cosA;
    return result;
}

// Поворот вокруг оси Y
Matrix4 Matrix4::rotationY(int32_t angleFixed)
{
    Matrix4 result = Matrix4::identity();
    int32_t cosA = float2fix(cosf(int2float(angleFixed)), FIXED_POINT_SHIFT);
    int32_t sinA = float2fix(sinf(int2float(angleFixed)), FIXED_POINT_SHIFT);
    result.data[0][0] = cosA;
    result.data[0][2] = sinA;
    result.data[2][0] = -sinA;
    result.data[2][2] = cosA;
    return result;
}

// Поворот вокруг оси Z
Matrix4 Matrix4::rotationZ(int32_t angleFixed)
{
    Matrix4 result = Matrix4::identity();
    int32_t cosA = float2fix(cosf(int2float(angleFixed)), FIXED_POINT_SHIFT);
    int32_t sinA = float2fix(sinf(int2float(angleFixed)), FIXED_POINT_SHIFT);
    result.data[0][0] = cosA;
    result.data[0][1] = -sinA;
    result.data[1][0] = sinA;
    result.data[1][1] = cosA;
    return result;
}

// Транспонирование матрицы
Matrix4 Matrix4::transpose() const
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

Matrix4 Matrix4::perspective(int32_t fov, int32_t aspectRatio, int32_t near, int32_t far)
{
    Matrix4 result;
    int32_t tanHalfFOV = float2fix(tanf(int2float(fov) / 2.0f), FIXED_POINT_SHIFT);
    int range = near - far;

    result.data[0][0] = float2fix((int2float(1) * fix2float(aspectRatio, FIXED_POINT_SHIFT)) / fix2float(tanHalfFOV, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);
    result.data[1][1] = float2fix(int2float(1) / fix2float(tanHalfFOV, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);
    result.data[2][2] = (near + far) / range;
    result.data[2][3] = float2fix((int2float(2) * int2float(near) * int2float(far) * 1) / int2float(range), FIXED_POINT_SHIFT);
    result.data[3][2] = float2fix(int2float(-1), FIXED_POINT_SHIFT);
    result.data[3][3] = 0;

    return result;
}

// Перегрузка оператора * для умножения матриц
Matrix4 Matrix4::operator*(const Matrix4 &other) const
{
    Matrix4 result;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            int sum = 0;
            for (int k = 0; k < 4; ++k)
            {
                sum += float2fix(fix2float(data[i][k], FIXED_POINT_SHIFT) * fix2float(other.data[k][j], FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

// Перегрузка оператора *= для умножения матриц и присвоения
Matrix4 &Matrix4::operator*=(const Matrix4 &other)
{
    *this = *this * other;
    return *this;
}
