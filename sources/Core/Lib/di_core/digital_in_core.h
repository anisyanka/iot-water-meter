#ifndef DIGITAL_IN_CORE_H__
#define DIGITAL_IN_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
    /* Internal item ID */
    uint32_t id;

    /* port:pin */
    uint32_t gpio_port;
    uint32_t gpio_pin;

    /* high - 1 or low - 0 */
    uint32_t activated_state;

    /* After this count the button or digital input will be treated as 'activated' state */
    uint32_t debounce_time_ms;

    /* 0 means the callback will be called immideatly after debounce time. */
    uint32_t time_to_activated_state_ms;

    /*
     * How ofter a callback will be called if after time_to_activated_state_ms elapsed.
     * 0 means the callback WON'T be called in repeat manner.
     */
    uint32_t time_to_repeat_activated_cb_ms;

    /* Here and below are internally used variables. Don't init its. Use the API! */
    uint32_t _is_activated;
    uint32_t _activated_time_start_ms;
    uint32_t _repeat_activated_time_start_ms;
    uint32_t _is_simulate_click;
    uint32_t _debounce_cnt_start;
    uint32_t _cb_called_firstly;

    void (*activate_cb)(void *);
    void (*deactivate_cb)(void *);
    void (*clicked_cb)(void *);

    void *activated_data;
    void *deactivated_data;
    void *clicked_data;
} digital_in_t;

/* Tell the core array of your ditital inputs */
void digital_in_core_init(digital_in_t (*di_arr)[], int di_cnt,
                          uint32_t (*gpio_read_func)(uint32_t port, uint32_t pin),
                          uint32_t (*get_tick_ms)(void));

/* Polling function to call it in thread or main loop */
void digital_in_poll(void);

void digital_in_set_activate_cb(unsigned int di_id,
                                uint32_t time_to_activated_state_ms, /* Needed to handle holding of some DIs */
                                uint32_t time_to_repeat_activated_cb_ms, /* Needed to repeat calling cb when DI is activated and holding in progress */
                                void (*activate_cb)(void *),
                                void *data);
void digital_in_set_deactivate_cb(unsigned int di_id,
                                  void (*deactivate_cb)(void *),
                                  void *data);
void digital_in_set_clicked_cb(unsigned int di_id, void (*clicked_cb)(void *), void *data);
void digital_in_simulate_click(unsigned int di_id);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* DIGITAL_IN_CORE_H__ */
