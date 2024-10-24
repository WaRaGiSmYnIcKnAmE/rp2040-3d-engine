#ifndef VERTEX_H
#define VERTEX_H

#include "Vector.h"
#include "Color.h"

// Struct for texture vertex
struct UV
{
    float u, v;
    UV() : u(0.0f), v(0.0f) {}
    UV(float u, float v) : u(u), v(v) {}
};

// Optimize vector struct
struct Vertex
{
    Vector3 position; // Vertex position
    Vector3 normal;   // Normalize of Vertex (for light)
    Color color;      // Vertex color
    UV texCoords;     // Texture coordinates

    Vertex() : position(), normal(), color(), texCoords() {}

    Vertex(const Vector3 &pos, const Vector3 &norm, const Color &col, const UV &tex)
        : position(pos), normal(norm), color(col), texCoords(tex) {}
};

#endif // VERTEX_H
