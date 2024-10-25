#ifndef MESH_H
#define MESH_H

#include "pico/stdlib.h"

#include <vector>

#include "Vector3.h"
#include "Color.h"
#include "Vertex.h"
#include "Matrix4.h"

// Фиксированное значение масштаба для преобразования в fixed-point (16 целых, 16 дробных)
#define FIXED_POINT_SHIFT 16
#define TO_FIXED(x) ((int)((x) * (1 << FIXED_POINT_SHIFT)))   // Преобразовать float в fixed-point
#define FROM_FIXED(x) ((float)(x) / (1 << FIXED_POINT_SHIFT)) // Преобразовать fixed-point в float
#define MULT_FIXED(a, b) (((a) * (b)) >> FIXED_POINT_SHIFT)   // Умножение в fixed-point

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
    static Mesh createSphere(int radius, int segments);
    static Mesh createPyramid(int baseSize, int height);

private:
    std::vector<Vertex> vertices; // Массив вершин меша
    std::vector<int> indices;     // Индексация для треугольников и других примитивов
    Color color;                  // Цвет меша для применения общих эффектов
};

#endif // MESH_H
