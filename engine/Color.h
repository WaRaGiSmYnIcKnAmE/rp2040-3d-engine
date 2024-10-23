#ifndef COLOR_H
#define COLOR_H

struct Color
{
    float r, g, b, a;

    // Конструкторы
    Color() : r(0), g(0), b(0), a(0) {};
    Color(int red, int green, int blue, float alpha = 1.0f) : r(red), g(green), b(blue), a(alpha) {};

    // Предустановленные цвета
    static Color Red()
    {
        return Color(255, 0, 0.);
    }
    static Color Green()
    {
        return Color(0, 255, 0);
    }
    static Color Blue()
    {
        return Color(0, 0, 255);
    }
    static Color White()
    {
        return Color(255, 255, 255);
    }
    static Color Black()
    {
        return Color(0, 0, 0);
    }
};
#endif // COLOR_H