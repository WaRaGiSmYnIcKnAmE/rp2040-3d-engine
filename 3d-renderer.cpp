#include <stdio.h>
#include "pico/stdlib.h"
#include "Engine.h"

int main()
{
    stdio_init_all();

    while (true)
    {
        Vector3 a = Vector3(2, 3, 1);

        Vector3 b = Vector3(2, 3, 1);

        Vector3 sum = addVectors(a, b);
        Vector3 subtract = subtractVectors(a, b);
        Vector3 multiply = multiplyVectors(a, b);
        float scalar = scalarVectors(a, b);
        Vector3 normalA = normalizeVector(a);
        Vector3 normalB = normalizeVector(b);
    }

    return 0;
}