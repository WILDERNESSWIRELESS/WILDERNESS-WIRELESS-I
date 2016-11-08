# Wilderness Wireless Map

## PHASE 1

### Prepare and Solder Hardware

- **Solder Cap on Charger**
  * You can find instructions from Adafruit [here](https://learn.adafruit.com/usb-dc-and-solar-lipoly-charger/solar-charger-preparation)


- **Solder JST connector**
  * The Adafruit charger comes with a JST connector with bare wire ends. It is difficult to  plug these tiny wires into a breadboard, so cut a jumper wire in half, solder each end to a bare wire. Use heat-shring tubing to insulate wires. Hold onto this DIY cable for now...


- **Solder Headers on the Feather**
  * The Adafruit Feather Huzzah ESP8266 comes with male header pins. You must cut the headers to the correct length and solder them to the board. You can find instructions from Adafruit [here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide?view=all#assembly)


- **Charge Battery**
  * Plug the LiPoly battery's JST connector into the BATT port on the charger. You can charge the battery by connecting the charger to your laptop or a wall adapter/charger with a mini USB cable.

  ### Install Tools and Their Dependencies

  - **Prepare esptool.py**
    * The Adafruit Feather already has NodeMCU firmware installed, but we need to use a custom version for our web server to work properly. The firmware is flashed to the Feather using a Python tool called esptool.py. You must first determine if you have Python installed.
      * **OSX:** Open Terminal (if you don't know where it is, search in spotlight). Type ``` python --version``` in the terminal. You should see something like ```Python 2.7.10``` returned. If not, skip down to Python installation.
      * **WIN:** Search for run or run.exe. Type CMD in the run dialog box. The command line terminal should open. Type ``` python --version``` in the terminal. You should see something like ```Python 2.7.10``` returned. If not, skip down to Python installation.
    * Install Python if you don't have it. Get it [here](https://www.python.org/downloads/)
    * esptool.py is a python program that will help you flash firmware to the Feather. You can find instructions [here](https://github.com/espressif/esptool)
  * Install VCPdrivers for Feather. The Feather uses a Silicon Labs CP2104 USB-Serial converter onboard with 921600 max baudrate for uploading. You must install drivers for this chip before connecting it to your computer and flashing the firmware. Download and install the Virtual Com Port drivers for you operating system [here](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx)
  * Connect Feather to your computer with a micro USB cable.
  * Locate firmware. The firmware for the Feather is located in the **firmware** folder in this repository. It is easiest to navigate to that folder using your command line terminal. The firmware file is: ```NodeMCU-FW-CaptiveIntraweb.bin``` With Python, esptool.py and VCP drivers now installed, flash the firmware using this command in your terminal:
  ```
  esptool.py --port /dev/tty.SLAB_USBtoUART
    write_flash -fm dio
    -fs 32m 0x00000
    NodeMCU-FW-CaptiveIntraweb.bin
  ```
  The device you are flashing is usually ```/dev/tty.SLAB_USBtoUART``` on OSX or something like ```COM3``` on Windows. Replace ```/dev/tty.SLAB_USBtoUART``` with the correct port if different.
