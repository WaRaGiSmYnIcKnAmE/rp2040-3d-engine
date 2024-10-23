#include <stdio.h>
#include "pico/stdlib.h"
// #include "Engine.h"
#include "engine/Vector.h"

int main()
{
    stdio_init_all();

    while (true)
    {
        Vector3 a = {1, 2, 3};
        Vector3 b = {3, 2, 1};

        Vector3 sum = addVectors(a, b);        // sum = {4, 4, 4}
        Vector3 difference = subVectors(a, b); // difference = {-2, 0, 2}
    }

    return 0;
}