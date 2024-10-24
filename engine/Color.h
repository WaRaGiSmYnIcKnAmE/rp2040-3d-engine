#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    int r, g, b;
    float a;

    Color() : r(0), g(0), b(0), a(0) {};
    Color(int red, int green, int blue, float alpha = 1.0f) : r(red), g(green), b(blue), a(alpha) {};

    static Color Red();
    static Color Green();
    static Color Blue();
    static Color White();
    static Color Black();

    // Function for mixing colors
    Color mix(const Color &other, int factor) const;

    // Function for color alignment for values [0, 255] and alfa [0, 1]
    void clamp();
};
#endif // COLOR_H