#include "ILI9341.h"
#include "hardware/spi.h"

int dma_channel;

// Function for sending commands to the display
void ili9341_write_command(uint8_t cmd)
{
    gpio_put(ILI9341_DC_PIN, 0);
    gpio_put(ILI9341_CS_PIN, 0);
    spi_write_blocking(SPI_PORT, &cmd, 1);
    gpio_put(ILI9341_CS_PIN, 1);
}

// Function for sending data to the display
void ili9341_write_data(uint8_t data)
{
    gpio_put(ILI9341_DC_PIN, 1);
    gpio_put(ILI9341_CS_PIN, 0);
    spi_write_blocking(SPI_PORT, &data, 1);
    gpio_put(ILI9341_CS_PIN, 1);
}

void ili9341_init()
{
    // Pins setup
    gpio_init(ILI9341_RST_PIN);
    gpio_set_dir(ILI9341_RST_PIN, GPIO_OUT);
    gpio_init(ILI9341_DC_PIN);
    gpio_set_dir(ILI9341_DC_PIN, GPIO_OUT);
    gpio_init(ILI9341_CS_PIN);
    gpio_set_dir(ILI9341_CS_PIN, GPIO_OUT);

    // Display reset
    gpio_put(ILI9341_RST_PIN, 0);
    sleep_ms(10);
    gpio_put(ILI9341_RST_PIN, 1);
    sleep_ms(120);

    // SPI init
    spi_init(SPI_PORT, 500 * 1000);
    gpio_set_function(ILI9341_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ILI9341_MOSI_PIN, GPIO_FUNC_SPI);

    // Setup DMA for SPI
    dma_channel = dma_claim_unused_channel(true);

    ili9341_write_command(ILI9341_SWRESET);
    sleep_ms(150);
    ili9341_write_command(ILI9341_SLPOUT);
    sleep_ms(500);
    ili9341_write_command(ILI9341_DISPON);
}

// Send buffer of frame to display
void ili9341_send_framebuffer(uint16_t *framebuffer)
{
    ili9341_write_command(ILI9341_CASET); // Rows
    ili9341_write_data(0);
    ili9341_write_data(0);
    ili9341_write_data(SCREEN_WIDTH >> 8);
    ili9341_write_data(SCREEN_WIDTH & 0xFF);

    ili9341_write_command(ILI9341_RASET); // Columns
    ili9341_write_data(0);
    ili9341_write_data(0);
    ili9341_write_data(SCREEN_HEIGHT >> 8);
    ili9341_write_data(SCREEN_HEIGHT & 0xFF);

    ili9341_write_command(ILI9341_RAMWR); // Switching to writing data to the display memory

    // Buffer data transfer via DMA
    ili9341_send_data_dma((uint8_t *)framebuffer, SCREEN_WIDTH * SCREEN_HEIGHT * 2);
}

// Sending data via DMA
void ili9341_send_data_dma(uint8_t *data, size_t length)
{
    dma_channel_config c = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_dreq(&c, DREQ_SPI0_TX);
    dma_channel_configure(dma_channel, &c, &spi_get_hw(SPI_PORT)->dr, data, length, true);
    dma_channel_wait_for_finish_blocking(dma_channel);
}