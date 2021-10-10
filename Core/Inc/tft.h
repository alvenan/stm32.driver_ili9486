/*
 * tft.h
 *
 *  Created on: Oct 9, 2021
 *      Author: alvenan
 */

#ifndef TFT_H_
#define TFT_H_

#include "stm32f4xx_hal.h"

#define TFT_SPI
#define TFT_ILI9486

#define WIDTH       320
#define HEIGHT      480
#define PIXEL_COUNT	WIDTH * HEIGHT

#define TFTCMD_NOP				0x00
#define TFTCMD_SLEEP_OUT		0x11
#define TFTCMD_DISPLAY_ON		0x29
#define TFTCMD_COLUMN_ADDR		0x2A
#define TFTCMD_PAGE_ADDR		0x2B
#define TFTCMD_GRAM				0x2C
#define TFTCMD_MAC			    0x36
#define TFTCMD_PIXEL_FORMAT    	0x3A
#define TFTCMD_POWER3			0xC2
#define TFTCMD_VCOM1			0xC5
#define TFTCMD_PGAMMA			0xE0
#define TFTCMD_NGAMMA			0xE1
#define TFTCMD_GAMMA_CTRL1		0xE2

#define MEMCONTROL  0x36
#define MADCTL_MY  	0x80
#define MADCTL_MX  	0x40
#define MADCTL_MV  	0x20
#define MADCTL_ML  	0x10
#define MADCTL_RGB 	0x00
#define MADCTL_BGR 	0x08
#define MADCTL_MH  	0x04

#define COLOR_BLACK           0x0000
#define COLOR_NAVY            0x000F
#define COLOR_DGREEN          0x03E0
#define COLOR_DCYAN           0x03EF
#define COLOR_MAROON          0x7800
#define COLOR_PURPLE          0x780F
#define COLOR_OLIVE           0x7BE0
#define COLOR_LGRAY           0xC618
#define COLOR_DGRAY           0x7BEF
#define COLOR_BLUE            0x001F
#define COLOR_BLUE2			  0x051D
#define COLOR_GREEN           0x07E0
#define COLOR_GREEN2		  0xB723
#define COLOR_GREEN3		  0x8000
#define COLOR_CYAN            0x07FF
#define COLOR_RED             0xF800
#define COLOR_MAGENTA         0xF81F
#define COLOR_YELLOW          0xFFE0
#define COLOR_WHITE           0xFFFF
#define COLOR_ORANGE          0xFD20
#define COLOR_GREENYELLOW     0xAFE5
#define COLOR_BROWN 		  0XBC40
#define COLOR_BRRED 		  0XFC07

#define tft_delay(x) HAL_Delay(x);
#define swap(x,y) { uint32_t tmp = x; x = y; y = tmp; }
#define min(x,y)  ( ( x < y ) ? x : y )

void tft_init(SPI_HandleTypeDef *spi,
		GPIO_TypeDef *cs_port, uint16_t cs_pin,
		GPIO_TypeDef *dc_port, uint16_t dc_pin,
		GPIO_TypeDef *rst_port, uint16_t rst_pin,
		uint32_t width, uint32_t height);
void tft_set_rotation(uint8_t rotate);
void tft_cursor_position(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void tft_fill_rectxy(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void tft_fill_screen(uint16_t color);
void tft_draw_horizontal_line(uint16_t x, uint16_t y, uint16_t w, uint16_t color);
void tft_draw_vertical_line(uint16_t x, uint16_t y, uint16_t w, uint16_t color);
void tft_draw_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void tft_draw_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void tft_fill_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
// Tests
void test_fill_screen();
void test_lines(uint16_t color);
void test_lines2(uint16_t color1, uint16_t color2);
void test_rects(uint16_t color);
void test_fill_rects(uint16_t color1, uint16_t color2);
void test_circles(uint8_t radius, uint16_t color);
void test_triangles(uint16_t color);
void test_fill_triangles(uint16_t color);
#endif /* TFT_H_ */
