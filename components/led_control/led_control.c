#include <stdio.h>
#include "led_control.h"
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"

// LED初始化
void led_init(gpio_num_t LED_GPIO)
{
    gpio_config_t led_gpio_cfg = {
        .pin_bit_mask = (1 << LED_GPIO),       // 指定GPIO
        .mode = GPIO_MODE_OUTPUT,              // 设置为输出模式
        .pull_up_en = GPIO_PULLUP_DISABLE,     // 禁止上拉
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // 禁止下拉
        .intr_type = GPIO_INTR_DISABLE,        // 禁止中断
        
    };
    gpio_config(&led_gpio_cfg);


}

// LED闪烁运行任务
void led_run_task(gpio_num_t gpio_num)
{
    //int i = 0;
    int gpio_level = 0;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(gpio_num, gpio_level);
        gpio_level = gpio_level ? 0 : 1;
        // i++;
        // if(i>100)
        // {
        //     // 删除任务的时机还没有想好，该函数待改进
        //     vTaskDelete(NULL);
        // }
       
    }
}

// LED亮运行任务
void led_run_open_task(TaskHandle_t led_ss)
{
    
    while (1)
    {
        if (led_ss != NULL)
        {
            vTaskSuspend(led_ss);
            vTaskDelete(led_ss);
            led_ss = NULL;
            ESP_LOGI("led_run", "delete led run");
        }
        gpio_set_level(18, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        
    }
}

// LED灭运行任务
void led_run_close_task(gpio_num_t gpio_num)
{
    while (1)
    {
        gpio_set_level(gpio_num, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        vTaskDelete(NULL);
    }
    
    
}
