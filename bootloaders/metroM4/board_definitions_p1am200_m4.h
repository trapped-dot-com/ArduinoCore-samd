
/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Atmel Corporation/Thibaut VIARD.  All right reserved.

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

#ifndef _BOARD_DEFINITIONS_H_
#define _BOARD_DEFINITIONS_H_
/*
 * USB device definitions
 */
#define STRING_PRODUCT "FACTS P1AM-200"
#define USB_VID_HIGH   0x13
#define USB_VID_LOW    0x54
#define USB_PID_HIGH   0x40
#define USB_PID_LOW    0x02


/*
 * If BOOT_DOUBLE_TAP_ADDRESS is defined the bootloader is started by
 * quickly tapping two times on the reset button.
 * BOOT_DOUBLE_TAP_ADDRESS must point to a free SRAM cell that must not
 * be touched from the loaded application.
 */
#define BOOT_DOUBLE_TAP_ADDRESS           (HSRAM_ADDR + HSRAM_SIZE - 4)
#define BOOT_DOUBLE_TAP_DATA              (*((volatile uint32_t *)BOOT_DOUBLE_TAP_ADDRESS))

/*
 * If BOOT_LOAD_PIN is defined the bootloader is started if the selected
 * pin is tied LOW.
 */
//#define BOOT_LOAD_PIN                     PIN_PA21 // Pin 7
//#define BOOT_LOAD_PIN                     PIN_PA15 // Pin 5

#define GPIO(port, pin) ((((port)&0x7u) << 5) + ((pin)&0x1Fu))

#define BOOK_USART_MASK					  APBAMASK
#define BOOT_USART_MODULE                 SERCOM0
#define BOOT_USART_BUS_CLOCK_INDEX        MCLK_APBAMASK_SERCOM0
#define BOOT_GCLK_ID_CORE				  SERCOM0_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW				  SERCOM0_GCLK_ID_SLOW
#define BOOT_USART_PAD_SETTINGS           UART_RX_PAD3_TX_PAD2
#define BOOT_USART_PAD3                   PINMUX_UNUSED
#define BOOT_USART_PAD2                   PINMUX_UNUSED

#define BOOT_USART_PAD1                   PINMUX_PA10C_SERCOM0_PAD2
#define BOOT_USART_PAD0                   PINMUX_PA11C_SERCOM0_PAD3

/* Master clock frequency */
#define CPU_FREQUENCY                     (48000000ul)
#define VARIANT_MCK                       CPU_FREQUENCY

/* Frequency of the board main oscillator */
#define VARIANT_MAINOSC                   (32768ul)

/* Calibration values for DFLL48 pll */
#define NVM_SW_CALIB_DFLL48M_COARSE_VAL   (58)
#define NVM_SW_CALIB_DFLL48M_FINE_VAL     (64)

#define BOARD_LED_PORT                    (0)
#define BOARD_LED_PIN                     (21)

#define BOARD_LEDRX_PORT                  (1)
#define BOARD_LEDRX_PIN                   (6)

#define BOARD_LEDTX_PORT                  (0)
#define BOARD_LEDTX_PIN                   (27)

#endif // _BOARD_DEFINITIONS_H_
