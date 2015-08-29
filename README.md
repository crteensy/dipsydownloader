# dipsydownloader
(arduino compatible) C++ library for configuring a Lattice iCE40UL FPGA via SPI

Written for DIPSY: https://hackaday.io/project/6592-dipsy

The aim here is to provide an interface that
- accepts almost any source for configuration data (array, EEPROM, SD card, some command line interface over UART, ...)
- can use every peripheral interface that exposes an interface that looks like an arduino SPI (hardware SPI, bit-banged software SPI, ...)
