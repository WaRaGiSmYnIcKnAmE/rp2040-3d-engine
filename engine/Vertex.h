#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"
#include "Vector2.h"

struct Vertex
{
    Vector3 position;
    Vector2 texCoords;

    Vertex() : position(Vector3()), texCoords(Vector2()) {}

    Vertex(Vector3 verPosition, Vector2 texCoords)
        : position(verPosition), texCoords(texCoords) {}
};

#endif // VERTEX_H