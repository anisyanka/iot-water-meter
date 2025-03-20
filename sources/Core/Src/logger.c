#include "logger.h"
#include "main.h"

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#if (FW_DEBUG_MODE == 1)
extern UART_HandleTypeDef huart1;
static uint8_t log_buf[512] = { 0 };
#endif

void logger_dgb_print(const char *format, ...)
{
#if (FW_DEBUG_MODE == 1)
    int32_t len = 0;

    va_list args;
    va_start(args, format);
    len = vsnprintf((char *)log_buf, sizeof(log_buf), format, args);
    va_end(args);

    HAL_UART_Transmit(&huart1, log_buf, len, 100);
#endif
}

void logger_dgb_print_no_lib(const char *msg, size_t len)
{
    extern uint32_t SystemCoreClock;

    for (int i = 0; i < len; ++i) {
        (&huart1)->Instance->TDR = msg[i];

        /* This function is used in error handler.
           UART might be broken, therefore we can't wait UART_FLAG_TXE flag.
           So delay here to prevent freezing */
        for (int i = 0; i < SystemCoreClock / 2000; ++i) {
            __NOP();
        }
    }
}
