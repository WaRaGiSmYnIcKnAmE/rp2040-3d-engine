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
    int fixedScalar = TO_FIXED(scalar);
    return Vector2(MULT_FIXED(vector.x, fixedScalar), MULT_FIXED(vector.y, fixedScalar));
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
    return FROM_FIXED(MULT_FIXED(vector1.x, vector2.x) + MULT_FIXED(vector1.y, vector2.y));
}