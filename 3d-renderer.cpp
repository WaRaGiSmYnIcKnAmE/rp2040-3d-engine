#include "pico/stdlib.h"
#include "Engine.h"
#include "ILI9341.h"

uint16_t frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

Camera camera;
Scene scene;

void core1_render_task()
{
    ili9341_init(); // Инициализация дисплея

    // Инициализируем камеру в начале координат, направленную вперед
    Camera camera;

    // Создаем куб с размерами 80 единиц
    Mesh cubeMesh = Mesh::createCube(50);

    // ili9341_draw_text({60, 10}, 1, "(%f, %f, %f)\n(%f, %f, %f)\n(%f, %f, %f)", fix2float(cubeMesh.vertices[0].position.x, FIXED_POINT_SHIFT), fix2float(cubeMesh.vertices[0].position.y, FIXED_POINT_SHIFT), fix2float(cubeMesh.vertices[0].position.z, FIXED_POINT_SHIFT), fix2float(cubeMesh.vertices[1].position.x, FIXED_POINT_SHIFT), fix2float(cubeMesh.vertices[1].position.y, FIXED_POINT_SHIFT), fix2float(cubeMesh.vertices[1].position.z, FIXED_POINT_SHIFT), fix2float(cubeMesh.vertices[2].position.x, FIXED_POINT_SHIFT), fix2float(cubeMesh.vertices[3].position.y, FIXED_POINT_SHIFT), fix2float(cubeMesh.vertices[3].position.z, FIXED_POINT_SHIFT));

    // Создаем объект с позицией в пределах видимости камеры
    Object cubeObject;
    cubeObject.mesh = &cubeMesh;

    cubeObject.setPosition(Vector3(120.0f, 150.0f, 5.0f));
    cubeObject.setScale(Vector3(3.0f, 3.0f, 3.0f));

    // Инициализируем сцену и добавляем объект на сцену
    Scene scene;
    scene.addObject(&cubeObject);

    int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0;

    while (true)
    {
        float x = xRotation % 360;
        float y = yRotation % 360;
        float z = zRotation % 360;
        cubeObject.setRotation(Vector3(x, y, z));

        Renderer::renderFrame(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, camera, scene);

        ili9341_send_framebuffer(frameBuffer);

        sleep_ms(36);

        xRotation += 2;
        yRotation += 3;
        zRotation += 1;
    }
}

int main()
{
    stdio_init_all();
    multicore_launch_core1(core1_render_task);

    while (true)
    {
    }

    return 0;
}