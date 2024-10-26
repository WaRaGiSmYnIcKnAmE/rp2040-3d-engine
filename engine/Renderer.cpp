#include "Renderer.h"
#include "pico/stdlib.h"
#include "pico/float.h"

// Значение цвета для фона и объектов
#define COLOR_BACKGROUND 0x0000 // Черный фон
#define COLOR_OBJECT 0xFFFF     // Белый объект

// Основная функция рендера
void Renderer::renderFrame(uint16_t *frameBuffer, int width, int height, Camera &camera, Scene &scene)
{
    // Очистка кадра
    for (int i = 0; i < width * height; ++i)
    {
        frameBuffer[i] = COLOR_BACKGROUND;
    }

    // Матрицы для преобразования объекта в пространство камеры и затем в пространство экрана
    Matrix4 viewMatrix = Matrix4::rotationX(camera.rotation.x) * Matrix4::rotationY(camera.rotation.y) * Matrix4::rotationZ(camera.rotation.z);
    viewMatrix = viewMatrix * Matrix4::translation(-camera.position.x, -camera.position.y, -camera.position.z);
    Matrix4 projectionMatrix = Matrix4::perspective(TO_FIXED(60), TO_FIXED(width) / height, TO_FIXED(1), TO_FIXED(100));

    // Проход по объектам сцены и рендер только видимых
    for (int i = 0; i < scene.objectCount; ++i)
    {
        Object *obj = scene.objects[i];
        /*if (!obj->visible)
            continue;*/

        Matrix4 modelMatrix = Matrix4::translation(obj->position.x, obj->position.y, obj->position.z) * Matrix4::rotationX(obj->rotation.x) * Matrix4::rotationY(obj->rotation.y) * Matrix4::rotationZ(obj->rotation.z) * Matrix4::scale(obj->scale.x, obj->scale.y, obj->scale.z);

        // Проход по треугольникам меша
        for (size_t j = 0; j < obj->mesh->indices.size(); j += 3)
        {
            const Vertex &v0 = obj->mesh->vertices[obj->mesh->indices[j]];
            const Vertex &v1 = obj->mesh->vertices[obj->mesh->indices[j + 1]];
            const Vertex &v2 = obj->mesh->vertices[obj->mesh->indices[j + 2]];

            // Преобразование в пространство камеры и проекция на экран
            Vector3 p0 = projectVertex(v0.position, width, height, viewMatrix, projectionMatrix);
            Vector3 p1 = projectVertex(v1.position, width, height, viewMatrix, projectionMatrix);
            Vector3 p2 = projectVertex(v2.position, width, height, viewMatrix, projectionMatrix);

            // Проверка на видимость в пределах экрана
            /*if (isInClipSpace(p0) && isInClipSpace(p1) && isInClipSpace(p2))
            {*/
            // Простая отрисовка линии между вершинами треугольника
            drawLine(frameBuffer, width, height, p0, p1);
            drawLine(frameBuffer, width, height, p1, p2);
            drawLine(frameBuffer, width, height, p2, p0);
            //}
        }
    }
}

// Преобразование вершины в пространство экрана
Vector3 Renderer::projectVertex(const Vector3 &position, int width, int height, const Matrix4 &viewMatrix, const Matrix4 &projectionMatrix)
{
    Vector3 transformed = viewMatrix.multiply(position);
    transformed = projectionMatrix.multiply(transformed);

    // Преобразование координат в экранные
    int screenX = (width / 2) + (FROM_FIXED(transformed.x) * width / 2);
    int screenY = (height / 2) - (FROM_FIXED(transformed.y) * height / 2);
    return Vector3(screenX, screenY, transformed.z);
}

// Проверка, находится ли вершина в пределах видимого пространства
bool Renderer::isInClipSpace(const Vector3 &vertex)
{
    return vertex.x >= -TO_FIXED(1) && vertex.x <= TO_FIXED(1) &&
           vertex.y >= -TO_FIXED(1) && vertex.y <= TO_FIXED(1) &&
           vertex.z >= 0 && vertex.z <= TO_FIXED(1);
}

// Алгоритм Брезенхэма для рисования линии
void Renderer::drawLine(uint16_t *frameBuffer, int width, int height, Vector3 v0, Vector3 v1)
{
    int x0 = FROM_FIXED(v0.x), y0 = FROM_FIXED(v0.y);
    int x1 = FROM_FIXED(v1.x), y1 = FROM_FIXED(v1.y);

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true)
    {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
        {
            frameBuffer[y0 * width + x0] = COLOR_OBJECT;
        }
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
