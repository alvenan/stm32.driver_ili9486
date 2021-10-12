/*
 * spi.h
 *
 *  Created on: Oct 9, 2021
 *      Author: alvenan
 */

#ifndef TFT_SPI_H_
#define TFT_SPI_H_

#include "tft.h"
#include <stdlib.h>

#define SPI_SIZE8 	1
#define SPI_SIZE16 	2
#define SPI_TIMEOUT 5

#define tft_spi_dc_cmd(x)		HAL_GPIO_WritePin(x->dc_port, x->dc_pin, GPIO_PIN_RESET)
#define tft_spi_dc_data(x)		HAL_GPIO_WritePin(x->dc_port, x->dc_pin, GPIO_PIN_SET)
#define tft_spi_cs_on(x)		HAL_GPIO_WritePin(x->cs_port, x->cs_pin, GPIO_PIN_RESET)
#define tft_spi_cs_off(x)		HAL_GPIO_WritePin(x->cs_port, x->cs_pin, GPIO_PIN_SET)
#define tft_spi_rst_on(x)		HAL_GPIO_WritePin(x->rst_port, x->rst_pin, GPIO_PIN_RESET)
#define tft_spi_rst_off(x)		HAL_GPIO_WritePin(x->rst_port, x->rst_pin, GPIO_PIN_SET)
#define tft_spi_transmit(x,y)	HAL_SPI_Transmit(x->spi_handler, &y, SPI_SIZE8, SPI_TIMEOUT)
#define tft_spi_transmit16(x,y)	HAL_SPI_Transmit(x->spi_handler, &y, SPI_SIZE16, SPI_TIMEOUT)

typedef struct {
	SPI_HandleTypeDef *spi_handler;
	GPIO_TypeDef *cs_port;
	GPIO_TypeDef *dc_port;
	GPIO_TypeDef *rst_port;
	uint16_t cs_pin;
	uint16_t dc_pin;
	uint16_t rst_pin;
} TFT;

void tft_send_cmd(TFT *tft_struct, uint8_t cmd);
void tft_send_data(TFT *tft_struct, uint8_t data);
TFT* tft_interface_init(SPI_HandleTypeDef *spi, GPIO_TypeDef *cs_port,
		uint16_t cs_pin, GPIO_TypeDef *dc_port, uint16_t dc_pin,
		GPIO_TypeDef *rst_port, uint16_t rst_pin);

#endif /* TFT_SPI_H_ */
