#ifndef __LCD_H
#define __LCD_H

#include "stdlib.h"
#include "main.h"

void LCD_Init(void);

void LCD_Clear(uint16_t color);

void LCD_ShowImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p);

#define WHITE           0xFFFF
#define BLACK           0x0000
#define BLUE            0x001F
#define BRED            0XF81F
#define GRED            0XFFE0
#define GBLUE           0X07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define GREEN           0x07E0
#define CYAN            0x7FFF
#define YELLOW          0xFFE0
#define BROWN           0XBC40
#define BRRED           0XFC07
#define GRAY            0X8430

#endif




