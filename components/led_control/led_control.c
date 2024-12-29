#include <stdio.h>
#include "led_control.h"
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"
#include "button_fun.h"

// LED初始化
void led_init()
{
    gpio_config_t led_gpio_cfg = {
        .pin_bit_mask = (1 << LED_GPIO_NUM),   // 指定GPIO
        .mode = GPIO_MODE_OUTPUT,              // 设置为输出模式
        .pull_up_en = GPIO_PULLUP_DISABLE,     // 禁止上拉
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // 禁止下拉
        .intr_type = GPIO_INTR_DISABLE,        // 禁止中断

    };
    gpio_config(&led_gpio_cfg);
}

// LED闪烁运行任务
void led_run_task()
{
    int gpio_level = 0;
    while (1)
    {
        if (led_open_Handle != NULL)
        {
            vTaskSuspend(led_open_Handle);
            vTaskDelete(led_open_Handle);
            led_open_Handle = NULL;
        }
        if (led_close_Handle != NULL)
        {
            vTaskSuspend(led_close_Handle);
            vTaskDelete(led_close_Handle);
            led_close_Handle = NULL;
        }
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_GPIO_NUM, gpio_level);
        gpio_level = gpio_level ? 0 : 1;
    }
}

// LED亮运行任务
void led_run_open_task()
{

    while (1)
    {
        if (led_ss_Handle != NULL)
        {
            vTaskSuspend(led_ss_Handle);
            vTaskDelete(led_ss_Handle);
            led_ss_Handle = NULL;
        }
        if (led_close_Handle != NULL)
        {
            vTaskSuspend(led_close_Handle);
            vTaskDelete(led_close_Handle);
            led_close_Handle = NULL;
        }
        gpio_set_level(18, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// LED灭运行任务
void led_run_close_task()
{
    while (1)
    {
        if (led_ss_Handle != NULL)
        {
            vTaskSuspend(led_ss_Handle);
            vTaskDelete(led_ss_Handle);
            led_ss_Handle = NULL;
        }
        if (led_open_Handle != NULL)
        {
            vTaskSuspend(led_open_Handle);
            vTaskDelete(led_open_Handle);
            led_open_Handle = NULL;
        }
        gpio_set_level(LED_GPIO_NUM, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        
    }
}
