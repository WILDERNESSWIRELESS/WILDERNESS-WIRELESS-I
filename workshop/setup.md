# Wilderness Wireless Setup

## :floppy_disk: Install VCP (Virtual COM Port) Drivers for CP210x

* Download from [Silicon Labs](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx).

## :floppy_disk: Install ESPtool

Windows users mush have Python installed, get it [here](https://www.python.org/downloads/windows/).

OSX users already have Python installed

Follow instructions to install esptool.py [here](https://github.com/themadinventor/esptool)

WIN users might have an easier time using NodeMCU Flasher instead of setting up python, etc. It con be found [here](https://github.com/nodemcu/nodemcu-flasher)

## :floppy_disk: Grab Firmware

NodeMCU Firmware releases can be found [here](https://github.com/nodemcu/nodemcu-firmware/releases).

The default Adafruit NodeMCU firmware is __0.9.5 build 20150318__

The firmware for the Captive Intraweb is in the CaptiveIntraweb repository listed below.

OSX Terminal Command to flash ESP8266 with firmware. ```NodeMCU-FW-CaptiveIntraweb.bin``` should be replaced with the proper firmware filename.
```
esptool.py --port /dev/tty.SLAB_USBtoUART
  write_flash -fm dio
  -fs 32m 0x00000
  NodeMCU-FW-CaptiveIntraweb.bin
```


## Grab ESPlorer

Download it from [here](http://esp8266.ru/esplorer/).

ESPlorer is a cross-platform tool for working with the ESP8266. It is written in Java, so if it doesn't run on either OSX or WIN, grab the latest JRE (Java Runtime Environment) from [Oracle](http://www.oracle.com/technetwork/java/javase/downloads/jre8-downloads-2133155.html).

## :book: Read the NodeMCU Documentation
Take a look [here](https://nodemcu.readthedocs.io/en/master/).

## :electric_plug: Adafruit's Introduction to the Hardware

Take a look [here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266).

## Grab the CaptiveIntraweb code from github

Find it [here](https://github.com/reischle/CaptiveIntraweb)
