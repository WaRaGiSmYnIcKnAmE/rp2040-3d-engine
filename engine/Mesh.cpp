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
    int halfSide = TO_FIXED(sideLength / 2);
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
    int halfBase = TO_FIXED(baseSize / 2);
    int heightFixed = TO_FIXED(height);

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
    int radiusFixed = TO_FIXED(radius);

    for (int lat = 0; lat <= segments; ++lat)
    {
        float theta = M_PI * lat / segments;
        int sinThetaFixed = TO_FIXED(sinf(theta));
        int cosThetaFixed = TO_FIXED(cosf(theta));

        for (int lon = 0; lon <= segments; ++lon)
        {
            float phi = 2 * M_PI * lon / segments;
            int sinPhiFixed = TO_FIXED(sinf(phi));
            int cosPhiFixed = TO_FIXED(cosf(phi));

            // Вычисление координат вершины в fixed-point
            int x = MULT_FIXED(MULT_FIXED(cosPhiFixed, sinThetaFixed), radiusFixed);
            int y = MULT_FIXED(cosThetaFixed, radiusFixed);
            int z = MULT_FIXED(MULT_FIXED(sinPhiFixed, sinThetaFixed), radiusFixed);

            sphere.vertices.push_back(Vertex({x, y, z}, {0, 0}));
        }
    }

    for (int lat = 0; lat < segments; ++lat)
    {
        for (int lon = 0; lon < segments; ++lon)
        {
            int first = (lat * (segments + 1)) + lon;
            int second = first + segments + 1;

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