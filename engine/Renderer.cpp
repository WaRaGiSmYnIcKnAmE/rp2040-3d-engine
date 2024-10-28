#include "Renderer.h"
#include "pico/stdlib.h"
#include "pico/float.h"

// Значение цвета для фона и объектов
#define COLOR_BACKGROUND 0x0000 // Черный фон
#define COLOR_OBJECT 0xFFFF     // Белый объект

#define FOCAL_LENGTH 255

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

        Matrix4 modelMatrix = obj->getTransformationMatrix();

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

            // Простая отрисовка линии между вершинами треугольника

            drawLine(frameBuffer, width, height, v0.position, v1.position);
            drawLine(frameBuffer, width, height, v1.position, v2.position);
            drawLine(frameBuffer, width, height, v2.position, v0.position);

            /*drawLine(frameBuffer, width, height, p0, p1);
            drawLine(frameBuffer, width, height, p1, p2);
            drawLine(frameBuffer, width, height, p2, p0);*/
        }
    }
}

// Преобразование вершины в пространство экрана
Vector3 Renderer::projectVertex(const Vector3 &position, int width, int height, const Matrix4 &viewMatrix, const Matrix4 &projectionMatrix)
{
    // Переводим вершину в пространство камеры
    Vector3 transformed = viewMatrix.multiply(position);

    // Проверяем значение Z, чтобы избежать деления на ноль
    if (transformed.z <= 0)
        transformed.z = 1; // Исправляем Z для корректного проецирования

    // Применяем перспективную проекцию
    transformed = projectionMatrix.multiply(transformed);

    // Нормализация координат после проекции
    int screenX = (width / 2) + FROM_FIXED((transformed.x * FOCAL_LENGTH) / transformed.z) * (width / 2);
    int screenY = (height / 2) - FROM_FIXED((transformed.y * FOCAL_LENGTH) / transformed.z) * (height / 2);

    return Vector3(screenX, screenY, transformed.z);
}

// Алгоритм Брезенхэма для рисования линии
void Renderer::drawLine(uint16_t *frameBuffer, int width, int height, Vector3 v0, Vector3 v1)
{
    int x0 = FROM_FIXED(v0.x);
    int y0 = FROM_FIXED(v0.y);
    int x1 = FROM_FIXED(v1.x);
    int y1 = FROM_FIXED(v1.y);

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
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
