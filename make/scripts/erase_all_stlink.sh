#!/bin/bash

openocd -f make/target/stm32l0-relax-openocd.cfg -c "init" -c "halt" -c "flash erase_address 0x08000000 0x10000" -c "exit"
