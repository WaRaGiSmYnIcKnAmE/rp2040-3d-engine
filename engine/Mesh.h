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

    void addVertex(const Vertex &vertex);
    void addIndex(int index);
    Vertex getVertex(int index) const;

    void applyTransformation(const Matrix4 &matrix);

    int getVertexCount() const;
    int getIndexCount() const;

    Color getColor() const;

    static Mesh createPlane(float width, float depth);
    static Mesh createCube(int size);
    static Mesh createSphere(float radius, int sectors);
    static Mesh createPyramid(float baseLength, float height);
    static Mesh createCone(float radius, float height, int sectors);

    std::vector<Vertex> vertices;
    std::vector<int> indices;
    Color color;
};

#endif // MESH_H
