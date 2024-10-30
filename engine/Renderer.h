#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Camera.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vertex.h"
#include "pico/stdlib.h"
#include <vector>

class Renderer
{
public:
    static void renderFrame(uint16_t *frameBuffer, int width, int height, Camera &camera, Scene &scene);

    static void fillTriangle(uint16_t *frameBuffer, Vector3 &v0, Vector3 &v1, Vector3 &v2, Color color);
    static void drawLine(uint16_t *frameBuffer, int width, int height, Vector3 v0, Vector3 v1);

private:
    static bool isInClipSpace(const Vector3 &vertex);
    static int32_t interpolate(int32_t y, Vector3 v0, Vector3 v1);
};

#endif // RENDERER_H
