## *Optionally Install ESPtool*

Windows users mush have Python installed, get it [here](https://www.python.org/downloads/windows/).

OSX users already have Python installed

Follow instructions to install esptool.py [here](https://github.com/themadinventor/esptool)



```
esptool.py --port /dev/tty.SLAB_USBtoUART
  write_flash -fm dio -fs 32m 0x00000 NodeMCU-FW-CaptiveIntraweb.bin
```
