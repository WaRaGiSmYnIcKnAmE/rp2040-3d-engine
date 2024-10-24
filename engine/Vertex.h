#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"
#include "Vector2.h"

struct Vertex {
    Vector3 position;  // Позиция вершины в 3D пространстве
    Vector2 texCoords; // Текстурные координаты (опционально, если нужен текстуринг)

    Vertex() : position(Vector3()), texCoords(Vector2()) {}

    Vertex(Vector3 position, Vector2 texCoords)
        : position(position), texCoords(texCoords) {}
};

#endif // VERTEX_H