#include "pico/stdlib.h"
#include "hardware/clocks.h"
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
    // set_sys_clock_khz(200000, true);
    stdio_init_all();
    multicore_launch_core1(core1_render_task);

    ili9341_init();

    Camera camera;
    camera.setPosition(-10.0f, -10.0f, 0.0f);
    camera.setRotation(15.0f, 15.0f, 1.0f);

    // Создаем куб с размерами 80 единиц
    Mesh cubeMesh = Mesh::createCube(160);
    Mesh cubeMesh2 = Mesh::createCube(120);
    Mesh cubeMesh3 = Mesh::createCube(40);

    Mesh sphereMesh = Mesh::createSphere(40, 8);

    Object cubeObject;
    Object cubeObject2;
    Object cubeObject3;

    Object sphereObject;

    cubeObject.mesh = &cubeMesh;
    cubeObject2.mesh = &cubeMesh2;
    cubeObject3.mesh = &cubeMesh3;

    sphereObject.mesh = &sphereMesh;

    cubeObject.setPosition(Vector3(120.0f, 160.0f, 0.0f));
    cubeObject2.setPosition(Vector3(120.0f, 160.0f, 0.0f));
    cubeObject3.setPosition(Vector3(120.0f, 160.0f, 0.0f));

    sphereObject.setPosition(Vector3(120.0f, 160.0f, 0.0f));

    Scene scene;

    scene.addObject(&cubeObject);
    scene.addObject(&cubeObject2);
    // scene.addObject(&cubeObject3);

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
        cubeObject2.setRotation(Vector3(-x+90, -y+90, -z+90));
        cubeObject3.setRotation(Vector3(x, y, z));

        sphereObject.setRotation(Vector3(x, y, z));

        Renderer::renderFrame(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, camera, scene);

        xRotation += 3;
        yRotation += 3;
        zRotation += 3;

        ili9341_send_framebuffer(frameBuffer);

        // sleep_ms(16);
    }

    return 0;
}