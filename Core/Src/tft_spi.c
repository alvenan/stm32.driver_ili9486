/*
 * spi.c
 *
 *  Created on: Oct 9, 2021
 *      Author: alvenan
 */

#include "tft_spi.h"

static SPI_HandleTypeDef *tft_spi_handler;
static GPIO_TypeDef *tft_spi_cs_port;
static GPIO_TypeDef *tft_spi_dc_port;
static GPIO_TypeDef *tft_spi_rst_port;
static uint16_t tft_spi_cs_pin;
static uint16_t tft_spi_dc_pin;
static uint16_t tft_spi_rst_pin;

void tft_send_cmd(uint8_t cmd) {
	tft_spi_dc_cmd(tft_spi_dc_port, tft_spi_dc_pin);
	tft_spi_cs_on(tft_spi_cs_port, tft_spi_cs_pin);
	tft_spi_transmit(tft_spi_handler, cmd);
	tft_spi_cs_off(tft_spi_cs_port, tft_spi_cs_pin);
}

void tft_send_data(uint8_t data) {
	tft_spi_dc_data(tft_spi_dc_port, tft_spi_dc_pin);
	tft_spi_cs_on(tft_spi_cs_port, tft_spi_cs_pin);
	tft_spi_transmit(tft_spi_handler, data);
	tft_spi_cs_off(tft_spi_cs_port, tft_spi_cs_pin);
}

void tft_reset_on() {
	tft_spi_rst_on(tft_spi_rst_port, tft_spi_rst_pin);
}

void tft_reset_off() {
	tft_spi_rst_off(tft_spi_rst_port, tft_spi_rst_pin);
}

void tft_interface_init(SPI_HandleTypeDef *spi, GPIO_TypeDef *cs_port,
		uint16_t cs_pin, GPIO_TypeDef *dc_port, uint16_t dc_pin,
		GPIO_TypeDef *rst_port, uint16_t rst_pin) {

	tft_spi_handler = spi;
	tft_spi_cs_port = cs_port;
	tft_spi_cs_pin = cs_pin;
	tft_spi_dc_port = dc_port;
	tft_spi_dc_pin = dc_pin;
	tft_spi_rst_port = rst_port;
	tft_spi_rst_pin = rst_pin;

	tft_spi_cs_off(tft_spi_cs_port, tft_spi_cs_pin);
}
