#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H

#include "main.h"
#include "stdbool.h"

/// define the pins of i2c
//#define SDA_GPIO_Port 
//#define SDA_Pin
//#define SCL_GPIO_Port
//#define SCL_Pin

/**
 * @brief Set the SDA Pin.
 * 
 */
void SDA_Set();

/**
 * @brief Reset the SDA Pin
 * 
 */
void SDA_Reset();

/**
 * @brief Set the SCL Pin
 * 
 */
void SCL_Set();

/**
 * @brief Reset the SCL Pin
 * 
 */
void SCL_Reset();

/**
 * @brief delay microsecond
 * 
 */
void Delay_us(uint32_t us);

/**
 * @brief read the state of the SDA Pin
 * @note the SDA Pin should be switched to input mode if 
 *      using push-pull mode
 * @return true if the SDA Pin is Set
 * @return false if the SDA Pin is Reset
 */
bool ReadSDAState();

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
void Soft_I2c_Send(uint8_t DevAddr, uint8_t *cmd, uint8_t len);

#endif
