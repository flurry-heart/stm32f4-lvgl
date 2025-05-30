#include "spi.h"

/**
 * @brief SPI初始化函数
 * 
 */
void SPI_Simulate_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能SPI SCK MISO MOSI对应GPIO引脚的时钟
    RCC_SPI_SCK_GPIO_CLK_ENABLE();
    RCC_SPI_MISO_GPIO_CLK_ENABLE();
    RCC_SPI_MOSI_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = SPI_SCK_GPIO_PIN;                                     // SPI的SCL引脚
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;                                 // 推挽输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;                                         // 不使用上下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;                               // 输出速度
    HAL_GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SPI_MOSI_GPIO_PIN;                                    // SPI的MOSI引脚
    HAL_GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SPI_MISO_GPIO_PIN;                                    // SPI的MISO引脚
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                                     // 输入模式
    HAL_GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStruct);


    SPI_SCK(0);                                                                 // SPI的SCK引脚默认为低电平，选择工作模式0或1
    // SPI_SCK(1);                                                                 // SPI的SCK引脚默认为高电平，选择工作模式2或3
}

/**
 * @brief SPI交换一个字节函数
 * 
 * @param data 待交换的数据
 * @return uint8_t 交换后的数据
 */
uint8_t SPI_Simulate_SwapOneByte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        // SCK下降沿
        SPI_SCK(0);
        Delay_us(1);
        // 移出数据
        SPI_MOSI(data & 0x80);
        data <<= 1;
        // 移入数据
        if (SPI_MISO())
        {
            data |= 0x01;
        }
        // SCK上升沿
        SPI_SCK(1);
        Delay_us(1);
    }

    SPI_SCK(0);

    return data;
}