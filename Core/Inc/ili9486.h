#ifndef __ILI9486_H
#define __ILI9486_H

//List of includes
#include <stdbool.h>
//** CHANGE BASED ON STM32 CHIP F4/F7/F1...**//
#include "stm32f4xx_hal.h"   

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//LCD dimensions defines
#define ILI9486_WIDTH       320
#define ILI9486_HEIGHT      480
#define ILI9486_PIXEL_COUNT	ILI9486_WIDTH * ILI9486_HEIGHT
//ILI9486 LCD commands
#define ILI9486_MODE_CONTROL				0x00
#define ILI9486_RESET			 		    0x01
#define ILI9486_SLEEP_OUT		  			0x11
#define ILI9486_GAMMA			    		0x26
#define ILI9486_DISPLAY_OFF					0x28
#define ILI9486_DISPLAY_ON					0x29
#define ILI9486_COLUMN_ADDR					0x2A
#define ILI9486_PAGE_ADDR			  		0x2B
#define ILI9486_GRAM				    	0x2C
#define ILI9486_TEARING_OFF					0x34
#define ILI9486_TEARING_ON					0x35
#define ILI9486_DISPLAY_INVERSION			0xb4
#define ILI9486_MAC			        		0x36
#define ILI9486_PIXEL_FORMAT    			0x3A
#define ILI9486_WDB			    	  		0x51
#define ILI9486_WCD				      		0x53
#define ILI9486_RGB_INTERFACE   			0xB0
#define ILI9486_FRC					    	0xB1
#define ILI9486_BPC					    	0xB5
#define ILI9486_DFC				 	    	0xB6
#define ILI9486_Entry_Mode_Set				0xB7
#define ILI9486_POWER1						0xC0
#define ILI9486_POWER2						0xC1
#define ILI9486_POWER3						0xC2
#define ILI9486_VCOM1						0xC5
#define ILI9486_VCOM2						0xC7
#define ILI9486_POWERA						0xCB
#define ILI9486_POWERB						0xCF
#define ILI9486_PGAMMA						0xE0
#define ILI9486_NGAMMA						0xE1
#define ILI9486_GAMMA_CTRL1					0xE2
#define ILI9486_DTCA						0xE8
#define ILI9486_DTCB						0xEA
#define ILI9486_POWER_SEQ					0xED
#define ILI9486_3GAMMA_EN					0xF2
#define ILI9486_INTERFACE					0xF6
#define ILI9486_PRC				   	  		0xF7
#define ILI9486_VERTICAL_SCROLL 			0x33

#define ILI9486_MEMCONTROL  0x36
#define ILI9486_MADCTL_MY  	0x80
#define ILI9486_MADCTL_MX  	0x40
#define ILI9486_MADCTL_MV  	0x20
#define ILI9486_MADCTL_ML  	0x10
#define ILI9486_MADCTL_RGB 	0x00
#define ILI9486_MADCTL_BGR 	0x08
#define ILI9486_MADCTL_MH  	0x04

//List of colors
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

//Functions defines Macros
#define swap(a, b) { int16_t t = a; a = b; b = t; }
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define min(a,b) (((a)<(b))?(a):(b))

//***** Functions prototypes *****//
//1. Write Command to LCD
void ILI9486_SendCommand(uint8_t com);
//2. Write data to LCD
void ILI9486_SendData(uint8_t data);
//2.2 Write multiple/DMA
void ILI9486_SendData_Multi(uint16_t Colordata, uint32_t size);


//3. Set cursor position
void ILI9486_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
//4. Initialise function
void ILI9486_Init(SPI_HandleTypeDef *spiLcdHandle, GPIO_TypeDef *csPORT, uint16_t csPIN, GPIO_TypeDef *dcPORT, uint16_t dcPIN, GPIO_TypeDef *resetPORT, uint16_t resetPIN);
//5. Write data to a single pixel
void ILI9486_DrawPixel(uint16_t x, uint16_t y, uint16_t color); //Draw single pixel to ILI9341
//6. Fill the entire screen with a background color
void ILI9341_Fill(uint16_t color); //Fill entire ILI9341 with color
//7. Rectangle drawing functions
void ILI9341_Fill_Rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, uint16_t color);
//8. Circle drawing functions
void ILI9341_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
static void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
static void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
void ILI9486_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
//9. Line drawing functions
void ILI9486_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void ILI9486_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void ILI9486_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
//10. Triangle drawing
void ILI9486_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void ILI9486_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
//11. Text printing functions
void ILI9486_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
void ILI9486_printText(char text[], int16_t x, int16_t y, uint16_t color, uint16_t bg, uint8_t size);
//12. Image print (RGB 565, 2 bytes per pixel)
void ILI9486_printImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t *data, uint32_t size);
//13. Set screen rotation
void ILI9341_setRotation(uint8_t rotate);
//14. Get screen rotation
uint8_t ILI9486_getRotation(void);


#endif
