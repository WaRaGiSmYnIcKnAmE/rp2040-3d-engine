#ifndef VECTOR2_H
#define VECTOR2_H

// struct for use 2D Vectors
struct Vector2
{
    int x, y;

    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}
};

// Function for addition two 2D Vectors
Vector2 addVectors(const Vector2 &vector1, const Vector2 &vector2);

// Function for subtraction two 2D Vectors
Vector2 subVectors(const Vector2 &vector1, const Vector2 &vector2);

// Function for alculating the product of a 2D Vector by a scalar
Vector2 multiplyVectorByScalar(const Vector2 &v, float scalar);

// Аunction for 2D Vector normalization
Vector2 normalizeVector(const Vector2 &vector);

// Function for alculating the scalar product of 2D Vector by a 3D Vector
int scalarProduct(const Vector2 &vector1, const Vector2 &vector2);

#endif // VECTOR_H