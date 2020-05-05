/* ATM90E26 Energy Monitor Demo Application

    The MIT License (MIT)

  Copyright (c) 2016 whatnick and Ryzee

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// the sensor communicates using SPI, so include the library:
//#include <SPI.h>
#include <bcm2835.h>
#include <stdio.h>
#include <iostream>


/*******************
 * WEMOS SPI Pins:
 * SCLK - D5
 * MISO - D6
 * MOSI - D7
 * SS   - D8
 *******************/
#include "energyic_SPI.h"

ATM90E26_SPI eic;

int main(int argc, char **argv)
{
  printf("Program started \n");
  if (!bcm2835_init())
     return 1;
  printf("init done! \n");
  bcm2835_spi_begin();
  printf("spi started \n");
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
  printf("MSB sent! \n");
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);                   // The default
  printf("Mode sent! \n");
 // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_2048); // The default
  //bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_4096); // The default
  bcm2835_spi_set_speed_hz(200000);
  printf("Clock Divider sent! \n");
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
  printf("SPI_CS0 sent! \n");
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);    
  eic.InitEnergyIC();

  printf("Sys Status: %02X  \n", eic.GetSysStatus());

 // yield();
  printf("Meter Status: %02X  \n", eic.GetMeterStatus());
  
//  yield();
//Serial.print(":");
//while (1) {
  printf("Voltage %02X  \n", eic.GetLineVoltage());
  printf("Voltage %4.2f  \n", eic.GetLineVoltage());
  printf("Current %4.2f \n", eic.GetLineCurrent());
  printf("Active power: %4.2f \n", eic.GetActivePower());
  printf("p.f.: %4.2f \n", eic.GetPowerFactor());
  delay(500);
//}
 /*
  yield();
  Serial.print("Current:");
  Serial.println(eic.GetLineCurrent());
  
  yield();
  Serial.print("Active power:");
  Serial.println(eic.GetActivePower());
  yield();
  Serial.print("p.f.:");
  Serial.println(eic.GetPowerFactor()); */
  bcm2835_spi_end();
  delay(1000);
}
