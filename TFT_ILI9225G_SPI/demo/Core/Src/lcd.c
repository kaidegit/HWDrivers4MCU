#include "lcd.h"
#include "stdlib.h"
#include "usart.h"
#include "spi.h"

#define LCD_Height  220
#define LCD_Width  176

void SPI_SendByte(uint8_t dat) {
    HAL_SPI_Transmit(&hspi2, &dat, 1, 0xff);
}

void delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}

void Set_CS_Low() {
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

void Set_CS_High() {
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void Set_AO_Low() {
    HAL_GPIO_WritePin(LCD_AO_GPIO_Port, LCD_AO_Pin, GPIO_PIN_RESET);
}

void Set_AO_High() {
    HAL_GPIO_WritePin(LCD_AO_GPIO_Port, LCD_AO_Pin, GPIO_PIN_SET);
}

void Set_RST_Low() {
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
}

void Set_RST_High() {
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
}

void LCD_WriteComm(uint8_t i) {
    Set_CS_Low();
    Set_AO_Low();
    SPI_SendByte(i);
    Set_CS_High();
}

void LCD_WriteData(uint8_t i) {
    Set_CS_Low();
    Set_AO_High();
    SPI_SendByte(i);
    Set_CS_High();
}

void LCD_RESET(void) {
    Set_RST_High();
    delay_ms(50);
    Set_RST_Low();
    delay_ms(100);
    Set_RST_High();
    delay_ms(50);
}

void LCD_Init(void) {
    LCD_RESET();
//----------------------------------End ST7775R Reset Sequence ------------------------------------//
//------------------------------------Display Control Setting----------------------------------------------//
    LCD_WriteComm(0x01);
    LCD_WriteData(0x01);
    LCD_WriteData(0x1C);
    LCD_WriteComm(0x02);
    LCD_WriteData(0x01);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x03);
    LCD_WriteData(0x10);
    LCD_WriteData(0x30);
    LCD_WriteComm(0x08);
    LCD_WriteData(0x08);
    LCD_WriteData(0x08);
    LCD_WriteComm(0x0C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x0F);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteComm(0x20);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x21);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
//-----------------------------------End Display Control setting-----------------------------------------//
//-------------------------------- Power Control Registers Initial --------------------------------------//
    LCD_WriteComm(0x10);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x11);
    LCD_WriteData(0x1B);
    LCD_WriteData(0x41);
    LCD_WriteComm(0x12);                     //VCI
    LCD_WriteData(0x20);
    LCD_WriteData(0x0E);     //VCI
    LCD_WriteComm(0x13);
    LCD_WriteData(0x00);
    LCD_WriteData(0x52);
    LCD_WriteComm(0x14);
    LCD_WriteData(0x4B);
    LCD_WriteData(0x5C);
//---------------------------------End Power Control Registers Initial -------------------------------//
    delay_ms(100);
//----------------------------------Display Windows 176 X 220----------------------------------------//
    LCD_WriteComm(0x30);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x31);
    LCD_WriteData(0x00);
    LCD_WriteData(0xDB);
    LCD_WriteComm(0x32);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x33);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x34);
    LCD_WriteData(0x00);
    LCD_WriteData(0xDB);
    LCD_WriteComm(0x35);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x36);
    LCD_WriteData(0x00);
    LCD_WriteData(0xAF);
    LCD_WriteComm(0x37);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x38);
    LCD_WriteData(0x00);
    LCD_WriteData(0xDB);
    LCD_WriteComm(0x39);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
//----------------------------------End Display Windows 176 X 220----------------------------------//
    delay_ms(10);
    LCD_WriteComm(0xff);
    LCD_WriteData(0x00);
    LCD_WriteData(0x03);
//-------------------------------------Gamma Cluster Setting-------------------------------------------//
    LCD_WriteComm(0x50);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x51);
    LCD_WriteData(0x03);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x52);
    LCD_WriteData(0x01);
    LCD_WriteData(0x03);
    LCD_WriteComm(0x53);
    LCD_WriteData(0x20);
    LCD_WriteData(0x11);
    LCD_WriteComm(0x54);
    LCD_WriteData(0x07);
    LCD_WriteData(0x03);
    LCD_WriteComm(0x55);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x56);
    LCD_WriteData(0x04);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x57);
    LCD_WriteData(0x01);
    LCD_WriteData(0x07);
    LCD_WriteComm(0x58);
    LCD_WriteData(0x20);
    LCD_WriteData(0x11);
    LCD_WriteComm(0x59);
    LCD_WriteData(0x07);
    LCD_WriteData(0x03);
//---------------------------------------End Gamma Setting---------------------------------------------//
    LCD_WriteComm(0xB0);
    LCD_WriteData(0x1d);
    LCD_WriteData(0x01);
//---------------------------------------End Vcom Setting---------------------------------------------//
    LCD_WriteComm(0xff);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x07);
    LCD_WriteData(0x10);
    LCD_WriteData(0x17);
    delay_ms(200);
}

void LCD_SetDrawArea(uint16_t Xstart, uint16_t Xend, uint16_t Ystart, uint16_t Yend) //reentrant
{
    LCD_WriteComm(0x36);
    LCD_WriteData(0x00);
    LCD_WriteData(Xend); //HEA7-0
    LCD_WriteComm(0x37);
    LCD_WriteData(0x00);
    LCD_WriteData(Xstart); // HSA7-0
    LCD_WriteComm(0x38);
    LCD_WriteData(0x00);
    LCD_WriteData(Yend); // VEA7-0
    LCD_WriteComm(0x39);
    LCD_WriteData(0x00);
    LCD_WriteData(Ystart); // VSA7-0
    LCD_WriteComm(0x20);
    LCD_WriteData(0x00);
    LCD_WriteData(Xstart);
    LCD_WriteComm(0x21);
    LCD_WriteData(0x00);
    LCD_WriteData(Ystart);
    LCD_WriteData(0x00);
    LCD_WriteComm(0x22);
}

void LCD_Clear(uint16_t color) {
    uint16_t i, j;
    LCD_SetDrawArea(0, LCD_Width - 1, 0, LCD_Height - 1);

    Set_CS_Low();
    Set_AO_High();

    for (i = 0; i < LCD_Height; i++) {
        for (j = 0; j < LCD_Width; j++) {
            SPI_SendByte(color >> 8);
            SPI_SendByte(color);
        }
    }
    Set_CS_High();
}

void LCD_ShowImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p) {
    uint32_t img_size = width * height * 2;        //图片所占字节数
    uint32_t remain_size = img_size;            //图片每次发送后剩余的字节数

    if (x + width > LCD_Width || y + height > LCD_Height) {
        return;
    }

    LCD_SetDrawArea(x, x + width - 1, y, y + height - 1);

    Set_CS_Low();
    Set_AO_High();

    for (int i = 0; i <= img_size / 65536; i++) {
        if (remain_size / 65536 >= 1) {
            HAL_SPI_Transmit(&hspi2, p, 65535, 0xff);
            p += 65535;
            remain_size -= 65535;
        } else {
            HAL_SPI_Transmit(&hspi2, p, remain_size % 65535, 0xff);
        }
    }

    Set_CS_High();
}