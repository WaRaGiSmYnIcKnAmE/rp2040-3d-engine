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

        Vector3 C = addVectors(a, b);

        Vector3 D = multiplyVectorByScalar(a, 3);

        int scalar = scalarProduct(a, b);

        Matrix4 matrix = Matrix4::identity();

        matrix.transpose();

        matrix.rotationY(15);

        Color cyan = Color::Cyan();

        cyan.mix(Color::White(), 3);
    }

    return 0;
}