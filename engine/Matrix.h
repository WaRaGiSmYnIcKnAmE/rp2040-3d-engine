#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

struct Matrix4
{
    float data[4][4];

    Matrix4();
    static Matrix4 identity();
    static Matrix4 perspective(float fov, float aspectRatio, float nearPlane, float farPlane);
    static Matrix4 lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);
};

#endif // MATRIX_H