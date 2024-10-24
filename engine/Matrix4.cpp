#include "Matrix4.h"
#include <pico/float.h>

Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            data[i][j] = 0.0f;
}

Matrix4 Matrix4::identity()
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
        result.data[i][i] = 1.0f;
    return result;
}

Matrix4 Matrix4::multiply(const Matrix4 &other) const
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.data[i][j] = 0.0f;
            for (int k = 0; k < 4; k++)
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Vector3 Matrix4::multiply(const Vector3 &vec) const
{
    Vector3 result;
    result.x = data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3] * 1.0f;
    result.y = data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3] * 1.0f;
    result.z = data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3] * 1.0f;
    return result;
}

Matrix4 Matrix4::translation(float x, float y, float z)
{
    Matrix4 result = Matrix4::identity();
    result.data[0][3] = x;
    result.data[1][3] = y;
    result.data[2][3] = z;
    return result;
}

Matrix4 Matrix4::scale(float sx, float sy, float sz)
{
    Matrix4 result = Matrix4::identity();
    result.data[0][0] = sx;
    result.data[1][1] = sy;
    result.data[2][2] = sz;
    return result;
}

Matrix4 Matrix4::rotationX(float angle)
{
    Matrix4 result = Matrix4::identity();
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    result.data[1][1] = cosA;
    result.data[1][2] = -sinA;
    result.data[2][1] = sinA;
    result.data[2][2] = cosA;
    return result;
}

Matrix4 Matrix4::rotationY(float angle)
{
    Matrix4 result = Matrix4::identity();
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    result.data[0][0] = cosA;
    result.data[0][2] = sinA;
    result.data[2][0] = -sinA;
    result.data[2][2] = cosA;
    return result;
}

Matrix4 Matrix4::rotationZ(float angle)
{
    Matrix4 result = Matrix4::identity();
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    result.data[0][0] = cosA;
    result.data[0][1] = -sinA;
    result.data[1][0] = sinA;
    result.data[1][1] = cosA;
    return result;
}

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