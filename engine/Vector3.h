#ifndef VECTOR3_H
#define VECTOR3_H

// struct for use 3D Vectors
struct Vector3
{
    int x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(int x, int y, int z) : x(x), y(y), z(z) {}
};

// Function for addition two 3D Vectors
Vector3 addVectors(const Vector3 &vector1, const Vector3 &vector2);

// Function for subtraction two 3D Vectors
Vector3 subVectors(const Vector3 &vector1, const Vector3 &vector2);

// Function for alculating the product of a 3D Vector by a scalar
Vector3 multiplyVectorByScalar(const Vector3 &v, float scalar);

// Аunction for 3D Vector normalization
Vector3 normalizeVector(const Vector3 &vector);

// Function for alculating the scalar product of 3D Vector by a 3D Vector
int scalarProduct(const Vector3 &vector1, const Vector3 &vector2);

#endif // VECTOR_H