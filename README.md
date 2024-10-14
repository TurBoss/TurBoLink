Building from sources
=====================

Get z88dk development kit


+ https://github.com/z88dk/z88dk
+ https://github.com/z88dk/z88dk/wiki/installation



to build run make in the root directory of the project

```
make
```
should output this 

`z88dk-z80asm -mez80 -b -Iinclude -oturbolink.bin  main.asm`
and `turbolink.bin` should have been created


Running on the agon
===================

copy the bin file to any place on the SD card,  placing it on /MOS has issues don't place the bin there


```
/ *load turbolink.bin
/ * run
```

Dial some server
================



+ Zimodem esp32 https://github.com/bozimmerman/Zimodem
+ espressiff AT es8266 & esp32 https://www.espressif.com/en/support/download/at
+ PicoWifiModem Easpberry Pi Pico W https://github.com/mecparts/PicoWiFiModem/
+ tcpser PC + rs232 ttl adptor https://github.com/FozzTexx/tcpser


This may depend on your modem but should be similar to this



```
ATDTserver.address:port
```

refer to each modem At commands doc