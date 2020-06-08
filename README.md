ATM90E26 Raspberry Pi port by Giuseppe Conti tested on Raspberry pi 3.

To use it follow the instruction below

1) Make sure you the SPI is enabled on the Rpi 
	how to --> https://www.raspberrypi-spy.co.uk/2014/08/enabling-the-spi-interface-on-the-raspberry-pi/

2) Please install the bcm2835 library from:
	Download & install --> https://www.airspayce.com/mikem/bcm2835/

3) Compile on Rpi as follows:
	g++ -o ATM90E26_SPI ATM90E26_SPI.cpp energyic_SPI.cpp -lbcm2835
    
4) Run as sudo:
	sudo ./ATM90E26_SPI


Connections:

 * Raspberry Pi SPI Pins:
 * SCLK - 23
 * MISO - 21
 * MOSI - 19
 * CS0  - 24
 
