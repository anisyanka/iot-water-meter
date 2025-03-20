#ifndef MQTT_ADAPTER_H
#define MQTT_ADAPTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

void mqtt_init(void);
void mqtt_poll(void);
void mqtt_send_data(char *data, size_t len);
void mqtt_rx_new_byte_isr(void);

#ifdef __cplusplus
}
#endif

#endif /* MQTT_ADAPTER_H */
