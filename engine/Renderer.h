#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Camera.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vertex.h"
#include "pico/stdlib.h"
#include <vector>
#include "Defines.h"

class Renderer
{
public:
    static void renderFrame(uint16_t *frameBuffer, int width, int height, Camera &camera, Scene &scene);

    static void fillTriangle(uint16_t *frameBuffer, Vector3 &v0, Vector3 &v1, Vector3 &v2, Color color);
    static void drawLine(uint16_t *frameBuffer, int width, int height, Vector3 v0, Vector3 v1, Color color);

private:
    static bool isTriangleVisible(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);
    static void renderTriangleIfVisible(uint16_t *frameBuffer, Vector3 p0, Vector3 p1, Vector3 p2);
    static void fillTriangle(uint16_t *frameBuffer, Vector3 p0, Vector3 p1, Vector3 p2);
};

#endif // RENDERER_H
