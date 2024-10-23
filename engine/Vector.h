#ifndef VECTOR_H
#define VECTOR_H

#include "Vector.cpp"

// Двумерный вектор с плавающей точностью
struct Vector2
{
    float x, y;
    Vector2() : x(0), y(0) {}
    Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}
};

// Двумерный вектор с целочисленной точностью
struct Vector2Int
{
    int x, y;
    Vector2Int() : x(0), y(0) {}
    Vector2Int(int xVal, int yVal) : x(xVal), y(yVal) {}
};

// Трехмерный вектор с плавающей точностью
struct Vector3
{
    float x, y, z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}
};

// Трехмерный вектор с целочисленной точностью
struct Vector3Int
{
    int x, y, z;
    Vector3Int() : x(0), y(0), z(0) {}
    Vector3Int(int xVal, int yVal, int zVal) : x(xVal), y(yVal), z(zVal) {}
};

// Четырехмерный вектор с плавающей точностью
struct Vector4
{
    float x, y, z, w;
    Vector4() : x(0), y(0), z(0), w(1) {}
    Vector4(float xVal, float yVal, float zVal, float wVal) : x(xVal), y(yVal), z(zVal), w(wVal) {}
};

// Четырехмерный вектор с целочисленной точностью
struct Vector4Int
{
    float x, y, z, w;
    Vector4Int() : x(0), y(0), z(0), w(1) {}
    Vector4Int(int xVal, int yVal, int zVal, int wVal) : x(xVal), y(yVal), z(zVal), w(wVal) {}
};

// Сложение векторов

Vector2 addVectors(const Vector2 &vector1, const Vector2 &vector2);
Vector3 addVectors(const Vector3 &vector1, const Vector3 &vector2);
Vector2Int addVectors(const Vector2Int &vector1, const Vector2Int &vector2);
Vector3Int addVectors(const Vector3Int &vector1, const Vector3Int &vector2);

// Вычитание векторов

Vector2 subtractVectors(const Vector2 &vector1, const Vector2 &vector2);
Vector3 subtractVectors(const Vector3 &vector1, const Vector3 &vector2);
Vector2Int subtractVectors(const Vector2Int &vector1, const Vector2Int &vector2);
Vector3Int subtractVectors(const Vector3Int &vector1, const Vector3Int &vector2);

// Векторное произведение векторов

Vector2 multiplyVectors(const Vector2 &vector1, const Vector2 &vector2);
Vector3 multiplyVectors(const Vector3 &vector1, const Vector3 &vector2);
Vector2Int multiplyVectors(const Vector2Int &vector1, const Vector2Int &vector2);
Vector3Int multiplyVectors(const Vector3Int &vector1, const Vector3Int &vector2);

// Умножение вектора на скаляр

Vector2 multiplyVectorScalar(const Vector2 &vector, float scalar);
Vector3 multiplyVectorScalar(const Vector3 &vector, float scalar);
Vector2Int multiplyVectorScalar(const Vector2Int &vector, int scalar);
Vector3Int multiplyVectorScalar(const Vector3Int &vector, int scalar);

// Нормализация вектора

Vector2 normalizeVector(const Vector2 &vector);
Vector3 normalizeVector(const Vector3 &vector);
Vector2Int normalizeVector(const Vector2Int &vector);
Vector3Int normalizeVector(const Vector3Int &vector);

// Скалярное произведение векторов

float scalarVectors(const Vector2 &vector1, const Vector2 &vector2);
float scalarVectors(const Vector3 &vector1, const Vector3 &vector2);
int scalarVectors(const Vector2Int &vector1, const Vector2Int &vector2);
int scalarVectors(const Vector3Int &vector1, const Vector3Int &vector2);

#endif // VECTOR_H