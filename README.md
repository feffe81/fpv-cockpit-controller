# FPV Cockpit
Soft and hardware for creating a functional cockpit used for controlling RC drones/planes with a flight stick and rudder pedals as well as a thrust lever.

## Overview


# Instructions


# Part list

## Hardware
### Rudder pedals
I use two of these as rudder pedals: [5V scooter pedal](https://www.amazon.de/XFUYI-Elektro-Scooter-Fu%C3%9Fpedal-Gasgriff-E-Elektro-Dreirad-Pedal-Geschwindigkeitsregelung-Braun/dp/B0DZCVHP1T/ref=sr_1_52?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=1AF7EJG1U2Q8Q&dib=eyJ2IjoiMSJ9.0zo3uY2syh4c520tf6m-wx2U24Q27wWn2Y6a9vBiXjw26Ukakg27CDL59ZUhxyvHg3t4bipouGHzhsgzciDN3QyfNE_a5mj5hg54hcWFHmIO2fspOHSD_cFuyrQN6Sb5zM9uoIgV5NSL0Ee8SIC2dWLel4ODeAQJa-fDfLHWdtYFjavNMAnKJ2LuDS6dj8QMcucVpfrAnThVmA-x65RubmEKHFya8YazTCQIy0pZLpew46xIV-phQhXBz4gUkmtGIetZRRSXLr2y6V3aLY-sfqvpp4iDX7w9OYCuG3DY4ZM.uREC5iUgX4aYnahMFY9sXlDJ5pyNyYcXpcXJsZi-2Uw&dib_tag=se&keywords=5v+scooter+pedal&qid=1745588133&sprefix=5v+scoote+rpeda%2Caps%2C133&sr=8-52)

And then I use a https://store.arduino.cc/en-de/products/arduino-nano to mix the two analog signals. You can find the source code in the folder 'rudder-pedal-mixer'

### Flight Stick position sensor
I used an https://store.arduino.cc/products/arduino-nano-33-ble-with-headers and programmed it with the https://headtracker.gitbook.io/head-tracker software via the windows GUI. Just connect via USB and upload the firmware. Not need for a separate bootloader upfront.

### Thrust lever
I use an P3022-V1-CW360 angular sensor and connected it via a voltage divider to the flight stick position sensor Arduino: https://de.aliexpress.com/item/1005005806329401.html?gatewayAdapt=glo2deu

## 3D models
### Rudder pedals
Box for Arduino based mixer unit: TBD

### Flight stick
I used this model as a flight stick and added a potentiometer in one of the holes to adjust the flaps: https://www.printables.com/model/202391-digital-arcade-flightstick-3-the-raptor-stl-versio

### Thrust lever
I used this model as a basis for my print so I could integrate the angular sensor: https://www.printables.com/model/903412-big-lever
 
## Software

### Head Tracker
This project I use without modifications in two Arduino Nano BLE 33 for head and flightstick movement as well as to ingest the analog values from the
* Rudder Pedal
* Thrust lever
* Flap Switch
  
https://headtracker.gitbook.io/head-tracker
