#include "main.h"
#include "logger.h"
#include "mqtt_adapter.h"
#include "sim7080.h"
#include "sim7080_configs.h"

extern UART_HandleTypeDef hlpuart1;

static sim7080_dev_t sim7080_dev = { 0 };
static sim7080_ll_t ll = { 0 };
static uint8_t rx_byte = 0;

static void pwrkey_pin_set(void) { HAL_GPIO_WritePin(GSM_PWRKEY_PORT, GSM_PWRKEY_PIN, GPIO_PIN_RESET); }
static void pwrkey_pin_reset(void) { HAL_GPIO_WritePin(GSM_PWRKEY_PORT, GSM_PWRKEY_PIN, GPIO_PIN_SET); }
static void dtr_pin_set(void) {  }
static void dtr_pin_reset(void) {  }

int transmit_data(uint8_t *data, size_t len)
{
    if (HAL_UART_Transmit(&hlpuart1, (const uint8_t *)data,
                          (uint16_t)len, 100) != HAL_OK) {
        return SIM7080_RET_STATUS_HW_TX_FAIL;
    }

    return SIM7080_RET_STATUS_SUCCESS;
}

void mqtt_init(void)
{
    int rv = 0;

    ll.delay_ms = HAL_Delay;
    ll.get_tick_ms = HAL_GetTick;
    ll.dtr_pin_set = dtr_pin_set;
    ll.dtr_pin_reset = dtr_pin_reset;
    ll.pwrkey_pin_set = pwrkey_pin_set;
    ll.pwrkey_pin_reset = pwrkey_pin_reset;
    ll.transmit_data = transmit_data;

    sim7080_dev.ll_funcs = &ll;

    rv = sim7080_init_hw_and_net_params(&sim7080_dev, &net_mts_nbiot,
                                        &protocol_yandex_mqtt);
    if (rv != SIM7080_RET_STATUS_SUCCESS) {
        logger_dgb_print("[mqtt] sim7080_init_hw_and_net_params() failed. err=%d --> %s\r\n",
                         rv, sim7080_err_to_string(rv));
    }

    /* Start bytes waiting from the module */
    if (HAL_UART_Receive_IT(&hlpuart1, &rx_byte, 1) != HAL_OK) {
        logger_dgb_print("[mqtt] HAL_UART_Receive_IT() failed. Can't start UART RX\r\n");
        rv = -1;
    }

    if (rv == 0) {
        logger_dgb_print("[sim7080] Setup net and protocol params done\r\n");
    }
}

void mqtt_poll(void)
{
    int rv = 0;
    int err = 0;

    rv = sim7080_poll(&sim7080_dev, &err);
    switch (rv) {
    case SIM7080_SM_SOME_ERR_HAPPENED:
        logger_dgb_print("[sim7080] unvalid state. err=%d --> %s\r\n",
                         err, sim7080_err_to_string(err));
        HAL_Delay(2000);
        /* TODO: might be needed to do re-init sim7080 here and start connection sequence again */
        break;

    /* State when fw started and power key has been toggled */
    case SIM7080_SM_INITIAL:
        if (sim7080_init(&sim7080_dev) == SIM7080_RET_STATUS_SUCCESS) {
            logger_dgb_print("[sim7080] base init started...\r\n");
        }
        break;

    /* Base module init sequence has been started */
    case SIM7080_SM_INIT_IN_PROGRESS:
        break;
    case SIM7080_SM_INIT_DONE:
        if (sim7080_net_connect(&sim7080_dev) == SIM7080_RET_STATUS_SUCCESS) {
            logger_dgb_print("[sim7080] base init done!\r\n");
            logger_dgb_print("[sim7080] nbiot connection started...\r\n");
        }
        break;

    /* Base init done. Setup NB-Iot connection has been started */
    case SIM7080_SM_NET_CONNECT_IN_PROGRESS:
        break;
    case SIM7080_SM_NET_CONNECT_FAILED:
        break;
    case SIM7080_SM_NET_CONNECTED:
        if (sim7080_proto_connect(&sim7080_dev) == SIM7080_RET_STATUS_SUCCESS) {
            logger_dgb_print("[sim7080] nbiot connection done!\r\n");
            logger_dgb_print("[sim7080] yandex mqtt connection started...\r\n");
        }
        break;

    /* Connect to MTS NB-Iot done. Setup MQTT connection has been started */
    case SIM7080_SM_PROTO_CONNECT_IN_PROGRESS:
        break;
    case SIM7080_SM_PROTO_CONNECT_FAILED:
        break;
    case SIM7080_SM_PROTO_CONNECTED:
        logger_dgb_print("[sim7080] yandex mqtt connection done!\r\n");
        break;

    default:
        break;
    }
}

void mqtt_send_data(char *data, size_t len)
{
    ;
}

void mqtt_rx_new_byte_isr(void)
{
    sim7080_rx_byte_isr(&sim7080_dev, rx_byte);
    HAL_UART_Receive_IT(&hlpuart1, &rx_byte, 1);

#if 0
    logger_dgb_print_no_lib("rx\r\n", 4);
#endif
}
