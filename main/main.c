#include <stdio.h>
#include "led_control.h"
#include "button_fun.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_GPIO_NUM 19

void app_main(void)
{
    led_init();
    button_init(BUTTON_GPIO_NUM);
   
}