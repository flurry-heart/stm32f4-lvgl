#ifndef __TIM_H__
#define __TIM_H__

#include "stm32f4xx_hal.h"

#include "./tick/lv_tick.h"

extern TIM_HandleTypeDef g_tim6_handle;

void TIM_Base_Init(TIM_HandleTypeDef *htim, TIM_TypeDef *TIMx, uint16_t prescaler, uint16_t period);

#endif // !__TIM_H__