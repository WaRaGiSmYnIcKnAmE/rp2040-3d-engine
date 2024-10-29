#ifndef COLOR_H
#define COLOR_H

#define FIXED_POINT_SHIFT 16

class Color
{
public:
    int r, g, b;
    int a; // Альфа канал теперь тоже хранится как int в формате fixed-point

    // Конструктор по умолчанию (значения по умолчанию для черного цвета)
    Color() : r(0), g(0), b(0), a(float2fix(1.0f, FIXED_POINT_SHIFT)) {}

    // Конструктор с параметрами (все значения — целые числа, альфа — fixed-point)
    Color(int red, int green, int blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(float2fix(alpha, FIXED_POINT_SHIFT)) {}

    // Конструкторы для стандартных цветов
    static Color White();
    static Color Black();

    static Color Red();
    static Color Green();
    static Color Blue();

    static Color Cyan();
    static Color Yellow();
    static Color Purple();

    // Функция смешивания цветов (factor от 0 до 255)
    Color mix(const Color &other, int factor) const;

    // Функция для корректировки значений цвета в диапазоне [0, 255] и альфа [0, 1]
    void clamp();

    static uint16_t color565(uint8_t red, uint8_t green, uint8_t blue);
};

#endif // COLOR_H
