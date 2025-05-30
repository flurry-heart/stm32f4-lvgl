#include "tim.h"

TIM_HandleTypeDef g_tim6_handle;

/**
 * @brief 定时器定时功能初始化函数
 * 
 * @param htim 定时器句柄
 * @param TIMx 定时器寄存器基地址，可选值: TIMx, x可选范围: 1 ~ 14
 * @param prescaler 预分频系数，可选值: 0 ~ 65535
 * @param period 自动重装载值，可选值: 0 ~ 65535
 * 
 * @note 默认为向上计数模式
 */
void TIM_Base_Init(TIM_HandleTypeDef *htim, TIM_TypeDef *TIMx, uint16_t prescaler, uint16_t period)
{
    htim->Instance = TIMx;                                                      // 定时器寄存器基地址
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;                                // 计数模式
    htim->Init.Prescaler = prescaler;                                           // 预分频系数
    htim->Init.Period = period;                                                 // 自动重装载值
    HAL_TIM_Base_Init(htim);
}

/**
 * @brief 基本定时器底层初始化函数
 * 
 * @param htim 定时器句柄
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();                                            // 使能定时器6的时钟

        HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);                                      // 使能定时器6中断
        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 4, 0);                              // 设置中断优先级
    }
}

/**
 * @brief 定时器6中断服务函数
 * 
 */
void TIM6_DAC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_tim6_handle);                                         // 调用HAL库公共处理函数
}

/**
 * @brief 定时器更新中断回调函数
 * 
 * @param htim 定时器句柄
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        // 这里定时器的定时时间要与形参一致
        lv_tick_inc(1);
    }
}
