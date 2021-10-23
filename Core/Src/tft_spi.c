/*
 * spi.c
 *
 *  Created on: Oct 9, 2021
 *      Author: alvenan
 */

#include "tft_spi.h"

static SPI_HandleTypeDef *spi_handler;
static GPIO_TypeDef *cs_port;
static GPIO_TypeDef *dc_port;
static GPIO_TypeDef *rst_port;
static uint16_t cs_pin;
static uint16_t dc_pin;
static uint16_t rst_pin;

void tft_send_cmd(uint8_t cmd) {
	tft_spi_dc_cmd(dc_port, dc_pin);
	tft_spi_cs_on(cs_port, cs_pin);
	tft_spi_transmit(spi_handler, cmd);
	tft_spi_cs_off(cs_port, cs_pin);
}

void tft_send_data(uint8_t data) {
	tft_spi_dc_data(dc_port, dc_pin);
	tft_spi_cs_on(cs_port, cs_pin);
	tft_spi_transmit(spi_handler, data);
	tft_spi_cs_off(cs_port, cs_pin);
}

void tft_send_data16(uint16_t data) {
	tft_spi_dc_data(dc_port, dc_pin);
	tft_spi_cs_on(cs_port, cs_pin);
	tft_spi_transmit16(spi_handler, data);
	tft_spi_cs_off(cs_port, cs_pin);
}

void tft_reset_on() {
	tft_spi_rst_on(rst_port, rst_pin);
}

void tft_reset_off() {
	tft_spi_rst_off(rst_port, rst_pin);
}

void tft_interface_init(SPI_HandleTypeDef *tft_spi, GPIO_TypeDef *tft_cs_port,
		uint16_t tft_cs_pin, GPIO_TypeDef *tft_dc_port, uint16_t tft_dc_pin,
		GPIO_TypeDef *tft_rst_port, uint16_t tft_rst_pin) {

	spi_handler = tft_spi;
	cs_port = tft_cs_port;
	cs_pin = tft_cs_pin;
	dc_port = tft_dc_port;
	dc_pin = tft_dc_pin;
	rst_port = tft_rst_port;
	rst_pin = tft_rst_pin;

	tft_spi_cs_off(cs_port, cs_pin);
}
