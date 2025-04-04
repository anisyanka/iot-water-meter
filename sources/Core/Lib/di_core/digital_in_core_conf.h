#ifndef DIGITAL_IN_CORE_CONF_H__
#define DIGITAL_IN_CORE_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define DIGITAL_IN_LIB_USE_LOGGER 0
#if (DIGITAL_IN_LIB_USE_LOGGER == 1)
# include "logger.h"
# define di_lib_log(...) logger_dgb_print(__VA_ARGS__)

#  if !defined(di_lib_log)
#  error "Define di_lib_log() function for DI lib or disable DIGITAL_IN_LIB_USE_LOGGER!"
#  endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* DIGITAL_IN_CORE_CONF_H__ */
