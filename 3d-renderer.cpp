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

    // Создаем объект с позицией в пределах видимости камеры
    Object cubeObject;
    cubeObject.mesh = &cubeMesh;

    cubeObject.setPosition(Vector3(40.0f, 40.0f, 10.0f));
    cubeObject.setRotation(Vector3(30.0f, 0.0f, 45.0f));
    //  cubeObject.setScale(Vector3(10.0f, 10.0f, 10.0f));

    // Инициализируем сцену и добавляем объект на сцену
    Scene scene;
    scene.addObject(&cubeObject);

    Matrix4 trMa = cubeObject.getTransformationMatrix();

    // Matrix4 trMa = Matrix4::rotationY(float2fix(30.0f, FIXED_POINT_SHIFT));

    // ili9341_draw_text(Vector2(60, 10), 1, "Position: { %f, %f, %f }", fix2float(cubeObject.position.x, FIXED_POINT_SHIFT), fix2float(cubeObject.position.y, FIXED_POINT_SHIFT), fix2float(cubeObject.position.z, FIXED_POINT_SHIFT));
    // ili9341_draw_text(Vector2(80, 10), 1, "Rotation: { %f, %f, %f }", fix2float(cubeObject.rotation.x, FIXED_POINT_SHIFT), fix2float(cubeObject.rotation.y, FIXED_POINT_SHIFT), fix2float(cubeObject.rotation.z, FIXED_POINT_SHIFT));
    // ili9341_draw_text(Vector2(100, 10), 1, "Scale: { %f, %f, %f }", fix2float(cubeObject.scale.x, FIXED_POINT_SHIFT), fix2float(cubeObject.scale.y, FIXED_POINT_SHIFT), fix2float(cubeObject.scale.z, FIXED_POINT_SHIFT));

    Renderer::renderFrame(frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, camera, scene);

    // Renderer::drawLine(frameBuffer, 320, 240, Vector3(10.0f, 10.0f, 1.0f), Vector3(30.0f, 50.0f, 15.0f));

    ili9341_send_framebuffer(frameBuffer);

    // ili9341_draw_text({45, 45}, 1, "(%f, %f, %f)\n(%f, %f, %f)\n(%f, %f, %f)", cubeMesh.vertices[0].position.x, cubeMesh.vertices[0].position.y, cubeMesh.vertices[0].position.z, cubeMesh.vertices[1].position.x, cubeMesh.vertices[1].position.y, cubeMesh.vertices[1].position.z, cubeMesh.vertices[2].position.x, cubeMesh.vertices[3].position.y, cubeMesh.vertices[3].position.z);

    /*ili9341_draw_text(Vector2(10, 10), 1, "Matrix transformation of cube object:\n{ %f, %f, %f, %f }\n{ %f, %f, %f, %f }\n{ %f, %f, %f, %f }\n{ %f, %f, %f, %f }",
                      fix2float(trMa.data[0][0], FIXED_POINT_SHIFT), fix2float(trMa.data[0][1], FIXED_POINT_SHIFT), fix2float(trMa.data[0][2], FIXED_POINT_SHIFT), fix2float(trMa.data[0][3], FIXED_POINT_SHIFT),
                      fix2float(trMa.data[1][0], FIXED_POINT_SHIFT), fix2float(trMa.data[1][1], FIXED_POINT_SHIFT), fix2float(trMa.data[1][2], FIXED_POINT_SHIFT), fix2float(trMa.data[1][3], FIXED_POINT_SHIFT),
                      fix2float(trMa.data[2][0], FIXED_POINT_SHIFT), fix2float(trMa.data[2][1], FIXED_POINT_SHIFT), fix2float(trMa.data[2][2], FIXED_POINT_SHIFT), fix2float(trMa.data[2][3], FIXED_POINT_SHIFT),
                      fix2float(trMa.data[3][0], FIXED_POINT_SHIFT), fix2float(trMa.data[3][1], FIXED_POINT_SHIFT), fix2float(trMa.data[3][2], FIXED_POINT_SHIFT), fix2float(trMa.data[3][3], FIXED_POINT_SHIFT));*/
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