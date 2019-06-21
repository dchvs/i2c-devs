# I2C devices

## Installation

```js
export KERNEL_SRC=<kernel-headers-path>

export KTF_INCLUDE_DIRS=<ktf-include-path>

<build-path>$ cmake <i2c-devs-path> -DCMAKE_INSTALL_PREFIX=<installation-path>

make

make install

make driver_install
```
