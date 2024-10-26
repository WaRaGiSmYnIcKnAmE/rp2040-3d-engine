#include <stdio.h>
#include "pico/stdlib.h"
#include "Engine.h"
#include "ILI9341.h"

uint16_t frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

Camera camera;
Scene scene;

void core1_render_task()
{
    ili9341_init(); // Инициализация дисплея

    while (true)
    {
        // Инициализируем камеру в начале координат, направленную вперед
        Camera camera;

        // Создаем куб с размерами 80 единиц
        Mesh cubeMesh = Mesh::createCube(80);

        // Создаем объект с позицией в пределах видимости камеры
        Object cubeObject;
        cubeObject.mesh = &cubeMesh;

        cubeObject.setPosition(Vector3(0, 0, 50));
        cubeObject.setRotation(Vector3(30, 30, 30));

        // Инициализируем сцену и добавляем объект на сцену
        Scene scene;
        scene.addObject(&cubeObject);

        // Вызываем рендер и получаем отрендеренный кадр в frameBuffer
        Renderer::renderFrame(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, camera, scene);

        Renderer::drawLine(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, Vector3(TO_FIXED(10), TO_FIXED(40), TO_FIXED(1)), Vector3(TO_FIXED(10), TO_FIXED(100), TO_FIXED(1)));

        ili9341_send_framebuffer(frameBuffer);

        sleep_ms(10);
    }
}

int main()
{
    stdio_init_all();
    multicore_launch_core1(core1_render_task);

    while (true)
    {
        /*Vector3 a = {1, 2, 3};
        Vector3 b = {3, 2, 1};

        Vector3 C = addVectors(a, b);

        Vector3 D = multiplyVectorByScalar(a, 3);

        int scalar = scalarProduct(a, b);

        Matrix4 matrix1 = Matrix4::identity();
        Matrix4 matrix2 = Matrix4();

        Matrix4 result = matrix1 * matrix2;

        result.transpose();

        result.rotationY(15);

        Color cyan = Color::Cyan();

        cyan.mix(Color::White(), 3);*/
    }

    return 0;
}