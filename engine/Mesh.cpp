#include "Mesh.h"
#include "pico/float.h"

// Конструктор по умолчанию
Mesh::Mesh() : color(Color::White()) {}

// Конструктор с массивом вершин и индексов
Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<int> &indices)
    : vertices(vertices), indices(indices), color(Color::White()) {}

// Добавление вершины
void Mesh::addVertex(const Vertex &vertex)
{
    vertices.push_back(vertex);
}

// Добавление индекса
void Mesh::addIndex(int index)
{
    indices.push_back(index);
}

// Получение вершины по индексу
Vertex Mesh::getVertex(int index) const
{
    if (index < vertices.size())
    {
        return vertices[index];
    }
    return Vertex(); // Возврат пустой вершины, если индекс вне диапазона
}

// Применение трансформации к мешу
void Mesh::applyTransformation(const Matrix4 &matrix)
{
    for (auto &vertex : vertices)
    {
        Vector3 transformedPosition = matrix.multiply(vertex.position);
        vertex.position = transformedPosition;
    }
}

// Получение количества вершин
int Mesh::getVertexCount() const
{
    return vertices.size();
}

// Получение количества индексов
int Mesh::getIndexCount() const
{
    return indices.size();
}

// Получение цвета
Color Mesh::getColor() const
{
    return color;
}

// Создание куба
Mesh Mesh::createCube(int sideLength)
{
    Mesh cube;
    float halfSide = float2fix(int2float(sideLength / 2), FIXED_POINT_SHIFT);
    cube.vertices = {
        // Вершины куба (8 вершин)
        Vertex({-halfSide, -halfSide, -halfSide}, {0, 0}),
        Vertex({halfSide, -halfSide, -halfSide}, {0, 0}),
        Vertex({halfSide, halfSide, -halfSide}, {0, 0}),
        Vertex({-halfSide, halfSide, -halfSide}, {0, 0}),
        Vertex({-halfSide, -halfSide, halfSide}, {0, 0}),
        Vertex({halfSide, -halfSide, halfSide}, {0, 0}),
        Vertex({halfSide, halfSide, halfSide}, {0, 0}),
        Vertex({-halfSide, halfSide, halfSide}, {0, 0})};

    cube.indices = {
        0, 1, 2, 2, 3, 0, // Задняя грань
        4, 5, 6, 6, 7, 4, // Передняя грань
        0, 4, 7, 7, 3, 0, // Левая грань
        1, 5, 6, 6, 2, 1, // Правая грань
        0, 1, 5, 5, 4, 0, // Нижняя грань
        3, 2, 6, 6, 7, 3  // Верхняя грань
    };

    return cube;
}

// Создание четырехугольной пирамиды
Mesh Mesh::createPyramid(int baseSize, int height)
{
    Mesh pyramid;
    float halfBase = float2fix(int2float(baseSize / 2), FIXED_POINT_SHIFT);
    float heightFixed = float2fix(int2float(height), FIXED_POINT_SHIFT);

    pyramid.vertices = {
        Vertex({-halfBase, 0, -halfBase}, {0, 0}),
        Vertex({halfBase, 0, -halfBase}, {0, 0}),
        Vertex({halfBase, 0, halfBase}, {0, 0}),
        Vertex({-halfBase, 0, halfBase}, {0, 0}),
        Vertex({0, halfBase, 0}, {0, 0})};

    pyramid.indices = {
        0, 1, 4,         // Передняя грань
        1, 2, 4,         // Правая грань
        2, 3, 4,         // Задняя грань
        3, 0, 4,         // Левая грань
        0, 1, 2, 2, 3, 0 // Основание
    };

    return pyramid;
}

// Создание сферы
Mesh Mesh::createSphere(int radius, int segments)
{
    Mesh sphere;
    int32_t radiusFixed = float2fix(int2float(radius), FIXED_POINT_SHIFT);

    for (int32_t lat = 0; lat <= segments; ++lat)
    {
        float theta = M_PI * lat / segments;
        int32_t sinThetaFixed = float2fix(int2float(sinf(theta)), FIXED_POINT_SHIFT);
        int32_t cosThetaFixed = float2fix(int2float(cosf(theta)), FIXED_POINT_SHIFT);

        for (int lon = 0; lon <= segments; ++lon)
        {
            float phi = 2 * M_PI * lon / segments;
            int32_t sinPhiFixed = float2fix(int2float(sinf(phi)), FIXED_POINT_SHIFT);
            int32_t cosPhiFixed = float2fix(int2float(cosf(phi)), FIXED_POINT_SHIFT);

            // Вычисление координат вершины в fixed-point
            int32_t x = float2fix(fix2float(cosPhiFixed, FIXED_POINT_SHIFT) * fix2float(sinThetaFixed, FIXED_POINT_SHIFT) * fix2float(radiusFixed, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);
            int32_t y = float2fix(fix2float(cosThetaFixed, FIXED_POINT_SHIFT) * fix2float(radiusFixed, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);
            int32_t z = float2fix(fix2float(sinPhiFixed, FIXED_POINT_SHIFT) * fix2float(sinThetaFixed, FIXED_POINT_SHIFT) * fix2float(radiusFixed, FIXED_POINT_SHIFT), FIXED_POINT_SHIFT);

            sphere.vertices.push_back(Vertex({fix2float(x, FIXED_POINT_SHIFT), fix2float(y, FIXED_POINT_SHIFT), fix2float(z, FIXED_POINT_SHIFT)}, {0, 0}));
        }
    }

    for (int lat = 0; lat < segments; ++lat)
    {
        for (int lon = 0; lon < segments; ++lon)
        {
            int32_t first = (lat * (segments + 1)) + lon;
            int32_t second = first + segments + 1;

            // Треугольники, формирующие сферу
            sphere.indices.push_back(first);
            sphere.indices.push_back(second);
            sphere.indices.push_back(first + 1);

            sphere.indices.push_back(second);
            sphere.indices.push_back(second + 1);
            sphere.indices.push_back(first + 1);
        }
    }

    return sphere;
}