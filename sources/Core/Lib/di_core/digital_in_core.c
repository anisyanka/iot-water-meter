#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <ctype.h>

#include "digital_in_core.h"
#include "digital_in_core_conf.h"

static digital_in_t (*_di_array)[] = { NULL };
static int _di_cnt = 0;
static uint32_t (*_pin_read_func)(uint32_t port, uint32_t pin) = NULL;
static uint32_t (*_get_tick_ms)(void) = NULL;

void digital_in_core_init(digital_in_t (*di_arr)[], int di_cnt,
                          uint32_t (*gpio_read_func)(uint32_t port, uint32_t pin),
                          uint32_t (*get_tick_ms)(void))
{
    _di_array = di_arr;
    _di_cnt = di_cnt;
    _pin_read_func = gpio_read_func;
    _get_tick_ms = get_tick_ms;
}

void digital_in_poll(void)
{
    for (int i = 0; i < _di_cnt; ++i)
    {
        uint32_t pin_state = _pin_read_func((*_di_array)[i].gpio_port, (*_di_array)[i].gpio_pin);

        if (((pin_state == (*_di_array)[i].activated_state) && (!(*_di_array)[i]._is_activated)) || \
            ((pin_state == (*_di_array)[i].activated_state) && ((*_di_array)[i].time_to_activated_state_ms != 0)) || \
            ((pin_state == (*_di_array)[i].activated_state) && ((*_di_array)[i].time_to_repeat_activated_cb_ms != 0)))
        {
            /* Debounce a digital input if needed */
            if (!(*_di_array)[i]._is_activated)
            {
                if (!(*_di_array)[i]._debounce_cnt_start)
                {
                    (*_di_array)[i]._debounce_cnt_start = _get_tick_ms();
                }

                if ( _get_tick_ms() - (*_di_array)[i]._debounce_cnt_start < (*_di_array)[i].debounce_time_ms)
                {
                    continue;
                }
            }

            /* Handle holding state if needed */
            if (!(*_di_array)[i]._activated_time_start_ms)
            {
                (*_di_array)[i]._activated_time_start_ms = _get_tick_ms();
            }

            if (_get_tick_ms() - (*_di_array)[i]._activated_time_start_ms >= (*_di_array)[i].time_to_activated_state_ms)
            {
                /* For now a digital input is in 'activated' state */
                (*_di_array)[i]._is_activated = 1;
                (*_di_array)[i]._debounce_cnt_start = 0;

                /* Holding time (until a di is treated as active) elasped, so call the callback and do repeat logic */
                if (((*_di_array)[i].activate_cb) && (!(*_di_array)[i]._cb_called_firstly))
                {
                    (*_di_array)[i].activate_cb((*_di_array)[i].activated_data);
                    #if (DIGITAL_IN_LIB_USE_LOGGER == 1)
                        di_lib_log("[di-core] di[%d] is in active state (firstly)\r\n", i);
                    #endif

                    /* set callback have been called flag to allow only repeat called for now */;
                    (*_di_array)[i]._cb_called_firstly = 1;
                }

                /* Repeat logic starts here. If user set it - do it. */
                if ((*_di_array)[i].time_to_repeat_activated_cb_ms)
                {
                    if (!(*_di_array)[i]._repeat_activated_time_start_ms)
                    {
                        (*_di_array)[i]._repeat_activated_time_start_ms = _get_tick_ms();
                    }

                    if (_get_tick_ms() - (*_di_array)[i]._repeat_activated_time_start_ms >= (*_di_array)[i].time_to_repeat_activated_cb_ms)
                    {
                        if ((*_di_array)[i].activate_cb)
                        {
                            (*_di_array)[i].activate_cb((*_di_array)[i].activated_data);
                            #if (DIGITAL_IN_LIB_USE_LOGGER == 1)
                                di_lib_log("[di-core] di[%d] is in active state (repeat)\r\n", i);
                            #endif
                        }
                        (*_di_array)[i]._repeat_activated_time_start_ms = 0;
                    }
                }
            }
        }
        else if ((pin_state == !(*_di_array)[i].activated_state) && ((*_di_array)[i]._is_activated))
        {
            (*_di_array)[i]._is_activated = 0;
            (*_di_array)[i]._debounce_cnt_start = 0;
            (*_di_array)[i]._activated_time_start_ms = 0;
            (*_di_array)[i]._cb_called_firstly = 0;
            (*_di_array)[i]._repeat_activated_time_start_ms = 0;

            if ((*_di_array)[i].deactivate_cb)
            {
                (*_di_array)[i].deactivate_cb((*_di_array)[i].deactivated_data);
                #if (DIGITAL_IN_LIB_USE_LOGGER == 1)
                    di_lib_log("[di-core] di[%d] is deactivated\r\n", i);
                #endif
            }

            if ((*_di_array)[i].clicked_cb)
            {
                (*_di_array)[i].clicked_cb((*_di_array)[i].clicked_data);
                #if (DIGITAL_IN_LIB_USE_LOGGER == 1)
                    di_lib_log("[di-core] di[%d] clicked\r\n", i);
                #endif
            }
        }
        else
        {
            (*_di_array)[i]._activated_time_start_ms = 0;
            (*_di_array)[i]._debounce_cnt_start = 0;
            (*_di_array)[i]._repeat_activated_time_start_ms = 0;
        }

        if ((*_di_array)[i]._is_simulate_click)
        {
            (*_di_array)[i]._is_simulate_click = 0;

            if ((*_di_array)[i].clicked_cb)
            {
                (*_di_array)[i].clicked_cb((*_di_array)[i].clicked_data);
                #if (DIGITAL_IN_LIB_USE_LOGGER == 1)
                    di_lib_log("[di-core] di[%d] SW clicked\r\n", i);
                #endif
            }
        }
    }
}

void digital_in_set_activate_cb(unsigned int di_id,
                               uint32_t time_to_activated_state_ms,
                               uint32_t time_to_repeat_activated_cb_ms,
                               void (*activate_cb)(void *),
                               void *data)
{
    if ((di_id < 0) || (di_id >= _di_cnt))
    {
        return;
    }

    (*_di_array)[di_id].time_to_activated_state_ms = time_to_activated_state_ms;
    (*_di_array)[di_id].time_to_repeat_activated_cb_ms = time_to_repeat_activated_cb_ms;
    (*_di_array)[di_id].activate_cb = activate_cb;
    (*_di_array)[di_id].activated_data = data;

    (*_di_array)[di_id]._is_activated = 0;
    (*_di_array)[di_id]._activated_time_start_ms = 0;
    (*_di_array)[di_id]._repeat_activated_time_start_ms = 0;
    (*_di_array)[di_id]._cb_called_firstly = 0;
    (*_di_array)[di_id]._is_simulate_click = 0;
    (*_di_array)[di_id]._debounce_cnt_start = 0;
}

void digital_in_set_deactivate_cb(unsigned int di_id, void (*deactivate_cb)(void *), void *data)
{
    if ((di_id < 0) || (di_id >= _di_cnt))
    {
        return;
    }

    (*_di_array)[di_id].deactivate_cb = deactivate_cb;
    (*_di_array)[di_id].deactivated_data = data;

    (*_di_array)[di_id]._is_activated = 0;
    (*_di_array)[di_id]._activated_time_start_ms = 0;
    (*_di_array)[di_id]._repeat_activated_time_start_ms = 0;
    (*_di_array)[di_id]._cb_called_firstly = 0;
    (*_di_array)[di_id]._is_simulate_click = 0;
    (*_di_array)[di_id]._debounce_cnt_start = 0;
}

void digital_in_set_clicked_cb(unsigned int di_id, void (*clicked_cb)(void *), void *data)
{
    if ((di_id < 0) || (di_id >= _di_cnt))
    {
        return;
    }

    (*_di_array)[di_id].clicked_cb = clicked_cb;
    (*_di_array)[di_id].clicked_data = data;

    (*_di_array)[di_id]._is_activated = 0;
    (*_di_array)[di_id]._activated_time_start_ms = 0;
    (*_di_array)[di_id]._repeat_activated_time_start_ms = 0;
    (*_di_array)[di_id]._cb_called_firstly = 0;
    (*_di_array)[di_id]._is_simulate_click = 0;
    (*_di_array)[di_id]._debounce_cnt_start = 0;
}

void digital_in_simulate_click(unsigned int di_id)
{
    (*_di_array)[di_id]._is_simulate_click = 1;
}
