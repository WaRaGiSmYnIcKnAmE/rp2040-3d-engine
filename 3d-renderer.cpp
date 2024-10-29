#include "pico/stdlib.h"
#include "Engine.h"
#include "ILI9341.h"

uint16_t frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

Camera camera;
Scene scene;

void core1_render_task()
{
}

int main()
{
    stdio_init_all();
    multicore_launch_core1(core1_render_task);

    ili9341_init();

    Camera camera;

    // Создаем куб с размерами 80 единиц
    Mesh cubeMesh = Mesh::createCube(50);
    Mesh sphereMesh = Mesh::createSphere(30, 7);

    Object cubeObject;
    Object sphereObject;

    cubeObject.mesh = &cubeMesh;
    sphereObject.mesh = &sphereMesh;

    cubeObject.setPosition(Vector3(170.0f, 70.0f, 5.0f));
    cubeObject.setScale(Vector3(3.0f, 3.0f, 3.0f));

    sphereObject.setPosition(Vector3(70.0f, 70.0f, 5.0f));

    Scene scene;

    scene.addObject(&cubeObject);
    scene.addObject(&sphereObject);

    int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0;

    while (true)
    {
        float x = xRotation % 360;
        float y = yRotation % 360;
        float z = zRotation % 360;
        cubeObject.setRotation(Vector3(x, y, z));
        sphereObject.setRotation(Vector3(x, y, z));

        Renderer::renderFrame(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, camera, scene);

        xRotation += 2;
        yRotation += 3;
        zRotation += 1;

        ili9341_send_framebuffer(frameBuffer);

        // sleep_ms(16);
    }

    return 0;
}