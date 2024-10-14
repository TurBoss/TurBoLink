Agon Terminal Client TurBoLink
==============================


https://github.com/TurBoss/TurBoLink

TurboLink Opens Port UART1 from the UEXT and GPIO pin headers and allows you to send and receive data

https://agonconsole8.github.io/agon-docs/GPIO/



Binaries distribution
=====================


Check the releases page for binaries

https://github.com/TurBoss/TurBoLink/releases



Building from sources
=====================


Get z88dk development kit

+ https://z88dk.org
+ https://github.com/z88dk/z88dk
+ https://github.com/z88dk/z88dk/wiki/installation


Obtain the source code using git.

Run make in the root directory of the project


```
git cloen https://github.com/TurBoss/TurBoLink.git
cd TurBoLink
make
```


Should output this 


`z88dk-z80asm -mez80 -b -Iinclude -oturbolink.bin  main.asm`

`turbolink.bin` should have been created



Running on the agon
===================


Copy the bin file to any place on the SD card,

placing it on /MOS has issues don't place the bin there


```
/ *load turbolink.bin
/ *run
```



Dial some server
================


Using a modem to dial bbs servers


+ Zimodem esp32 https://github.com/bozimmerman/Zimodem
+ espressiff AT es8266 & esp32 https://www.espressif.com/en/support/download/at
+ PicoWifiModem Easpberry Pi Pico W https://github.com/mecparts/PicoWiFiModem/
+ tcpser PC + rs232 ttl adapter https://github.com/FozzTexx/tcpser


This may depend on your modem but should be similar to this



```
ATDTserver.address:port
```

Please refer to each modem At commands reference docs


