#include "Renderer.h"
#include "pico/stdlib.h"
#include "pico/float.h"

#include "../ILI9341.h"

#define COLOR_BACKGROUND 0x0000
#define COLOR_OBJECT 0xFFFF

#define FOCAL_LENGTH 255

void Renderer::renderFrame(uint8_t *depthBuffer, uint16_t *frameBuffer, int width, int height, Camera &camera, Scene &scene)
{
    for (int i = 0; i < width * height; ++i)
    {
        frameBuffer[i] = COLOR_BACKGROUND;
        depthBuffer[i] = 0xFF;
    }

    float yaw = camera.rotation.y;
    float pitch = camera.rotation.x;
    float roll = camera.rotation.z;

    Vector3 targerVector = camera.position + Vector3(cosf(pitch) * sinf(yaw), sinf(pitch), cosf(pitch) * cos(yaw));

    Matrix4 viewMatrix = Matrix4::getViewMatrix(camera.position, targerVector, {0.0f, 1.0f, 0.0f});

    float aspetRatio = int2float(SCREEN_WIDTH) / int2float(SCREEN_HEIGHT);

    Matrix4 projectionMatrix = Matrix4::getProjectionMatrix(60.0f, aspetRatio, 0.01f, 100.0f);

    for (int i = 0; i < scene.objectCount; ++i)
    {
        Object *obj = scene.objects[i];

        Matrix4 modelMatrix = obj->getTransformationMatrix();

        Matrix4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

        for (size_t j = 0; j < obj->mesh->indices.size(); j += 3)
        {
            Vertex v0 = obj->mesh->vertices[obj->mesh->indices[j]];
            Vertex v1 = obj->mesh->vertices[obj->mesh->indices[j + 1]];
            Vertex v2 = obj->mesh->vertices[obj->mesh->indices[j + 2]];

            Vector3 vector0 = MVPMatrix * v0.position;
            Vector3 vector1 = MVPMatrix * v1.position;
            Vector3 vector2 = MVPMatrix * v2.position;

            // fillTriangle(depthBuffer, frameBuffer, vector0, vector1, vector2);

            drawLine(frameBuffer, height, width, vector0, vector1, Color(255, 0, 0));
            drawLine(frameBuffer, height, width, vector1, vector2, Color(255, 0, 0));
            drawLine(frameBuffer, height, width, vector2, vector0, Color(255, 0, 0));
        }
    }
}

void Renderer::fillTriangle(uint8_t *depthBuffer, uint16_t *frameBuffer, Vector3 p0, Vector3 p1, Vector3 p2)
{
    float x0 = fix2float(p0.x, FIXED_POINT_SHIFT);
    float y0 = fix2float(p0.y, FIXED_POINT_SHIFT);
    float x1 = fix2float(p1.x, FIXED_POINT_SHIFT);
    float y1 = fix2float(p1.y, FIXED_POINT_SHIFT);
    float x2 = fix2float(p2.x, FIXED_POINT_SHIFT);
    float y2 = fix2float(p2.y, FIXED_POINT_SHIFT);

    if (y0 > y1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    if (y0 > y2)
    {
        std::swap(x0, x2);
        std::swap(y0, y2);
    }
    if (y1 > y2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    for (float y = y0; y <= y2; y++)
    {
        float xStart, xEnd;

        if (y < y1)
        {
            xStart = x0 + (x1 - x0) * ((y - y0) / (y1 - y0));
            xEnd = x0 + (x2 - x0) * ((y - y0) / (y2 - y0));
        }
        else
        {
            xStart = x1 + (x2 - x1) * ((y - y1) / (y2 - y1));
            xEnd = x0 + (x2 - x0) * ((y - y0) / (y2 - y0));
        }

        if (xStart > xEnd)
            std::swap(xStart, xEnd);

        drawLine(frameBuffer, SCREEN_HEIGHT, SCREEN_WIDTH, Vector3(xStart, y, 0.0f), Vector3(xEnd, y, 0.0f), Color(80, 80, 80));
    }
}

// The Bresenham algorithm for drawing a line
void Renderer::drawLine(uint16_t *frameBuffer, int width, int height, Vector3 v0, Vector3 v1, Color color)
{
    int x0 = fix2float(v0.x, FIXED_POINT_SHIFT);
    int y0 = fix2float(v0.y, FIXED_POINT_SHIFT);
    int x1 = fix2float(v1.x, FIXED_POINT_SHIFT);
    int y1 = fix2float(v1.y, FIXED_POINT_SHIFT);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int step_x = (x0 < x1) ? 1 : -1;
    int step_y = (y0 < y1) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (true)
    {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
        {
            frameBuffer[y0 * width + x0] = Color::color565(color.r, color.g, color.b);
        }

        if (x0 == x1 && y0 == y1)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += step_x;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += step_y;
        }
    }
}