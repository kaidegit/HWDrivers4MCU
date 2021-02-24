#include "lcd.h"
#include "font.h"

static uint8_t lcd_buf[LCD_Buf_Size];

void LCD_Write_Cmd(uint8_t cmd) {
    LCD_WR_RS(0);
    LCD_SPI_Send(&cmd, 1);
}

void LCD_Write_Data(uint8_t dat) {
    LCD_WR_RS(1);
    LCD_SPI_Send(&dat, 1);
}

void LCD_Write_2Byte(const uint16_t dat) {
    uint8_t data[2] = {0};

    data[0] = dat >> 8;
    data[1] = dat;

    LCD_WR_RS(1);
    LCD_SPI_Send(data, 2);
}

void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    LCD_Write_Cmd(0x2a);
    LCD_Write_Data(x1 >> 8);
    LCD_Write_Data(x1);
    LCD_Write_Data(x2 >> 8);
    LCD_Write_Data(x2);

    LCD_Write_Cmd(0x2b);
    LCD_Write_Data(y1 >> 8);
    LCD_Write_Data(y1);
    LCD_Write_Data(y2 >> 8);
    LCD_Write_Data(y2);

    LCD_Write_Cmd(0x2C);
}

void LCD_DisplayOn(void) {
    LCD_PWR(1);
}

void LCD_DisplayOff(void) {
    LCD_PWR(0);
}

void LCD_Clear(uint16_t color) {
    uint16_t i, j;
    uint8_t data[2] = {0};  //LCD屏幕色彩深度16bit，data[0]是颜色数据的高位，data[1]是颜色数据的低位
    
    data[0] = color >> 8;
    data[1] = color;

    LCD_Address_Set(0, 0, LCD_Width - 1, LCD_Height - 1);

    for (j = 0; j < LCD_Buf_Size / 2; j++) {
        lcd_buf[j * 2] = data[0];
        lcd_buf[j * 2 + 1] = data[1];
    }

    LCD_WR_RS(1);

    for (i = 0; i < (LCD_TOTAL_BUF_SIZE / LCD_Buf_Size); i++) {
        LCD_SPI_Send(lcd_buf, LCD_Buf_Size);
    }
}

void LCD_Init(void) {

    LCD_PWR(0);
    LCD_RST(0);
    Delay_ms(12);
    LCD_RST(1);
    Delay_ms(12);

    /* Sleep Out */
    LCD_Write_Cmd(0x11);
    /* wait for power stability */
    Delay_ms(12);

    /* Memory Data Access Control */
    LCD_Write_Cmd(0x36);
    LCD_Write_Data(0x00);

    /* RGB 5-6-5-bit  */
    LCD_Write_Cmd(0x3A);
    LCD_Write_Data(0x65);

    /* Porch Setting */
    LCD_Write_Cmd(0xB2);
    LCD_Write_Data(0x0C);
    LCD_Write_Data(0x0C);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x33);
    LCD_Write_Data(0x33);

    /*  Gate Control */
    LCD_Write_Cmd(0xB7);
    LCD_Write_Data(0x72);

    /* VCOM Setting */
    LCD_Write_Cmd(0xBB);
    LCD_Write_Data(0x3D);   //Vcom=1.625V

    /* LCM Control */
    LCD_Write_Cmd(0xC0);
    LCD_Write_Data(0x2C);

    /* VDV and VRH Command Enable */
    LCD_Write_Cmd(0xC2);
    LCD_Write_Data(0x01);

    /* VRH Set */
    LCD_Write_Cmd(0xC3);
    LCD_Write_Data(0x19);

    /* VDV Set */
    LCD_Write_Cmd(0xC4);
    LCD_Write_Data(0x20);

    /* Frame Rate Control in Normal Mode */
    LCD_Write_Cmd(0xC6);
    LCD_Write_Data(0x0F);    //60MHZ

    /* Power Control 1 */
    LCD_Write_Cmd(0xD0);
    LCD_Write_Data(0xA4);
    LCD_Write_Data(0xA1);

    /* Positive Voltage Gamma Control */
    LCD_Write_Cmd(0xE0);
    LCD_Write_Data(0xD0);
    LCD_Write_Data(0x04);
    LCD_Write_Data(0x0D);
    LCD_Write_Data(0x11);
    LCD_Write_Data(0x13);
    LCD_Write_Data(0x2B);
    LCD_Write_Data(0x3F);
    LCD_Write_Data(0x54);
    LCD_Write_Data(0x4C);
    LCD_Write_Data(0x18);
    LCD_Write_Data(0x0D);
    LCD_Write_Data(0x0B);
    LCD_Write_Data(0x1F);
    LCD_Write_Data(0x23);

    /* Negative Voltage Gamma Control */
    LCD_Write_Cmd(0xE1);
    LCD_Write_Data(0xD0);
    LCD_Write_Data(0x04);
    LCD_Write_Data(0x0C);
    LCD_Write_Data(0x11);
    LCD_Write_Data(0x13);
    LCD_Write_Data(0x2C);
    LCD_Write_Data(0x3F);
    LCD_Write_Data(0x44);
    LCD_Write_Data(0x51);
    LCD_Write_Data(0x2F);
    LCD_Write_Data(0x1F);
    LCD_Write_Data(0x1F);
    LCD_Write_Data(0x20);
    LCD_Write_Data(0x23);

    /* Display Inversion On */
    LCD_Write_Cmd(0x21);

    LCD_Write_Cmd(0x29);

    LCD_Address_Set(0, 0, LCD_Width - 1, LCD_Height - 1);

    LCD_Clear(WHITE);

    /*打开显示*/
    LCD_PWR(1);
}

void LCD_Draw_ColorPoint(uint16_t x, uint16_t y, uint16_t color) {
    LCD_Address_Set(x, y, x, y);
    LCD_Write_2Byte(color);
}

void LCD_Draw_ColorLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t i = 0;
    int16_t delta_x = 0, delta_y = 0;
    int8_t incx = 0, incy = 0;
    uint16_t distance = 0;
    uint16_t t = 0;
    uint16_t x = 0, y = 0;
    uint16_t x_temp = 0, y_temp = 0;


    if (y1 == y2) {
        /* 快速画水平线 */
        LCD_Address_Set(x1, y1, x2, y2);

        for (i = 0; i < x2 - x1; i++) {
            lcd_buf[2 * i] = color >> 8;
            lcd_buf[2 * i + 1] = color;
        }

        LCD_WR_RS(1);
        LCD_SPI_Send(lcd_buf, (x2 - x1) * 2);
        return;
    } else {
        /* 画斜线（Bresenham算法） */
        /* 计算两点之间在x和y方向的间距，得到画笔在x和y方向的步进值 */
        delta_x = x2 - x1;
        delta_y = y2 - y1;
        if (delta_x > 0) {
            //斜线(从左到右)
            incx = 1;
        } else if (delta_x == 0) {
            //垂直斜线(竖线)
            incx = 0;
        } else {
            //斜线(从右到左)
            incx = -1;
            delta_x = -delta_x;
        }
        if (delta_y > 0) {
            //斜线(从左到右)
            incy = 1;
        } else if (delta_y == 0) {
            //水平斜线(水平线)
            incy = 0;
        } else {
            //斜线(从右到左)
            incy = -1;
            delta_y = -delta_y;
        }

        /* 计算画笔打点距离(取两个间距中的最大值) */
        if (delta_x > delta_y) {
            distance = delta_x;
        } else {
            distance = delta_y;
        }

        /* 开始打点 */
        x = x1;
        y = y1;
        //第一个点无效，所以t的次数加一
        for (t = 0; t <= distance + 1; t++) {
            LCD_Draw_ColorPoint(x, y, color);

            /* 判断离实际值最近的像素点 */
            x_temp += delta_x;
            if (x_temp > distance) {
                //x方向越界，减去距离值，为下一次检测做准备
                x_temp -= distance;
                //在x方向递增打点
                x += incx;

            }
            y_temp += delta_y;
            if (y_temp > distance) {
                //y方向越界，减去距离值，为下一次检测做准备
                y_temp -= distance;
                //在y方向递增打点
                y += incy;
            }
        }
    }
}

void LCD_Draw_ColorRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    LCD_Draw_ColorLine(x1, y1, x2, y1, color);
    LCD_Draw_ColorLine(x1, y1, x1, y2, color);
    LCD_Draw_ColorLine(x1, y2, x2, y2, color);
    LCD_Draw_ColorLine(x2, y1, x2, y2, color);
}

void LCD_Draw_ColorCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
    /* Bresenham画圆算法 */
    int16_t a = 0, b = r;
    int16_t d = 3 - (r << 1);        //算法决策参数

    /* 如果圆在屏幕可见区域外，直接退出 */
    if (x - r < 0 || x + r > LCD_Width || y - r < 0 || y + r > LCD_Height) {
        return;
    }

    /* 开始画圆 */
    while (a <= b) {
        LCD_Draw_ColorPoint(x - b, y - a, color);
        LCD_Draw_ColorPoint(x + b, y - a, color);
        LCD_Draw_ColorPoint(x - a, y + b, color);
        LCD_Draw_ColorPoint(x - b, y - a, color);
        LCD_Draw_ColorPoint(x - a, y - b, color);
        LCD_Draw_ColorPoint(x + b, y + a, color);
        LCD_Draw_ColorPoint(x + a, y - b, color);
        LCD_Draw_ColorPoint(x + a, y + b, color);
        LCD_Draw_ColorPoint(x - b, y + a, color);
        a++;

        if (d < 0) {
            d += 4 * a + 6;
        } else {
            d += 10 + 4 * (a - b);
            b--;
        }

        LCD_Draw_ColorPoint(x + a, y + b, color);
    }
}

void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t i = 0;
    uint32_t size = 0, size_remain = 0;

    size = (x2 - x1 + 1) * (y2 - y1 + 1) * 2;

    if (size > LCD_Buf_Size) {
        size_remain = size - LCD_Buf_Size;
        size = LCD_Buf_Size;
    }

    LCD_Address_Set(x1, y1, x2, y2);

    while (1) {
        for (i = 0; i < size / 2; i++) {
            lcd_buf[2 * i] = color >> 8;
            lcd_buf[2 * i + 1] = color;
        }

        LCD_WR_RS(1);
        LCD_SPI_Send(lcd_buf, size);

        if (size_remain == 0)
            break;

        if (size_remain > LCD_Buf_Size) {
            size_remain = size_remain - LCD_Buf_Size;
        } else {
            size = size_remain;
            size_remain = 0;
        }
    }
}

#if USE_ASCII_FONT_LIB

void LCD_ShowChar(uint16_t x, uint16_t y, char ch, uint16_t back_color, uint16_t font_color, uint8_t font_size)
{
    int i = 0, j = 0;
    uint8_t temp = 0;
    uint8_t size = 0;
    uint8_t t = 0;

    /* 检测显示是否会越界 */
     if((x > (LCD_Width - font_size / 2)) || (y > (LCD_Height - font_size)))
         return;

    /* 根据字符大小设置显存操作区域 */
    LCD_Address_Set(x, y, x + font_size/2 - 1, y + font_size - 1);

     /* 计算字符在字库中的偏移值*/
     ch = ch - ' ';

     /* 显示16号/32号字体 */
     if((font_size == 16) || (font_size == 32) )
     {
          /* 计算字体一个字符对应点阵集所占的字节数 */
             size = (font_size / 8 + ((font_size % 8) ? 1 : 0)) * (font_size / 2);

            for(i = 0; i < size; i++)
            {
                    if(font_size == 16)
                            temp = asc2_1608[ch][i];	//调用1608字体
                    else if(font_size == 32)
                            temp = asc2_3216[ch][i];	//调用3216字体
                    else
                            return;			//没有的字库

                    for(j = 0; j < 8; j++)
                    {
                            if(temp & 0x80)
                                LCD_Write_2Byte(font_color);
                            else
                                LCD_Write_2Byte(back_color);

                            temp <<= 1;
                    }
            }
     }
      /* 显示12号字体 */
     else if(font_size == 12)
     {
          /* 计算字体一个字符对应点阵集所占的字节数 */
             size = (font_size / 8 + ((font_size % 8) ? 1 : 0)) * (font_size / 2);

            for(i = 0; i < size; i++)
            {
                  temp = asc2_1206[ch][i];

                    for(j = 0; j < 6; j++)
                    {
                            if(temp & 0x80)
                                LCD_Write_2Byte(font_color);
                            else
                                LCD_Write_2Byte(back_color);

                            temp <<= 1;
                    }
            }
     }
     /* 显示24号字体 */
     else if(font_size == 24)
     {
          /* 计算字体一个字符对应点阵集所占的字节数 */
             size = (font_size * 16) / 8;

            for(i = 0; i < size; i++)
            {
                  temp = asc2_2412[ch][i];
                    if(i % 2 == 0)
                            t = 8;
                    else
                            t = 4;
                    for(j = 0; j < t; j++)
                    {
                            if(temp & 0x80)
                                LCD_Write_2Byte(font_color);
                            else
                                LCD_Write_2Byte(back_color);

                            temp <<= 1;
                    }
            }
     }
     /* 其余字体 */
     else
         return;
}

void LCD_ShowCharStr(uint16_t x, uint16_t y, uint8_t max_width, char* str, uint16_t back_color, uint16_t font_color, uint8_t font_size)
{

    max_width += x;

    while((*str <= '~') && (*str >= ' '))	//判断是否非法字符
    {
            if(x >= max_width)
            {
                    //x方向越界，结束
                    break;
            }

            LCD_ShowChar(x,y,*str,back_color, font_color,font_size);
            x += font_size / 2;
            str++;
    }
}
#endif /* USE_ASCII_FONT_LIB */

void LCD_Draw_ColorSixPointStar(uint16_t x, uint16_t y, uint8_t r, uint16_t color) {
    uint16_t a = r / 2;
    uint16_t b = 1.432 * r;

    /* 绘制倒三角 */
    LCD_Draw_ColorLine(x - b, y - a, x + b, y - a, color);
    LCD_Draw_ColorLine(x + b, y - a, x, y + r, color);
    LCD_Draw_ColorLine(x, y + r, x - b, y - a, color);

    /* 绘制正三角 */
    LCD_Draw_ColorLine(x - b, y + a, x + b, y + a, color);
    LCD_Draw_ColorLine(x + b, y + a, x, y - r, color);
    LCD_Draw_ColorLine(x, y - r, x - b, y + a, color);

}

#if USE_PICTURE_DISPLAY

void LCD_Show_Image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p)
{
    uint32_t img_size = width * height * 2;		//图片所占字节数
    uint32_t remain_size = img_size;		    //图片每次发送后剩余的字节数
    uint8_t i = 0;

    /* 错误检测 */
    if(x + width > LCD_Width || y + height > LCD_Height)
    {
        return;
    }

    LCD_Address_Set(x, y, x + width - 1, y + height - 1);

    LCD_WR_RS(1);

    /* SPI每次最大发送2^16 = 65536个数据,图片最大大小为240*240*2 = 115200，会超过此大小，所以设计循环发送算法 */
    for(i = 0;i <= img_size / 65536; i++)
    {
        if(remain_size / 65536 >= 1)
        {
            LCD_SPI_Send((uint8_t *)p, 65535);
            p += 65535;
            remain_size -= 65535;
        }
        else
        {
            LCD_SPI_Send((uint8_t *)p, remain_size % 65535);
        }

    }
}
#endif /*  USE_PICTURE_DISPLAY */