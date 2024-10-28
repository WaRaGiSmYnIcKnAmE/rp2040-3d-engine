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
    Mesh cubeMesh = Mesh::createCube(10);

    // Создаем объект с позицией в пределах видимости камеры
    Object cubeObject;
    cubeObject.mesh = &cubeMesh;

    cubeObject.setPosition(Vector3(40.0f, 40.0f, 10.0f));
    cubeObject.setRotation(Vector3(0, 30.0f, 90.0f));
    cubeObject.setScale(Vector3(10.0f, 10.0f, 10.0f));

    // Инициализируем сцену и добавляем объект на сцену
    Scene scene;
    scene.addObject(&cubeObject);

    Matrix4 trMa = cubeObject.getTransformationMatrix(); // Matrix4::translation(0.4f);

    // ili9341_draw_text(Vector2(5, 5), 1, "{%f, %f, %f}", fix2float(cubeObject.rotation.x, FIXED_POINT_SHIFT), fix2float(cubeObject.rotation.y, FIXED_POINT_SHIFT), fix2float(cubeObject.rotation.z, FIXED_POINT_SHIFT));

    ili9341_draw_text(Vector2(5, 5), 1, "Matrix4:");
    ili9341_draw_text(Vector2(15, 15), 1, "{%f, %f, %f, %f}\n{%f, %f, %f, %f}\n{%f, %f, %f, %f}\n{%f, %f, %f, %f}",
                      fix2float(trMa.data[0][0], FIXED_POINT_SHIFT), fix2float(trMa.data[0][1], FIXED_POINT_SHIFT), fix2float(trMa.data[0][2], FIXED_POINT_SHIFT), fix2float(trMa.data[0][3], FIXED_POINT_SHIFT),
                      fix2float(trMa.data[1][0], FIXED_POINT_SHIFT), fix2float(trMa.data[1][1], FIXED_POINT_SHIFT), fix2float(trMa.data[1][2], FIXED_POINT_SHIFT), fix2float(trMa.data[1][3], FIXED_POINT_SHIFT),
                      fix2float(trMa.data[2][0], FIXED_POINT_SHIFT), fix2float(trMa.data[2][1], FIXED_POINT_SHIFT), fix2float(trMa.data[2][2], FIXED_POINT_SHIFT), fix2float(trMa.data[2][3], FIXED_POINT_SHIFT),
                      fix2float(trMa.data[3][0], FIXED_POINT_SHIFT), fix2float(trMa.data[3][1], FIXED_POINT_SHIFT), fix2float(trMa.data[3][2], FIXED_POINT_SHIFT), fix2float(trMa.data[3][3], FIXED_POINT_SHIFT));

    while (true)
    {
        Renderer::renderFrame(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, camera, scene);

        // Renderer::drawLine(frameBuffer, 320, 240, cubeObject.scale, cubeObject.position);

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