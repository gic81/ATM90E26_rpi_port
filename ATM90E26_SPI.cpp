/* ATM90E26 Energy Monitor Demo Application

    The MIT License (MIT)

  Copyright (c) 2016 whatnick and Ryzee

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/***
Raspberry Pi port by Giuseppe Conti    @gic81 -- giuseppe@altervista.it
***/
// the sensor communicates using SPI, the Raspberry Pi use bcm2835.h so include the library:
#include <bcm2835.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>


/*******************
 * Raspberry Pi SPI Pins:
 * SCLK - 23
 * MISO - 21
 * MOSI - 19
 * CS0  - 24
 *******************/
#include "energyic_SPI.h"

ATM90E26_SPI eic;

int config_spi() {
  if (!bcm2835_init())
     return 1;

  bcm2835_spi_begin();
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);                   
  //SPI interface rate is 200 to 160k bps. It Will need to be slowed down for EnergyIC
  //bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_2048); // The default
  //bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_4096); // The default
  bcm2835_spi_set_speed_hz(200000);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW); 
  printf("Raspberry Pi SPI configuration complete! \n");
  return 0;
}

int main(int argc, char **argv)
{
  if (config_spi())
    return 1;
  //usleep(10);   
  eic.InitEnergyIC();
  printf("Sys Status: %02X  \n", eic.GetSysStatus());
  printf("Meter Status: %02X  \n", eic.GetMeterStatus());
  printf("press a key to exit  \n");
 
  while (1) {
    usleep(500000);
    //sleep(1);
    printf("Voltage %4.2f  \n", eic.GetLineVoltage());
    printf("Current %4.2f \n", eic.GetLineCurrent());
    printf("Active power: %4.2f \n", eic.GetActivePower());
    printf("p.f.: %4.2f \n", eic.GetPowerFactor());
  }
 bcm2835_spi_end();
}
