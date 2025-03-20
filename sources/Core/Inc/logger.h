#ifndef __LOGGER_H
#define __LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void logger_dgb_print(const char *format, ...);
void logger_dgb_print_no_lib(const char *msg, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* __LOGGER_H */