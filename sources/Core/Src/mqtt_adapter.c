#include "main.h"
#include "logger.h"
#include "mqtt_adapter.h"
#include "sim7080.h"

#if (USE_EXERNAL_SIM7080 == 1)
extern UART_HandleTypeDef huart1;
# define SIM7080_UART huart1
#else
extern UART_HandleTypeDef hlpuart1;
# define SIM7080_UART hlpuart1
#endif

static volatile uint8_t rx_byte = 0;
static sim7080_dev_t sim7080_dev = { 0 };
static sim7080_ll_t ll = { 0 };
static sim7080_app_func_t app_funcs = { 0 };

static void pwrkey_pin_set(void)
{
#if (USE_EXERNAL_SIM7080 == 1)
    HAL_GPIO_WritePin(GSM_PWRKEY_PORT, GSM_PWRKEY_PIN, GPIO_PIN_SET);
#else
    HAL_GPIO_WritePin(GSM_PWRKEY_PORT, GSM_PWRKEY_PIN, GPIO_PIN_RESET);
#endif
}

static void pwrkey_pin_reset(void)
{
#if (USE_EXERNAL_SIM7080 == 1)
    HAL_GPIO_WritePin(GSM_PWRKEY_PORT, GSM_PWRKEY_PIN, GPIO_PIN_RESET);
#else
    HAL_GPIO_WritePin(GSM_PWRKEY_PORT, GSM_PWRKEY_PIN, GPIO_PIN_SET);
#endif
}

static int transmit_data_poll(uint8_t *data, size_t len, uint32_t timeout_ms)
{
    if (HAL_UART_Transmit(&SIM7080_UART, (const uint8_t *)data,
                          (uint16_t)len, timeout_ms) != HAL_OK) {
        logger_dgb_print("[mqtt] HAL_UART_Transmit() failed\r\n");
        return SIM7080_RET_STATUS_HW_TX_FAIL;
    }

    return SIM7080_RET_STATUS_SUCCESS;
}

static void mqtt_adapter_bootup_done_cb(void) {}
static void mqtt_adapter_initial_setup_done_cb(void) {}
static void mqtt_adapter_setup_device_keys_done_cb(void) {}

static void mqtt_adapter_net_registration_done_cb(void)
{
    logger_dgb_print("[mqtt] NB-Iot net registration - SUCCESS\t\n");
}

static void mqtt_adapter_server_connection_done_cb(void)
{
    logger_dgb_print("[mqtt] Yandex broker connection - SUCCESS\t\n");

    /*
     * TODO: here the sim7080 is ready to operate with Yandex broker.
     * We can start sending data.
     */
}

static void mqtt_adapter_transmittion_done_cb(void)
{
    logger_dgb_print("[mqtt] Tx data - SUCCESS\t\n");

    /*
     * TODO: useful data has been sent.
     * Start some timer (RTC?) to send it again after some time?
     */
}

static void mqtt_adapter_error_occured_cb(int error)
{
    logger_dgb_print("[mqtt] sim7080 failed. err=%d --> %s\r\n",
                     error, sim7080_err_to_string(error));

    if (error != SIM7080_RET_STATUS_NOT_SUPPORTED) {
        /* TODO: reinit UART here */

        sim7080_reset(&sim7080_dev);
    }
}

void mqtt_init(void)
{
    int rv = SIM7080_RET_STATUS_SUCCESS;

    ll.delay_ms = HAL_Delay;
    ll.get_tick_ms = HAL_GetTick;
    ll.pwrkey_pin_set = pwrkey_pin_set;
    ll.pwrkey_pin_reset = pwrkey_pin_reset;
    ll.transmit_data_polling_mode = transmit_data_poll;

    if (HAL_UART_Receive_IT(&SIM7080_UART, (uint8_t *)(&rx_byte), 1) \
            != HAL_OK) {
        logger_dgb_print("[mqtt] HAL_UART_Receive_IT() failed."
                         "Can't start UART RX in async mode\r\n");
    }

    rv = sim7080_init(&sim7080_dev, &ll);
    if (rv != SIM7080_RET_STATUS_SUCCESS) {
        logger_dgb_print("[mqtt] sim7080_init() failed. err=%d --> %s\r\n",
                         rv, sim7080_err_to_string(rv));
    }

#if (FW_DEBUG_MODE == 1)
    sim7080_debug_mode(&sim7080_dev, logger_dgb_print);
#endif

    /* Setup user callbacks */
    app_funcs.bootup_done = mqtt_adapter_bootup_done_cb;
    app_funcs.initial_setup_done = mqtt_adapter_initial_setup_done_cb;
    app_funcs.net_registration_done = mqtt_adapter_net_registration_done_cb;
    app_funcs.setup_device_keys_done = mqtt_adapter_setup_device_keys_done_cb;
    app_funcs.mqtt_server_connection_done = mqtt_adapter_server_connection_done_cb;
    app_funcs.mqtt_transmission_done = mqtt_adapter_transmittion_done_cb;
    app_funcs.error_occured = mqtt_adapter_error_occured_cb;

    rv = sim7080_setup_app_cb(&sim7080_dev, &app_funcs);
    if (rv != SIM7080_RET_STATUS_SUCCESS) {
        logger_dgb_print("[mqtt] sim7080_setup_app_cb() failed. err=%d --> %s\r\n",
                         rv, sim7080_err_to_string(rv));
    }

    logger_dgb_print("[sim7080] Setup net and protocol params done\r\n");
}

void mqtt_poll(void)
{
    sim7080_poll(&sim7080_dev);
}

void mqtt_send_data(const char *data, size_t len)
{
    if (sim7080_publish_data(&sim7080_dev, data, len) == SIM7080_RET_STATUS_SUCCESS) {
        logger_dgb_print("[mqtt] sending data in progress...\r\n");
    } else {
        logger_dgb_print("[mqtt] failed to start send data\r\n");
    }
}

void mqtt_rx_new_byte_isr(void)
{
    sim7080_rx_byte_isr(&sim7080_dev, rx_byte);
    HAL_UART_Receive_IT(&SIM7080_UART, (uint8_t *)(&rx_byte), 1);
}
