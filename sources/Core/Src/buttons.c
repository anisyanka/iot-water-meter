#include "main.h"
#include "logger.h"
#include "buttons.h"
#include "digital_in_core.h"
#include "mqtt_adapter.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static digital_in_t btns_array[] =
{
    [SW1_BTN_ID] = { SW1_BTN_ID, (uint32_t)SW1_BTN_PORT, (uint32_t)SW1_BTN_PIN, 0, 20, },
    [SW2_BTN_ID] = { SW2_BTN_ID, (uint32_t)SW2_BTN_PORT, (uint32_t)SW2_BTN_PIN, 0, 20, },
};

static uint32_t read_pin_func(uint32_t port, uint32_t pin)
{
    return (uint32_t)HAL_GPIO_ReadPin((GPIO_TypeDef *)port, (uint16_t)pin);
}

#if (SIM7080_SEND_DATA_TEST == 1)
static void sw1_click_cb(void *data)
{
    (void)data;
    static const char *sw1_data = "{\"ch1\": \"100\", \"ch1\": \"875759\", \"pressure\": \"20kPa\", \"charge\": \"76%\", \"safety_flags\": \"0x00\"}";

    mqtt_send_data(sw1_data, strlen(sw1_data));
}

static void sw2_click_cb(void *data)
{
    (void)data;
    static const char *sw2_data = "{\"ch1\": \"000\", \"ch1\": \"000000\", \"pressure\": \"90kPa\", \"charge\": \"01%\", \"safety_flags\": \"0xff\"}";

    mqtt_send_data(sw2_data, strlen(sw2_data));
}
#endif

void buttons_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    SW1_PORT_CLK_EN();
    SW2_PORT_CLK_EN();

    GPIO_InitStruct.Pin = SW1_BTN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SW1_BTN_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SW2_BTN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SW2_BTN_PORT, &GPIO_InitStruct);

    digital_in_core_init(&btns_array, sizeof(btns_array)/sizeof(btns_array[0]),
                         read_pin_func, HAL_GetTick);

#if (SIM7080_SEND_DATA_TEST == 1)
    digital_in_set_clicked_cb(SW1_BTN_ID, sw1_click_cb, NULL);
    digital_in_set_clicked_cb(SW2_BTN_ID, sw2_click_cb, NULL);
#endif
}
