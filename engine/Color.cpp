#include "Color.h"

Color Color::mix(const Color &other, int factor) const
{
    return Color(
        r * (255 - factor) + other.r * factor,
        g * (255 - factor) + other.g * factor,
        b * (255 - factor) + other.b * factor,
        a * (255 - factor) + other.a * factor);
}

void Color::clamp()
{
    if (r < 0)
        r = 0;
    if (r > 255)
        r = 255;
    if (g < 0)
        g = 0;
    if (g > 255)
        g = 255;
    if (b < 0)
        b = 0;
    if (b > 255)
        b = 255;
    if (a < 0)
        a = 0;
    if (a > 255)
        a = 255;
}

Color Color::Red()
{
    return Color(255, 0, 0);
}

Color Color::Green()
{
    return Color(0, 255, 0);
}

Color Color::Blue()
{
    return Color(0, 0, 255);
}

Color Color::White()
{
    return Color(255, 255, 255);
}

Color Color::Black()
{
    return Color(0, 0, 0);
}