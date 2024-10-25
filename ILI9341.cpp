#include "ILI9341.h"
#include "hardware/spi.h"
#include "pico/platform.h"

int dma_channel;

// Функция для отправки команды
void send_command(uint8_t cmd)
{
    gpio_put(ILI9341_DC_PIN, 0); // Устанавливаем DC в режим команды
    gpio_put(ILI9341_CS_PIN, 0); // Активируем CS (низкий уровень)
    spi_write_blocking(SPI_PORT, &cmd, 1);
    gpio_put(ILI9341_CS_PIN, 1); // Деактивируем CS
}

// Функция для отправки данных
void send_data(uint8_t *data, size_t len)
{
    gpio_put(ILI9341_DC_PIN, 1); // Устанавливаем DC в режим данных
    gpio_put(ILI9341_CS_PIN, 0); // Активируем CS
    spi_write_blocking(SPI_PORT, data, len);
    gpio_put(ILI9341_CS_PIN, 1); // Деактивируем CS
}

// Функция для сброса дисплея
void reset_display()
{
    gpio_put(ILI9341_RST_PIN, 0);
    sleep_ms(10);
    gpio_put(ILI9341_RST_PIN, 1);
    sleep_ms(120);
}

// Функция инициализации дисплея ILI9341
void ili9341_init()
{
    gpio_init(ILI9341_CS_PIN);
    gpio_set_dir(ILI9341_CS_PIN, GPIO_OUT);
    gpio_put(ILI9341_CS_PIN, 1);

    gpio_init(ILI9341_DC_PIN);
    gpio_set_dir(ILI9341_DC_PIN, GPIO_OUT);

    gpio_init(ILI9341_RST_PIN);
    gpio_set_dir(ILI9341_RST_PIN, GPIO_OUT);

    // Инициализация SPI
    spi_init(SPI_PORT, 100000 * 1000);
    gpio_set_function(ILI9341_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ILI9341_MOSI_PIN, GPIO_FUNC_SPI);

    reset_display();

    send_command(0x01); // Software Reset
    sleep_ms(5);

    send_command(0x11); // Sleep Out
    sleep_ms(120);

    uint8_t color_mode = 0x55; // 16-битный цвет (RGB565)
    send_command(0x3A);        // Pixel Format Set
    send_data(&color_mode, 1);

    send_command(0x29); // Display ON
    sleep_ms(100);
}

// Установка адреса окна (по всей ширине экрана)
void set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint8_t data[4];

    send_command(0x2A); // Column Address Set
    data[0] = x0 >> 8;
    data[1] = x0 & 0xFF;
    data[2] = x1 >> 8;
    data[3] = x1 & 0xFF;
    send_data(data, 4);

    send_command(0x2B); // Page Address Set
    data[0] = y0 >> 8;
    data[1] = y0 & 0xFF;
    data[2] = y1 >> 8;
    data[3] = y1 & 0xFF;
    send_data(data, 4);

    send_command(0x2C); // Memory Write
}

// Заливка экрана цветом
void fill_screen(uint16_t color)
{
    set_address_window(0, 0, 239, 319); // Для ILI9341 240x320

    uint8_t data[2] = {color >> 8, color & 0xFF};
    for (uint32_t i = 0; i < 240 * 320; i++)
    {
        send_data(data, 2); // Отправляем цвет пикселя
    }
}

// Функция для отправки кадра
void ili9341_send_framebuffer(uint16_t *framebuffer)
{
    set_address_window(0, 0, ILI9341_TFTWIDTH - 1, ILI9341_TFTHEIGHT - 1); // Устанавливаем окно для передачи

    // Устанавливаем режим передачи данных (Data mode)
    gpio_put(ILI9341_DC_PIN, 1);
    gpio_put(ILI9341_CS_PIN, 0);

    // Отправляем данные из буфера через DMA
    ili9341_send_data_dma((uint8_t *)framebuffer, ILI9341_TFTWIDTH * ILI9341_TFTHEIGHT * 2); // RGB565 — 2 байта на пиксель

    // Отключаем CS после завершения передачи
    gpio_put(ILI9341_CS_PIN, 1);
}

// Функция для отправки данных через DMA
void ili9341_send_data_dma(uint8_t *data, size_t length)
{
    dma_channel = dma_claim_unused_channel(true); // Резервируем свободный канал DMA

    dma_channel_config config = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&config, DMA_SIZE_8);     // Размер данных — 8 бит (байт)
    channel_config_set_dreq(&config, spi_get_dreq(SPI_PORT, true)); // Устанавливаем запрос на SPI TX

    // Настраиваем DMA-канал
    dma_channel_configure(
        dma_channel,
        &config,
        &spi_get_hw(SPI_PORT)->dr, // Адрес регистра данных SPI
        data,                      // Адрес исходных данных
        length,                    // Длина передаваемых данных
        true                       // Начать передачу сразу
    );

    // Ожидаем завершения передачи
    dma_channel_wait_for_finish_blocking(dma_channel);

    // Освобождаем канал DMA после завершения
    dma_channel_unclaim(dma_channel);
}