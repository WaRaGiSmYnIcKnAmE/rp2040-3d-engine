#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector3.h"
#include "pico/float.h"

#define FIXED_POINT_SHIFT 16

struct Matrix4
{
    int32_t data[4][4];

    Matrix4();

    static Matrix4 identity();

    Matrix4 multiply(const Matrix4 &other) const;

    Vector3 multiply(const Vector3 &vec) const;

    Matrix4 operator*(const Matrix4 &other) const;
    Vector3 operator*(const Vector3 &vec) const;
    Matrix4 &operator*=(const Matrix4 &other);

    static Matrix4 translation(int32_t x, int32_t y, int32_t z);
    static Matrix4 scale(int32_t sx, int32_t sy, int32_t sz);
    static Matrix4 rotationX(int32_t angleFixed);
    static Matrix4 rotationY(int32_t angleFixed);
    static Matrix4 rotationZ(int32_t angleFixed);

    Matrix4 transpose() const;

    static Matrix4 perspective(int32_t fov, int32_t aspectRatio, int32_t near, int32_t far);

    static Matrix4 getViewMatrix(const Vector3 &cameraPosition, const Vector3 &target, const Vector3 &up);
    static Matrix4 getProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);
};

#endif // MATRIX4_H
