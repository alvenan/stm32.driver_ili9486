/*
 * tft.c
 *
 *  Created on: Oct 9, 2021
 *      Author: alvenan
 */

#include "tft.h"

static TFT *tft;
static uint8_t rot_num = 1;
static uint32_t tft_width, tft_height, tft_pixel_count;
static uint8_t _cp437 = 0;

uint8_t cursor_y = 0, cursor_x = 0;

static //Text simple font array (You can your own font)
const unsigned char font1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x5B, 0x4F,
		0x5B, 0x3E, 0x3E, 0x6B, 0x4F, 0x6B, 0x3E, 0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
		0x18, 0x3C, 0x7E, 0x3C, 0x18, 0x1C, 0x57, 0x7D, 0x57, 0x1C, 0x1C, 0x5E,
		0x7F, 0x5E, 0x1C, 0x00, 0x18, 0x3C, 0x18, 0x00, 0xFF, 0xE7, 0xC3, 0xE7,
		0xFF, 0x00, 0x18, 0x24, 0x18, 0x00, 0xFF, 0xE7, 0xDB, 0xE7, 0xFF, 0x30,
		0x48, 0x3A, 0x06, 0x0E, 0x26, 0x29, 0x79, 0x29, 0x26, 0x40, 0x7F, 0x05,
		0x05, 0x07, 0x40, 0x7F, 0x05, 0x25, 0x3F, 0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
		0x7F, 0x3E, 0x1C, 0x1C, 0x08, 0x08, 0x1C, 0x1C, 0x3E, 0x7F, 0x14, 0x22,
		0x7F, 0x22, 0x14, 0x5F, 0x5F, 0x00, 0x5F, 0x5F, 0x06, 0x09, 0x7F, 0x01,
		0x7F, 0x00, 0x66, 0x89, 0x95, 0x6A, 0x60, 0x60, 0x60, 0x60, 0x60, 0x94,
		0xA2, 0xFF, 0xA2, 0x94, 0x08, 0x04, 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E,
		0x20, 0x10, 0x08, 0x08, 0x2A, 0x1C, 0x08, 0x08, 0x1C, 0x2A, 0x08, 0x08,
		0x1E, 0x10, 0x10, 0x10, 0x10, 0x0C, 0x1E, 0x0C, 0x1E, 0x0C, 0x30, 0x38,
		0x3E, 0x38, 0x30, 0x06, 0x0E, 0x3E, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x14,
		0x7F, 0x14, 0x7F, 0x14, 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x23, 0x13, 0x08,
		0x64, 0x62, 0x36, 0x49, 0x56, 0x20, 0x50, 0x00, 0x08, 0x07, 0x03, 0x00,
		0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, 0x41, 0x22, 0x1C, 0x00, 0x2A, 0x1C,
		0x7F, 0x1C, 0x2A, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x80, 0x70, 0x30,
		0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x60, 0x60, 0x00, 0x20,
		0x10, 0x08, 0x04, 0x02, 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x42, 0x7F,
		0x40, 0x00, 0x72, 0x49, 0x49, 0x49, 0x46, 0x21, 0x41, 0x49, 0x4D, 0x33,
		0x18, 0x14, 0x12, 0x7F, 0x10, 0x27, 0x45, 0x45, 0x45, 0x39, 0x3C, 0x4A,
		0x49, 0x49, 0x31, 0x41, 0x21, 0x11, 0x09, 0x07, 0x36, 0x49, 0x49, 0x49,
		0x36, 0x46, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
		0x40, 0x34, 0x00, 0x00, 0x00, 0x08, 0x14, 0x22, 0x41, 0x14, 0x14, 0x14,
		0x14, 0x14, 0x00, 0x41, 0x22, 0x14, 0x08, 0x02, 0x01, 0x59, 0x09, 0x06,
		0x3E, 0x41, 0x5D, 0x59, 0x4E, 0x7C, 0x12, 0x11, 0x12, 0x7C, 0x7F, 0x49,
		0x49, 0x49, 0x36, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x7F, 0x41, 0x41, 0x41,
		0x3E, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x7F, 0x09, 0x09, 0x09, 0x01, 0x3E,
		0x41, 0x41, 0x51, 0x73, 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x41, 0x7F,
		0x41, 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, 0x7F, 0x08, 0x14, 0x22, 0x41,
		0x7F, 0x40, 0x40, 0x40, 0x40, 0x7F, 0x02, 0x1C, 0x02, 0x7F, 0x7F, 0x04,
		0x08, 0x10, 0x7F, 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x7F, 0x09, 0x09, 0x09,
		0x06, 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x7F, 0x09, 0x19, 0x29, 0x46, 0x26,
		0x49, 0x49, 0x49, 0x32, 0x03, 0x01, 0x7F, 0x01, 0x03, 0x3F, 0x40, 0x40,
		0x40, 0x3F, 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x3F, 0x40, 0x38, 0x40, 0x3F,
		0x63, 0x14, 0x08, 0x14, 0x63, 0x03, 0x04, 0x78, 0x04, 0x03, 0x61, 0x59,
		0x49, 0x4D, 0x43, 0x00, 0x7F, 0x41, 0x41, 0x41, 0x02, 0x04, 0x08, 0x10,
		0x20, 0x00, 0x41, 0x41, 0x41, 0x7F, 0x04, 0x02, 0x01, 0x02, 0x04, 0x40,
		0x40, 0x40, 0x40, 0x40, 0x00, 0x03, 0x07, 0x08, 0x00, 0x20, 0x54, 0x54,
		0x78, 0x40, 0x7F, 0x28, 0x44, 0x44, 0x38, 0x38, 0x44, 0x44, 0x44, 0x28,
		0x38, 0x44, 0x44, 0x28, 0x7F, 0x38, 0x54, 0x54, 0x54, 0x18, 0x00, 0x08,
		0x7E, 0x09, 0x02, 0x18, 0xA4, 0xA4, 0x9C, 0x78, 0x7F, 0x08, 0x04, 0x04,
		0x78, 0x00, 0x44, 0x7D, 0x40, 0x00, 0x20, 0x40, 0x40, 0x3D, 0x00, 0x7F,
		0x10, 0x28, 0x44, 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, 0x7C, 0x04, 0x78,
		0x04, 0x78, 0x7C, 0x08, 0x04, 0x04, 0x78, 0x38, 0x44, 0x44, 0x44, 0x38,
		0xFC, 0x18, 0x24, 0x24, 0x18, 0x18, 0x24, 0x24, 0x18, 0xFC, 0x7C, 0x08,
		0x04, 0x04, 0x08, 0x48, 0x54, 0x54, 0x54, 0x24, 0x04, 0x04, 0x3F, 0x44,
		0x24, 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x3C,
		0x40, 0x30, 0x40, 0x3C, 0x44, 0x28, 0x10, 0x28, 0x44, 0x4C, 0x90, 0x90,
		0x90, 0x7C, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 0x08, 0x36, 0x41, 0x00,
		0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x41, 0x36, 0x08, 0x00, 0x02, 0x01,
		0x02, 0x04, 0x02, 0x3C, 0x26, 0x23, 0x26, 0x3C, 0x1E, 0xA1, 0xA1, 0x61,
		0x12, 0x3A, 0x40, 0x40, 0x20, 0x7A, 0x38, 0x54, 0x54, 0x55, 0x59, 0x21,
		0x55, 0x55, 0x79, 0x41, 0x22, 0x54, 0x54, 0x78, 0x42, 0x21, 0x55, 0x54,
		0x78, 0x40, 0x20, 0x54, 0x55, 0x79, 0x40, 0x0C, 0x1E, 0x52, 0x72, 0x12,
		0x39, 0x55, 0x55, 0x55, 0x59, 0x39, 0x54, 0x54, 0x54, 0x59, 0x39, 0x55,
		0x54, 0x54, 0x58, 0x00, 0x00, 0x45, 0x7C, 0x41, 0x00, 0x02, 0x45, 0x7D,
		0x42, 0x00, 0x01, 0x45, 0x7C, 0x40, 0x7D, 0x12, 0x11, 0x12, 0x7D, 0xF0,
		0x28, 0x25, 0x28, 0xF0, 0x7C, 0x54, 0x55, 0x45, 0x00, 0x20, 0x54, 0x54,
		0x7C, 0x54, 0x7C, 0x0A, 0x09, 0x7F, 0x49, 0x32, 0x49, 0x49, 0x49, 0x32,
		0x3A, 0x44, 0x44, 0x44, 0x3A, 0x32, 0x4A, 0x48, 0x48, 0x30, 0x3A, 0x41,
		0x41, 0x21, 0x7A, 0x3A, 0x42, 0x40, 0x20, 0x78, 0x00, 0x9D, 0xA0, 0xA0,
		0x7D, 0x3D, 0x42, 0x42, 0x42, 0x3D, 0x3D, 0x40, 0x40, 0x40, 0x3D, 0x3C,
		0x24, 0xFF, 0x24, 0x24, 0x48, 0x7E, 0x49, 0x43, 0x66, 0x2B, 0x2F, 0xFC,
		0x2F, 0x2B, 0xFF, 0x09, 0x29, 0xF6, 0x20, 0xC0, 0x88, 0x7E, 0x09, 0x03,
		0x20, 0x54, 0x54, 0x79, 0x41, 0x00, 0x00, 0x44, 0x7D, 0x41, 0x30, 0x48,
		0x48, 0x4A, 0x32, 0x38, 0x40, 0x40, 0x22, 0x7A, 0x00, 0x7A, 0x0A, 0x0A,
		0x72, 0x7D, 0x0D, 0x19, 0x31, 0x7D, 0x26, 0x29, 0x29, 0x2F, 0x28, 0x26,
		0x29, 0x29, 0x29, 0x26, 0x30, 0x48, 0x4D, 0x40, 0x20, 0x38, 0x08, 0x08,
		0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x38, 0x2F, 0x10, 0xC8, 0xAC, 0xBA,
		0x2F, 0x10, 0x28, 0x34, 0xFA, 0x00, 0x00, 0x7B, 0x00, 0x00, 0x08, 0x14,
		0x2A, 0x14, 0x22, 0x22, 0x14, 0x2A, 0x14, 0x08, 0x55, 0x00, 0x55, 0x00,
		0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0xFF, 0x55, 0xFF, 0x55, 0xFF, 0x00,
		0x00, 0x00, 0xFF, 0x00, 0x10, 0x10, 0x10, 0xFF, 0x00, 0x14, 0x14, 0x14,
		0xFF, 0x00, 0x10, 0x10, 0xFF, 0x00, 0xFF, 0x10, 0x10, 0xF0, 0x10, 0xF0,
		0x14, 0x14, 0x14, 0xFC, 0x00, 0x14, 0x14, 0xF7, 0x00, 0xFF, 0x00, 0x00,
		0xFF, 0x00, 0xFF, 0x14, 0x14, 0xF4, 0x04, 0xFC, 0x14, 0x14, 0x17, 0x10,
		0x1F, 0x10, 0x10, 0x1F, 0x10, 0x1F, 0x14, 0x14, 0x14, 0x1F, 0x00, 0x10,
		0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
		0x1F, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x10, 0x00, 0x00, 0x00, 0xFF, 0x10,
		0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xFF, 0x10, 0x00, 0x00,
		0x00, 0xFF, 0x14, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x1F, 0x10,
		0x17, 0x00, 0x00, 0xFC, 0x04, 0xF4, 0x14, 0x14, 0x17, 0x10, 0x17, 0x14,
		0x14, 0xF4, 0x04, 0xF4, 0x00, 0x00, 0xFF, 0x00, 0xF7, 0x14, 0x14, 0x14,
		0x14, 0x14, 0x14, 0x14, 0xF7, 0x00, 0xF7, 0x14, 0x14, 0x14, 0x17, 0x14,
		0x10, 0x10, 0x1F, 0x10, 0x1F, 0x14, 0x14, 0x14, 0xF4, 0x14, 0x10, 0x10,
		0xF0, 0x10, 0xF0, 0x00, 0x00, 0x1F, 0x10, 0x1F, 0x00, 0x00, 0x00, 0x1F,
		0x14, 0x00, 0x00, 0x00, 0xFC, 0x14, 0x00, 0x00, 0xF0, 0x10, 0xF0, 0x10,
		0x10, 0xFF, 0x10, 0xFF, 0x14, 0x14, 0x14, 0xFF, 0x14, 0x10, 0x10, 0x10,
		0x1F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x38, 0x44, 0x44, 0x38,
		0x44, 0xFC, 0x4A, 0x4A, 0x4A, 0x34, 0x7E, 0x02, 0x02, 0x06, 0x06, 0x02,
		0x7E, 0x02, 0x7E, 0x02, 0x63, 0x55, 0x49, 0x41, 0x63, 0x38, 0x44, 0x44,
		0x3C, 0x04, 0x40, 0x7E, 0x20, 0x1E, 0x20, 0x06, 0x02, 0x7E, 0x02, 0x02,
		0x99, 0xA5, 0xE7, 0xA5, 0x99, 0x1C, 0x2A, 0x49, 0x2A, 0x1C, 0x4C, 0x72,
		0x01, 0x72, 0x4C, 0x30, 0x4A, 0x4D, 0x4D, 0x30, 0x30, 0x48, 0x78, 0x48,
		0x30, 0xBC, 0x62, 0x5A, 0x46, 0x3D, 0x3E, 0x49, 0x49, 0x49, 0x00, 0x7E,
		0x01, 0x01, 0x01, 0x7E, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x44, 0x44, 0x5F,
		0x44, 0x44, 0x40, 0x51, 0x4A, 0x44, 0x40, 0x40, 0x44, 0x4A, 0x51, 0x40,
		0x00, 0x00, 0xFF, 0x01, 0x03, 0xE0, 0x80, 0xFF, 0x00, 0x00, 0x08, 0x08,
		0x6B, 0x6B, 0x08, 0x36, 0x12, 0x36, 0x24, 0x36, 0x06, 0x0F, 0x09, 0x0F,
		0x06, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x30,
		0x40, 0xFF, 0x01, 0x01, 0x00, 0x1F, 0x01, 0x01, 0x1E, 0x00, 0x19, 0x1D,
		0x17, 0x12, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

void tft_init(SPI_HandleTypeDef *spi, GPIO_TypeDef *cs_port, uint16_t cs_pin,
		GPIO_TypeDef *dc_port, uint16_t dc_pin, GPIO_TypeDef *rst_port,
		uint16_t rst_pin, uint32_t width, uint32_t height) {

	tft_width = width;
	tft_height = height;
	tft_pixel_count = width * height;

	tft = tft_interface_init(spi, cs_port, cs_pin, dc_port, dc_pin, rst_port,
			rst_pin);

	tft_spi_rst_off(tft);
	tft_spi_rst_on(tft);
	tft_spi_rst_off(tft);

	tft_send_cmd(tft, TFTCMD_NOP);
	tft_send_data(tft, 0x00);
	tft_send_cmd(tft, TFTCMD_SLEEP_OUT);

	tft_delay(150);
#ifdef TFT_ILI9486
	tft_send_cmd(tft, TFTCMD_PIXEL_FORMAT);
	tft_send_data(tft, 0x55);

	tft_send_cmd(tft, TFTCMD_MAC);
	tft_send_data(tft, 0x48);

	tft_send_cmd(tft, TFTCMD_POWER3);
	tft_send_data(tft, 0x44);

	tft_send_cmd(tft, TFTCMD_VCOM1);
	tft_send_data(tft, 0x00);
	tft_send_data(tft, 0x00);
	tft_send_data(tft, 0x00);
	tft_send_data(tft, 0x00);

	tft_send_cmd(tft, TFTCMD_PGAMMA);
	tft_send_data(tft, 0x0f);
	tft_send_data(tft, 0x1f);
	tft_send_data(tft, 0x1c);
	tft_send_data(tft, 0x0c);
	tft_send_data(tft, 0x0f);
	tft_send_data(tft, 0x08);
	tft_send_data(tft, 0x48);
	tft_send_data(tft, 0x98);
	tft_send_data(tft, 0x37);
	tft_send_data(tft, 0x0a);
	tft_send_data(tft, 0x13);
	tft_send_data(tft, 0x04);
	tft_send_data(tft, 0x11);
	tft_send_data(tft, 0x0d);
	tft_send_data(tft, 0x00);

	tft_send_cmd(tft, TFTCMD_NGAMMA);
	tft_send_data(tft, 0x0f);
	tft_send_data(tft, 0x32);
	tft_send_data(tft, 0x2e);
	tft_send_data(tft, 0x0b);
	tft_send_data(tft, 0x0d);
	tft_send_data(tft, 0x05);
	tft_send_data(tft, 0x47);
	tft_send_data(tft, 0x75);
	tft_send_data(tft, 0x37);
	tft_send_data(tft, 0x06);
	tft_send_data(tft, 0x10);
	tft_send_data(tft, 0x03);
	tft_send_data(tft, 0x24);
	tft_send_data(tft, 0x20);
	tft_send_data(tft, 0x00);

	tft_send_cmd(tft, TFTCMD_GAMMA_CTRL1);
	tft_send_data(tft, 0x0f);
	tft_send_data(tft, 0x32);
	tft_send_data(tft, 0x2e);
	tft_send_data(tft, 0x0b);
	tft_send_data(tft, 0x0d);
	tft_send_data(tft, 0x05);
	tft_send_data(tft, 0x47);
	tft_send_data(tft, 0x75);
	tft_send_data(tft, 0x37);
	tft_send_data(tft, 0x06);
	tft_send_data(tft, 0x10);
	tft_send_data(tft, 0x03);
	tft_send_data(tft, 0x24);
	tft_send_data(tft, 0x20);
	tft_send_data(tft, 0x00);
#endif
	tft_send_cmd(tft, TFTCMD_SLEEP_OUT);
	tft_send_cmd(tft, TFTCMD_DISPLAY_ON);

	tft_delay(150);

}

void tft_set_rotation(uint8_t rotate) {
	tft_send_cmd(tft, MEMCONTROL);
	switch (rotate) {
	case 1:
		rot_num = 1;
		tft_send_data(tft,
		MADCTL_MY | MADCTL_BGR);
		break;
	case 2:
		rot_num = 2;
		tft_send_data(tft,
		MADCTL_MV | MADCTL_BGR);
		break;
	case 3:
		rot_num = 3;
		tft_send_data(tft,
		MADCTL_MX | MADCTL_BGR);
		break;
	case 4:
		rot_num = 4;
		tft_send_data(tft,
		MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
		break;
	default:
		rot_num = 1;
		tft_send_data(tft,
		MADCTL_MY | MADCTL_BGR);
		break;
	}
}
void tft_cursor_position(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

	tft_send_cmd(tft, TFTCMD_COLUMN_ADDR);
	tft_send_data(tft, x0 >> 8);
	tft_send_data(tft, x0 & 0xff);
	tft_send_data(tft, x1 >> 8);
	tft_send_data(tft, x1 & 0xff);

	tft_send_cmd(tft, TFTCMD_PAGE_ADDR);
	tft_send_data(tft, y0 >> 8);
	tft_send_data(tft, y0 & 0xff);
	tft_send_data(tft, y1 >> 8);
	tft_send_data(tft, y1 & 0xff);

	tft_send_cmd(tft, TFTCMD_GRAM);
}

void tft_main_draw(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
		uint16_t color) {
	uint32_t n = ((x1 + 1) - x0) * ((y1 + 1) - y0);

	if (n > tft_pixel_count)
		n = tft_pixel_count;

	tft_cursor_position(x0, y0, x1, y1);
	for (; n > 0; n--) {
		tft_send_data(tft, color >> 8);
		tft_send_data(tft, color & 0xff);
	}
}

void tft_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	tft_main_draw(x, y, x + w, y + h, color);
}

void tft_fill_screen(uint16_t color) {

	if (rot_num == 1 || rot_num == 3)
		tft_fill_rect(0, 0, tft_height - 1, tft_width - 1, color);
	else if (rot_num == 2 || rot_num == 4)
		tft_fill_rect(0, 0, tft_width - 1, tft_height - 1, color);

}

void tft_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
	tft_main_draw(x, y, x, y, color);
}

void tft_draw_horizontal_line(uint16_t x, uint16_t y, uint16_t w,
		uint16_t color) {
	tft_main_draw(x, y, x + w, y, color);
}

void tft_draw_vertical_line(uint16_t x, uint16_t y, uint16_t w, uint16_t color) {
	tft_main_draw(x, y, x, y + w, color);
}

void tft_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	tft_draw_horizontal_line(x, y, w, color);
	tft_draw_horizontal_line(x, y + h, w, color);

	tft_draw_vertical_line(x, y, h, color);
	tft_draw_vertical_line(x + w, y, h, color);
}

void tft_draw_round_rect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,
		uint16_t color) {
	int16_t max_radius = ((w < h) ? w : h) / 2;
	if (r > max_radius)
		r = max_radius;

	tft_draw_horizontal_line(x + r, y, w - 2 * r, color); // Top
	tft_draw_horizontal_line(x + r, y + h - 1, w - 2 * r, color); // Bottom
	tft_draw_vertical_line(x, y + r, h - 2 * r, color); // Left
	tft_draw_vertical_line(x + w - 1, y + r, h - 2 * r, color); // Right

	tft_draw_circle_helper(x + r, y + r, r, 1, color);
	tft_draw_circle_helper(x + w - r - 1, y + r, r, 2, color);
	tft_draw_circle_helper(x + w - r - 1, y + h - r - 1, r, 4, color);
	tft_draw_circle_helper(x + r, y + h - r - 1, r, 8, color);
}

void tft_fill_round_rect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,
		uint16_t color) {
	int16_t max_radius = ((w < h) ? w : h) / 2;
	if (r > max_radius)
		r = max_radius;

	tft_main_draw(x + r, y, x + r + w - 2 * r, y + h, color);

	tft_fill_circle_helper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
	tft_fill_circle_helper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}

void tft_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
		uint16_t color) {
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}
	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1)
		ystep = 1;
	else
		ystep = -1;

	for (; x0 <= x1; x0++) {
		if (steep)
			tft_draw_pixel(y0, x0, color);
		else
			tft_draw_pixel(x0, y0, color);

		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void tft_draw_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	tft_draw_pixel(x0, y0 + r, color);
	tft_draw_pixel(x0, y0 - r, color);
	tft_draw_pixel(x0 + r, y0, color);
	tft_draw_pixel(x0 - r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		tft_draw_pixel(x0 + x, y0 + y, color);
		tft_draw_pixel(x0 - x, y0 + y, color);
		tft_draw_pixel(x0 + x, y0 - y, color);
		tft_draw_pixel(x0 - x, y0 - y, color);
		tft_draw_pixel(x0 + y, y0 + x, color);
		tft_draw_pixel(x0 - y, y0 + x, color);
		tft_draw_pixel(x0 + y, y0 - x, color);
		tft_draw_pixel(x0 - y, y0 - x, color);
	}
}

void tft_fill_circle(int16_t x, int16_t y, int16_t r, uint16_t color) {
	tft_draw_vertical_line(x, y-r, 2*r+1, color);
	tft_fill_circle_helper(x, y, r, 3, 0, color);
}


void tft_draw_circle_helper(int16_t x0, int16_t y0, int16_t r,
		uint8_t cornername, uint16_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x4) {
			tft_draw_pixel(x0 + x, y0 + y, color);
			tft_draw_pixel(x0 + y, y0 + x, color);
		}
		if (cornername & 0x2) {
			tft_draw_pixel(x0 + x, y0 - y, color);
			tft_draw_pixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8) {
			tft_draw_pixel(x0 - y, y0 + x, color);
			tft_draw_pixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1) {
			tft_draw_pixel(x0 - y, y0 - x, color);
			tft_draw_pixel(x0 - x, y0 - y, color);
		}
	}
}

void tft_fill_circle_helper(int16_t x0, int16_t y0, int16_t r, uint8_t corners,
		int16_t delta, uint16_t color) {

	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;
	int16_t px = x;
	int16_t py = y;

	delta++;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (x < (y + 1)) {
			if (corners & 1)
				tft_draw_vertical_line(x0 + x, y0 - y, 2 * y + delta, color);
			if (corners & 2)
				tft_draw_vertical_line(x0 - x, y0 - y, 2 * y + delta, color);
		}
		if (y != py) {
			if (corners & 1)
				tft_draw_vertical_line(x0 + py, y0 - px, 2 * px + delta, color);
			if (corners & 2)
				tft_draw_vertical_line(x0 - py, y0 - px, 2 * px + delta, color);
			py = y;
		}
		px = x;
	}
}

void tft_draw_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint16_t color) {
	tft_draw_line(x0, y0, x1, y1, color);
	tft_draw_line(x1, y1, x2, y2, color);
	tft_draw_line(x2, y2, x0, y0, color);
}

void tft_fill_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint16_t color) {
	int16_t a, b, y, last;

	if (y0 > y1) {
		swap(y0, y1);
		swap(x0, x1);
	}
	if (y1 > y2) {
		swap(y2, y1);
		swap(x2, x1);
	}
	if (y0 > y1) {
		swap(y0, y1);
		swap(x0, x1);
	}

	if (y0 == y2) {
		a = b = x0;
		if (x1 < a)
			a = x1;
		else if (x1 > b)
			b = x1;

		if (x2 < a)
			a = x2;
		else if (x2 > b)
			b = x2;
		tft_draw_horizontal_line(a, y0, b - a + 1, color);
		return;
	}

	int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0,
			dx12 = x2 - x1, dy12 = y2 - y1;
	int32_t sa = 0, sb = 0;

	if (y1 == y2)
		last = y1;
	else
		last = y1 - 1;

	for (y = y0; y <= last; y++) {
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;

		if (a > b)
			swap(a, b);
		tft_draw_horizontal_line(a, y, b - a + 1, color);
	}

	sa = (int32_t) dx12 * (y - y1);
	sb = (int32_t) dx02 * (y - y0);
	for (; y <= y2; y++) {
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if (a > b)
			swap(a, b);
		tft_draw_horizontal_line(a, y, b - a + 1, color);
	}
}

void tft_draw_char(int16_t x, int16_t y, unsigned char c, uint16_t color,
		uint16_t bg, uint8_t size) {

	if (rot_num == 1 || rot_num == 3) {
		if ((x >= tft_height) || // Clip right
				(y >= tft_width) || // Clip bottom
				((x + 6 * size - 1) < 0) || // Clip left
				((y + 8 * size - 1) < 0))   // Clip top
			return;

	} else if ((y >= tft_height) || // Clip right
			(x >= tft_width) || // Clip bottom
			((y + 6 * size - 1) < 0) || // Clip left
			((x + 8 * size - 1) < 0))   // Clip top
		return;

	if (!_cp437 && (c >= 176))
		c++; // Handle 'classic' charset behavior

	for (int8_t i = 0; i < 6; i++) {
		uint8_t line;
		if (i == 5)
			line = 0x0;
		else
			line = pgm_read_byte(font1 + (c * 5) + i);
		for (int8_t j = 0; j < 8; j++) {
			if (line & 0x1) {
				if (size == 1) // default size
					tft_draw_pixel(x + i, y + j, color);
				else {  // big size
					tft_main_draw(x + i * size, y + j * size,
							x + (i + 1) * size, y + (j + 1) * size, color);
				}
			} else if (bg != color) {
				if (size == 1) // default size
					tft_draw_pixel(x + i, y + j, bg);
				else {  // big size
					tft_main_draw(x + i * size, y + j * size,
							x + (i + 1) * size, y + (j + 1) * size, bg);
				}
			}
			line >>= 1;
		}
	}
}

void tft_draw_RGB_bitmap(int16_t x, int16_t y, const uint16_t bitmap[],
		int16_t w, int16_t h) {
	for (int16_t j = 0; j < h; j++, y++) {
		for (int16_t i = 0; i < w; i++) {
			tft_draw_pixel(x + i, y, pgm_read_word(&bitmap[j * w + i]));
		}
	}
}

// Testes
void test_fill_screen() {

	tft_fill_screen(COLOR_BLACK);
	tft_fill_screen(COLOR_RED);
	tft_fill_screen(COLOR_GREEN);
	tft_fill_screen(COLOR_BLUE);
	tft_fill_screen(COLOR_BLACK);
}

void test_lines(uint16_t color) {
	int x0, y0, x1, y1;

	tft_fill_screen(COLOR_BLACK);

	x0 = y0 = x1 = 0;
	y1 = tft_height;
	for (; x1 < tft_width; x1 += 5) {
		tft_draw_line(x0, y0, x1, y1, color);
	}
	for (; y1 > 0; y1 -= 5)
		tft_draw_line(x0, y0, x1, y1, color);

	tft_fill_screen(COLOR_BLACK);

	x0 = x1 = tft_width;
	y1 = tft_height;
	y0 = 0;
	for (; x1 > 0; x1 -= 5)
		tft_draw_line(x0, y0, x1, y1, color);
	for (; y1 > 0; y1 -= 5)
		tft_draw_line(x0, y0, x1, y1, color);

	tft_fill_screen(COLOR_BLACK);

	x0 = tft_width;
	y0 = y1 = tft_height;
	x1 = 0;
	for (; y1 > 0; y1 -= 5)
		tft_draw_line(x0, y0, x1, y1, color);
	for (; x1 < tft_width; x1 += 5)
		tft_draw_line(x0, y0, x1, y1, color);

	tft_fill_screen(COLOR_BLACK);

	x0 = x1 = y1 = 0;
	y0 = tft_height;
	for (; x1 < tft_width; x1 += 5)
		tft_draw_line(x0, y0, x1, y1, color);
	for (; y1 < tft_height; y1 += 5)
		tft_draw_line(x0, y0, x1, y1, color);

}

void test_lines2(uint16_t color1, uint16_t color2) {

	int x, y;

	tft_fill_screen(COLOR_BLACK);
	for (y = 0; y < tft_height; y += 5)
		tft_draw_horizontal_line(0, y, tft_width - 1, color1);
	for (x = 0; x < tft_width; x += 5)
		tft_draw_vertical_line(x, 0, tft_height - 1, color2);
}

void test_rects(uint16_t color) {
	int n, i1, i2, x = tft_width / 2, y = tft_height / 2;

	tft_fill_screen(COLOR_BLACK);

	n = min(tft_width, tft_height);
	for (i1 = 2; i1 < n; i1 += 6) {
		i2 = i1 / 2;
		tft_draw_rect(x - i2, y - i2, i1, i1, color);
	}

}

void test_fill_rects(uint16_t color1, uint16_t color2) {
	int n, i1, i2, x = tft_width / 2, y = tft_height / 2;

	tft_fill_screen(COLOR_BLACK);

	n = min(tft_width, tft_height);
	for (i1 = n; i1 > 0; i1 -= 5) {
		i2 = i1 / 2;

		tft_fill_rect(x - i2, y - i2, i1, i1, color1);
		tft_draw_rect(x - i2, y - i2, i1, i1, color2);
	}
}

void test_circles(uint8_t radius, uint16_t color) {
	int x, y, diameter = radius * 2, w = tft_width + radius, h = tft_height
			+ radius;

	tft_fill_screen(COLOR_BLACK);

	for (x = 0; x < w; x += diameter) {
		for (y = 0; y < h; y += diameter) {
			tft_draw_circle(x, y, radius, color);
		}
	}

}

void test_triangles(uint16_t color) {
	int n, i, cx = tft_width / 2, cy = tft_height / 2;

	tft_fill_screen(COLOR_BLACK);

	n = min(cx, cy);
	for (i = 0; i < n; i += 5) {
		tft_draw_triangle(cx, cy - i, // peak
		cx - i, cy + i, // bottom left
		cx + i, cy + i, // bottom right
		color);
	}

}

void test_fill_triangles(uint16_t color) {
	int i, cx = tft_width / 2, cy = tft_height / 2;

	tft_fill_screen(COLOR_BLACK);

	for (i = min(cx, cy); i > 10; i -= 5) {
		tft_fill_triangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, color);
		tft_draw_triangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, color);
	}
}

void test_round_rects() {
	int w, i1, i2, red, step, cx = tft_width / 2, cy = tft_height / 2;

	tft_fill_screen(COLOR_WHITE);

	w = min(tft_width, tft_height);
	red = 0;
	step = (256 * 6) / w;
	for (i1 = 0; i1 < w; i1 += 6) {
		i2 = i1 / 2;
		red += step;
		tft_draw_round_rect(cx - i2, cy - i2, i1, i1, i1 / 8,
				color565(red, 0, 0));
	}
}

void test_fill_round_rects() {
	int i1, i2, green, step, cx = tft_width / 2, cy = tft_height / 2;

	tft_fill_screen(COLOR_WHITE);

	green = 256;
	step = (256 * 6) / min(tft_width, tft_height);
	for (i1 = min(tft_width, tft_height); i1 > 20; i1 -= 6) {
		i2 = i1 / 2;
		green -= step;
		tft_fill_round_rect(cx - i2, cy - i2, i1, i1, i1 / 8,
				color565(0, green, 0));
	}

}
