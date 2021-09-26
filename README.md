# StacKlipper
Wireless remote controller for Klipper 3D printers

# Description
StacKlipper is a remote controller for Klipper 3D printers made by M5Stack.
This program is derived from the sample program of M5TreeView.

# Build
First of all, Get your M5Stack.

Add two external library to Arduino IDE.
* M5TreeView         https://github.com/lovyan03/M5Stack_TreeView
* M5OnScreenKeyboard https://github.com/lovyan03/M5OnScreenKeyboard

You also have to add ESP32 Arduino board libraly, Arduino M5Stack library, and Arduino_JSON library.

Open StacKilipper.ino via Arduino IDE and edit SSID, PASSWORD, Klipper IP adress as yours. Then build it.

# Screenshot
![image0(1)](https://user-images.githubusercontent.com/3067670/134805837-d0115359-6195-484d-8ded-0dcf1a991599.jpeg)

# What can do
* Show status of the 3D printer 
* Set Bed and Nozzle temperature
* Move Home position and any XYZ position
* Reset firmware
* Emergency stop (M112)

# To do
* Support Bluetooth connection Klipper server and M5Stack.

# Licence
GPLv3

# Acknowledgments
lovyan03 (https://github.com/lovyan03/), who create M5TreeView and M5OnScreenKeyboard.

Discord group Klipper_jp (https://discord.com/channels/889871356609581086/), provided information and suggestion about this program.
