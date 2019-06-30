# I2C devices

This is an I²C driver that display time from RTC in a LCD.

## Requirements
- Raspberry Pi 3 (BCM2837)
- I²C devices:
  - RTC DS3231
  - LCD 16x2

## Installation

```js
export KERNEL_SRC=<kernel-headers-path>

export KTF_INCLUDE_DIRS=<ktf-include-path>

<build-path>$ cmake <i2c-devs-path> -DCMAKE_INSTALL_PREFIX=<installation-path>

make

make install

```
