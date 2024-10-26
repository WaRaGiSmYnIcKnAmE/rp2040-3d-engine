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
        result.data[i][i] = TO_FIXED(1.0f);
    return result;
}

// Умножение матрицы на другую матрицу
Matrix4 Matrix4::multiply(const Matrix4 &other) const
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.data[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                result.data[i][j] += MULT_FIXED(data[i][k], other.data[k][j]);
            }
        }
    }
    return result;
}

// Умножение матрицы на вектор
Vector3 Matrix4::multiply(const Vector3 &vec) const
{
    Vector3 result;
    result.x = MULT_FIXED(data[0][0], vec.x) + MULT_FIXED(data[0][1], vec.y) + MULT_FIXED(data[0][2], vec.z) + data[0][3];
    result.y = MULT_FIXED(data[1][0], vec.x) + MULT_FIXED(data[1][1], vec.y) + MULT_FIXED(data[1][2], vec.z) + data[1][3];
    result.z = MULT_FIXED(data[2][0], vec.x) + MULT_FIXED(data[2][1], vec.y) + MULT_FIXED(data[2][2], vec.z) + data[2][3];
    return result;
}

// Функции трансформации (перевод в fixed-point)

// Перемещение
Matrix4 Matrix4::translation(int x, int y, int z)
{
    Matrix4 result = Matrix4::identity();
    result.data[0][3] = x;
    result.data[1][3] = y;
    result.data[2][3] = z;
    return result;
}

// Масштабирование
Matrix4 Matrix4::scale(int sx, int sy, int sz)
{
    Matrix4 result = Matrix4::identity();
    result.data[0][0] = sx;
    result.data[1][1] = sy;
    result.data[2][2] = sz;
    return result;
}

// Поворот вокруг оси X
Matrix4 Matrix4::rotationX(int angleFixed)
{
    Matrix4 result = Matrix4::identity();
    int cosA = TO_FIXED(cosf(FROM_FIXED(angleFixed)));
    int sinA = TO_FIXED(sinf(FROM_FIXED(angleFixed)));
    result.data[1][1] = cosA;
    result.data[1][2] = -sinA;
    result.data[2][1] = sinA;
    result.data[2][2] = cosA;
    return result;
}

// Поворот вокруг оси Y
Matrix4 Matrix4::rotationY(int angleFixed)
{
    Matrix4 result = Matrix4::identity();
    int cosA = TO_FIXED(cosf(FROM_FIXED(angleFixed)));
    int sinA = TO_FIXED(sinf(FROM_FIXED(angleFixed)));
    result.data[0][0] = cosA;
    result.data[0][2] = sinA;
    result.data[2][0] = -sinA;
    result.data[2][2] = cosA;
    return result;
}

// Поворот вокруг оси Z
Matrix4 Matrix4::rotationZ(int angleFixed)
{
    Matrix4 result = Matrix4::identity();
    int cosA = TO_FIXED(cosf(FROM_FIXED(angleFixed)));
    int sinA = TO_FIXED(sinf(FROM_FIXED(angleFixed)));
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

Matrix4 Matrix4::perspective(int fov, int aspectRatio, int near, int far)
{
    Matrix4 result;
    int tanHalfFOV = TO_FIXED(tanf(FROM_FIXED(fov) / 2.0f));
    int range = near - far;

    result.data[0][0] = MULT_FIXED(TO_FIXED(1), aspectRatio) / tanHalfFOV;
    result.data[1][1] = TO_FIXED(1) / tanHalfFOV;
    result.data[2][2] = (near + far) / range;
    result.data[2][3] = MULT_FIXED(TO_FIXED(2) * near * far, 1) / range;
    result.data[3][2] = TO_FIXED(-1);
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
                sum += MULT_FIXED(data[i][k], other.data[k][j]);
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
