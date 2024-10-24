#include "Vector3.h"
#include "pico/float.h"

Vector3 addVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return Vector3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector3 subVectors(const Vector3 &vector1, const Vector3 &vector2)
{
    return Vector3(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
}

Vector3 multiplyVectorByScalar(const Vector3 &v, int scalar)
{
    int fixedScalar = TO_FIXED(scalar);
    return Vector3(MULT_FIXED(v.x, fixedScalar), MULT_FIXED(v.y, fixedScalar), MULT_FIXED(v.z, fixedScalar));
}

Vector3 normalizeVector(const Vector3 &vector)
{
    int32_t magnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

    if (magnitude > 0)
    {
        return multiplyVectorByScalar(vector, 1000 / magnitude);
    }
    return vector;
}

int scalarProduct(const Vector3 &vector1, const Vector3 &vector2)
{
    return FROM_FIXED(MULT_FIXED(vector1.x, vector2.x) + MULT_FIXED(vector1.y, vector2.y) + MULT_FIXED(vector1.z, vector2.z));
}