#include "pico/stdlib.h"
#include "pico/float.h"
#include "Color.h"

Color Color::mix(const Color &other, int factor) const
{
    int invFactor = 255 - factor;
    return Color(
        (r * invFactor + other.r * factor) / 255,
        (g * invFactor + other.g * factor) / 255,
        (b * invFactor + other.b * factor) / 255,
        (fix2float(a * invFactor + other.a * factor, FIXED_POINT_SHIFT) / 255));
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
        a = float2fix(0.0f, FIXED_POINT_SHIFT);
    if (a > 1.0f)
        a = float2fix(1.0f, FIXED_POINT_SHIFT);
}

Color Color::White()
{
    return Color(255, 255, 255);
}

Color Color::Black()
{
    return Color(0, 0, 0);
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

Color Color::Cyan()
{
    return Color(0, 255, 255);
}
Color Color::Yellow()
{
    return Color(255, 255, 0);
}

Color Color::Purple()
{
    return Color(128, 0, 128);
}

uint16_t Color::color565(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((red & 0xF8) << 8) | ((blue & 0xFC) << 3) | (green >> 3);
}