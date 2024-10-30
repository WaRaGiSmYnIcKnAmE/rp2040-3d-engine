#include "Renderer.h"
#include "pico/stdlib.h"
#include "pico/float.h"

#include "../ILI9341.h"

#define COLOR_BACKGROUND 0x0000
#define COLOR_OBJECT 0xFFFF

#define FOCAL_LENGTH 255

void Renderer::renderFrame(uint16_t *frameBuffer, int width, int height, Camera &camera, Scene &scene)
{
    for (int i = 0; i < width * height; ++i)
    {
        frameBuffer[i] = COLOR_BACKGROUND;
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

            // fillTriangle(frameBuffer, vector0, vector1, vector2, Color(255, 255, 255));

            drawLine(frameBuffer, height, width, vector0, vector1);
            drawLine(frameBuffer, height, width, vector1, vector2);
            drawLine(frameBuffer, height, width, vector2, vector0);
        }
    }
}

void Renderer::fillTriangle(uint16_t *frameBuffer, Vector3 &v0, Vector3 &v1, Vector3 &v2, Color color)
{
    // Сортируем вершины по y-координате
    if (v0.y > v1.y)
        std::swap(v0, v1);
    if (v1.y > v2.y)
        std::swap(v1, v2);
    if (v0.y > v1.y)
        std::swap(v0, v1);

    // Нижний треугольник
    if (v1.y != v0.y)
    {
        for (int32_t y = v0.y; y <= v1.y; y++)
        {
            int xStart = interpolate(y, v0, v1);
            int xEnd = interpolate(y, v0, v2);
            if (xStart > xEnd)
                std::swap(xStart, xEnd);

            // Заполняем строку между xStart и xEnd
            for (int32_t x = xStart; x <= xEnd; x++)
            {
                int yScreen = fix2float(y, FIXED_POINT_SHIFT); // Преобразуем для индексации буфера
                int xScreen = fix2float(x, FIXED_POINT_SHIFT);
                frameBuffer[yScreen * SCREEN_WIDTH + xScreen] = Color::color565(color.r, color.g, color.b);
            }
        }
    }

    // Верхний треугольник
    if (v2.y != v1.y)
    {
        for (int32_t y = v1.y; y <= v2.y; y++)
        {
            int xStart = interpolate(y, v1, v2);
            int xEnd = interpolate(y, v0, v2);
            if (xStart > xEnd)
                std::swap(xStart, xEnd);

            for (int32_t x = xStart; x <= xEnd; x++)
            {
                int yScreen = fix2float(y, FIXED_POINT_SHIFT);
                int xScreen = fix2float(x, FIXED_POINT_SHIFT);
                frameBuffer[yScreen * SCREEN_WIDTH + xScreen] = Color::color565(color.r, color.g, color.b);
            }
        }
    }
}

int32_t Renderer::interpolate(int32_t y, Vector3 v0, Vector3 v1)
{
    if (v1.y == v0.y)
    {
        return v0.x;
    }

    float yFloat = fix2float(y, FIXED_POINT_SHIFT);
    float x0Float = fix2float(v0.x, FIXED_POINT_SHIFT);
    float x1Float = fix2float(v1.x, FIXED_POINT_SHIFT);
    float y0Float = fix2float(v0.y, FIXED_POINT_SHIFT);
    float y1Float = fix2float(v1.y, FIXED_POINT_SHIFT);

    float resultFloat = x0Float + (x1Float - x0Float) * (yFloat - y0Float) / (y1Float - y0Float);
    return float2fix(resultFloat, FIXED_POINT_SHIFT);
}

// The Bresenham algorithm for drawing a line
void Renderer::drawLine(uint16_t *frameBuffer, int width, int height, Vector3 v0, Vector3 v1)
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
            frameBuffer[y0 * width + x0] = Color::color565(0, 255, 0);
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