#include "stm32f4xx_hal.h"

#include "clock.h"
#include "systick.h"

#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"

#include "spi.h"
#include "tim.h"

#include "lcd/lcd.h"
#include "touch/touch.h"
#include "sram/sram.h"

int main(void)
{
    HAL_Init();
    System_Clock_Init(8, 336, 2, 7);
    Delay_Init();

    SPI_Simulate_Init();
    // SRAM_Init();
    TIM_Base_Init(&g_tim6_handle, TIM6, 83, 999);
    __HAL_TIM_CLEAR_IT(&g_tim6_handle, TIM_IT_UPDATE);                          // 清除更新中断标志位
    HAL_TIM_Base_Start_IT(&g_tim6_handle);                                      // 使能更新中断，并启动计数器

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    // 测试代码
    lv_obj_t *switch_obj = lv_switch_create(lv_scr_act());
    lv_obj_set_size(switch_obj, 120, 60);
    lv_obj_align(switch_obj, LV_ALIGN_CENTER, 0, 0);

    while (1)
    {
        lv_timer_handler();
        Delay_ms(5);
    }
  
    return 0;
}