#include "Matrix4.h"
#include "pico/float.h"

#define PI 3.14159265358979323846

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
    result.x = data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3] * float2fix(1.0f, FIXED_POINT_SHIFT);
    result.y = data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3] * float2fix(1.0f, FIXED_POINT_SHIFT);
    result.z = data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3] * float2fix(1.0f, FIXED_POINT_SHIFT);
    return result;
}

/*
|  1  0  0  x  |
|  0  1  0  y  |
|  0  0  1  z  |
|  0  0  0  1  |
*/
Matrix4 Matrix4::translation(int32_t x, int32_t y, int32_t z)
{
    Matrix4 result = Matrix4::identity();
    result.data[0][3] = x;
    result.data[1][3] = y;
    result.data[2][3] = z;
    return result;
}

/*
|  x  0  0  0  |
|  0  y  0  0  |
|  0  0  z  0  |
|  0  0  0  1  |
*/
Matrix4 Matrix4::scale(int32_t sx, int32_t sy, int32_t sz)
{
    Matrix4 result = Matrix4::identity();
    result.data[0][0] = sx;
    result.data[1][1] = sy;
    result.data[2][2] = sz;
    return result;
}

/*
|  1   0   0   0  |
|  0  cos -sin 0  |
|  0  sin cos  0  |
|  0   0   0   1  |
*/
Matrix4 Matrix4::rotationX(int32_t angleFixed)
{
    Matrix4 matrix = Matrix4::identity();

    float angle = fix2float(angleFixed, FIXED_POINT_SHIFT);
    float radians = (angle * PI) / 180;

    float cos_angle = cosf(radians);
    float sin_angle = sinf(radians);

    int32_t cos_fixed = float2fix(cos_angle, FIXED_POINT_SHIFT);
    int32_t sin_fixed = float2fix(sin_angle, FIXED_POINT_SHIFT);

    matrix.data[1][1] = cos_fixed;
    matrix.data[1][2] = -sin_fixed;
    matrix.data[2][1] = sin_fixed;
    matrix.data[2][2] = cos_fixed;

    return matrix;
}

/*
| cos  0  sin  0  |
|  0   1   0   0  |
| -sin 0  cos  0  |
|  0   0   0   1  |
*/
Matrix4 Matrix4::rotationY(int32_t angleFixed)
{
    Matrix4 matrix = Matrix4::identity();

    float angle = fix2float(angleFixed, FIXED_POINT_SHIFT);
    float radians = (angle * PI) / 180;

    float cos_angle = cosf(radians);
    float sin_angle = sinf(radians);

    int32_t cos_fixed = float2fix(cos_angle, FIXED_POINT_SHIFT);
    int32_t sin_fixed = float2fix(sin_angle, FIXED_POINT_SHIFT);

    matrix.data[0][0] = cos_fixed;
    matrix.data[0][2] = sin_fixed;
    matrix.data[2][0] = -sin_fixed;
    matrix.data[2][2] = cos_fixed;

    return matrix;
}

/*
| cos -sin 0   0  |
| sin cos  0   0  |
|  0   0   1   0  |
|  0   0   0   1  |
*/
Matrix4 Matrix4::rotationZ(int32_t angleFixed)
{
    Matrix4 matrix = Matrix4::identity();

    float angle = fix2float(angleFixed, FIXED_POINT_SHIFT);
    float radians = (angle * PI) / 180;

    float cos_angle = cosf(radians);
    float sin_angle = sinf(radians);

    int32_t cos_fixed = float2fix(cos_angle, FIXED_POINT_SHIFT);
    int32_t sin_fixed = float2fix(sin_angle, FIXED_POINT_SHIFT);

    matrix.data[0][0] = cos_fixed;
    matrix.data[0][1] = -sin_fixed;
    matrix.data[1][0] = sin_fixed;
    matrix.data[1][1] = cos_fixed;

    return matrix;
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

// Перегрузка оператора * для умножения матрицы на вектор
Vector3 Matrix4::operator*(const Vector3 &vec) const
{
    Vector3 result;

    result.x = float2fix(fix2float(data[0][0], FIXED_POINT_SHIFT) * fix2float(vec.x, FIXED_POINT_SHIFT) + fix2float(data[0][1], FIXED_POINT_SHIFT) * fix2float(vec.y, FIXED_POINT_SHIFT) + fix2float(data[0][2], FIXED_POINT_SHIFT) * fix2float(vec.z, FIXED_POINT_SHIFT) + fix2float(data[0][3], FIXED_POINT_SHIFT) * 1.0f, FIXED_POINT_SHIFT);
    result.y = float2fix(fix2float(data[1][0], FIXED_POINT_SHIFT) * fix2float(vec.x, FIXED_POINT_SHIFT) + fix2float(data[1][1], FIXED_POINT_SHIFT) * fix2float(vec.y, FIXED_POINT_SHIFT) + fix2float(data[1][2], FIXED_POINT_SHIFT) * fix2float(vec.z, FIXED_POINT_SHIFT) + fix2float(data[1][3], FIXED_POINT_SHIFT) * 1.0f, FIXED_POINT_SHIFT);
    result.z = float2fix(fix2float(data[2][0], FIXED_POINT_SHIFT) * fix2float(vec.x, FIXED_POINT_SHIFT) + fix2float(data[2][1], FIXED_POINT_SHIFT) * fix2float(vec.y, FIXED_POINT_SHIFT) + fix2float(data[2][2], FIXED_POINT_SHIFT) * fix2float(vec.z, FIXED_POINT_SHIFT) + fix2float(data[2][3], FIXED_POINT_SHIFT) * 1.0f, FIXED_POINT_SHIFT);

    return result;
}

Matrix4 Matrix4::getViewMatrix(const Vector3 &cameraPosition, const Vector3 &target, const Vector3 &up)
{
    Vector3 zAxis = cameraPosition - target;
    Vector3 normZ = normalizeVector(zAxis);
    Vector3 xAxis = up * zAxis;
    Vector3 normX = normalizeVector(xAxis);
    Vector3 yAxis = zAxis * xAxis;
    Vector3 normY = normalizeVector(yAxis);

    Matrix4 viewMatrix;
    // Заполняем элементы матрицы построчно
    viewMatrix.data[0][0] = normX.x;
    viewMatrix.data[0][1] = normY.x;
    viewMatrix.data[0][2] = normZ.x;
    viewMatrix.data[0][3] = float2fix(0.0f, FIXED_POINT_SHIFT);

    viewMatrix.data[1][0] = normX.y;
    viewMatrix.data[1][1] = normY.y;
    viewMatrix.data[1][2] = normZ.y;
    viewMatrix.data[1][3] = float2fix(0.0f, FIXED_POINT_SHIFT);

    viewMatrix.data[2][0] = normX.z;
    viewMatrix.data[2][1] = normY.z;
    viewMatrix.data[2][2] = normZ.z;
    viewMatrix.data[2][3] = float2fix(1.0f, FIXED_POINT_SHIFT);

    viewMatrix.data[3][0] = scalarProduct(-normX, cameraPosition);
    viewMatrix.data[3][1] = scalarProduct(-normY, cameraPosition);
    viewMatrix.data[3][2] = scalarProduct(-normZ, cameraPosition);
    viewMatrix.data[3][3] = float2fix(1.0f, FIXED_POINT_SHIFT);
    return viewMatrix;
}

Matrix4 Matrix4::getProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    float radiansFOV = fov * PI / 180;

    float tanHalfFOV = tanf(radiansFOV / 2.0f);
    float zRange = nearPlane - farPlane;

    Matrix4 projectionMatrix;
    // Заполняем элементы матрицы построчно
    projectionMatrix.data[0][0] = float2fix((1.0f / (tanHalfFOV * aspectRatio)), FIXED_POINT_SHIFT);
    projectionMatrix.data[0][1] = 0;
    projectionMatrix.data[0][2] = 0;
    projectionMatrix.data[0][3] = 0;

    projectionMatrix.data[1][0] = 0;
    projectionMatrix.data[1][1] = float2fix(1.0f / tanHalfFOV, FIXED_POINT_SHIFT);
    projectionMatrix.data[1][2] = 0;
    projectionMatrix.data[1][3] = 0;

    projectionMatrix.data[2][0] = 0;
    projectionMatrix.data[2][1] = 0;
    projectionMatrix.data[2][2] = float2fix((farPlane + nearPlane) / zRange, FIXED_POINT_SHIFT);
    projectionMatrix.data[2][3] = float2fix((2 * farPlane * nearPlane) / (nearPlane - farPlane), FIXED_POINT_SHIFT);

    projectionMatrix.data[3][0] = 0;
    projectionMatrix.data[3][1] = 0;
    projectionMatrix.data[3][2] = float2fix(-1.0f, FIXED_POINT_SHIFT);
    projectionMatrix.data[3][3] = float2fix(1.0f, FIXED_POINT_SHIFT);

    return projectionMatrix;
}