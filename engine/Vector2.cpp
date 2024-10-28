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
    int32_t fixedScalar = float2fix(scalar, FIXED_POINT_SHIFT); // Преобразование в фиксированную точку
    return Vector2(fix2float(vector.x * fixedScalar, FIXED_POINT_SHIFT),
                   fix2float(vector.y * fixedScalar, FIXED_POINT_SHIFT));
}

Vector2 normalizeVector(const Vector2 &vector)
{
    float magnitude = sqrtf(fix2float(vector.x * vector.x + vector.y * vector.y, FIXED_POINT_SHIFT));

    if (magnitude > 0.0f)
    {
        // Вычисляем нормализованный вектор, деля каждый компонент на модуль
        float invMagnitude = 1.0f / magnitude;
        return Vector2(float2fix(fix2float(vector.x, FIXED_POINT_SHIFT) * invMagnitude, FIXED_POINT_SHIFT),
                       float2fix(fix2float(vector.y, FIXED_POINT_SHIFT) * invMagnitude, FIXED_POINT_SHIFT));
    }
    return vector; // Возвращаем исходный вектор, если величина равна 0
}

int32_t scalarProduct(const Vector2 &vector1, const Vector2 &vector2)
{
    return float2fix(fix2float(vector1.x, FIXED_POINT_SHIFT) * fix2float(vector2.x, FIXED_POINT_SHIFT) + fix2float(vector1.y, FIXED_POINT_SHIFT) * fix2float(vector2.y, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);
}