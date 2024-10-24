#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h" // Для хранения вершин
#include "pico/stdlib.h"

// Тип примитива: треугольники или линии
enum PrimitiveType
{
    TRIANGLES,
    LINES
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    PrimitiveType primitiveType;

    Mesh(PrimitiveType type = TRIANGLES) : primitiveType(type) {}

    // Vertex adding
    void addVertex(const Vertex &vertex);

    // Index adding
    void addIndex(uint16_t index);

    // Mesh render
    void render() const;
};

#endif // MESH_H