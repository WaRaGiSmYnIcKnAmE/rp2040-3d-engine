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

// Функция для умножения 3D-вектора на скаляр, используя фиксированную точку
Vector3 multiplyVectorByScalar(const Vector3 &vector, int scalar)
{
    int32_t fixedScalar = float2fix(scalar, FIXED_POINT_SHIFT); // Преобразование в фиксированную точку
    return Vector3(fix2float(vector.x * fixedScalar, FIXED_POINT_SHIFT),
                   fix2float(vector.y * fixedScalar, FIXED_POINT_SHIFT),
                   fix2float(vector.z * fixedScalar, FIXED_POINT_SHIFT));
}

// Функция для нормализации 3D-вектора (преобразование в единичный вектор)
Vector3 normalizeVector(const Vector3 &vector)
{
    // Вычисляем величину (модуль) вектора и конвертируем в float
    float magnitude = sqrtf(fix2float(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z, FIXED_POINT_SHIFT));

    if (magnitude > 0.0f)
    {
        // Вычисляем нормализованный вектор, деля каждый компонент на модуль
        float invMagnitude = 1.0f / magnitude;
        return Vector3(float2fix(fix2float(vector.x, FIXED_POINT_SHIFT) * invMagnitude, FIXED_POINT_SHIFT),
                       float2fix(fix2float(vector.y, FIXED_POINT_SHIFT) * invMagnitude, FIXED_POINT_SHIFT),
                       float2fix(fix2float(vector.z, FIXED_POINT_SHIFT) * invMagnitude, FIXED_POINT_SHIFT));
    }
    return vector; // Возвращаем исходный вектор, если величина равна 0
}

// Скалярное произведение двух векторов
int32_t scalarProduct(const Vector3 &vector1, const Vector3 &vector2)
{
    return float2fix(fix2float(vector1.x, FIXED_POINT_SHIFT) * fix2float(vector2.x, FIXED_POINT_SHIFT) + fix2float(vector1.y, FIXED_POINT_SHIFT) * fix2float(vector2.y, FIXED_POINT_SHIFT) + fix2float(vector1.z, FIXED_POINT_SHIFT) * fix2float(vector2.z, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);
}