#include "main.h"
#include "dht11.h"

void SetDHT11PinOutput() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_Wire_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_Wire_GPIO_Port, &GPIO_InitStruct);
}

void SetDHT11PinInput() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_Wire_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT11_Wire_GPIO_Port, &GPIO_InitStruct);
}

uint8_t DHT11_ReadByte(void) {
    uint8_t i, temp = 0;
    uint16_t count;
    for (i = 0; i < 8; i++) {
        count = 0;
        while (ReadDHT11Pin_Reset() && (++count <= COUNTMAX));        // 等待低电平结束
        Delay_us(60);
        if (ReadDHT11Pin_Set()) {
            count = 0;
            while (ReadDHT11Pin_Set() && (++count <= COUNTMAX));    // 等待高电平结束
            temp |= (uint8_t) (0X01 << (7 - i));            // 先发送高位 MSB
        } else {
            temp &= (uint8_t) ~(0X01 << (7 - i));
        }
    }
    return temp;
}

int dht11Read(DHT11_Data_TypeDef *DHT11_Data) {
    uint16_t count;

    SetDHT11PinOutput();
    WriteDHT11Pin_Reset();
    Delay_ms(18);
    WriteDHT11Pin_Set();
    Delay_us(30);
    SetDHT11PinInput();

    if (ReadDHT11Pin_Reset())            // 收到从机应答
    {
        count = 0;
        while (ReadDHT11Pin_Reset() && (++count <= COUNTMAX));
        count = 0;
        while (ReadDHT11Pin_Set() && (++count <= COUNTMAX));        // 等待从机应答的高电平结束

        /*开始接收数据*/
        DHT11_Data->humi_int = DHT11_ReadByte();
        DHT11_Data->humi_deci = DHT11_ReadByte();
        DHT11_Data->temp_int = DHT11_ReadByte();
        DHT11_Data->temp_deci = DHT11_ReadByte();
        DHT11_Data->check_sum = DHT11_ReadByte();

        SetDHT11PinOutput();        // 读取结束，主机拉高
        WriteDHT11Pin_Set();

        // 数据校验
        if (DHT11_Data->check_sum ==
            DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int + DHT11_Data->temp_deci) {
            return 1;
        } else {
            return 0;
        }
    } else {     // 未收到从机应答
        return 0;
    }
}

