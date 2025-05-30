#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f4xx_hal.h"

#include "systick.h"

#define SPI_SCK_GPIO_PORT               GPIOB
#define SPI_SCK_GPIO_PIN                GPIO_PIN_0
#define RCC_SPI_SCK_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()


#define SPI_MOSI_GPIO_PORT              GPIOF
#define SPI_MOSI_GPIO_PIN               GPIO_PIN_11
#define RCC_SPI_MOSI_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE()

#define SPI_MISO_GPIO_PORT              GPIOB
#define SPI_MISO_GPIO_PIN               GPIO_PIN_2
#define RCC_SPI_MISO_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()

#define SPI_SCK(x)                      do{ x ? \
                                            HAL_GPIO_WritePin(SPI_SCK_GPIO_PORT,SPI_SCK_GPIO_PIN, GPIO_PIN_SET):\
                                            HAL_GPIO_WritePin(SPI_SCK_GPIO_PORT,SPI_SCK_GPIO_PIN, GPIO_PIN_RESET);\
                                        }while(0)

#define SPI_MOSI(x)                     do{ x ? \
                                            HAL_GPIO_WritePin(SPI_MOSI_GPIO_PORT, SPI_MOSI_GPIO_PIN, GPIO_PIN_SET):\
                                            HAL_GPIO_WritePin(SPI_MOSI_GPIO_PORT, SPI_MOSI_GPIO_PIN, GPIO_PIN_RESET);\
                                        }while(0)

#define SPI_MISO()                      HAL_GPIO_ReadPin(SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN)

void SPI_Simulate_Init(void);
uint8_t SPI_Simulate_SwapOneByte(uint8_t data);

#endif // !__SPI_H__