#ifndef VECTOR_H
#define VECTOR_H

struct Vector2
{
    int x, y;
    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}
};

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

// Function for alculating the product of a vector by a scalar
Vector3 multiplyVectorScalar(const Vector3 &v, float scalar);

// Аunction for vector normalization
Vector3 normalizeVector(const Vector3 &vector);

#endif // VECTOR_H