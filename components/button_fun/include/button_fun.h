#ifndef __BUTTON_FUN_H__
#define __BUTTON_FUN_H__
#include "esp_err.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void button_init(uint32_t button_num);
//定义全局变量，并在button_fun.c中初始化
extern TaskHandle_t led_ss_Handle;
extern TaskHandle_t led_open_Handle;
extern TaskHandle_t led_close_Handle;
#endif