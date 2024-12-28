#ifndef __LED_CONTROL_H__
#define __LED_CONTROL_H__
#include "esp_err.h"
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void led_init(gpio_num_t LED_GPIO);
void led_run_task(gpio_num_t gpio_num);
void led_run_open_task(TaskHandle_t led_ss);
void led_run_close_task(gpio_num_t gpio_num);
#endif