
/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

/*
 * Pins descriptions
 * TCC0 IOSET4
 * TCC1 IOSET2
 * TCC2 IOSET1
 * TCC3 IOSET1
 * TCC4 IOSET1
 */
const PinDescription g_APinDescription[]=
{
 /*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 00         | D0               |  PA23  |                 |  *07   |     |     | X11 |     |   4/01  |   1/07  |* TC4/1 | TCC1/7 |          | GCLK_I7  |
 | 01         | D1               |  PA22  |                 |  *06   |     |     | X10 |     |   4/00  |   1/06  |* TC4/0 | TCC1/6 | USB/SOF  | GCLK_I6  |
 | 02         | D2               |  PC18  |                 |   2    |     |     |     |     |   6/02  |   0/02  |        | TCC0/2 |          |          |
 | 03         | D3               |  PC19  |                 |   3    |     |     |     |     |   6/03  |   0/03  |        | TCC0/3 |          |          |
 | 04         | D4               |  PC20  |                 |   4    |     |     |     |     |         |         |        | TCC0/4 |          | GCLK_I9  |
 | 05         | D5               |  PC10  |                 |   5    |     |     |     |     |         |         |        | TCC0/5 |          | GCLK_I10 |
 | 06         | D6               |  PA12  |                 |   12   |     |     |     |     |   2/00  |   4/01  |*TC2/0  |*TCC0/6 |          |          |	//TCC1/2
 | 07         | D7               |  PA13  |                 |   13   |     |     |     |     |   2/01  |   4/00  |*TC2/1  |*TCC0/7 |          |          |	//TCC1/3
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
  { PORTA, 23, PIO_SERCOM_ALT, PIN_ATTR_PWM_E, No_ADC_Channel, PWM4_CH1, TC4_CH1, EXTERNAL_INT_7 },    // TX2: SERCOM5/PAD[0]
  { PORTA, 22, PIO_SERCOM_ALT, PIN_ATTR_PWM_E, No_ADC_Channel, PWM4_CH0, TC4_CH0, EXTERNAL_INT_6 },    // RX2: SERCOM5/PAD[1]
  { PORTC, 18, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, PWM0_CH2, TCC0_CH2, EXTERNAL_INT_NONE },
  { PORTC, 19, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, PWM0_CH3, TCC0_CH3, EXTERNAL_INT_NONE },
  { PORTC, 20, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, PWM0_CH4, TCC0_CH4, EXTERNAL_INT_4 },
  { PORTC, 10, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_10 },          //changed on rev XB   previously pc21
  { PORTA, 12, PIO_PWM, PIN_ATTR_PWM_G, No_ADC_Channel, PWM1_CH2, TCC1_CH2, EXTERNAL_INT_12 },    	//DE_TB2 Serial Shield
  { PORTA, 13, PIO_PWM, PIN_ATTR_PWM_G, No_ADC_Channel, PWM1_CH3, TCC1_CH3, EXTERNAL_INT_13 },

  /*
  +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
  | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
  |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
  |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |       SPI        |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  | 08         | MOSI             |  PD08  |                 |  *03   |     |     |     |     |  *7/00  |  6/01   |        | TCC0/1 |          |          |
  | 09         | BCK              |  PD09  |                 |  *04   |     |     |     |     |  *7/01  |  6/00   |        | TCC0/2 |          |          |
  | 10         | MISO             |  PD11  |                 |   06   |     |     |     |     |   7/03  |  6/03   |        | TCC0/4 |          |          |
  +------------+------------------+--------+-----------------+--------------------+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |       Wire       |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  | 11         | SDA              |  PB20  |                 |   04   |     |     |     |     |  *3/00  |  7/01   |        | TCC1/2 |          |          |
  | 12         | BCL              |  PB21  |                 |   05   |     |     |     |     |  *3/01  |  7/00   |        | TCC1/3 |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |      Serial1     |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  | 13         | RX               |  PB13  |                 |   13   |     |     | x13 |     |         |  *4/01  |        |        | can1/RX  |          |
  | 14         | TX               |  PB12  |                 |   12   |     |     | x12 |     |         |  *4/00  |        |        | can1/TX  |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  */
  //SPI
  //8..10
  { PORTD, 8, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_3 },   			// MOSI
  { PORTD, 9, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },   	// BCK
  { PORTD, 11, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, PWM0_CH4, TCC0_CH4, EXTERNAL_INT_NONE },  			// MISO

  //I2C
  //11..12
  { PORTB, 20, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  	//same as SDA
  { PORTB, 21, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, PWM1_CH3, TCC1_CH3, EXTERNAL_INT_NONE },  			//same as SCL

  //SERIAL1
  //13..14
  { PORTB, 13, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },     	// UART1_RX
  { PORTB, 12, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },     	// UART1_TX


  /*
  +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
  | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
  |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
  |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  | 15         | A0 / DAC0        |  PA02  |                 |   02   | *A00 |    | Y00 | OUT |         |         |        |        |          |          |
  | 16         | A1               |  PA05  |                 |  *05   | *A05 |    | Y03 |     |         |   0/RX  | TC0/1 |        |          | GCLK_I1  |
  | 17         | A2               |  PB00  |                 |  *03   | *A15 |    | Y09 |     |         |   5/RX  | TC6/1  |        |          |          |
  | 18         | A3               |  PC00  |                 |   00   | *B10 |    |     |     |         |         |        |        |          |          |
  | 19         | A4               |  PC01  |                 |   01   | *B11 |    |     |     |         |         |        |        |          |          |
  | 20         | A5               |  PC02  |                 |   02   | *B04 |    |     |     |         |         |        |        |          |          |
  | 21         | A6               |  PC03  |                 |   03   | *B05 |    |     |     |         |         |        |        |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  */
  //Analog
  // A0(15)..A6(21)
  { PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 5, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel5, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_5 },
  { PORTB, 0, PIO_ANALOG, PIN_ATTR_PWM_E, ADC_Channel15, PWM7_CH0, TC7_CH0, EXTERNAL_INT_0 },                       //changed on rev XB previously pb03
  { PORTC, 0, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel10, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0 },         //NOT ON TIMER
  { PORTC, 1, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel11, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1 },       //NOT ON TIMER
  { PORTC, 2, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTC, 3, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },        //DE_TB1 Serial Shield

  /*
  +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
  | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
  |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
  |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |       USB        |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  | 22         |                  |  PA24  | USB N           |   12   |     |     |     |     |   3/02  |   5/02  |  TC5/0 | TCC1/2 | USB/DM   |          |
  | 23         |                  |  PA25  | USB P           |   13   |     |     |     |     |   3/03  |   5/03  |  TC5/1 | TCC1/3 | USB/DP   |          |
  | 24         |                  |  PA27  | USB ID          |   02   |     |     | X06 |     |   1/02  |   3/02  |  TC3/0 | TCC0/2 |          | AC/CMP0  |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  | 25         | AREF             |  PA03  |                 |   03   |  01 |     | Y01 |     |         |         |        |        |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  */
  // 85..86 - Alternate use of A0 and A1 (DAC output)
  // { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },   // DAC/VOUT[0]
  // { PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 },   // DAC/VOUT[1]    //not a DAC pin on p1am-100 will leave in for now
  // 77..79 - USB
  // --------------------
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },        // USB/DM
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },        // USB/DP
  { PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // USB Host enable
  // 84 (AREF)
  { PORTA, 3, PIO_ANALOG, PIN_ATTR_ANALOG, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // DAC/VREFP

  //---------------------------------------------------------------------------------------------------------------------------------------------------------
  /*
  +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
  | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
  |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
  |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |    SD SPI        |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  |  26        |                  | PB27   |  SD_BCK         |  13    |     |     |     |     |  2/01   |  4/00   |        |        |          |          |
  |  27        |                  | PB26   |  SD_MOSI        |  12    |     |     |     |     |  2/00   |  4/01   |        |        |          |          |
  |  28        |                  | PB28   |  SD_NSS         |  14    |     |     |     |     |  2/02   |  4/02   |        |        |          |          |
  |  29        |                  | PB29   |  SD_MISO        |  15    |     |     |     |     |  2/03   |  4/03   |        |        |          |          |
  |  30        |                  | PB31   |  SD_CD          |  15    |     |     |     |     |  7/01   |  5/00   |        |        |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |  31        |                  | PB02   |  SWITCH_BUILTIN |  02    | A14 |     | Y8  |     |  5/00   |         |  TC6/0 |        |          | GCLK_O1  |
  |  32        |                  | PB01   |  LED_BUILTIN    |  01    | A13 |     | Y7  |     |  5/03   |         |  TC7/1 |        |          | GCLK_I1  |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  */
  // 80..83 - SD SPI pins (SD:MISO,BCK,MOSI,CS)
  // ----------------------
  { PORTB, 27, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },             //SD_BCK
  { PORTB, 26, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },             //SD_MOSI
  { PORTB, 28, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },             //SD_NSS
  { PORTB, 29, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },             //SD_MISO
  { PORTB, 31, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },            //SD_CD
  //Faceplate stuff
  { PORTB, 2, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },            //RUN SWITCH
  { PORTB, 1, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER,  EXTERNAL_INT_NONE },           //LED pin
  
  //---------------------------------------------------------------------------------------------------------------------------------------------------------
  /*
  +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
  | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
  |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
  |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |    I2C_INTERNAL  |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  |  33        |                  | PC17   |  BCL_INT        |  1     |     |     |     |     |  6/01   |  0/00   |        |        |          |          |
  |  34        |                  | PC16   |  SDA_INT        |  0     |     |     |     |     |  6/00   |  0/01   |        |        |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |    FLASH_SPI     |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  |  35        |                  | PB10   |  FLASH_BCK      |  10    |     |     |     |     |         |  4/02   | TC5/00 |        |          |          |
  |  36        |                  | PB11   |  FLASH_CS       |  11    |     |     |     |     |         |  4/03   | TC5/01 |        |          |          |
  |  37        |                  | PA08   |  FLASH_IO0      |  NMI   |A8/B2|     | X0  |     |  0/00   |  2/01   | TCC0/00| TCC1/02|   QSPID0 | GCLK_I3  |
  |  38        |                  | PA09   |  FLASH_IO1      |  9     |A9/B3|     | X1  |     |  0/01   |  2/00   | TCC0/01| TCC1/03|   QSPID1 | GCLK_I4  |
  |  39        |                  | PA10   |  FLASH_IO2      |  15    |     |     |     |     |  2/03   |  4/03   |        |        |   QSPID2 | GCLK_I5  |
  |  40        |                  | PA11   |  FLASH_IO3      |  15    |     |     |     |     |  7/01   |  5/00   |        |        |   QSPID3 | GCLK_O1  |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |    BC            |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  |  41        |                  | PC11   |  BC_EXTRA       |  11    |     |     |     |     |  6/03   | 7/03    |        |        |          |          |
  |  42        |                  | PC22   |  BC_MOSI        |  06    |     |     |     |     |  1/00   | 3/01    |        |        |          |          |
  |  43        |                  | PC23   |  BC_BCK         |  07    |     |     |     |     |  1/01   | 3/00    |        |        |          |          |
  |  44        |                  | PD20   |  BC_CS          |  10    |     |     |     |     |  1/02   | 3/02    |        |        |          |          |
  |  45        |                  | PD21   |  BC_MISO        |  11    |     |     |     |     |  1/03   | 3/03    |        |        |          |          |
  |  46        |                  | PB17   |  BASE ENABLE    |  01    |     |     |     |     |  5/01   |         |  TC6/1 |        |          | GCLK_I11 |
  |  47        |                  | PB16   |  BC_READY   |  00    |     |     |     |     |  5/00   |         |  TC6/0 |        |          | GCLK_O3  |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |  48        |                  | PC31   |  BP_PGOOD       |  01    | A13 |     | Y7  |     |  5/03   |         |  TC7/1 |        |          | GCLK_I1  |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |  49        |                  | PC24   |  NEOPIXEL       |        |     |     |     |     |        |         |         |        |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  */
  //internal I2C connected to AT24MAC
  { PORTC, 17, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },      // BCL_1 internal
  { PORTC, 16, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },      // SDA_1 internal
  // ----------------------
  // 89 - 94 QSPI (BCK, CS, IO0, IO1, IO2, IO3)
  { PORTB, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },     //flash_BCK
  { PORTB, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },     //FLASH_CS
  { PORTA, 8, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI },     //flash_IO0
  { PORTA, 9, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },       //flash_I01
  { PORTA, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },     //flash_IO2
  { PORTA, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },     //flash_IO3
  // ----------------------
  //BC
  { PORTC, 11, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },    //BC Extra
  { PORTC, 22, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // Sercom1[0] MOSI  //BC_mosi
  { PORTC, 23, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // Sercom1[1]BCK    //BC_BCK
  { PORTD, 20, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },	  //Sercom1[2]SS (Implemented as GPIO)   //BC_cs
  { PORTD, 21, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },	    //Sercom1[3] MISO     //BC_miso
  { PORTB, 17, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // Base Enable
  { PORTB, 16, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },            // BC_READY
  // ----------------------
  { PORTC, 31, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },   // BP_PGOOD checks that 24V is applied
  { PORTC, 24, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER,  EXTERNAL_INT_NONE }, //NEOPIXEL PIN

};

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TCC3, TCC4, TC0, TC1, TC2, TC3, TC4, TC5, TC6, TC7 };
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM+TC_INST_NUM] = { TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TCC3_GCLK_ID, TCC4_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID, TC4_GCLK_ID, TC5_GCLK_ID, TC6_GCLK_ID, TC7_GCLK_ID };


// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 );
SERCOM sercom1( SERCOM1 );
SERCOM sercom2( SERCOM2 );
SERCOM sercom3( SERCOM3 );
SERCOM sercom4( SERCOM4 );
SERCOM sercom5( SERCOM5 );
SERCOM sercom6( SERCOM6 );
SERCOM sercom7( SERCOM7 );

Uart Serial1( &sercom4, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX );
Uart Serial2 (&SERCOM_SERIAL2, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX);

void SERCOM5_0_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM5_1_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM5_2_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM5_3_Handler()
{
  Serial2.IrqHandler();
}

void SERCOM4_0_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM4_1_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM4_2_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM4_3_Handler()
{
  Serial1.IrqHandler();
}


