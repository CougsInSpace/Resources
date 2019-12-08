/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */

#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "PinNamesTypes.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { ALT0 = 0x100, ALT1 = 0x200, ALT2 = 0x300, ALT3 = 0x400 } ALTx;

typedef enum {
  PA_0       = 0x00,
  PA_0_ALT0  = PA_0 | ALT0,
  PA_0_ALT1  = PA_0 | ALT1,
  PA_1       = 0x01,
  PA_1_ALT0  = PA_1 | ALT0,
  PA_1_ALT1  = PA_1 | ALT1,
  PA_2       = 0x02,
  PA_3       = 0x03,
  PA_4       = 0x04,
  PA_4_ALT0  = PA_4 | ALT0,
  PA_5       = 0x05,
  PA_5_ALT0  = PA_5 | ALT0,
  PA_6       = 0x06,
  PA_6_ALT0  = PA_6 | ALT0,
  PA_7       = 0x07,
  PA_7_ALT0  = PA_7 | ALT0,
  PA_7_ALT1  = PA_7 | ALT1,
  PA_7_ALT2  = PA_7 | ALT2,
  PA_8       = 0x08,
  PA_9       = 0x09,
  PA_10      = 0x0A,
  PA_11      = 0x0B,
  PA_12      = 0x0C,
  PA_13      = 0x0D,
  PA_14      = 0x0E,
  PA_15      = 0x0F,
  PA_15_ALT0 = PA_15 | ALT0,

  PB_0       = 0x10,
  PB_0_ALT0  = PB_0 | ALT0,
  PB_0_ALT1  = PB_0 | ALT1,
  PB_1       = 0x11,
  PB_1_ALT0  = PB_1 | ALT0,
  PB_1_ALT1  = PB_1 | ALT1,
  PB_2       = 0x12,
  PB_3       = 0x13,
  PB_3_ALT0  = PB_3 | ALT0,
  PB_4       = 0x14,
  PB_4_ALT0  = PB_4 | ALT0,
  PB_4_ALT1  = PB_4 | ALT1,
  PB_5       = 0x15,
  PB_5_ALT0  = PB_5 | ALT0,
  PB_5_ALT1  = PB_5 | ALT1,
  PB_6       = 0x16,
  PB_6_ALT0  = PB_6 | ALT0,
  PB_7       = 0x17,
  PB_7_ALT0  = PB_7 | ALT0,
  PB_8       = 0x18,
  PB_8_ALT0  = PB_8 | ALT0,
  PB_8_ALT1  = PB_8 | ALT1,
  PB_9       = 0x19,
  PB_9_ALT0  = PB_9 | ALT0,
  PB_9_ALT1  = PB_9 | ALT1,
  PB_10      = 0x1A,
  PB_11      = 0x1B,
  PB_12      = 0x1C,
  PB_13      = 0x1D,
  PB_13_ALT0 = PB_13 | ALT0,
  PB_14      = 0x1E,
  PB_14_ALT0 = PB_14 | ALT0,
  PB_14_ALT1 = PB_14 | ALT1,
  PB_15      = 0x1F,
  PB_15_ALT0 = PB_15 | ALT0,
  PB_15_ALT1 = PB_15 | ALT1,

  PC_0       = 0x20,
  PC_0_ALT0  = PC_0 | ALT0,
  PC_0_ALT1  = PC_0 | ALT1,
  PC_1       = 0x21,
  PC_1_ALT0  = PC_1 | ALT0,
  PC_1_ALT1  = PC_1 | ALT1,
  PC_2       = 0x22,
  PC_2_ALT0  = PC_2 | ALT0,
  PC_2_ALT1  = PC_2 | ALT1,
  PC_3       = 0x23,
  PC_3_ALT0  = PC_3 | ALT0,
  PC_3_ALT1  = PC_3 | ALT1,
  PC_4       = 0x24,
  PC_4_ALT0  = PC_4 | ALT0,
  PC_5       = 0x25,
  PC_5_ALT0  = PC_5 | ALT0,
  PC_6       = 0x26,
  PC_6_ALT0  = PC_6 | ALT0,
  PC_7       = 0x27,
  PC_7_ALT0  = PC_7 | ALT0,
  PC_8       = 0x28,
  PC_8_ALT0  = PC_8 | ALT0,
  PC_9       = 0x29,
  PC_9_ALT0  = PC_9 | ALT0,
  PC_10      = 0x2A,
  PC_10_ALT0 = PC_10 | ALT0,
  PC_11      = 0x2B,
  PC_11_ALT0 = PC_11 | ALT0,
  PC_12      = 0x2C,
  PC_13      = 0x2D,
  PC_14      = 0x2E,
  PC_15      = 0x2F,

  PD_2 = 0x32,

  PH_0 = 0x70,
  PH_1 = 0x71,

  // ADC internal channels
  ADC_TEMP = 0xF0,
  ADC_VREF = 0xF1,
  ADC_VBAT = 0xF2,

  /**** OSCILLATOR pins ****/
  RCC_OSC32_IN  = PC_14,
  RCC_OSC32_OUT = PC_15,
  RCC_OSC_IN    = PH_0,
  RCC_OSC_OUT   = PH_1,

  /**** DEBUG pins ****/
  SYS_JTCK_SWCLK = PA_14,
  SYS_JTDI       = PA_15,
  SYS_JTDO_SWO   = PB_3,
  SYS_JTMS_SWDIO = PA_13,
  SYS_JTRST      = PB_4,
  SYS_PVD_IN     = PB_7,
  SYS_WKUP1      = PA_0,
  SYS_WKUP2      = PC_13,
  SYS_WKUP4      = PA_2,
  SYS_WKUP5      = PC_5,

  // Not connected
  NC = (int)0xFFFFFFFF,

  STDIO_UART_TX = NC,
  STDIO_UART_RX = NC,
  USBTX         = STDIO_UART_TX,
  USBRX         = STDIO_UART_RX,

  /*** Comms HW V1.0 ***/
  LED1 = PD_2,

  /*** Electronic Load ***/
  ADC_INPUT_CURRENT = PC_0,
  ADC_INPUT_VOLTAGE = PC_1,

  ADC_OUTPUT_CURRENT     = PC_2,
  ADC_OUTPUT_VOLTAGE     = PC_3,
  DAC_OUTPUT_CURRENT_SET = PA_4,

  SENSE_RANGE_HIGH = PC_5, // GPIO = determine later
  SENSE_RANGE_MED  = PC_6, // GPIO

  FAN_PWM = PA_8,

  channelA  = PC_7, // GPIO - encoder_A - knob twist clockwise
  channelB  = PC_8, // GPIO - encoder_B - knob twist counter-clockwise
  ENCODER_SW = PC_9, // GPIO - encoder - knob push

  UI_BUTTON1 = PC_11, // Switch modes (my choice, Bradley demands it)

  LCD_MOSI  = PA_7, // LCD master to slave input
  LCD_SCK   = PA_5, // LCD serial clock
  LCD_A0    = PA_0,   // GPIO
  LCD_RST_N = PA_1,   // GPIO Active low - pull to a low signal to reset
  LCD_CS1_N = PA_2,   // GPIO Active low - pull to a low signal to reset
} PinName;

#ifdef __cplusplus
}
#endif

#endif
