#ifndef FONT_H
#define FONT_H

#include <pico/stdlib.h>
#include "pico/platform.h"

// Определение ширины и высоты символов в пикселях
#define CHARACTER_WIDTH 5
#define CHARACTER_HEIGHT 7

const uint8_t font5x7[][CHARACTER_WIDTH] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // ' ' (space)
    {0x04, 0x04, 0x04, 0x00, 0x04}, // '!'
    {0x0A, 0x0A, 0x00, 0x00, 0x00}, // '"'
    {0x0A, 0x1F, 0x0A, 0x1F, 0x0A}, // '#'
    {0x04, 0x0F, 0x14, 0x1E, 0x04}, // '$'
    {0x18, 0x19, 0x02, 0x04, 0x13}, // '%'
    {0x0C, 0x12, 0x0A, 0x14, 0x0A}, // '&'
    {0x04, 0x04, 0x00, 0x00, 0x00}, // '''
    {0x02, 0x04, 0x04, 0x04, 0x02}, // '('
    {0x04, 0x02, 0x02, 0x02, 0x04}, // ')'
    {0x00, 0x0A, 0x0E, 0x0A, 0x00}, // '*'
    {0x00, 0x04, 0x0E, 0x04, 0x00}, // '+'
    {0x00, 0x00, 0x00, 0x04, 0x04}, // ','
    {0x00, 0x00, 0x1F, 0x00, 0x00}, // '-'
    {0x00, 0x00, 0x00, 0x04, 0x00}, // '.'
    {0x01, 0x02, 0x04, 0x08, 0x10}, // '/'
    {0x0E, 0x11, 0x11, 0x11, 0x0E}, // '0'
    {0x04, 0x0C, 0x04, 0x04, 0x0E}, // '1'
    {0x0E, 0x01, 0x0E, 0x10, 0x1F}, // '2'
    {0x0E, 0x01, 0x06, 0x01, 0x0E}, // '3'
    {0x02, 0x06, 0x12, 0x1F, 0x02}, // '4'
    {0x1F, 0x10, 0x1E, 0x01, 0x1E}, // '5'
    {0x0E, 0x10, 0x1E, 0x11, 0x0E}, // '6'
    {0x1F, 0x02, 0x04, 0x08, 0x10}, // '7'
    {0x0E, 0x11, 0x0E, 0x11, 0x0E}, // '8'
    {0x0E, 0x11, 0x0F, 0x01, 0x0E}, // '9'
    {0x00, 0x04, 0x00, 0x04, 0x00}, // ':'
    {0x00, 0x04, 0x00, 0x04, 0x08}, // ';'
    {0x02, 0x04, 0x08, 0x04, 0x02}, // '<'
    {0x00, 0x0E, 0x00, 0x0E, 0x00}, // '='
    {0x08, 0x04, 0x02, 0x04, 0x08}, // '>'
    {0x0E, 0x11, 0x02, 0x00, 0x04}, // '?'
    {0x0E, 0x15, 0x17, 0x10, 0x0E}, // '@'
    {0x04, 0x0A, 0x11, 0x1F, 0x11}, // 'A'
    {0x1E, 0x11, 0x1E, 0x11, 0x1E}, // 'B'
    {0x0E, 0x11, 0x10, 0x11, 0x0E}, // 'C'
    {0x1E, 0x11, 0x11, 0x11, 0x1E}, // 'D'
    {0x1F, 0x10, 0x1E, 0x10, 0x1F}, // 'E'
    {0x1F, 0x10, 0x1E, 0x10, 0x10}, // 'F'
    {0x0E, 0x10, 0x17, 0x11, 0x0E}, // 'G'
    {0x11, 0x11, 0x1F, 0x11, 0x11}, // 'H'
    {0x1F, 0x04, 0x04, 0x04, 0x1F}, // 'I'
    {0x1F, 0x02, 0x02, 0x12, 0x0C}, // 'J'
    {0x11, 0x12, 0x1C, 0x12, 0x11}, // 'K'
    {0x10, 0x10, 0x10, 0x10, 0x1F}, // 'L'
    {0x11, 0x1B, 0x15, 0x11, 0x11}, // 'M'
    {0x11, 0x19, 0x15, 0x13, 0x11}, // 'N'
    {0x0E, 0x11, 0x11, 0x11, 0x0E}, // 'O'
    {0x1E, 0x11, 0x1E, 0x10, 0x10}, // 'P'
    {0x0E, 0x11, 0x11, 0x13, 0x0F}, // 'Q'
    {0x1E, 0x11, 0x1E, 0x12, 0x11}, // 'R'
    {0x0F, 0x10, 0x0E, 0x01, 0x1E}, // 'S'
    {0x1F, 0x04, 0x04, 0x04, 0x04}, // 'T'
    {0x11, 0x11, 0x11, 0x11, 0x0E}, // 'U'
    {0x11, 0x11, 0x0A, 0x0A, 0x04}, // 'V'
    {0x11, 0x11, 0x15, 0x15, 0x0A}, // 'W'
    {0x11, 0x0A, 0x04, 0x0A, 0x11}, // 'X'
    {0x11, 0x11, 0x0A, 0x04, 0x04}, // 'Y'
    {0x1F, 0x02, 0x04, 0x08, 0x1F}, // 'Z'
    {0x07, 0x04, 0x04, 0x04, 0x07}, // '['
    {0x10, 0x08, 0x04, 0x02, 0x01}, // '\'
    {0x0E, 0x02, 0x02, 0x02, 0x0E}, // ']'
    {0x04, 0x0A, 0x00, 0x00, 0x00}, // '^'
    {0x00, 0x00, 0x00, 0x00, 0x1F}, // '_'
    {0x04, 0x02, 0x00, 0x00, 0x00}, // '`'
    {0x00, 0x0E, 0x13, 0x13, 0x0F}, // 'a'
    {0x10, 0x1E, 0x11, 0x11, 0x1E}, // 'b'
    {0x00, 0x0E, 0x10, 0x10, 0x0E}, // 'c'
    {0x01, 0x0F, 0x11, 0x11, 0x0F}, // 'd'
    {0x0E, 0x11, 0x1F, 0x10, 0x0E}, // 'e'
    {0x06, 0x08, 0x1E, 0x08, 0x08}, // 'f'
    {0x0F, 0x11, 0x0F, 0x01, 0x0E}, // 'g'
    {0x10, 0x1E, 0x11, 0x11, 0x11}, // 'h'
    {0x04, 0x00, 0x0C, 0x04, 0x0E}, // 'i'
    {0x02, 0x00, 0x02, 0x12, 0x0C}, // 'j'
    {0x10, 0x12, 0x1C, 0x12, 0x11}, // 'k'
    {0x0C, 0x04, 0x04, 0x04, 0x0E}, // 'l'
    {0x00, 0x1B, 0x15, 0x15, 0x11}, // 'm'
    {0x00, 0x1E, 0x11, 0x11, 0x11}, // 'n'
    {0x00, 0x0E, 0x11, 0x11, 0x0E}, // 'o'
    {0x00, 0x1E, 0x11, 0x1E, 0x10}, // 'p'
    {0x00, 0x0F, 0x11, 0x0F, 0x01}, // 'q'
    {0x00, 0x16, 0x18, 0x10, 0x10}, // 'r'
    {0x0F, 0x10, 0x0E, 0x01, 0x1E}, // 's'
    {0x08, 0x1E, 0x08, 0x08, 0x07}, // 't'
    {0x00, 0x11, 0x11, 0x13, 0x0F}, // 'u'
    {0x00, 0x11, 0x11, 0x0A, 0x04}, // 'v'
    {0x00, 0x11, 0x15, 0x15, 0x0A}, // 'w'
    {0x00, 0x11, 0x0A, 0x0A, 0x11}, // 'x'
    {0x00, 0x11, 0x0F, 0x01, 0x0E}, // 'y'
    {0x00, 0x1F, 0x02, 0x04, 0x1F}, // 'z'
    {0x06, 0x04, 0x08, 0x04, 0x06}, // '{'
    {0x04, 0x04, 0x04, 0x04, 0x04}, // '|'
    {0x0C, 0x04, 0x02, 0x04, 0x0C}, // '}'
    {0x00, 0x00, 0x02, 0x15, 0x08}  // '~'
};

// Возвращает битовую карту для символа ASCII
const uint8_t *font_get_bitmap(char c)
{
    if (c < 32 || c > 126)
    {
        return font5x7[0]; // По умолчанию пробел, если символ не поддерживается
    }
    return font5x7[c - 32];
}

#endif // FONT_H