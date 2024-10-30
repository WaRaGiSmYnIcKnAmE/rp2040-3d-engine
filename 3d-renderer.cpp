#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/clocks.h"
#include "Engine.h"
#include "ILI9341.h"

#define PI 3.14159265358979323846

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
    camera.setPosition(-10.0f, -10.0f, -20.0f);
    camera.setRotation(15.0f, 15.0f, -10.0f);

    Mesh plane = Mesh::createPlane(100, 100);

    Mesh cubeMesh = Mesh::createCube(120);
    Mesh cubeMesh2 = Mesh::createCube(80);
    Mesh cubeMesh3 = Mesh::createCube(20);

    Mesh sphereMesh = Mesh::createSphere(27, 10);

    Object planeObject;

    Object cubeObject;
    Object cubeObject2;
    Object cubeObject3;

    Object sphereObject;

    planeObject.mesh = &plane;

    cubeObject.mesh = &cubeMesh;
    cubeObject2.mesh = &cubeMesh2;
    cubeObject3.mesh = &cubeMesh3;

    sphereObject.mesh = &sphereMesh;

    planeObject.setPosition({0.0f, 0.0f, 0.0f});
    planeObject.setRotation({0.0f, 0.0f, 0.0f});

    cubeObject.setPosition(Vector3(120.0f, 160.0f, 30.0f));
    cubeObject2.setPosition(Vector3(120.0f, 160.0f, 15.0f));
    cubeObject3.setPosition(Vector3(120.0f, 160.0f, 15.0f));

    sphereObject.setPosition(Vector3(120.0f, 160.0f, 15.0f));

    Scene scene;

    // scene.addObject(&planeObject);

    // scene.addObject(&cubeObject);
    // scene.addObject(&cubeObject2);
    // scene.addObject(&cubeObject3);

    scene.addObject(&sphereObject);

    int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0;

    int timer;
    uint32_t delta = 1000 * 1000;

    unsigned int frame = 0;

    uint16_t fps;

    while (true)
    {
        frame++;

        float x = xRotation % 360;
        float y = yRotation % 360;
        float z = zRotation % 360;

        cubeObject.setRotation(Vector3(x, y, z));
        cubeObject2.setRotation(Vector3(-x + 90, -y + 90, -z + 90));
        cubeObject3.setRotation(Vector3(x, y, z));

        sphereObject.setRotation(Vector3(x, y, z));

        Renderer::renderFrame(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, camera, scene);
        Vector3 xV = Vector3(10.0f, 10.0f, 3.0f);
        Vector3 yV = Vector3(10.0f, 15.0f, 5.0f);
        Vector3 zV = Vector3(20.0f, 20.0f, 11.0f);

        xRotation += 3;
        yRotation += 3;
        zRotation += 3;

        if (get_absolute_time() - timer >= 1000 * 1000)
        {
            fps = frame;
            frame = 0;
            timer = get_absolute_time();
        }

        ili9341_draw_text(Vector2(15.0f, 15.0f), 1, "FPS: %d\nTimer: %d", frameBuffer, fps, get_absolute_time() / (1000 * 1000));

        ili9341_send_framebuffer(frameBuffer);
    }

    return 0;
}