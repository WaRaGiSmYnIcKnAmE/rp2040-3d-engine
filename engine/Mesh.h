#ifndef MESH_H
#define MESH_H

#include "pico/stdlib.h"

#include <vector>

#include "Vector3.h"
#include "Color.h"
#include "Vertex.h"
#include "Matrix4.h"

#define FIXED_POINT_SHIFT 16

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<Vertex> &vertices, const std::vector<int> &indices);

    // Методы работы с вершинами и индексацией
    void addVertex(const Vertex &vertex);
    void addIndex(int index);
    Vertex getVertex(int index) const;

    // Применение трансформаций к мешу
    void applyTransformation(const Matrix4 &matrix);

    // Получение количества вершин и индексов
    int getVertexCount() const;
    int getIndexCount() const;

    // Получение цвета меша
    Color getColor() const;

    // Статические методы для генерации примитивов
    static Mesh createCube(int size);

    std::vector<Vertex> vertices; // Массив вершин меша
    std::vector<int> indices;     // Индексация для треугольников и других примитивов
    Color color;                  // Цвет меша для применения общих эффектов

    // private:
};

#endif // MESH_H
