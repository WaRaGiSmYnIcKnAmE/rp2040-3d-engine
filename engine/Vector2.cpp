#include "Vector2.h"
#include "pico/float.h"

Vector2 addVectors(const Vector2 &vector1, const Vector2 &vector2)
{
    return Vector2(vector1.x + vector2.x, vector1.y + vector2.y);
}

Vector2 subVectors(const Vector2 &vector1, const Vector2 &vector2)
{
    return Vector2(vector1.x - vector2.x, vector1.y - vector2.y);
}

Vector2 multiplyVectorByScalar(const Vector2 &vector, float scalar)
{
    return Vector2(vector.x * scalar, vector.y * scalar);
}

Vector2 normalizeVector(const Vector2 &vector)
{
    int32_t magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);

    if (magnitude > 0)
    {
        return multiplyVectorByScalar(vector, 1000 / magnitude);
    }
    return vector;
}

int scalarProduct(const Vector2 &vector1, const Vector2 &vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}