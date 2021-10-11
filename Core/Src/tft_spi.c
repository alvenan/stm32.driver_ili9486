/*
 * spi.c
 *
 *  Created on: Oct 9, 2021
 *      Author: alvenan
 */

#include "tft_spi.h"

void tft_send_cmd(TFT *tft, uint8_t cmd) {
	tft_dc_cmd(tft); tft_cs_on(tft);
	tft_spi_transmit(tft, cmd);
	tft_cs_off(tft);
}

void tft_send_data(TFT *tft, uint8_t data) {
	tft_dc_data(tft); tft_cs_on(tft);
	tft_spi_transmit(tft, data);
	tft_cs_off(tft);
}

void tft_send_data16(TFT *tft, uint16_t data) {
	tft_dc_data(tft); tft_cs_on(tft);
	tft_spi_transmit16(tft, data);
	tft_cs_off(tft);
}

TFT* tft_interface_init(SPI_HandleTypeDef *spi,
		GPIO_TypeDef *cs_port, uint16_t cs_pin,
		GPIO_TypeDef *dc_port, uint16_t dc_pin,
		GPIO_TypeDef *rst_port, uint16_t rst_pin) {

	TFT *tft = (TFT*) malloc(sizeof(TFT));

	tft->spi_handler = spi;
	tft->cs_port = cs_port;
	tft->cs_pin = cs_pin;
	tft->dc_port = dc_port;
	tft->dc_pin = dc_pin;
	tft->rst_port = rst_port;
	tft->rst_pin = rst_pin;

	tft_cs_off(tft);

	return tft;
}
