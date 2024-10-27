#include "pico/stdlib.h"
#include "Engine.h"
#include "ILI9341.h"

uint16_t frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

Camera camera;
Scene scene;

uint16_t frame = 0;

void core1_render_task()
{
    ili9341_init(); // Инициализация дисплея

    // Инициализируем камеру в начале координат, направленную вперед
    Camera camera;

    // Создаем куб с размерами 80 единиц
    Mesh cubeMesh = Mesh::createCube(30);

    // Создаем объект с позицией в пределах видимости камеры
    Object cubeObject;
    cubeObject.mesh = &cubeMesh;

    cubeObject.setPosition(Vector3(40, 40, 10));
    cubeObject.setRotation(Vector3(30, 30, 30));

    // Инициализируем сцену и добавляем объект на сцену
    Scene scene;
    scene.addObject(&cubeObject);

    Matrix4 trMa = cubeObject.getTransformationMatrix();

    ili9341_draw_text(Vector2(5, 5), 2, "{%d, %d, %d, %d}\n{%d, %d, %d, %d}\n{%d, %d, %d, %d}\n{%d, %d, %d, %d}",
                      trMa.data[0][0], trMa.data[0][1], trMa.data[0][2], trMa.data[0][3],
                      trMa.data[1][0], trMa.data[1][1], trMa.data[1][2], trMa.data[1][3],
                      trMa.data[2][0], trMa.data[2][1], trMa.data[2][2], trMa.data[2][3],
                      trMa.data[3][0], trMa.data[3][1], trMa.data[3][2], trMa.data[3][3]);

    while (true)
    {

        // Вызываем рендер и получаем отрендеренный кадр в frameBuffer
        Renderer::renderFrame(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, camera, scene);

        // ili9341_send_framebuffer(frameBuffer);

        frame += 1;

        sleep_ms(10);
    }
}

int main()
{
    stdio_init_all();
    multicore_launch_core1(core1_render_task);

    while (true)
    {
        sleep_ms(1000);
        uint16_t fps = 1000 / frame;
        frame = 0;

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