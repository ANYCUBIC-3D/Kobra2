/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

//
// File: pins/pins_postprocess.h
// Post-process pins according to configured settings
//

// Define certain undefined pins
#ifndef X_MS1_PIN
  #define X_MS1_PIN -1
#endif
#ifndef X_MS2_PIN
  #define X_MS2_PIN -1
#endif
#ifndef X_MS3_PIN
  #define X_MS3_PIN -1
#endif
#ifndef Y_MS1_PIN
  #define Y_MS1_PIN -1
#endif
#ifndef Y_MS2_PIN
  #define Y_MS2_PIN -1
#endif
#ifndef Y_MS3_PIN
  #define Y_MS3_PIN -1
#endif
#ifndef Z_MS1_PIN
  #define Z_MS1_PIN -1
#endif
#ifndef Z_MS2_PIN
  #define Z_MS2_PIN -1
#endif
#ifndef Z_MS3_PIN
  #define Z_MS3_PIN -1
#endif
#ifndef E0_MS1_PIN
  #define E0_MS1_PIN -1
#endif
#ifndef E0_MS2_PIN
  #define E0_MS2_PIN -1
#endif
#ifndef E0_MS3_PIN
  #define E0_MS3_PIN -1
#endif
#ifndef E1_MS1_PIN
  #define E1_MS1_PIN -1
#endif
#ifndef E1_MS2_PIN
  #define E1_MS2_PIN -1
#endif
#ifndef E1_MS3_PIN
  #define E1_MS3_PIN -1
#endif
#ifndef E2_MS1_PIN
  #define E2_MS1_PIN -1
#endif
#ifndef E2_MS2_PIN
  #define E2_MS2_PIN -1
#endif
#ifndef E2_MS3_PIN
  #define E2_MS3_PIN -1
#endif
#ifndef E3_MS1_PIN
  #define E3_MS1_PIN -1
#endif
#ifndef E3_MS2_PIN
  #define E3_MS2_PIN -1
#endif
#ifndef E3_MS3_PIN
  #define E3_MS3_PIN -1
#endif
#ifndef E4_MS1_PIN
  #define E4_MS1_PIN -1
#endif
#ifndef E4_MS2_PIN
  #define E4_MS2_PIN -1
#endif
#ifndef E4_MS3_PIN
  #define E4_MS3_PIN -1
#endif
#ifndef E5_MS1_PIN
  #define E5_MS1_PIN -1
#endif
#ifndef E5_MS2_PIN
  #define E5_MS2_PIN -1
#endif
#ifndef E5_MS3_PIN
  #define E5_MS3_PIN -1
#endif
#ifndef E6_MS1_PIN
  #define E6_MS1_PIN -1
#endif
#ifndef E6_MS2_PIN
  #define E6_MS2_PIN -1
#endif
#ifndef E6_MS3_PIN
  #define E6_MS3_PIN -1
#endif
#ifndef E7_MS1_PIN
  #define E7_MS1_PIN -1
#endif
#ifndef E7_MS2_PIN
  #define E7_MS2_PIN -1
#endif
#ifndef E7_MS3_PIN
  #define E7_MS3_PIN -1
#endif

#ifndef E0_STEP_PIN
  #define E0_STEP_PIN -1
#endif
#ifndef E0_DIR_PIN
  #define E0_DIR_PIN -1
#endif
#ifndef E0_ENABLE_PIN
  #define E0_ENABLE_PIN -1
#endif
#ifndef E1_STEP_PIN
  #define E1_STEP_PIN -1
#endif
#ifndef E1_DIR_PIN
  #define E1_DIR_PIN -1
#endif
#ifndef E1_ENABLE_PIN
  #define E1_ENABLE_PIN -1
#endif
#ifndef E2_STEP_PIN
  #define E2_STEP_PIN -1
#endif
#ifndef E2_DIR_PIN
  #define E2_DIR_PIN -1
#endif
#ifndef E2_ENABLE_PIN
  #define E2_ENABLE_PIN -1
#endif
#ifndef E3_STEP_PIN
  #define E3_STEP_PIN -1
#endif
#ifndef E3_DIR_PIN
  #define E3_DIR_PIN -1
#endif
#ifndef E3_ENABLE_PIN
  #define E3_ENABLE_PIN -1
#endif
#ifndef E4_STEP_PIN
  #define E4_STEP_PIN -1
#endif
#ifndef E4_DIR_PIN
  #define E4_DIR_PIN -1
#endif
#ifndef E4_ENABLE_PIN
  #define E4_ENABLE_PIN -1
#endif
#ifndef E5_STEP_PIN
  #define E5_STEP_PIN -1
#endif
#ifndef E5_DIR_PIN
  #define E5_DIR_PIN -1
#endif
#ifndef E5_ENABLE_PIN
  #define E5_ENABLE_PIN -1
#endif
#ifndef E6_STEP_PIN
  #define E6_STEP_PIN -1
#endif
#ifndef E6_DIR_PIN
  #define E6_DIR_PIN -1
#endif
#ifndef E6_ENABLE_PIN
  #define E6_ENABLE_PIN -1
#endif
#ifndef E7_STEP_PIN
  #define E7_STEP_PIN -1
#endif
#ifndef E7_DIR_PIN
  #define E7_DIR_PIN -1
#endif
#ifndef E7_ENABLE_PIN
  #define E7_ENABLE_PIN -1
#endif

#ifndef X_CS_PIN
  #define X_CS_PIN -1
#endif
#ifndef Y_CS_PIN
  #define Y_CS_PIN -1
#endif
#ifndef Z_CS_PIN
  #define Z_CS_PIN -1
#endif
#ifndef E0_CS_PIN
  #define E0_CS_PIN -1
#endif
#ifndef E1_CS_PIN
  #define E1_CS_PIN -1
#endif
#ifndef E2_CS_PIN
  #define E2_CS_PIN -1
#endif
#ifndef E3_CS_PIN
  #define E3_CS_PIN -1
#endif
#ifndef E4_CS_PIN
  #define E4_CS_PIN -1
#endif
#ifndef E5_CS_PIN
  #define E5_CS_PIN -1
#endif
#ifndef E6_CS_PIN
  #define E6_CS_PIN -1
#endif
#ifndef E7_CS_PIN
  #define E7_CS_PIN -1
#endif

#ifndef FAN_PIN
  #define FAN_PIN -1
#endif
#define FAN0_PIN FAN_PIN
#ifndef FAN1_PIN
  #define FAN1_PIN -1
#endif
#ifndef FAN2_PIN
  #define FAN2_PIN -1
#endif
#ifndef CONTROLLER_FAN_PIN
  #define CONTROLLER_FAN_PIN  -1
#endif

#ifndef FANMUX0_PIN
  #define FANMUX0_PIN -1
#endif
#ifndef FANMUX1_PIN
  #define FANMUX1_PIN -1
#endif
#ifndef FANMUX2_PIN
  #define FANMUX2_PIN -1
#endif

#ifndef HEATER_0_PIN
  #define HEATER_0_PIN -1
#endif
#ifndef HEATER_1_PIN
  #define HEATER_1_PIN -1
#endif
#ifndef HEATER_2_PIN
  #define HEATER_2_PIN -1
#endif
#ifndef HEATER_3_PIN
  #define HEATER_3_PIN -1
#endif
#ifndef HEATER_4_PIN
  #define HEATER_4_PIN -1
#endif
#ifndef HEATER_5_PIN
  #define HEATER_5_PIN -1
#endif
#ifndef HEATER_6_PIN
  #define HEATER_6_PIN -1
#endif
#ifndef HEATER_7_PIN
  #define HEATER_7_PIN -1
#endif
#ifndef HEATER_BED_PIN
  #define HEATER_BED_PIN -1
#endif

#ifndef TEMP_0_PIN
  #define TEMP_0_PIN -1
#endif
#ifndef TEMP_1_PIN
  #define TEMP_1_PIN -1
#endif
#ifndef TEMP_2_PIN
  #define TEMP_2_PIN -1
#endif
#ifndef TEMP_3_PIN
  #define TEMP_3_PIN -1
#endif
#ifndef TEMP_4_PIN
  #define TEMP_4_PIN -1
#endif
#ifndef TEMP_5_PIN
  #define TEMP_5_PIN -1
#endif
#ifndef TEMP_6_PIN
  #define TEMP_6_PIN -1
#endif
#ifndef TEMP_7_PIN
  #define TEMP_7_PIN -1
#endif
#ifndef TEMP_BED_PIN
  #define TEMP_BED_PIN -1
#endif

#ifndef SD_DETECT_PIN
  #define SD_DETECT_PIN -1
#endif
#ifndef SDPOWER_PIN
  #define SDPOWER_PIN -1
#endif
#ifndef SDSS
  #define SDSS -1
#endif
#ifndef LED_PIN
  #define LED_PIN -1
#endif
#if !defined PSU_CONTROL || !defined(PS_ON_PIN)
  #undef PS_ON_PIN
  #define PS_ON_PIN -1
#endif
#ifndef KILL_PIN
  #define KILL_PIN -1
#endif
#ifndef SUICIDE_PIN
  #define SUICIDE_PIN -1
#endif
#ifndef SUICIDE_PIN_STATE
  #define SUICIDE_PIN_STATE LOW
#endif

#ifndef NUM_SERVO_PLUGS
  #define NUM_SERVO_PLUGS 4
#endif

//
// Assign endstop pins for boards with only 3 connectors
//
#ifdef X_STOP_PIN
  #if X_HOME_TO_MIN
    #define X_MIN_PIN X_STOP_PIN
    #ifndef X_MAX_PIN
      #define X_MAX_PIN -1
    #endif
  #else
    #define X_MAX_PIN X_STOP_PIN
    #ifndef X_MIN_PIN
      #define X_MIN_PIN -1
    #endif
  #endif
#elif X_HOME_TO_MIN
  #define X_STOP_PIN X_MIN_PIN
#else
  #define X_STOP_PIN X_MAX_PIN
#endif
#if !defined(X2_USE_ENDSTOP) && ENABLED(X_DUAL_ENDSTOPS) && PIN_EXISTS(X_STOP)
  #define X2_USE_ENDSTOP _XSTOP_
#endif

#if HAS_Y_AXIS
  #ifdef Y_STOP_PIN
    #if Y_HOME_TO_MIN
      #define Y_MIN_PIN Y_STOP_PIN
      #ifndef Y_MAX_PIN
        #define Y_MAX_PIN -1
      #endif
    #else
      #define Y_MAX_PIN Y_STOP_PIN
      #ifndef Y_MIN_PIN
        #define Y_MIN_PIN -1
      #endif
    #endif
  #elif Y_HOME_TO_MIN
    #define Y_STOP_PIN Y_MIN_PIN
  #else
    #define Y_STOP_PIN Y_MAX_PIN
  #endif
  #if !defined(Y2_USE_ENDSTOP) && ENABLED(Y_DUAL_ENDSTOPS) && PIN_EXISTS(Y_STOP)
    #define Y2_USE_ENDSTOP _YSTOP_
  #endif
#endif

#if HAS_Z_AXIS
  #ifdef Z_STOP_PIN
    #if Z_HOME_TO_MIN
      #define Z_MIN_PIN Z_STOP_PIN
      #ifndef Z_MAX_PIN
        #define Z_MAX_PIN -1
      #endif
    #else
      #define Z_MAX_PIN Z_STOP_PIN
      #ifndef Z_MIN_PIN
        #define Z_MIN_PIN -1
      #endif
    #endif
  #elif Z_HOME_TO_MIN
    #define Z_STOP_PIN Z_MIN_PIN
  #else
    #define Z_STOP_PIN Z_MAX_PIN
  #endif
  #if ENABLED(Z_MULTI_ENDSTOPS) && PIN_EXISTS(Z_STOP)
    #ifndef Z2_USE_ENDSTOP
      #define Z2_USE_ENDSTOP _ZSTOP_
    #endif
    #if NUM_Z_STEPPERS >= 3 && !defined(Z3_USE_ENDSTOP)
      #define Z3_USE_ENDSTOP _ZSTOP_
    #endif
    #if NUM_Z_STEPPERS >= 4 && !defined(Z4_USE_ENDSTOP)
      #define Z4_USE_ENDSTOP _ZSTOP_
    #endif
  #endif
#endif


  #define FIL_RUNOUT1_PIN FIL_RUNOUT_PIN

#ifndef LCD_PINS_D4
  #define LCD_PINS_D4 -1
#endif

#if HAS_MARLINUI_HD44780 || TOUCH_UI_ULTIPANEL
  #ifndef LCD_PINS_D5
    #define LCD_PINS_D5 -1
  #endif
  #ifndef LCD_PINS_D6
    #define LCD_PINS_D6 -1
  #endif
  #ifndef LCD_PINS_D7
    #define LCD_PINS_D7 -1
  #endif
#endif

/**
 * Auto-Assignment for Dual X, Dual Y, Multi-Z Steppers
 *
 * By default X2 is assigned to the next open E plug
 * on the board, then in order, Y2, Z2, Z3. These can be
 * overridden in Configuration.h or Configuration_adv.h.
 */

  #define X2_E_INDEX E_STEPPERS
  #define Y2_E_INDEX X2_E_INDEX
  #define Z2_E_INDEX Y2_E_INDEX


#undef HAS_FREE_AUX2_PINS

