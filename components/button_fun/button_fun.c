#include <stdio.h>
#include "button_fun.h"
#include "button_gpio.h"
#include "iot_button.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_control.h"
#define BUTTON_ACTIVE_LEVEL 1

static const char *TAG = "button_power_save";
//初始化全局变量
TaskHandle_t led_open_Handle=NULL;
TaskHandle_t led_ss_Handle=NULL;
TaskHandle_t led_close_Handle = NULL;

static void button_event_cb(void *arg, void *data)
{

    int req_data = (button_event_t)data;
    if (req_data == BUTTON_SINGLE_CLICK)
    {

        ESP_LOGI(TAG, "Button event: BUTTON_SINGLE_CLICK");
        xTaskCreatePinnedToCore(led_run_open_task, "led_open", 2048, NULL, 3, &led_open_Handle, 0);
        // if (led_ss_Handle != NULL)
        // {
        //     // 先暂停任务在删除任务
        //     vTaskSuspend(led_ss_Handle);
        //     vTaskDelete(led_ss_Handle);
        //     led_ss_Handle = NULL;
        // }
        // gpio_set_level(18, 1);
    }

    else if (req_data == BUTTON_DOUBLE_CLICK)
    {
        ESP_LOGI(TAG, "Button event: BUTTON_DOUBLE_CLICK ");
        xTaskCreatePinnedToCore(led_run_task, "led_ss", 2048,NULL, 3, &led_ss_Handle, 0);
    }

    else if (req_data == BUTTON_LONG_PRESS_START)
    {

        ESP_LOGI(TAG, "Button event: BUTTON_LONG_PRESS_START");
        xTaskCreatePinnedToCore(led_run_close_task, "led_close", 2048, NULL, 3, &led_close_Handle, 0);
        // 先暂停任务在删除任务
        // vTaskSuspend(led_ss_Handle);
        // vTaskDelete(led_ss_Handle);
        // led_ss_Handle = NULL;
        // gpio_set_level(18, 0);
    }
}

void button_init(uint32_t button_num)
{
    button_config_t btn_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = button_num,
            .active_level = BUTTON_ACTIVE_LEVEL,
        },
    };
    button_handle_t btn = iot_button_create(&btn_cfg);
    assert(btn);
    esp_err_t err = iot_button_register_cb(btn, BUTTON_PRESS_DOWN, button_event_cb, (void *)BUTTON_PRESS_DOWN);
    err |= iot_button_register_cb(btn, BUTTON_PRESS_UP, button_event_cb, (void *)BUTTON_PRESS_UP);
    err |= iot_button_register_cb(btn, BUTTON_PRESS_REPEAT, button_event_cb, (void *)BUTTON_PRESS_REPEAT);
    err |= iot_button_register_cb(btn, BUTTON_PRESS_REPEAT_DONE, button_event_cb, (void *)BUTTON_PRESS_REPEAT_DONE);
    err |= iot_button_register_cb(btn, BUTTON_SINGLE_CLICK, button_event_cb, (void *)BUTTON_SINGLE_CLICK);
    err |= iot_button_register_cb(btn, BUTTON_DOUBLE_CLICK, button_event_cb, (void *)BUTTON_DOUBLE_CLICK);
    err |= iot_button_register_cb(btn, BUTTON_LONG_PRESS_START, button_event_cb, (void *)BUTTON_LONG_PRESS_START);
    err |= iot_button_register_cb(btn, BUTTON_LONG_PRESS_HOLD, button_event_cb, (void *)BUTTON_LONG_PRESS_HOLD);
    err |= iot_button_register_cb(btn, BUTTON_LONG_PRESS_UP, button_event_cb, (void *)BUTTON_LONG_PRESS_UP);
    err |= iot_button_register_cb(btn, BUTTON_PRESS_END, button_event_cb, (void *)BUTTON_PRESS_END);

    ESP_ERROR_CHECK(err);
}
