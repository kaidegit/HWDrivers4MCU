#ifndef __LCD_H
#define __LCD_H

#include "main.h"

/// choose to display characters or a picture
#define    USE_ASCII_FONT_LIB             1       //使用ASCII字符显示请打开该宏(值设为1)
#define    USE_PICTURE_DISPLAY            0       //使用图片显示请打开该宏(值设为1)

///define the LCD control pins
#define LCD_PWR_GPIO_Port
#define LCD_PWR_Pin
#define LCD_WR_RS_GPIO_Port
#define LCD_WR_RS_Pin
#define LCD_RST_GPIO_Port
#define LCD_RST_Pin

/// define the width and height of the LCD
#define LCD_Width 240
#define LCD_Height 240

///define the buffer of the lcd 
#define LCD_TOTAL_BUF_SIZE    (240*240*2)
#define LCD_Buf_Size 1152

/// define the color
#define WHITE        0xFFFF    //白色
#define YELLOW       0xFFE0    //黄色
#define BRRED        0XFC07    //棕红色
#define PINK         0XF81F    //粉色
#define RED          0xF800    //红色
#define BROWN        0XBC40    //棕色
#define GRAY         0X8430    //灰色
#define GBLUE        0X07FF    //兰色
#define GREEN        0x07E0    //绿色
#define BLUE         0x001F    //蓝色
#define BLACK        0x0000    //黑色

/**
 * @brief	LCD底层SPI发送数据函数
 * @param   data 数据的起始地址
 * @param   size 发送数据字节数
 */
inline void LCD_SPI_Send(uint8_t *data, uint16_t size) {
   #error write the spi transmit function here
   // for STM32 HAL
   // HAL_SPI_Transmit(&hspi2, data, size, 0xff);
}

/**
 * @brief write the lcd power pin
 * 
 * @param state the state of the power pin
 */
inline void LCD_PWR(uint8_t state){
   #error write the pin control function here
   // for STM32 HAL
   // if (state){
   //    HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_SET)
   // } else {
   //    HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_RESET);
   // }
}

/**
 * @brief write the lcd wr/rs pin
 * 
 * @param state the state of the lcd wr/rs pin
 */
inline void LCD_WR_RS(uint8_t state){
   #error write the pin control function here
   // for STM32 HAL
   // if (state){
   //    HAL_GPIO_WritePin(LCD_WR_RS_GPIO_Port,LCD_WR_RS_Pin,GPIO_PIN_SET)
   // } else {
   //    HAL_GPIO_WritePin(LCD_WR_RS_GPIO_Port,LCD_WR_RS_Pin,GPIO_PIN_RESET);
   // }
}

/**
 * @brief write the lcd reset pin 
 * 
 * @param state the state of the lcd reset
 */
inline void LCD_RST(uint8_t state){
   #error write the pin control function here
   // for STM32 HAL
   // if (state){
   //    HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET)
   // } else {
   //    HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET);
   // }
}

/**
 * @brief delay millisecond
 * 
 * @param ms 
 */
inline void Delay_ms(uint16_t ms){
   #error write the millisecond delay function here 
   // for STM32 HAL
   // HAL_Delay(ms);
}

/**
 * @brief	写命令到LCD
 * @param   cmd —— 需要发送的命令
 * @return  none
 */
void LCD_Write_Cmd(uint8_t cmd);

/**
 * @brief	写数据到LCD
 * @param 	dat —— 需要发送的数据
 * @return  none
 */
void LCD_Write_Data(uint8_t dat);

/**
 * @brief		写16位的数据（两个字节）到LCD
 * @param   dat —— 需要发送的16bit数据
 * @return  none
 */
void LCD_Write_2Byte(const uint16_t dat);

/**
 * @brief	设置数据写入LCD缓存区域
 * @param   x1,y1	—— 起点坐标
 * @param   x2,y2	—— 终点坐标
 * @return  none
 */
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * @breif	打开LCD显示背光
 * @param   none
 * @return  none
 */
void LCD_DisplayOn(void);

/**
 * @brief	关闭LCD显示背光
 * @param   none
 * @return  none
 */
void LCD_DisplayOff(void);

/**
 * @brief	以一种颜色清空LCD屏
 * @param   color —— 清屏颜色(16bit)
 * @return  none
 */
void LCD_Clear(uint16_t color);

/**
 * @brief	LCD初始化
 * @param   none
 * @return  none
 */
void LCD_Init(void);            //LCD初始化函数

/**
 * @brief		带颜色画点函数
 * @param   x,y	—— 画点坐标
 * @return  none
 */
void LCD_Draw_ColorPoint(uint16_t x, uint16_t y, uint16_t color);

/**
 * @brief		带颜色画线函数(直线、斜线)
 * @param   x1,y1	起点坐标
 * @param   x2,y2	终点坐标
 * @return  none
 */
void LCD_Draw_ColorLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

/**
 * @brief	带颜色画矩形函数
 * @param   x1,y1 —— 矩形起始点
 * @param	x2,y2 —— 矩形终点
 * @param	color	—— 颜色
 * @retval	none
 */
void LCD_Draw_ColorRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

/**
 * @brief	带颜色画圆函数
 * @param   x1,x2 —— 圆心坐标
 * @param	r —— 半径
 * @param	color	—— 颜色
 * @retval	none
 */
void LCD_Draw_ColorCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);

/**
 * @brief	以一种颜色填充/清空某个矩形区域
 * @param   color —— 清屏颜色(16bit)
 * @return  none
 */
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

#if USE_ASCII_FONT_LIB

/**
 * @brief	显示一个ASCII码字符
 * @param   x,y		显示起始坐标
 * @param   ch		需要显示的字符
 * @param   size	字体大小(支持16/24/32号字体)
 * @return  none
 * @note	需要font.h字库文件的支持
 */
void LCD_ShowChar(uint16_t x, uint16_t y, char ch, uint16_t back_color, uint16_t font_color, uint8_t font_size);

/**
 * @brief		显示一个ASCII码字符串
 * @param   x,y		显示起始坐标
 * @param   str		需要显示的字符串
 * @param   size	字体大小(支持16/24/32号字体)
 * @return  none
 * @note		1. 需要font.h字库文件的支持
 * 					2. 超过指定width不显示超过的字符
 */
void LCD_ShowCharStr(uint16_t x, uint16_t y, uint8_t max_width, char* str, uint16_t back_color, uint16_t font_color, uint8_t font_size);

#endif /* USE_ASCII_FONT_LIB */

/**
 * @breif		带颜色画六芒星函数
 * @param   x,y —— 六芒星中心点
 * @param		r —— 六芒星半径
 * @param		color	—— 颜色
 * @retval	none
 */
void LCD_Draw_ColorSixPointStar(uint16_t x, uint16_t y, uint8_t r, uint16_t color);

#if USE_PICTURE_DISPLAY

/**
 * @brief	显示图片函数
 * @param   x,y	    —— 起点坐标
 * @param   width	—— 图片宽度
 * @param   height	—— 图片高度
 * @param   p       —— 图片缓存数据起始地址
 * @return  none
 * @note	Image2Lcd取模方式：C语言数据/水平扫描/16位真彩色(RGB565)/高位在前，其他的不选
 */
void LCD_Show_Image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p);

#endif /*USE_PICTURE_DISPLAY */

#endif //BEARPI_LCD_H
