#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H

#include "main.h"
#include "stdbool.h"

/// define the pins of i2c
#define SDA_GPIO_Port 
#define SDA_Pin
#define SCL_GPIO_Port
#define SCL_Pin

/**
 * @brief Set the SDA Pin.
 * 
 */
inline void SDA_Set() {
    #error write the setting SDA Pin function here
    // for STM32 HAL Lib
    // HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
}

/**
 * @brief Reset the SDA Pin
 * 
 */
inline void SDA_Reset() {
    #error write the resetting SDA Pin function here
    // for STM32 HAL Lib
    // HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Set the SCL Pin
 * 
 */
inline void SCL_Set() {
    #error write the setting SCL Pin function here
    // for STM32 HAL Lib
    // HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET);
}

/**
 * @brief Reset the SCL Pin
 * 
 */
inline void SCL_Reset() {
    #error write the resetting SCL Pin function here
    // for STM32 HAL Lib
    // HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief delay microsecond
 * 
 */
inline void Delay_us(us){
    #error write the microsecond delay here
}

/**
 * @brief read the state of the SDA Pin
 * @note the SDA Pin should be switched to input mode if 
 *      using push-pull mode
 * @return true if the SDA Pin is Set
 * @return false if the SDA Pin is Reset
 */
inline bool ReadSDAState(){
    #error write the read pin function here and return if the SDA Pin is set
    // for STM32 HAL Lib
    // return HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin) == GPIO_PIN_SET;
}

/**
 * @brief start the i2c communication
 * 
 */
void Soft_I2c_Start();

/**
 * @brief stop the i2c communication
 * 
 */
void Soft_I2c_Stop();

/**
 * @brief send a byte to the i2c bus
 * 
 * @param dat 
 */
void Soft_I2c_SendByte(uint8_t dat);

/**
 * @brief check if it is a device responsing
 * 
 * @return true if it is a device responsing
 * @return false no device responsing
 */
bool Soft_I2c_WaitAck();

/**
 * @brief send 3 bytes to the i2c bus.
 * 
 * @param DevAddr device address
 * @param cmd the first data
 * @param dat the second data
 */
void Soft_I2c_Send(uint8_t DevAddr, uint8_t cmd, uint8_t dat);

#endif
