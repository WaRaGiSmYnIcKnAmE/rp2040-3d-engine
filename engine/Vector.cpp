#include "Vector.h"
#include "pico/float.h"

Vector3 additionVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return Vector3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector3 subtractionVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return Vector3(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
}

Vector3 multiplyVectorScalar(const Vector3 &v, float scalar)
{
    return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vector3 normalizeVector(const Vector3 &vector)
{
    int32_t magnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

    if (magnitude > 0)
    {
        return multiplyVectorScalar(vector, 1000 / magnitude);
    }
    return vector;
}