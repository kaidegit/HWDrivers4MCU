#include "soft_i2c.h"
#include "delay.h"

void Soft_I2c_Start() {
    SDA_Set();
    SCL_Set();
    Delay_us(5);
    SDA_Reset();
    Delay_us(5);
    SCL_Reset();
}

void Soft_I2c_Stop() {
    SCL_Reset();
    SDA_Reset();
    Delay_us(5);
    SCL_Set();
    Delay_us(5);
    SDA_Set();
    Delay_us(5);
}

void Soft_I2c_SendByte(uint8_t dat) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        SCL_Reset();
        if ((dat & 0x80) >> 7) {
            SDA_Set();
        } else {
            SDA_Reset();
        }
        Delay_us(2);
        SCL_Set();
        dat <<= 1;
    }
    SCL_Reset();
    SDA_Set();
}

bool Soft_I2c_WaitAck() {
    uint8_t re;
    SDA_Set();
    Delay_us(5);
    SCL_Set();
    Delay_us(5);
    if (ReadSDAState()) {
        re = 1;
    } else {
        re = 0;
    }
    SCL_Reset();
    Delay_us(5);
    return re;
}

void Soft_I2c_Send(uint8_t DevAddr, uint8_t cmd, uint8_t dat) {
    Soft_I2c_Start();
    Soft_I2c_SendByte(DevAddr);
    if (Soft_I2c_WaitAck())
        return;
    Soft_I2c_SendByte(cmd);
    if (Soft_I2c_WaitAck())
        return;
    Soft_I2c_SendByte(dat);
    if (Soft_I2c_WaitAck())
        return;
    Soft_I2c_Stop();
}