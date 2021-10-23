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

#define tft_spi_dc_cmd(x,y)		HAL_GPIO_WritePin(x, y, GPIO_PIN_RESET)
#define tft_spi_dc_data(x,y)	HAL_GPIO_WritePin(x, y, GPIO_PIN_SET)
#define tft_spi_cs_on(x,y)		HAL_GPIO_WritePin(x, y, GPIO_PIN_RESET)
#define tft_spi_cs_off(x,y)		HAL_GPIO_WritePin(x, y, GPIO_PIN_SET)
#define tft_spi_rst_on(x,y)		HAL_GPIO_WritePin(x, y, GPIO_PIN_RESET)
#define tft_spi_rst_off(x,y)	HAL_GPIO_WritePin(x, y, GPIO_PIN_SET)
#define tft_spi_transmit(x,y)	HAL_SPI_Transmit(x, &y, SPI_SIZE8, SPI_TIMEOUT)
#define tft_spi_transmit16(x,y)	HAL_SPI_Transmit(x, &y, SPI_SIZE16, SPI_TIMEOUT)

void tft_send_cmd(uint8_t cmd);
void tft_send_data(uint8_t data);
void tft_reset_on();
void tft_reset_off();
void tft_interface_init(SPI_HandleTypeDef *spi, GPIO_TypeDef *cs_port,
		uint16_t cs_pin, GPIO_TypeDef *dc_port, uint16_t dc_pin,
		GPIO_TypeDef *rst_port, uint16_t rst_pin);

#endif /* TFT_SPI_H_ */
