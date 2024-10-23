#include "Vector.h"
#include <pico/float.h>

Vector2 addVectors(const Vector2 &vector1, const Vector2 &vector2)
{
    return Vector2(vector1.x + vector2.x, vector1.y + vector2.y);
}
Vector2Int addVectors(const Vector2Int &vector1, const Vector2Int &vector2)
{
    return Vector2Int(vector1.x + vector2.x, vector1.y + vector2.y);
}
Vector3 addVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return Vector3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}
Vector3Int addVectors(const Vector3Int &vector1, const Vector3Int &vector2)
{
    return Vector3Int(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector2 subtractVectors(const Vector2 &vector1, const Vector2 &vector2)
{
    return Vector2(vector1.x - vector2.x, vector1.y - vector2.y);
}
Vector3 subtractVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return Vector3(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
}
Vector2Int subtractVectors(const Vector2Int &vector1, const Vector2Int &vector2)
{
    return Vector2Int(vector1.x - vector2.x, vector1.y - vector2.y);
}
Vector3Int subtractVectors(const Vector3Int &vector1, const Vector3Int &vector2)
{
    return Vector3Int(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
}

Vector3 multiplyVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return Vector3(
        vector1.x * vector2.z - vector1.z * vector2.y,
        vector1.z * vector2.x - vector1.x * vector2.z,
        vector1.z * vector2.y - vector1.y * vector2.x);
}
Vector2 multiplyVectors(const Vector2 &vector1, const Vector2 &vector2)
{
    return Vector2(
        vector1.x * vector2.y - vector1.x * vector2.y,
        vector1.y * vector2.x - vector1.x * vector2.y);
}
Vector3Int multiplyVectors(const Vector3Int &vector1, const Vector3Int &vector2)
{
    return Vector3Int(
        vector1.x * vector2.z - vector1.z * vector2.y,
        vector1.z * vector2.x - vector1.x * vector2.z,
        vector1.z * vector2.y - vector1.y * vector2.x);
}
Vector2Int multiplyVectors(const Vector2Int &vector1, const Vector2Int &vector2)
{
    return Vector2Int(
        vector1.x * vector2.y - vector1.x * vector2.y,
        vector1.y * vector2.x - vector1.x * vector2.y);
}

Vector2 multiplyVectorScalar(const Vector2 &vector, float scalar)
{
    return Vector2(vector.x * scalar, vector.y * scalar);
}
Vector3 multiplyVectorScalar(const Vector3 &vector, float scalar)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}
Vector2Int multiplyVectorScalar(const Vector2Int &vector, int scalar)
{
    return Vector2Int(vector.x * scalar, vector.y * scalar);
}
Vector3Int multiplyVectorScalar(const Vector3Int &vector, int scalar)
{
    return Vector3Int(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

Vector2 normalizeVector(const Vector2 &vector)
{
    float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
    if (magnitude > 0)
    {
        return multiplyVectorScalar(vector, 1.0f / magnitude);
    }
    return vector;
}
Vector3 normalizeVector(const Vector3 &vector)
{
    float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    if (magnitude > 0)
    {
        return multiplyVectorScalar(vector, 1.0f / magnitude);
    }
    return vector;
}
Vector2Int normalizeVector(const Vector2Int &vector)
{
    int32_t magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
    if (magnitude > 0)
    {
        return multiplyVectorScalar(vector, 1000 / magnitude);
    }
    return vector;
}
Vector3Int normalizeVector(const Vector3Int &vector)
{
    int32_t magnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    if (magnitude > 0)
    {
        return multiplyVectorScalar(vector, 1000 / magnitude);
    }
    return vector;
}

float scalarVectors(const Vector2 &vector1, const Vector2 &vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}
float scalarVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}
int scalarVectors(const Vector2Int &vector1, const Vector2Int &vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}
int scalarVectors(const Vector3Int &vector1, const Vector3Int &vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}
