# Wilderness Wireless Map

## INTRODUCTION

### About

The following are instructions for making your very own Solar-Powered Wilderness Wireless WiFi Access Point and Web Server. When you are finished, there will be an access point (AP) with a name (SSID) of your own choosing. When you or someone else connects to this AP with a phone or computer, a captive portal page will open, displaying a web page of your own design, not unlike the captive portal pages of some paid public wifi networks. This personal area network (PAN) is not connected to the internet and does not provide a route to any place on the internet. This AP is in essence its own internet. After connecting, all http requests are resolved to the internal address. The information contained here has been pulled from many difference sources and integrates the work of many others without whose work this project would not be possible. Please see the references.md file for acknowedgements and links to sources.

### Materials and Tools

A comprehensive list of materials is provided as an Adafruit wishlist that can be accessed [here]() You may try to source materials from other places, but there is no guarantee the project will work as expected. This project involves soldering, so a basic set of electronics tools is required. Here's a general list of useful things:
 * Soldering iron
 * Soldering Iron Tip Cleaner
 * Solder
 * Wire Strippers
 * Wire Cutters
 * Needle Nose Pliers
 * Multimeter
 * Lighter or Heat Gun

### Disclaimer

This information is provided free and without warranty. I offer no guarantee that this project will work as stated. The author or any of the included sources are not responsible for any wrongdoing, damage, transgression of rules, laws or regulations. Use at your own risk.

### License

**CC** Creative Commons Attribution, Non-Commercial Share-Alike

## PHASE 1

### Prepare and Solder Hardware

- **Solder Capacitor on Charger**
  * You can find instructions from Adafruit [here](https://learn.adafruit.com/usb-dc-and-solar-lipoly-charger/solar-charger-preparation)


- **Solder JST connector**
  * The Adafruit charger comes with a JST connector with bare wire ends. It is difficult to  plug these tiny wires into a breadboard, so cut a jumper wire in half, solder each end to a bare wire. Use heat-shring tubing to insulate wires. Hold onto this DIY cable for now...


- **Solder Headers on the Feather**
  * The Adafruit Feather Huzzah ESP8266 comes with male header pins. You must cut the headers to the correct length and solder them to the board. You can find instructions from Adafruit [here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide?view=all#assembly)


- **Charge Battery**
  * Plug the LiPoly battery's JST connector into the BATT port on the charger. You can charge the battery by connecting the charger to your laptop or a wall adapter/charger with a mini USB cable.

### Install Software Tools and Their Dependencies

! _WIN users might have an easier time using NodeMCU Flasher instead of setting up python, etc. It can be found [here](https://github.com/nodemcu/nodemcu-flasher)_

  - **Prepare esptool.py**
    * The Adafruit Feather already has NodeMCU firmware installed, but we need to use a custom version for our web server to work properly. The firmware is flashed to the Feather using a Python tool called esptool.py. You must first determine if you have Python installed.
      * **OSX:** Open Terminal (if you don't know where it is, search in spotlight). Type ``` python --version``` in the terminal. You should see something like ```Python 2.7.10``` returned. If not, skip down to Python installation.
      * **WIN:** Search for run or run.exe. Type CMD in the run dialog box. The command line terminal should open. Type ``` python --version``` in the terminal. You should see something like ```Python 2.7.10``` returned. If not, skip down to Python installation.
    * Install Python if you don't have it. Get it [here](https://www.python.org/downloads/)
    * esptool.py is a python program that will help you flash firmware to the Feather. You can find instructions [here](https://github.com/espressif/esptool)
  * **Install VCPdrivers for Feather:** The Feather uses a Silicon Labs CP2104 USB-Serial converter onboard with 921600 max baudrate for uploading. You must install drivers for this chip before connecting it to your computer and flashing the firmware. Download and install the Virtual Com Port drivers for you operating system [here](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx)
  * **Connect Feather to your computer with a micro USB cable.**
  * **Locate firmware.** The firmware for the Feather is located in the _firmware_ folder in this repository. It is easiest to navigate to that folder using your command line terminal. The firmware file is: ```NodeMCU-FW-CaptiveIntraweb.bin```
  * **Flash Firmware:** With Python, esptool.py and VCP drivers now installed, flash the firmware using this command in your terminal:
  ```
  esptool.py --port /dev/tty.SLAB_USBtoUART
    write_flash -fm dio
    -fs 32m 0x00000
    NodeMCU-FW-CaptiveIntraweb.bin
  ```
  The device you are flashing is usually ```/dev/tty.SLAB_USBtoUART``` on OSX or something like ```COM3``` on Windows. Replace ```/dev/tty.SLAB_USBtoUART``` with the correct port if different.



  ## PHASE 2

  ### Communicating With Feather

  Communication with the Feather NodeMCU firmware can be done via a Serial Terminal Application like CoolTerm (WIN/OSX) or Screen (OSX/NIX). A useful application is ESPLorer which provides a FTP-like interface for manipulating files on the Feather. Since we are going to use the Feather as a Web Server, this seems like the best tool for the job. ESPlorer application is a cross-platform Java application. You can get it from the Download it from the _tools_ folder in this repository or alternatively download it [here](http://esp8266.ru/esplorer/). Since ESPLorer is a java application, you need to have a recent version of the Java Runtime Environment (JRE) installed on your machine to use it. Try to open the _**ESPLorer.jar**_ file. If it doesn't open, you probably don't have java installed. The JRE is free and can be downloaded [here](http://www.oracle.com/technetwork/java/javase/downloads/jre8-downloads-2133155.html).

  ### Edit Server Files

  This is your own access point and webserver. You have control over the name of the accesspoint and the content of the web page. In keeping with the idea of wilderness wireless, think about what you might name your AP. Does a wilderness wireless network use a particular language? Does it have to be intelligible? Think about stumbling across a wireless network in the wilderness where there are no others around. What kind of content might you find in this network? Is it text, an image, perhaps just a color? 

  ### Upload Server Files

  ## PHASE 3

  ### Breadboard circuit
