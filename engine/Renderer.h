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
    static void renderFrame(uint8_t *depthBuffer, uint16_t *frameBuffer, int width, int height, Camera &camera, Scene &scene);
    static void drawLine(uint16_t *frameBuffer, int width, int height, Vector3 v0, Vector3 v1, Color color);

private:
    static void fillTriangle(uint8_t *depthBuffer, uint16_t *frameBuffer, Vector3 p0, Vector3 p1, Vector3 p2);

    static bool checkAndUpdateDepth(uint8_t *depthBuffer, int x, int y, int width, float depth);
    static uint8_t floatToDepth(float depth);
    static float calculateDepthAtPixel(float x, float y, const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);
};

#endif // RENDERER_H
