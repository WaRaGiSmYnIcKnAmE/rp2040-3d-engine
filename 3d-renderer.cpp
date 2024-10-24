#include <stdio.h>
#include "pico/stdlib.h"
#include "Engine.h"

int main()
{
    stdio_init_all();

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
    }

    return 0;
}