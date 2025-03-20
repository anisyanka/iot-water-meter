#include "main.h"
#include "logger.h"

extern DMA_HandleTypeDef hdma_adc;
extern LCD_HandleTypeDef hlcd;
extern UART_HandleTypeDef hlpuart1;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* SIM7080 module Rx byte callback */
    if (huart->Instance == LPUART1) {
        // rs485_receiver_rx_byte_isr();
    }
}
