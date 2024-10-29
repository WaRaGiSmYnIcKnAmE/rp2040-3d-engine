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

Mesh Mesh::createPlane(float width, float depth)
{
    Mesh plane;

    // Вершины
    float halfWidth = width / 2;
    float halfDepth = depth / 2;
    plane.vertices = {
        Vertex({-halfWidth, 0, -halfDepth}, {0, 0}),
        Vertex({halfWidth, 0, -halfDepth}, {0, 0}),
        Vertex({halfWidth, 0, halfDepth}, {0, 0}),
        Vertex({-halfWidth, 0, halfDepth}, {0, 0}),
    };

    // Индексы
    plane.indices = {
        0, 1, 2,
        0, 2, 3};

    return plane;
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

Mesh Mesh::createSphere(float radius, int sectors)
{
    Mesh sphere;

    float phiStep = M_PI / sectors;       // Угол по широте
    float thetaStep = 2 * M_PI / sectors; // Угол по долготе

    for (int i = 0; i <= sectors; ++i)
    {
        for (int j = 0; j <= sectors; ++j)
        {
            float phi = i * phiStep;     // Угол по широте
            float theta = j * thetaStep; // Угол по долготе

            // Вычисление координат вершины
            float x = radius * sinf(phi) * cosf(theta);
            float y = radius * cosf(phi);
            float z = radius * sinf(phi) * sinf(theta);

            sphere.vertices.push_back(Vertex({x, y, z}, {0, 0}));
        }
    }

    for (int i = 0; i < sectors; ++i)
    {
        for (int j = 0; j < sectors; ++j)
        {
            int first = i * (sectors + 1) + j;
            int second = first + sectors + 1;

            // Формирование индексов треугольников
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

Mesh Mesh::createPyramid(float baseLength, float height)
{
    Mesh pyramid;

    // Вершины
    float halfBase = baseLength / 2;
    pyramid.vertices = {
        Vertex({0, height, 0}, {0, 0}),            // Вершина
        Vertex({-halfBase, 0, -halfBase}, {0, 0}), // Задний левый угол
        Vertex({halfBase, 0, -halfBase}, {0, 0}),  // Задний правый угол
        Vertex({halfBase, 0, halfBase}, {0, 0}),   // Передний правый угол
        Vertex({-halfBase, 0, halfBase}, {0, 0})   // Передний левый угол
    };

    // Индексы
    pyramid.indices = {
        0, 1, 2,         // Задняя грань
        0, 2, 3,         // Правая грань
        0, 3, 4,         // Передняя грань
        0, 4, 1,         // Левая грань
        1, 2, 3, 3, 4, 1 // Основание
    };

    return pyramid;
}

Mesh Mesh::createCone(float radius, float height, int sectors)
{
    Mesh cone;

    // Вершина конуса
    cone.vertices.push_back(Vertex({0, height, 0}, {0, 0}));

    // Вершины основания
    for (int i = 0; i <= sectors; ++i)
    {
        float theta = i * 2 * M_PI / sectors;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        cone.vertices.push_back(Vertex({x, 0, z}, {0, 0}));
    }

    // Индексы
    for (int i = 1; i <= sectors; ++i)
    {
        cone.indices.push_back(0);               // Вершина
        cone.indices.push_back(i);               // Текущая вершина
        cone.indices.push_back(i % sectors + 1); // Следующая вершина
    }

    return cone;
}