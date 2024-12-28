#include <stdio.h>
#include "led_control.h"
#include "button_fun.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define LED_GPIO_NUM 18
#define BUTTON_GPIO_NUM 19

void app_main(void)
{
    led_init(LED_GPIO_NUM);
    button_init(BUTTON_GPIO_NUM);
   
}