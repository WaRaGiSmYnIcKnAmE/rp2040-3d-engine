#ifndef FIXED_POINT_H
#define FIXED_POINT_H

class FixedPoint
{
private:
    static constexpr int SHIFT = 16;
    int32_t value; // Основное значение хранится в формате int32_t

public:
    // Конструкторы
    FixedPoint() : value(0) {}

    // Конструктор из int
    FixedPoint(int32_t integer) : value(integer << SHIFT) {}

    // Конструктор из float
    FixedPoint(float number) : value(static_cast<int32_t>(number * (1 << SHIFT))) {}

    // Конструктор из int8_t, int16_t и их unsigned версий
    FixedPoint(int8_t integer) : value(static_cast<int32_t>(integer) << SHIFT) {}
    FixedPoint(uint8_t integer) : value(static_cast<int32_t>(integer) << SHIFT) {}
    FixedPoint(int16_t integer) : value(static_cast<int32_t>(integer) << SHIFT) {}
    FixedPoint(uint16_t integer) : value(static_cast<int32_t>(integer) << SHIFT) {}

    // Операторы приведения к int и float для обратного преобразования
    explicit operator int32_t() const { return value >> SHIFT; }
    explicit operator float() const { return static_cast<float>(value) / (1 << SHIFT); }

    // Оператор сложения
    FixedPoint operator+(const FixedPoint &other) const
    {
        return FixedPoint::fromRaw(value + other.value);
    }

    // Оператор вычитания
    FixedPoint operator-(const FixedPoint &other) const
    {
        return FixedPoint::fromRaw(value - other.value);
    }

    // Оператор умножения
    FixedPoint operator*(const FixedPoint &other) const
    {
        return FixedPoint::fromRaw(static_cast<int32_t>((static_cast<int64_t>(value) * other.value) >> SHIFT));
    }

    // Оператор деления
    FixedPoint operator/(const FixedPoint &other) const
    {
        return FixedPoint::fromRaw(static_cast<int32_t>((static_cast<int64_t>(value) << SHIFT) / other.value));
    }

    // Операторы сравнения
    bool operator==(const FixedPoint &other) const { return value == other.value; }
    bool operator!=(const FixedPoint &other) const { return value != other.value; }
    bool operator<(const FixedPoint &other) const { return value < other.value; }
    bool operator<=(const FixedPoint &other) const { return value <= other.value; }
    bool operator>(const FixedPoint &other) const { return value > other.value; }
    bool operator>=(const FixedPoint &other) const { return value >= other.value; }

    // Получение значения с фиксированной точкой в сыром виде
    int32_t getRawValue() const { return value; }

    // Создание FixedPoint из сырого значения
    static FixedPoint fromRaw(int32_t rawValue)
    {
        FixedPoint fp;
        fp.value = rawValue;
        return fp;
    }

    // Фабричный метод для int, чтобы избежать неоднозначности
    static FixedPoint fromInt(int integer)
    {
        return FixedPoint(static_cast<int32_t>(integer) << SHIFT);
    }

    // Метод квадратного корня
    static FixedPoint sqrt(const FixedPoint &number)
    {
        if (number.value <= 0)
        {
            return FixedPoint::fromInt(0); // Обработка случая с отрицательным числом
        }

        int32_t x = number.value;
        int32_t res = x; // Начальное предположение

        // Метод Ньютона для нахождения квадратного корня
        for (int i = 0; i < 10; ++i)
        { // Итерации, 10 обычно достаточно для сходимости
            res = (res + (x << SHIFT) / res) >> 1;
        }

        return FixedPoint::fromRaw(res);
    }
};

#endif // FIXED_POINT_H