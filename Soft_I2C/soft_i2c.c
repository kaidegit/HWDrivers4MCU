#include "soft_i2c.h"
#include "delay.h"

void SDA_Set() {
    #error write the setting SDA Pin function here
    // for STM32 HAL Lib
    // HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
}

void SDA_Reset() {
    #error write the resetting SDA Pin function here
    // for STM32 HAL Lib
    // HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET);
}

void SCL_Set() {
    #error write the setting SCL Pin function here
    // for STM32 HAL Lib
    // HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET);
}

void SCL_Reset() {
    #error write the resetting SCL Pin function here
    // for STM32 HAL Lib
    // HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_RESET);
}

void Delay_us(uint32_t us){
    #error write the microsecond delay here
}

bool ReadSDAState(){
    #error write the read pin function here and return if the SDA Pin is set
    // for STM32 HAL Lib
    // return HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin) == GPIO_PIN_SET;
}

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