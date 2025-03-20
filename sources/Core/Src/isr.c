#include "main.h"
#include "logger.h"
#include "mqtt_adapter.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* SIM7080 module Rx byte callback */
    if (huart->Instance == LPUART1) {
        mqtt_rx_new_byte_isr();
    }
}
