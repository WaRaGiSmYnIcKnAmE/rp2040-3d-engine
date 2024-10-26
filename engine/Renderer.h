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
    // Основная функция рендера
    static void renderFrame(uint16_t *frameBuffer, int width, int height, Camera &camera, Scene &scene);

    static void drawLine(uint16_t *frameBuffer, int width, int height, Vector3 v0, Vector3 v1);

private:
    // Помощники для проекции и вычислений видимости
    static Vector3 projectVertex(const Vector3 &position, int width, int height, const Matrix4 &viewMatrix, const Matrix4 &projectionMatrix);
    static bool isInClipSpace(const Vector3 &vertex);
};

#endif // RENDERER_H
