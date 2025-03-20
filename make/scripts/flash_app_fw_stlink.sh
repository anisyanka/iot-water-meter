#!/bin/bash

make app
openocd -f make/target/stm32l0-relax-openocd.cfg -c "init" -c "halt" -c "flash write_image erase build-app/app.bin 0x8000000" -c "reset" -c "exit"
