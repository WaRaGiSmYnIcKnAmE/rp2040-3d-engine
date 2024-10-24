#include <stdio.h>
#include "pico/stdlib.h"
#include "Engine.h"
#include "ILI9341.h"

uint16_t framebuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

void core1_render_task()
{
    // Init display on second core
    ili9341_init();

    while (true)
    {
        // Render frame to buffer
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                framebuffer[y * SCREEN_WIDTH + x] = 0x07E0; // For example: green color
            }
        }

        // Send buffer to display
        ili9341_send_framebuffer(framebuffer);

        sleep_ms(16); // FPS lock ~60fps
    }
}

int main()
{
    stdio_init_all();
    multicore_launch_core1(core1_render_task);

    while (true)
    {
        Vector3 a = {1, 2, 3};
        Vector3 b = {3, 2, 1};

        Vector3 sum = addVectors(a, b);        // sum = {4, 4, 4}
        Vector3 difference = subVectors(a, b); // difference = {-2, 0, 2}

        Matrix4 translationMatrix = Matrix4::translation(3.0f, 4.0f, 5.0f);
        Matrix4 scaleMatrix = Matrix4::scale(2.0f, 2.0f, 2.0f);
        Matrix4 rotationMatrix = Matrix4::rotationX(3.14159f / 4);

        Vector3 point(1.0f, 2.0f, 3.0f);

        Vector3 transformedPoint = translationMatrix.multiply(point);

        Color purple = Color(160, 32, 240); // Purple color

        Mesh mesh;

        // Create vertex
        Vertex v1(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Color(255, 0, 0), UV());
        Vertex v2(Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Color(0, 255, 0), UV());
        Vertex v3(Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Color(0, 0, 255), UV());

        // Add vertex to mesh
        mesh.addVertex(v1);
        mesh.addVertex(v2);
        mesh.addVertex(v3);
    }

    return 0;
}