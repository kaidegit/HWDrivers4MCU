
#ifndef __DHT11_H
#define __DHT11_H

#include "stdint.h"
#include "stdbool.h"
#include "delay.h"

/// define the dht11 pin. These defines may generate by STM32CubeMX automatically
#define DHT11_Wire_Pin GPIO_PIN_9
#define DHT11_Wire_GPIO_Port GPIOA

const uint16_t COUNTMAX = 1000;

typedef struct {
    uint8_t humi_int;                // 湿度的整数部分
    uint8_t humi_deci;            // 湿度的小数部分
    uint8_t temp_int;                // 温度的整数部分
    uint8_t temp_deci;            // 温度的小数部分
    uint8_t check_sum;            // 校验和
} DHT11_Data_TypeDef;

/**
 * @brief check if the DHT11 Pin is reset
 * @return true if the DHT11 Pin is reset
 */
inline bool ReadDHT11Pin_Reset(){
#error write the readpin function here and judge if the DHT11 Pin is reset
//    for STM32 HAL Lib
//    return HAL_GPIO_ReadPin(DHT11_Wire_GPIO_Port, DHT11_Wire_Pin) == GPIO_PIN_RESET;
}

/**
 * @brief check if the DHT11 Pin is set
 * @return true if the DHT11 Pin is set
 */
inline bool ReadDHT11Pin_Set() {
#error write the readpin function here and judge if the DHT11 Pin is set
    //    for STM32 HAL Lib
//    return HAL_GPIO_ReadPin(DHT11_Wire_GPIO_Port, DHT11_Wire_Pin) == GPIO_PIN_SET;
}

/**
 * @brief reset the DHT11 Pin
 */
inline void WriteDHT11Pin_Reset(){
#error write the writepin function here and reset the DHT11 Pin
    //    for STM32 HAL Lib
//    HAL_GPIO_WritePin(DHT11_Wire_GPIO_Port, DHT11_Wire_Pin, GPIO_PIN_RESET);
}

/**
 * @brief set the DHT11 Pin
 */
inline void WriteDHT11Pin_Set() {
#error write the writepin function here and set the DHT11 Pin
    //    for STM32 HAL Lib
//    HAL_GPIO_WritePin(DHT11_Wire_GPIO_Port, DHT11_Wire_Pin, GPIO_PIN_SET);
}

/**
 * @brief delay millisecond
 */
inline void Delay_ms(ms){
#error write the millisecond delay here
    //    for STM32 HAL Lib
//    HAL_Delay(ms);
}

/**
 * @brief delay microsecond
 */
inline void Delay_us(us){
#error write the microsecond delay here
//    HAL_delay_us(us);
}

/// @note if you init the DHT11 Pin to Open Drain mode and have a pull-up resistance,
///     it is no need to switch the DHT11 Pin mode.
/**
 * @brief Init the DHT11 Pin to output mode
 */
void SetDHT11PinOutput();

/**
 * @brief Init the DHT11 Pin to input mode
 */
void SetDHT11PinInput();

/**
 * @brief read a byte of the dht11 data
 * @return the read byte
 */
uint8_t DHT11_ReadByte(void);

/**
 * @brief read the temperature of the dht11
 * @param DHT11_Data the pointer of the struct
 * @return return 1 if the read is correct.
 */
int dht11Read(DHT11_Data_TypeDef *DHT11_Data);

#endif //DHT11_DHT11_H
