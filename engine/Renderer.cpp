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

    for (int i = 0; i < scene.objectCount; ++i)
    {
        Object *obj = scene.objects[i];

        Matrix4 modelMatrix = obj->getTransformationMatrix();
        Matrix4 viewMatrix = obj->getViewMatrix({4.0f, 4.0f, 2.0f}, {0.0f, 0.0f, 10.0f}, {0.0f, 10.0f, 0.0f});
        Matrix4 projectionMatrix = obj->getProjectionMatrix(90.0f, width / height, 0.1f, 50.0f);

        Matrix4 MVPMatrix = /*projectionMatrix * viewMatrix * */ modelMatrix;

        for (size_t j = 0; j < obj->mesh->indices.size(); j += 3)
        {
            Vertex v0 = obj->mesh->vertices[obj->mesh->indices[j]];
            Vertex v1 = obj->mesh->vertices[obj->mesh->indices[j + 1]];
            Vertex v2 = obj->mesh->vertices[obj->mesh->indices[j + 2]];

            Vector3 vector0 = MVPMatrix * v0.position;
            Vector3 vector1 = MVPMatrix * v1.position;
            Vector3 vector2 = MVPMatrix * v2.position;

            drawLine(frameBuffer, width, height, vector0, vector1);
            drawLine(frameBuffer, width, height, vector1, vector2);
            drawLine(frameBuffer, width, height, vector2, vector0);
        }
    }
}

// Алгоритм Брезенхэма для рисования линии
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
            frameBuffer[y0 * height + x0] = COLOR_OBJECT;
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