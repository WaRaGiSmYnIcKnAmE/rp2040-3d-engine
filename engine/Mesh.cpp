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
    float halfSide = sideLength / 2;

    cube.vertices = {
        Vertex({-10.0f, -10.0f, -10.0f}, {0, 0}),
        Vertex({10.0f, -10.0f, -10.0f}, {0, 0}),
        Vertex({10.0f, 10.0f, -10.0f}, {0, 0}),
        Vertex({-10.0f, 10.0f, -10.0f}, {0, 0}),
        Vertex({-10.0f, -10.0f, 10.0f}, {0, 0}),
        Vertex({10.0f, -10.0f, 10.0f}, {0, 0}),
        Vertex({10.0f, 10.0f, 10.0f}, {0, 0}),
        Vertex({-10.0f, 10.0f, 10.0f}, {0, 0})};

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
