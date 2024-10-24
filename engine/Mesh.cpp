#include "Mesh.h"
#include "pico/stdlib.h"

// Добавление вершины в меш
void Mesh::addVertex(const Vertex &vertex)
{
    vertices.push_back(vertex);
}

// Добавление индекса в меш
void Mesh::addIndex(uint16_t index)
{
    indices.push_back(index);
}