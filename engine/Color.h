#ifndef COLOR_H
#define COLOR_H

// Fixed-point настройки
#define FIXED_POINT_SHIFT 16
#define TO_FIXED(x) ((int)((x) * (1 << FIXED_POINT_SHIFT)))  // float -> fixed-point
#define FROM_FIXED(x) ((float)(x) / (1 << FIXED_POINT_SHIFT))  // fixed-point -> float
#define MULT_FIXED(a, b) (((a) * (b)) >> FIXED_POINT_SHIFT)  // Умножение fixed-point

class Color
{
public:
    int r, g, b;
    int a;  // Альфа канал теперь тоже хранится как int в формате fixed-point

    // Конструктор по умолчанию (значения по умолчанию для черного цвета)
    Color() : r(0), g(0), b(0), a(TO_FIXED(1.0f)) {}

    // Конструктор с параметрами (все значения — целые числа, альфа — fixed-point)
    Color(int red, int green, int blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(TO_FIXED(alpha)) {}

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
};

#endif // COLOR_H