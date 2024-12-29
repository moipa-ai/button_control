#ifndef __LED_CONTROL_H__
#define __LED_CONTROL_H__
#include "esp_err.h"
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#define LED_GPIO_NUM 18

void led_init();
void led_run_task();
void led_run_open_task();
void led_run_close_task();
#endif