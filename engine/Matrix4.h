#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector.h"

class Matrix4
{
public:
    float data[4][4];

    // Function for create the null matrix
    Matrix4();

    // Function for create the unit matrix
    static Matrix4 identity();

    // Multiplying a matrix by a matrix
    Matrix4 multiply(const Matrix4 &other) const;

    // Multiplying a matrix by a vector
    Vector3 multiply(const Vector3 &vec) const;

    // Creating matrices for transformations
    static Matrix4 translation(float x, float y, float z);
    static Matrix4 scale(float sx, float sy, float sz);
    static Matrix4 rotationX(float angle);
    static Matrix4 rotationY(float angle);
    static Matrix4 rotationZ(float angle);

    // Matrix transposition
    Matrix4 transpose() const;
};

#endif // MATRIX4X4_H
