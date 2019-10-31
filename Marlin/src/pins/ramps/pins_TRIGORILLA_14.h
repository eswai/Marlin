/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Arduino Mega with RAMPS v1.4 for Anycubic
 */

#define BOARD_INFO_NAME "Anycubic RAMPS 1.4"

//
// Servos
//
#if MB(TRIGORILLA_14_11)
  #define SERVO0_PIN        5
  #define SERVO1_PIN        4
  #define SERVO2_PIN       11
  #define SERVO3_PIN        6
#endif

// Labeled pins
#define TRIGORILLA_HEATER_BED_PIN  8
#define TRIGORILLA_HEATER_0_PIN   10
#define TRIGORILLA_HEATER_1_PIN   45   // Anycubic Kossel: Unused

#define TRIGORILLA_FAN0_PIN        9   // Anycubic Kossel: Usually the part cooling fan
#define TRIGORILLA_FAN1_PIN        7   // Anycubic Kossel: Unused
#define TRIGORILLA_FAN2_PIN       44   // Anycubic Kossel: Hotend fan

// Remap MOSFET pins to common usages:

#define RAMPS_D10_PIN    TRIGORILLA_HEATER_0_PIN // HEATER_0_PIN is always RAMPS_D10_PIN in pins_RAMPS.h

#if HOTENDS > 1   // EEF and EEB
  #define RAMPS_D9_PIN   TRIGORILLA_HEATER_1_PIN
  #if !TEMP_SENSOR_BED
    // EEF
    #define RAMPS_D8_PIN TRIGORILLA_FAN0_PIN
  #else
    // EEB
    #define RAMPS_D8_PIN TRIGORILLA_HEATER_BED_PIN
    #define FAN_PIN      TRIGORILLA_FAN0_PIN    // Override pin 4 in pins_RAMPS.h
  #endif
#elif TEMP_SENSOR_BED
  // EFB (Anycubic Kossel default)
  #define RAMPS_D9_PIN   TRIGORILLA_FAN0_PIN
  #define RAMPS_D8_PIN   TRIGORILLA_HEATER_BED_PIN
#else
  // EFF
  #define RAMPS_D9_PIN   TRIGORILLA_FAN1_PIN
  #define RAMPS_D8_PIN   TRIGORILLA_FAN0_PIN
#endif

#if HOTENDS > 1 || TEMP_SENSOR_BED      // EEF, EEB, EFB
  #define FAN1_PIN       TRIGORILLA_FAN1_PIN
#endif
#define FAN2_PIN         TRIGORILLA_FAN2_PIN
#define ORIG_E0_AUTO_FAN_PIN TRIGORILLA_FAN2_PIN  // Used in Anycubic Kossel example config

// Misc PINs
#define BUZZER         31
#define SDPOWER_PIN            -1
#define SDSS               53
#define LED_PIN            13
#define Z_MIN_PROBE_PIN    27
#define FIL_RUNOUT_PIN     19

// EndStops
#define X_MIN_PIN           3
#define Y_MIN_PIN          42
#define Z_MIN_PIN          18

#define X_MAX_PIN          43
#define Y_MAX_PIN          -1
#define Z_MAX_PIN          -1

#ifdef OutageTest
  #define OUTAGETEST_PIN  79
  #define OUTAGECON_PIN   58
#endif

#include "pins_RAMPS.h"

//
// AnyCubic made the following changes to 1.1.0-RC8
// If these are appropriate for your LCD let us know.
//
#if 0 && HAS_SPI_LCD

  // LCD Display output pins
  #if BOTH(NEWPANEL, PANEL_ONE)
    #undef LCD_PINS_D6
    #define LCD_PINS_D6    57
  #endif

  // LCD Display input pins
  #if ENABLED(NEWPANEL)
    #if ANY(VIKI2, miniVIKI)
      #undef DOGLCD_A0
      #define DOGLCD_A0    23
    #elif ENABLED(ELB_FULL_GRAPHIC_CONTROLLER)
      #undef BEEPER_PIN
      #define BEEPER_PIN   33
      #undef LCD_BACKLIGHT_PIN
      #define LCD_BACKLIGHT_PIN 67
    #endif
  #elif ENABLED(MINIPANEL)
    #undef BEEPER_PIN
    #define BEEPER_PIN     33
    #undef DOGLCD_A0
    #define DOGLCD_A0      42
  #endif

#endif // HAS_SPI_LCD

#if defined(ANYCUBIC_TFT_MODEL)
  #define BEEPER_PIN       31
  #define SD_DETECT_PIN    49
#endif

// LCD
#if defined(REPRAP_DISCOUNT_SMART_CONTROLLER) || defined(G3D_PANEL) || defined(ANYCUBIC_TFT_MODEL)
  #define KILL_PIN        41
#else
  #define KILL_PIN        -1
#endif

#ifdef ULTRA_LCD
  #ifdef NEWPANEL
    #define LCD_PINS_RS 16
    #define LCD_PINS_ENABLE 17
    #define LCD_PINS_D4 23
    #define LCD_PINS_D5 25
    #define LCD_PINS_D6 27
    #define LCD_PINS_D7 29

    #ifdef REPRAP_DISCOUNT_SMART_CONTROLLER
      #define BEEPER_PIN 37

      #define BTN_EN1 31
      #define BTN_EN2 33
      #define BTN_ENC 35

      #define SD_DETECT_PIN 49
      #elif defined(LCD_I2C_PANELOLU2)
        #define BTN_EN1 47  //reverse if the encoder turns the wrong way.
        #define BTN_EN2 43
        #define BTN_ENC 32
        #define SDSS 53
        #define SD_DETECT_PIN -1
        #define KILL_PIN 41
      #elif defined(LCD_I2C_VIKI)
        #define BTN_EN1 22  //reverse if the encoder turns the wrong way.
        #define BTN_EN2 7
        #define BTN_ENC -1
        #define SDSS 53
        #define SD_DETECT_PIN 49
      #elif defined(FULL_GRAPHIC_SMALL_PANEL)
        #define BEEPER_PIN 37

        // Pins for DOGM SPI LCD Support
        #define DOGLCD_A0  23
        #define DOGLCD_CS  27
        #define LCD_PIN_BL  25  // backlight LED on PA3

        #define KILL_PIN 41
        // GLCD features
        //#define LCD_CONTRAST 190
        // Uncomment screen orientation
        // #define LCD_SCREEN_ROT_90
        // #define LCD_SCREEN_ROT_180
        // #define LCD_SCREEN_ROT_270
        //The encoder and click button
        #define BTN_EN1 33
        #define BTN_EN2 -1
        #define BTN_ENC 35  //the click switch
        //not connected to a pin
        #define SD_DETECT_PIN 49
      #elif defined(MULTIPANEL)
        //         #define BEEPER_PIN 37
        // Pins for DOGM SPI LCD Support
        #define DOGLCD_A0  17
        #define DOGLCD_CS  16
        #define LCD_PIN_BL  23  // backlight LED on A11/D65
        #define SDSS   53

        #define KILL_PIN 64
        // GLCD features
        //#define LCD_CONTRAST 190
        // Uncomment screen orientation
        // #define LCD_SCREEN_ROT_90
        // #define LCD_SCREEN_ROT_180
        // #define LCD_SCREEN_ROT_270
        //The encoder and click button
        #define BTN_EN1 -1
        #define BTN_EN2 33
        #define BTN_ENC 35  //the click switch
        //not connected to a pin
        #define SD_DETECT_PIN 49
      #else
        //arduino pin which triggers an piezzo beeper
        #define BEEPER_PIN 31  // Beeper on AUX-4

      //buttons are directly attached using AUX-2
      #ifdef REPRAPWORLD_KEYPAD
        #define BTN_EN1 64 // encoder
        #define BTN_EN2 59 // encoder
        #define BTN_ENC 63 // enter button
        #define SHIFT_OUT 40 // shift register
        #define SHIFT_CLK 44 // shift register
        #define SHIFT_LD 42 // shift register
        #else
        #define BTN_EN1 37
        #define BTN_EN2 35
        #define BTN_ENC -1  //the click
      #endif

      #ifdef G3D_PANEL
        #define SD_DETECT_PIN 49
        #else
        #define SD_DETECT_PIN -1  // Ramps does not use this port
      #endif

    #endif

    #define LCD_PINS_RS 16
    #define LCD_PINS_ENABLE 17
    #define LCD_PINS_D4 23
    #define LCD_PINS_D5 25
    #define LCD_PINS_D6 27
    #define LCD_PINS_D7 29

  #endif
#endif