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

#ifndef _VARIANT_P1AM_200
#define _VARIANT_P1AM_200

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK        (F_CPU)

#define VARIANT_GCLK0_FREQ (F_CPU)
#define VARIANT_GCLK1_FREQ (48000000UL)
#define VARIANT_GCLK2_FREQ (100000000UL)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT           (49)
#define NUM_DIGITAL_PINS     (40)
#define NUM_ANALOG_INPUTS    (7)
#define NUM_ANALOG_OUTPUTS   (1)
#define analogInputToDigitalPin(p) ((p < 8) ? 67 + (p) : (p < 16) ? 54 + (p) - 8 : (p < 18) ? 12 + (p) - 16 : (p == 18) ? 9 : -1)

#define digitalPinToPort(P)        ( &(PORT->Group[g_APinDescription[P].ulPort]) )
#define digitalPinToBitMask(P)     ( 1 << g_APinDescription[P].ulPin )
#define portOutputRegister(port)   ( &(port->OUT.reg) )
#define portInputRegister(port)    ( &(port->IN.reg) )
#define portModeRegister(port)     ( &(port->DIR.reg) )
#define digitalPinHasPWM(P)        ( g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER )

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

// LEDs
#define PIN_LED             (32)
#define LED_BUILTIN         PIN_LED
#define NEOPIXEL_PIN		(49)

/*
 * Analog pins
 */
#define PIN_A0              (15)
#define PIN_A1              (PIN_A0 + 1)
#define PIN_A2              (PIN_A0 + 2)
#define PIN_A3              (PIN_A0 + 3)
#define PIN_A4              (PIN_A0 + 4)
#define PIN_A5              (PIN_A0 + 5)
#define PIN_A6              (PIN_A0 + 6)


#define PIN_DAC0            PIN_A0
#define PIN_DAC1            PIN_A1

static const uint8_t A0   = PIN_A0;
static const uint8_t A1   = PIN_A1;
static const uint8_t A2   = PIN_A2;
static const uint8_t A3   = PIN_A3;
static const uint8_t A4   = PIN_A4;
static const uint8_t A5   = PIN_A5;
static const uint8_t A6   = PIN_A6;


static const uint8_t DAC0 = PIN_DAC0;
static const uint8_t DAC1 = PIN_DAC1;

#define ADC_RESOLUTION		  12

// Other pins
#define PIN_ATN             (39)
static const uint8_t ATN = PIN_ATN;

/*
 * Ethernet interfaces
 */
#define PIN_SPI_SS_ETHERNET_LIB		5

/*
 * Serial interfaces
 */

// Serial1
#define PIN_SERIAL1_RX      (13)
#define PIN_SERIAL1_TX      (14)
#define PAD_SERIAL1_TX      (UART_TX_PAD_0)
#define PAD_SERIAL1_RX      (SERCOM_RX_PAD_1)
							//sercom0


// Serial2
#define PIN_SERIAL2_RX      (0)
#define PIN_SERIAL2_TX      (1)
#define PAD_SERIAL2_TX      (UART_TX_PAD_0)
#define PAD_SERIAL2_RX      (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL2		sercom5

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 3

#define PIN_SPI_MISO        (10)
#define PIN_SPI_MOSI        (8)
#define PIN_SPI_SCK         (9)
#define PERIPH_SPI          sercom7
#define PAD_SPI_TX          SPI_PAD_0_SCK_1
#define PAD_SPI_RX          SERCOM_RX_PAD_3

static const uint8_t SS	  = (2);
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#define PIN_SPI1_MISO       (29)
#define PIN_SPI1_MOSI       (27)
#define PIN_SPI1_SCK        (26)
#define PIN_SPI1_SS         (28)
#define PERIPH_SPI1         sercom2
#define PAD_SPI1_TX         SPI_PAD_0_SCK_1
#define PAD_SPI1_RX         SERCOM_RX_PAD_3

static const uint8_t SS1	 = PIN_SPI1_SS;
static const uint8_t MOSI1 = PIN_SPI1_MOSI;
static const uint8_t MISO1 = PIN_SPI1_MISO;
static const uint8_t SCK1  = PIN_SPI1_SCK;

// Needed for SD library
#define SDCARD_SPI          SPI1
#define SDCARD_MISO_PIN     PIN_SPI1_MISO
#define SDCARD_MOSI_PIN     PIN_SPI1_MOSI
#define SDCARD_SCK_PIN      PIN_SPI1_SCK
#define SDCARD_SS_PIN       PIN_SPI1_SS


#define PIN_SPI2_MISO       (45)
#define PIN_SPI2_MOSI       (42)
#define PIN_SPI2_SCK        (43)
#define PERIPH_SPI2         sercom1
#define PAD_SPI2_TX         SPI_PAD_0_SCK_1
#define PAD_SPI2_RX         SERCOM_RX_PAD_3

static const uint8_t SS2	 = (44);
static const uint8_t MOSI2 = PIN_SPI2_MOSI;
static const uint8_t MISO2 = PIN_SPI2_MISO;
static const uint8_t SCK2  = PIN_SPI2_SCK;


/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

#define PIN_WIRE_SDA        (11)
#define PIN_WIRE_SCL        (12)
#define PERIPH_WIRE         sercom3
#define WIRE_IT_HANDLER     SERCOM3_Handler
#define WIRE_IT_HANDLER_0   SERCOM3_0_Handler
#define WIRE_IT_HANDLER_1   SERCOM3_1_Handler
#define WIRE_IT_HANDLER_2   SERCOM3_2_Handler
#define WIRE_IT_HANDLER_3   SERCOM3_3_Handler

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#define PIN_WIRE1_SDA       (34)
#define PIN_WIRE1_SCL       (33)
#define PERIPH_WIRE1        sercom6
#define WIRE1_IT_HANDLER    SERCOM6_Handler
#define WIRE1_IT_HANDLER_0  SERCOM6_0_Handler
#define WIRE1_IT_HANDLER_1  SERCOM6_1_Handler
#define WIRE1_IT_HANDLER_2  SERCOM6_2_Handler
#define WIRE1_IT_HANDLER_3  SERCOM6_3_Handler

static const uint8_t SDA1 = PIN_WIRE1_SDA;
static const uint8_t SCL1 = PIN_WIRE1_SCL;

/*
 * USB
 */
#define PIN_USB_HOST_ENABLE (24)
#define PIN_USB_DM          (22)
#define PIN_USB_DP          (23)

// On-board QSPI Flash
#define EXTERNAL_FLASH_DEVICES   W25Q128JV_SQ
#define EXTERNAL_FLASH_USE_QSPI

//QSPI Pins
#define PIN_QSPI_SCK	      (35)
#define PIN_QSPI_CS		      (36)
#define PIN_QSPI_IO0	      (37)
#define PIN_QSPI_IO1	      (38)
#define PIN_QSPI_IO2	      (39)
#define PIN_QSPI_IO3	      (40)


#if !defined(VARIANT_QSPI_BAUD_DEFAULT)
  // TODO: meaningful value for this
  #define VARIANT_QSPI_BAUD_DEFAULT 5000000
#endif

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
*/
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;
extern SERCOM sercom4;
extern SERCOM sercom5;
extern SERCOM sercom6;
extern SERCOM sercom7;

extern Uart Serial1;
extern Uart Serial2;

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      Serial
#define SERIAL_PORT_MONITOR         Serial
// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

//WIFI
#define SPIWIFI_SS       A2
#define SPIWIFI_ACK      A1
#define SPIWIFI_RESET    A0
// #define NINA_GPIO0         A1    //Not used unless jumper is installed
#define ESP32_GPIO0       -1   // Not connected
#define NINA_RESETN        SPIWIFI_RESET
#define ESP32_RESETN    NINA_RESETN
#define SerialNina       Serial1
#define SPIWIFI          SPI
#define P1AM200

#define INTERNAL_EEPROM_PORT Wire1
#define INTERNAL_RTC_PORT Wire1

#endif /* _VARIANT_P1AM_200_M4_ */

