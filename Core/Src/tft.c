/*
 * tft.c
 *
 *  Created on: Oct 9, 2021
 *      Author: alvenan
 */

#include "tft.h"
#ifdef TFT_SPI
#include "tft_spi.h"
#endif


static TFT *tft;
static uint8_t rot_num = 1;
static uint32_t tft_width, tft_height, tft_pixel_count;

void tft_init(SPI_HandleTypeDef *spi,
		GPIO_TypeDef *cs_port, uint16_t cs_pin,
		GPIO_TypeDef *dc_port, uint16_t dc_pin,
		GPIO_TypeDef *rst_port, uint16_t rst_pin,
		uint32_t width, uint32_t height) {


	tft_width = width;
	tft_height = height;
	tft_pixel_count = width * height;

	tft = tft_interface_init(spi, cs_port, cs_pin, dc_port, dc_pin, rst_port, rst_pin);

	tft_rst_off(tft);
	tft_rst_on(tft);
	tft_rst_off(tft);

	tft_send_cmd(tft, TFTCMD_NOP);
	tft_send_data(tft, 0x00);
	tft_send_cmd(tft, TFTCMD_SLEEP_OUT);

	tft_delay(150);

	tft_send_cmd(tft, TFTCMD_PIXEL_FORMAT);
	tft_send_data(tft, 0x55);

	tft_send_cmd(tft, TFTCMD_MAC);
	tft_send_data(tft, 0x48);

	tft_send_cmd(tft, TFTCMD_POWER3);
	tft_send_data(tft, 0x44);

	tft_send_cmd(tft, TFTCMD_VCOM1);
	tft_send_data(tft, 0x00); tft_send_data(tft, 0x00);
	tft_send_data(tft, 0x00); tft_send_data(tft, 0x00);


	tft_send_cmd(tft, TFTCMD_PGAMMA);
	tft_send_data(tft, 0x0f); tft_send_data(tft, 0x1f);
	tft_send_data(tft, 0x1c); tft_send_data(tft, 0x0c);
	tft_send_data(tft, 0x0f); tft_send_data(tft, 0x08);
	tft_send_data(tft, 0x48); tft_send_data(tft, 0x98);
	tft_send_data(tft, 0x37); tft_send_data(tft, 0x0a);
	tft_send_data(tft, 0x13); tft_send_data(tft, 0x04);
	tft_send_data(tft, 0x11); tft_send_data(tft, 0x0d);
	tft_send_data(tft, 0x00);

	tft_send_cmd(tft, TFTCMD_NGAMMA);
	tft_send_data(tft, 0x0f); tft_send_data(tft, 0x32);
	tft_send_data(tft, 0x2e); tft_send_data(tft, 0x0b);
	tft_send_data(tft, 0x0d); tft_send_data(tft, 0x05);
	tft_send_data(tft, 0x47); tft_send_data(tft, 0x75);
	tft_send_data(tft, 0x37); tft_send_data(tft, 0x06);
	tft_send_data(tft, 0x10); tft_send_data(tft, 0x03);
	tft_send_data(tft, 0x24); tft_send_data(tft, 0x20);
	tft_send_data(tft, 0x00);

	tft_send_cmd(tft, TFTCMD_GAMMA_CTRL1);
	tft_send_data(tft, 0x0f); tft_send_data(tft, 0x32);
	tft_send_data(tft, 0x2e); tft_send_data(tft, 0x0b);
	tft_send_data(tft, 0x0d); tft_send_data(tft, 0x05);
	tft_send_data(tft, 0x47); tft_send_data(tft, 0x75);
	tft_send_data(tft, 0x37); tft_send_data(tft, 0x06);
	tft_send_data(tft, 0x10); tft_send_data(tft, 0x03);
	tft_send_data(tft, 0x24); tft_send_data(tft, 0x20);
	tft_send_data(tft, 0x00);

	tft_send_cmd(tft, TFTCMD_SLEEP_OUT);
	tft_send_cmd(tft, TFTCMD_DISPLAY_ON);

	tft_delay(150);

}

void tft_set_rotation(uint8_t rotate) {
	tft_send_cmd(tft, MEMCONTROL);
	switch(rotate)
	{
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
void tft_cursor_position(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {

  tft_send_cmd(tft, TFTCMD_COLUMN_ADDR);
  tft_send_data(tft, x1 >> 8);
  tft_send_data(tft, x1 & 0xff);
  tft_send_data(tft, x2 >> 8);
  tft_send_data(tft, x2 & 0xff);

  tft_send_cmd(tft, TFTCMD_PAGE_ADDR);
  tft_send_data(tft, y1 >> 8);
  tft_send_data(tft, y1 & 0xff);
  tft_send_data(tft, y2 >> 8);
  tft_send_data(tft, y2 & 0xff);

  tft_send_cmd(tft, TFTCMD_GRAM);
}

void tft_fill_screen(uint16_t color) {

	if(rot_num == 1 || rot_num==3)
		tft_cursor_position(0, 0, tft_width-1, tft_height-1);
	else if(rot_num==2 || rot_num==4)
		tft_cursor_position(0, 0, tft_height-1, tft_width-1);


	for(uint32_t n = tft_pixel_count; n > 0; n--) {
		tft_send_data(tft, color>>8);
		tft_send_data(tft, color&0xff);
	}
}

void test_fill_screen() {

	tft_fill_screen(COLOR_BLACK);
	tft_fill_screen(COLOR_RED);
	tft_fill_screen(COLOR_GREEN);
	tft_fill_screen(COLOR_BLUE);
	tft_fill_screen(COLOR_BLACK);
}
