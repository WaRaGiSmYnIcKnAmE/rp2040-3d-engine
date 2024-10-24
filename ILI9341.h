#ifndef ILI9341_H
#define ILI9341_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "pico/multicore.h"

#include "Defines.h"

#define ILI9341_RST_PIN 15
#define ILI9341_DC_PIN 8
#define ILI9341_CS_PIN 9
#define ILI9341_SCK_PIN 10
#define ILI9341_MOSI_PIN 11

#define SPI_PORT spi0

#define ILI9341_SWRESET 0x01
#define ILI9341_SLPOUT 0x11
#define ILI9341_DISPON 0x29
#define ILI9341_CASET 0x2A
#define ILI9341_RASET 0x2B
#define ILI9341_RAMWR 0x2C

// DMA chennel
extern int dma_channel;

// Display init
void ili9341_init();

// Transferring the frame buffer to the display
void ili9341_send_framebuffer(uint16_t *framebuffer);

// A function for transmitting a block of data via DMA
void ili9341_send_data_dma(uint8_t *data, size_t length);

// Function for sending commands to the display
void ili9341_write_command(uint8_t cmd);

// Function for sending data to the display
void ili9341_write_data(uint8_t data);

#endif // ILI9341_H