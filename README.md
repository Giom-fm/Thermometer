# Thermometer
A device that measures and displays temperature and relative humidity.

## Motivation
I needed a device to measure the temperature and especially the relative humidity in my room, because my houseplants need a certain air humidity and I didn't know if I had to spray them or not.  
It was important to me to work without external libraries. So the code is 100% self-made. 
I also wanted to work with a "naked" Atmega328P and not with a microcontroller from the Arduino family.
I surely could have made my life easier. But for didactic reasons I had chosen this approach.

## Tech used
An Amtega328P was used as microcontroller. This communicates with the DHT22 sensor via a one-wire bus. For the output a 128x64 0.96" Oled display which is controlled by a SSD1306 controller is used. It communicates with the display via a 4-Wire SPI.

## Roadmap
- [x] Uart as debug output
- [x] One-Wire communication with the DHT22
- [ ] SPI communication with the SSD1306
- [ ] Draw the temperature and humidity on the display
- [ ] PCB design
- [ ] 3D printed housing