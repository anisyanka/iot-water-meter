#
#Executable name
#
EXE_NAME=app

#
#Folder to place compiled objects
#
BUILDDIR = build-app

#
#Verbose mode
#
VERBOSE=no

#
#Colorize ouput
#
COLORIZE=yes

#
#Enable binary creation
#
MAKE_BINARY=yes

#
#Enable executable creation
#
MAKE_EXECUTABLE=yes

#
#Enable shared library creation
#
MAKE_SHARED_LIB=no

#
#Enable static library creation
#
MAKE_STATIC_LIB=no

#
#Enable MAP-file creation
#
CREATE_MAP=yes

#
# Debug or release mode
#
BUILD_DEBUG_MODE=yes

#
#Tool-chain prefix
#
TCHAIN = arm-none-eabi-

#
#CPU specific options
#
MCPU += -mcpu=cortex-m0plus
MCPU += -mthumb

#
#C language dialect
#
CDIALECT = gnu99

#
#C++ language dialect
#
#CXXDIALECT = c++0x

#
#Additional C flags
#
CFLAGS +=-fdata-sections -ffunction-sections 
CFLAGS +=-fsingle-precision-constant
CFLAGS +=-funsafe-math-optimizations
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#
#Additional CPP flags
#
CXXFLAGS +=-fdata-sections -ffunction-sections

#
#Additional linker flags
#
LDFLAGS +=-nostartfiles
LDFLAGS +=-specs=nano.specs
LDFLAGS +=-Wl,--gc-sections
LDFLAGS += -Wl,--print-memory-usage
LDFLAGS += -u _printf_float
LDFLAGS += -u _scanf_float

#
#Additional link objects
#
#EXT_OBJECTS =

#
#Additional static libraries
#
EXT_LIBS +=c
EXT_LIBS +=m
EXT_LIBS +=nosys

#
# Create git info about fw version
#
GIT_HASH=$(shell git rev-parse HEAD)
GIT_HASH_SHORT=$(shell git rev-parse --short HEAD)
GIT_BRANCH=$(shell git branch --show-current)

#
# Preprocessor definitions
#
PPDEFS += GIT_HASH=\"$(GIT_HASH)\"
PPDEFS += GIT_HASH_SHORT=\"$(GIT_HASH_SHORT)\"
PPDEFS += GIT_BRANCH=\"$(GIT_BRANCH)\"
PPDEFS += STM32L073xx
PPDEFS += USE_HAL_DRIVER
PPDEFS += SIM7080_UART_USE_FLOW_CTRL=0

#
#Include directories
#
INCDIR += sources/Core/Inc
INCDIR += sources/Drivers/STM32L0xx_HAL_Driver/Inc
INCDIR += sources/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy
INCDIR += sources/Drivers/CMSIS/Device/ST/STM32L0xx/Include
INCDIR += sources/Drivers/CMSIS/Include

#
#Source files
#
SOURCES += sources/Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l073xx.s

SOURCES += $(wildcard sources/Core/Src/*.c)
SOURCES += $(wildcard make/newlib/*.c)

SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_adc.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_adc_ex.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c_ex.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc_ex.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ramfunc.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ex.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_gpio.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dma.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr_ex.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cortex.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_exti.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_lcd.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart_ex.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim.c
SOURCES += sources/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim_ex.c

#
#Linker scripts
#
LDSCRIPT += make/ldscript/stm32l073v8tx_flash.ld

SELFDEP = app.mk

include core.mk
