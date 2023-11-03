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

/**
 * stepper/indirection.h
 *
 * Stepper motor driver indirection to allow some stepper functions to
 * be done via SPI/I2c instead of direct pin manipulation.
 *
 * Copyright (c) 2015 Dominik Wenger
 */

#include "../../inc/MarlinConfig.h"

#if HAS_TMC26X
  #include "TMC26X.h"
#endif

#if HAS_TRINAMIC_CONFIG
  #include "trinamic.h"
#endif

void restore_stepper_drivers();  // Called by powerManager.power_on()
void reset_stepper_drivers();    // Called by settings.load / settings.reset

// X Stepper
#ifndef X_ENABLE_INIT
  #define X_ENABLE_INIT() SET_OUTPUT(X_ENABLE_PIN)
  #define X_ENABLE_WRITE(STATE) WRITE(X_ENABLE_PIN,STATE)
  #define X_ENABLE_READ() bool(READ(X_ENABLE_PIN))
#endif
#ifndef X_DIR_INIT
  #define X_DIR_INIT() SET_OUTPUT(X_DIR_PIN)
  #define X_DIR_WRITE(STATE) WRITE(X_DIR_PIN,STATE)
  #define X_DIR_READ() bool(READ(X_DIR_PIN))
#endif
#define X_STEP_INIT() SET_OUTPUT(X_STEP_PIN)
#ifndef X_STEP_WRITE
  #define X_STEP_WRITE(STATE) WRITE(X_STEP_PIN,STATE)
#endif
#define X_STEP_READ() bool(READ(X_STEP_PIN))

// Y Stepper
#if HAS_Y_AXIS
  #ifndef Y_ENABLE_INIT
    #define Y_ENABLE_INIT() SET_OUTPUT(Y_ENABLE_PIN)
    #define Y_ENABLE_WRITE(STATE) WRITE(Y_ENABLE_PIN,STATE)
    #define Y_ENABLE_READ() bool(READ(Y_ENABLE_PIN))
  #endif
  #ifndef Y_DIR_INIT
    #define Y_DIR_INIT() SET_OUTPUT(Y_DIR_PIN)
    #define Y_DIR_WRITE(STATE) WRITE(Y_DIR_PIN,STATE)
    #define Y_DIR_READ() bool(READ(Y_DIR_PIN))
  #endif
  #define Y_STEP_INIT() SET_OUTPUT(Y_STEP_PIN)
  #ifndef Y_STEP_WRITE
    #define Y_STEP_WRITE(STATE) WRITE(Y_STEP_PIN,STATE)
  #endif
  #define Y_STEP_READ() bool(READ(Y_STEP_PIN))
#endif

// Z Stepper
#if HAS_Z_AXIS
  #ifndef Z_ENABLE_INIT
    #define Z_ENABLE_INIT() SET_OUTPUT(Z_ENABLE_PIN)
    #define Z_ENABLE_WRITE(STATE) WRITE(Z_ENABLE_PIN,STATE)
    #define Z_ENABLE_READ() bool(READ(Z_ENABLE_PIN))
  #endif
  #ifndef Z_DIR_INIT
    #define Z_DIR_INIT() SET_OUTPUT(Z_DIR_PIN)
    #define Z_DIR_WRITE(STATE) WRITE(Z_DIR_PIN,STATE)
    #define Z_DIR_READ() bool(READ(Z_DIR_PIN))
  #endif
  #define Z_STEP_INIT() SET_OUTPUT(Z_STEP_PIN)
  #ifndef Z_STEP_WRITE
    #define Z_STEP_WRITE(STATE) WRITE(Z_STEP_PIN,STATE)
  #endif
  #define Z_STEP_READ() bool(READ(Z_STEP_PIN))
#endif

// X2 Stepper
#if HAS_X2_ENABLE
  #ifndef X2_ENABLE_INIT
    #define X2_ENABLE_INIT() SET_OUTPUT(X2_ENABLE_PIN)
    #define X2_ENABLE_WRITE(STATE) WRITE(X2_ENABLE_PIN,STATE)
    #define X2_ENABLE_READ() bool(READ(X2_ENABLE_PIN))
  #endif
  #ifndef X2_DIR_INIT
    #define X2_DIR_INIT() SET_OUTPUT(X2_DIR_PIN)
    #define X2_DIR_WRITE(STATE) WRITE(X2_DIR_PIN,STATE)
    #define X2_DIR_READ() bool(READ(X2_DIR_PIN))
  #endif
  #define X2_STEP_INIT() SET_OUTPUT(X2_STEP_PIN)
  #ifndef X2_STEP_WRITE
    #define X2_STEP_WRITE(STATE) WRITE(X2_STEP_PIN,STATE)
  #endif
  #define X2_STEP_READ() bool(READ(X2_STEP_PIN))
#endif

// Y2 Stepper
#if HAS_Y2_ENABLE
  #ifndef Y2_ENABLE_INIT
    #define Y2_ENABLE_INIT() SET_OUTPUT(Y2_ENABLE_PIN)
    #define Y2_ENABLE_WRITE(STATE) WRITE(Y2_ENABLE_PIN,STATE)
    #define Y2_ENABLE_READ() bool(READ(Y2_ENABLE_PIN))
  #endif
  #ifndef Y2_DIR_INIT
    #define Y2_DIR_INIT() SET_OUTPUT(Y2_DIR_PIN)
    #define Y2_DIR_WRITE(STATE) WRITE(Y2_DIR_PIN,STATE)
    #define Y2_DIR_READ() bool(READ(Y2_DIR_PIN))
  #endif
  #define Y2_STEP_INIT() SET_OUTPUT(Y2_STEP_PIN)
  #ifndef Y2_STEP_WRITE
    #define Y2_STEP_WRITE(STATE) WRITE(Y2_STEP_PIN,STATE)
  #endif
  #define Y2_STEP_READ() bool(READ(Y2_STEP_PIN))
#else
  #define Y2_DIR_WRITE(STATE) NOOP
#endif

// Z2 Stepper
#if HAS_Z2_ENABLE
  #ifndef Z2_ENABLE_INIT
    #define Z2_ENABLE_INIT() SET_OUTPUT(Z2_ENABLE_PIN)
    #define Z2_ENABLE_WRITE(STATE) WRITE(Z2_ENABLE_PIN,STATE)
    #define Z2_ENABLE_READ() bool(READ(Z2_ENABLE_PIN))
  #endif
  #ifndef Z2_DIR_INIT
    #define Z2_DIR_INIT() SET_OUTPUT(Z2_DIR_PIN)
    #define Z2_DIR_WRITE(STATE) WRITE(Z2_DIR_PIN,STATE)
    #define Z2_DIR_READ() bool(READ(Z2_DIR_PIN))
  #endif
  #define Z2_STEP_INIT() SET_OUTPUT(Z2_STEP_PIN)
  #ifndef Z2_STEP_WRITE
    #define Z2_STEP_WRITE(STATE) WRITE(Z2_STEP_PIN,STATE)
  #endif
  #define Z2_STEP_READ() bool(READ(Z2_STEP_PIN))
#else
  #define Z2_DIR_WRITE(STATE) NOOP
#endif

// Z3 Stepper
#if HAS_Z3_ENABLE
  #ifndef Z3_ENABLE_INIT
    #define Z3_ENABLE_INIT() SET_OUTPUT(Z3_ENABLE_PIN)
    #define Z3_ENABLE_WRITE(STATE) WRITE(Z3_ENABLE_PIN,STATE)
    #define Z3_ENABLE_READ() bool(READ(Z3_ENABLE_PIN))
  #endif
  #ifndef Z3_DIR_INIT
    #define Z3_DIR_INIT() SET_OUTPUT(Z3_DIR_PIN)
    #define Z3_DIR_WRITE(STATE) WRITE(Z3_DIR_PIN,STATE)
    #define Z3_DIR_READ() bool(READ(Z3_DIR_PIN))
  #endif
  #define Z3_STEP_INIT() SET_OUTPUT(Z3_STEP_PIN)
  #ifndef Z3_STEP_WRITE
    #define Z3_STEP_WRITE(STATE) WRITE(Z3_STEP_PIN,STATE)
  #endif
  #define Z3_STEP_READ() bool(READ(Z3_STEP_PIN))
#else
  #define Z3_DIR_WRITE(STATE) NOOP
#endif

// Z4 Stepper
#if HAS_Z4_ENABLE
  #ifndef Z4_ENABLE_INIT
    #define Z4_ENABLE_INIT() SET_OUTPUT(Z4_ENABLE_PIN)
    #define Z4_ENABLE_WRITE(STATE) WRITE(Z4_ENABLE_PIN,STATE)
    #define Z4_ENABLE_READ() bool(READ(Z4_ENABLE_PIN))
  #endif
  #ifndef Z4_DIR_INIT
    #define Z4_DIR_INIT() SET_OUTPUT(Z4_DIR_PIN)
    #define Z4_DIR_WRITE(STATE) WRITE(Z4_DIR_PIN,STATE)
    #define Z4_DIR_READ() bool(READ(Z4_DIR_PIN))
  #endif
  #define Z4_STEP_INIT() SET_OUTPUT(Z4_STEP_PIN)
  #ifndef Z4_STEP_WRITE
    #define Z4_STEP_WRITE(STATE) WRITE(Z4_STEP_PIN,STATE)
  #endif
  #define Z4_STEP_READ() bool(READ(Z4_STEP_PIN))
#else
  #define Z4_DIR_WRITE(STATE) NOOP
#endif

// E0 Stepper
#ifndef E0_ENABLE_INIT
  #define E0_ENABLE_INIT() SET_OUTPUT(E0_ENABLE_PIN)
  #define E0_ENABLE_WRITE(STATE) WRITE(E0_ENABLE_PIN,STATE)
  #define E0_ENABLE_READ() bool(READ(E0_ENABLE_PIN))
#endif
#ifndef E0_DIR_INIT
  #define E0_DIR_INIT() SET_OUTPUT(E0_DIR_PIN)
  #define E0_DIR_WRITE(STATE) WRITE(E0_DIR_PIN,STATE)
  #define E0_DIR_READ() bool(READ(E0_DIR_PIN))
#endif
#define E0_STEP_INIT() SET_OUTPUT(E0_STEP_PIN)
#ifndef E0_STEP_WRITE
  #define E0_STEP_WRITE(STATE) WRITE(E0_STEP_PIN,STATE)
#endif
#define E0_STEP_READ() bool(READ(E0_STEP_PIN))

// E1 Stepper
#ifndef E1_ENABLE_INIT
  #define E1_ENABLE_INIT() SET_OUTPUT(E1_ENABLE_PIN)
  #define E1_ENABLE_WRITE(STATE) WRITE(E1_ENABLE_PIN,STATE)
  #define E1_ENABLE_READ() bool(READ(E1_ENABLE_PIN))
#endif
#ifndef E1_DIR_INIT
  #define E1_DIR_INIT() SET_OUTPUT(E1_DIR_PIN)
  #define E1_DIR_WRITE(STATE) WRITE(E1_DIR_PIN,STATE)
  #define E1_DIR_READ() bool(READ(E1_DIR_PIN))
#endif
#define E1_STEP_INIT() SET_OUTPUT(E1_STEP_PIN)
#ifndef E1_STEP_WRITE
  #define E1_STEP_WRITE(STATE) WRITE(E1_STEP_PIN,STATE)
#endif
#define E1_STEP_READ() bool(READ(E1_STEP_PIN))

// E2 Stepper
#ifndef E2_ENABLE_INIT
  #define E2_ENABLE_INIT() SET_OUTPUT(E2_ENABLE_PIN)
  #define E2_ENABLE_WRITE(STATE) WRITE(E2_ENABLE_PIN,STATE)
  #define E2_ENABLE_READ() bool(READ(E2_ENABLE_PIN))
#endif
#ifndef E2_DIR_INIT
  #define E2_DIR_INIT() SET_OUTPUT(E2_DIR_PIN)
  #define E2_DIR_WRITE(STATE) WRITE(E2_DIR_PIN,STATE)
  #define E2_DIR_READ() bool(READ(E2_DIR_PIN))
#endif
#define E2_STEP_INIT() SET_OUTPUT(E2_STEP_PIN)
#ifndef E2_STEP_WRITE
  #define E2_STEP_WRITE(STATE) WRITE(E2_STEP_PIN,STATE)
#endif
#define E2_STEP_READ() bool(READ(E2_STEP_PIN))

// E3 Stepper
#ifndef E3_ENABLE_INIT
  #define E3_ENABLE_INIT() SET_OUTPUT(E3_ENABLE_PIN)
  #define E3_ENABLE_WRITE(STATE) WRITE(E3_ENABLE_PIN,STATE)
  #define E3_ENABLE_READ() bool(READ(E3_ENABLE_PIN))
#endif
#ifndef E3_DIR_INIT
  #define E3_DIR_INIT() SET_OUTPUT(E3_DIR_PIN)
  #define E3_DIR_WRITE(STATE) WRITE(E3_DIR_PIN,STATE)
  #define E3_DIR_READ() bool(READ(E3_DIR_PIN))
#endif
#define E3_STEP_INIT() SET_OUTPUT(E3_STEP_PIN)
#ifndef E3_STEP_WRITE
  #define E3_STEP_WRITE(STATE) WRITE(E3_STEP_PIN,STATE)
#endif
#define E3_STEP_READ() bool(READ(E3_STEP_PIN))

// E4 Stepper
#ifndef E4_ENABLE_INIT
  #define E4_ENABLE_INIT() SET_OUTPUT(E4_ENABLE_PIN)
  #define E4_ENABLE_WRITE(STATE) WRITE(E4_ENABLE_PIN,STATE)
  #define E4_ENABLE_READ() bool(READ(E4_ENABLE_PIN))
#endif
#ifndef E4_DIR_INIT
  #define E4_DIR_INIT() SET_OUTPUT(E4_DIR_PIN)
  #define E4_DIR_WRITE(STATE) WRITE(E4_DIR_PIN,STATE)
  #define E4_DIR_READ() bool(READ(E4_DIR_PIN))
#endif
#define E4_STEP_INIT() SET_OUTPUT(E4_STEP_PIN)
#ifndef E4_STEP_WRITE
  #define E4_STEP_WRITE(STATE) WRITE(E4_STEP_PIN,STATE)
#endif
#define E4_STEP_READ() bool(READ(E4_STEP_PIN))

// E5 Stepper
#ifndef E5_ENABLE_INIT
  #define E5_ENABLE_INIT() SET_OUTPUT(E5_ENABLE_PIN)
  #define E5_ENABLE_WRITE(STATE) WRITE(E5_ENABLE_PIN,STATE)
  #define E5_ENABLE_READ() bool(READ(E5_ENABLE_PIN))
#endif
#ifndef E5_DIR_INIT
  #define E5_DIR_INIT() SET_OUTPUT(E5_DIR_PIN)
  #define E5_DIR_WRITE(STATE) WRITE(E5_DIR_PIN,STATE)
  #define E5_DIR_READ() bool(READ(E5_DIR_PIN))
#endif
#define E5_STEP_INIT() SET_OUTPUT(E5_STEP_PIN)
#ifndef E5_STEP_WRITE
  #define E5_STEP_WRITE(STATE) WRITE(E5_STEP_PIN,STATE)
#endif
#define E5_STEP_READ() bool(READ(E5_STEP_PIN))

// E6 Stepper
#ifndef E6_ENABLE_INIT
  #define E6_ENABLE_INIT() SET_OUTPUT(E6_ENABLE_PIN)
  #define E6_ENABLE_WRITE(STATE) WRITE(E6_ENABLE_PIN,STATE)
  #define E6_ENABLE_READ() bool(READ(E6_ENABLE_PIN))
#endif
#ifndef E6_DIR_INIT
  #define E6_DIR_INIT() SET_OUTPUT(E6_DIR_PIN)
  #define E6_DIR_WRITE(STATE) WRITE(E6_DIR_PIN,STATE)
  #define E6_DIR_READ() bool(READ(E6_DIR_PIN))
#endif
#define E6_STEP_INIT() SET_OUTPUT(E6_STEP_PIN)
#ifndef E6_STEP_WRITE
  #define E6_STEP_WRITE(STATE) WRITE(E6_STEP_PIN,STATE)
#endif
#define E6_STEP_READ() bool(READ(E6_STEP_PIN))

// E7 Stepper
#ifndef E7_ENABLE_INIT
  #define E7_ENABLE_INIT() SET_OUTPUT(E7_ENABLE_PIN)
  #define E7_ENABLE_WRITE(STATE) WRITE(E7_ENABLE_PIN,STATE)
  #define E7_ENABLE_READ() bool(READ(E7_ENABLE_PIN))
#endif
#ifndef E7_DIR_INIT
  #define E7_DIR_INIT() SET_OUTPUT(E7_DIR_PIN)
  #define E7_DIR_WRITE(STATE) WRITE(E7_DIR_PIN,STATE)
  #define E7_DIR_READ() bool(READ(E7_DIR_PIN))
#endif
#define E7_STEP_INIT() SET_OUTPUT(E7_STEP_PIN)
#ifndef E7_STEP_WRITE
  #define E7_STEP_WRITE(STATE) WRITE(E7_STEP_PIN,STATE)
#endif
#define E7_STEP_READ() bool(READ(E7_STEP_PIN))

#define INVERT_DIR(AXIS, D) (TERN_(INVERT_## AXIS ##_DIR, !)(D))

  #define E_STEP_WRITE(E,V) E0_STEP_WRITE(V)
  #define   NORM_E_DIR(E)   E0_DIR_WRITE(!INVERT_E0_DIR)
  #define    REV_E_DIR(E)   E0_DIR_WRITE( INVERT_E0_DIR)

//
// Individual stepper enable / disable macros
//

#ifndef ENABLE_STEPPER_X
  #define  ENABLE_STEPPER_X() TERN(HAS_X_ENABLE, X_ENABLE_WRITE( X_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_X
  #define DISABLE_STEPPER_X() TERN(HAS_X_ENABLE, X_ENABLE_WRITE(!X_ENABLE_ON), NOOP)
#endif

#ifndef ENABLE_STEPPER_X2
  #define  ENABLE_STEPPER_X2() TERN(HAS_X2_ENABLE, X2_ENABLE_WRITE( X_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_X2
  #define DISABLE_STEPPER_X2() TERN(HAS_X2_ENABLE, X2_ENABLE_WRITE(!X_ENABLE_ON), NOOP)
#endif

#ifndef ENABLE_STEPPER_Y
  #define  ENABLE_STEPPER_Y() TERN(HAS_Y_ENABLE, Y_ENABLE_WRITE( Y_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_Y
  #define DISABLE_STEPPER_Y() TERN(HAS_Y_ENABLE, Y_ENABLE_WRITE(!Y_ENABLE_ON), NOOP)
#endif

#ifndef ENABLE_STEPPER_Y2
  #define  ENABLE_STEPPER_Y2() TERN(HAS_Y2_ENABLE, Y2_ENABLE_WRITE( Y_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_Y2
  #define DISABLE_STEPPER_Y2() TERN(HAS_Y2_ENABLE, Y2_ENABLE_WRITE(!Y_ENABLE_ON), NOOP)
#endif

#ifndef ENABLE_STEPPER_Z
  #define  ENABLE_STEPPER_Z() TERN(HAS_Z_ENABLE, Z_ENABLE_WRITE( Z_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_Z
  #define DISABLE_STEPPER_Z() TERN(HAS_Z_ENABLE, Z_ENABLE_WRITE(!Z_ENABLE_ON), NOOP)
#endif

#ifndef ENABLE_STEPPER_Z2
  #define  ENABLE_STEPPER_Z2() TERN(HAS_Z2_ENABLE, Z2_ENABLE_WRITE( Z_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_Z2
  #define DISABLE_STEPPER_Z2() TERN(HAS_Z2_ENABLE, Z2_ENABLE_WRITE(!Z_ENABLE_ON), NOOP)
#endif

#ifndef ENABLE_STEPPER_Z3
  #define  ENABLE_STEPPER_Z3() TERN(HAS_Z3_ENABLE, Z3_ENABLE_WRITE( Z_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_Z3
  #define DISABLE_STEPPER_Z3() TERN(HAS_Z3_ENABLE, Z3_ENABLE_WRITE(!Z_ENABLE_ON), NOOP)
#endif

#ifndef ENABLE_STEPPER_Z4
  #define  ENABLE_STEPPER_Z4() TERN(HAS_Z4_ENABLE, Z4_ENABLE_WRITE( Z_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_Z4
  #define DISABLE_STEPPER_Z4() TERN(HAS_Z4_ENABLE, Z4_ENABLE_WRITE(!Z_ENABLE_ON), NOOP)
#endif


#ifndef ENABLE_STEPPER_E0
  #define  ENABLE_STEPPER_E0() TERN(HAS_E0_ENABLE, E0_ENABLE_WRITE( E_ENABLE_ON), NOOP)
#endif
#ifndef DISABLE_STEPPER_E0
  #define DISABLE_STEPPER_E0() TERN(HAS_E0_ENABLE, E0_ENABLE_WRITE(!E_ENABLE_ON), NOOP)
#endif

#ifndef ENABLE_STEPPER_E1
  #if (E_STEPPERS > 1 || ENABLED(E_DUAL_STEPPER_DRIVERS)) && HAS_E1_ENABLE
    #define  ENABLE_STEPPER_E1() E1_ENABLE_WRITE( E_ENABLE_ON)
  #else
    #define  ENABLE_STEPPER_E1() NOOP
  #endif
#endif
#ifndef DISABLE_STEPPER_E1
  #if (E_STEPPERS > 1 || ENABLED(E_DUAL_STEPPER_DRIVERS)) && HAS_E1_ENABLE
    #define DISABLE_STEPPER_E1() E1_ENABLE_WRITE(!E_ENABLE_ON)
  #else
    #define DISABLE_STEPPER_E1() NOOP
  #endif
#endif

#ifndef ENABLE_STEPPER_E2
  #if E_STEPPERS > 2 && HAS_E2_ENABLE
    #define  ENABLE_STEPPER_E2() E2_ENABLE_WRITE( E_ENABLE_ON)
  #else
    #define  ENABLE_STEPPER_E2() NOOP
  #endif
#endif
#ifndef DISABLE_STEPPER_E2
  #if E_STEPPERS > 2 && HAS_E2_ENABLE
    #define DISABLE_STEPPER_E2() E2_ENABLE_WRITE(!E_ENABLE_ON)
  #else
    #define DISABLE_STEPPER_E2() NOOP
  #endif
#endif

#ifndef ENABLE_STEPPER_E3
  #if E_STEPPERS > 3 && HAS_E3_ENABLE
    #define  ENABLE_STEPPER_E3() E3_ENABLE_WRITE( E_ENABLE_ON)
  #else
    #define  ENABLE_STEPPER_E3() NOOP
  #endif
#endif
#ifndef DISABLE_STEPPER_E3
  #if E_STEPPERS > 3 && HAS_E3_ENABLE
    #define DISABLE_STEPPER_E3() E3_ENABLE_WRITE(!E_ENABLE_ON)
  #else
    #define DISABLE_STEPPER_E3() NOOP
  #endif
#endif

#ifndef ENABLE_STEPPER_E4
  #if E_STEPPERS > 4 && HAS_E4_ENABLE
    #define  ENABLE_STEPPER_E4() E4_ENABLE_WRITE( E_ENABLE_ON)
  #else
    #define  ENABLE_STEPPER_E4() NOOP
  #endif
#endif
#ifndef DISABLE_STEPPER_E4
  #if E_STEPPERS > 4 && HAS_E4_ENABLE
    #define DISABLE_STEPPER_E4() E4_ENABLE_WRITE(!E_ENABLE_ON)
  #else
    #define DISABLE_STEPPER_E4() NOOP
  #endif
#endif

#ifndef ENABLE_STEPPER_E5
  #if E_STEPPERS > 5 && HAS_E5_ENABLE
    #define  ENABLE_STEPPER_E5() E5_ENABLE_WRITE( E_ENABLE_ON)
  #else
    #define  ENABLE_STEPPER_E5() NOOP
  #endif
#endif
#ifndef DISABLE_STEPPER_E5
  #if E_STEPPERS > 5 && HAS_E5_ENABLE
    #define DISABLE_STEPPER_E5() E5_ENABLE_WRITE(!E_ENABLE_ON)
  #else
    #define DISABLE_STEPPER_E5() NOOP
  #endif
#endif

#ifndef ENABLE_STEPPER_E6
  #if E_STEPPERS > 6 && HAS_E6_ENABLE
    #define  ENABLE_STEPPER_E6() E6_ENABLE_WRITE( E_ENABLE_ON)
  #else
    #define  ENABLE_STEPPER_E6() NOOP
  #endif
#endif
#ifndef DISABLE_STEPPER_E6
  #if E_STEPPERS > 6 && HAS_E6_ENABLE
    #define DISABLE_STEPPER_E6() E6_ENABLE_WRITE(!E_ENABLE_ON)
  #else
    #define DISABLE_STEPPER_E6() NOOP
  #endif
#endif

#ifndef ENABLE_STEPPER_E7
  #if E_STEPPERS > 7 && HAS_E7_ENABLE
    #define  ENABLE_STEPPER_E7() E7_ENABLE_WRITE( E_ENABLE_ON)
  #else
    #define  ENABLE_STEPPER_E7() NOOP
  #endif
#endif
#ifndef DISABLE_STEPPER_E7
  #if E_STEPPERS > 7 && HAS_E7_ENABLE
    #define DISABLE_STEPPER_E7() E7_ENABLE_WRITE(!E_ENABLE_ON)
  #else
    #define DISABLE_STEPPER_E7() NOOP
  #endif
#endif

//
// Axis steppers enable / disable macros
//
#if ENABLED(SOFTWARE_DRIVER_ENABLE)
  // Avoid expensive calls to enable / disable steppers
  extern xyz_bool_t axis_sw_enabled;
  #define SHOULD_ENABLE(N)  !axis_sw_enabled.N
  #define SHOULD_DISABLE(N)  axis_sw_enabled.N
  #define AFTER_CHANGE(N,TF) axis_sw_enabled.N = TF
#else
  #define SHOULD_ENABLE(N)   true
  #define SHOULD_DISABLE(N)  true
  #define AFTER_CHANGE(N,TF) NOOP
#endif

#define  ENABLE_AXIS_X() if (SHOULD_ENABLE(x))  {  ENABLE_STEPPER_X();  ENABLE_STEPPER_X2(); AFTER_CHANGE(x, true); }
#define DISABLE_AXIS_X() if (SHOULD_DISABLE(x)) { DISABLE_STEPPER_X(); DISABLE_STEPPER_X2(); AFTER_CHANGE(x, false); set_axis_untrusted(X_AXIS); }

#if HAS_Y_AXIS
  #define  ENABLE_AXIS_Y() if (SHOULD_ENABLE(y))  {  ENABLE_STEPPER_Y();  ENABLE_STEPPER_Y2(); AFTER_CHANGE(y, true); }
  #define DISABLE_AXIS_Y() if (SHOULD_DISABLE(y)) { DISABLE_STEPPER_Y(); DISABLE_STEPPER_Y2(); AFTER_CHANGE(y, false); set_axis_untrusted(Y_AXIS); }
#else
  #define  ENABLE_AXIS_Y() NOOP
  #define DISABLE_AXIS_Y() NOOP
#endif

#if HAS_Z_AXIS
  #define  ENABLE_AXIS_Z() if (SHOULD_ENABLE(z))  {  ENABLE_STEPPER_Z();  ENABLE_STEPPER_Z2();  ENABLE_STEPPER_Z3();  ENABLE_STEPPER_Z4(); AFTER_CHANGE(z, true); }
  #define DISABLE_AXIS_Z() if (SHOULD_DISABLE(z)) { DISABLE_STEPPER_Z(); DISABLE_STEPPER_Z2(); DISABLE_STEPPER_Z3(); DISABLE_STEPPER_Z4(); AFTER_CHANGE(z, false); set_axis_untrusted(Z_AXIS); Z_RESET(); TERN_(BD_SENSOR, bdl.config_state = 0); }
#else
  #define  ENABLE_AXIS_Z() NOOP
  #define DISABLE_AXIS_Z() NOOP
#endif

#ifdef Z_IDLE_HEIGHT
  #define Z_RESET() do{ current_position.z = Z_IDLE_HEIGHT; sync_plan_position(); }while(0)
#else
  #define Z_RESET()
#endif


//
// Extruder steppers enable / disable macros
//

#if ENABLED(MIXING_EXTRUDER)

  /**
   * Mixing steppers keep all their enable (and direction) states synchronized
   */
  #define _CALL_ENA_E(N)  ENABLE_STEPPER_E##N () ;
  #define _CALL_DIS_E(N) DISABLE_STEPPER_E##N () ;
  #define  ENABLE_AXIS_E0() { RREPEAT(MIXING_STEPPERS, _CALL_ENA_E) }
  #define DISABLE_AXIS_E0() { RREPEAT(MIXING_STEPPERS, _CALL_DIS_E) }

#elif ENABLED(E_DUAL_STEPPER_DRIVERS)

  #define  ENABLE_AXIS_E0() do{  ENABLE_STEPPER_E0();  ENABLE_STEPPER_E1(); }while(0)
  #define DISABLE_AXIS_E0() do{ DISABLE_STEPPER_E0(); DISABLE_STEPPER_E1(); }while(0)

#endif

#ifndef ENABLE_AXIS_E0
  #if E_STEPPERS && HAS_E0_ENABLE
    #define  ENABLE_AXIS_E0() ENABLE_STEPPER_E0()
  #else
    #define  ENABLE_AXIS_E0() NOOP
  #endif
#endif
#ifndef DISABLE_AXIS_E0
  #if E_STEPPERS && HAS_E0_ENABLE
    #define DISABLE_AXIS_E0() DISABLE_STEPPER_E0()
  #else
    #define DISABLE_AXIS_E0() NOOP
  #endif
#endif

#ifndef ENABLE_AXIS_E1
  #if E_STEPPERS > 1 && HAS_E1_ENABLE
    #define  ENABLE_AXIS_E1() ENABLE_STEPPER_E1()
  #else
    #define  ENABLE_AXIS_E1() NOOP
  #endif
#endif
#ifndef DISABLE_AXIS_E1
  #if E_STEPPERS > 1 && HAS_E1_ENABLE
    #define DISABLE_AXIS_E1() DISABLE_STEPPER_E1()
  #else
    #define DISABLE_AXIS_E1() NOOP
  #endif
#endif

#ifndef ENABLE_AXIS_E2
  #if E_STEPPERS > 2 && HAS_E2_ENABLE
    #define  ENABLE_AXIS_E2() ENABLE_STEPPER_E2()
  #else
    #define  ENABLE_AXIS_E2() NOOP
  #endif
#endif
#ifndef DISABLE_AXIS_E2
  #if E_STEPPERS > 2 && HAS_E2_ENABLE
    #define DISABLE_AXIS_E2() DISABLE_STEPPER_E2()
  #else
    #define DISABLE_AXIS_E2() NOOP
  #endif
#endif

#ifndef ENABLE_AXIS_E3
  #if E_STEPPERS > 3 && HAS_E3_ENABLE
    #define  ENABLE_AXIS_E3() ENABLE_STEPPER_E3()
  #else
    #define  ENABLE_AXIS_E3() NOOP
  #endif
#endif
#ifndef DISABLE_AXIS_E3
  #if E_STEPPERS > 3 && HAS_E3_ENABLE
    #define DISABLE_AXIS_E3() DISABLE_STEPPER_E3()
  #else
    #define DISABLE_AXIS_E3() NOOP
  #endif
#endif

#ifndef ENABLE_AXIS_E4
  #if E_STEPPERS > 4 && HAS_E4_ENABLE
    #define  ENABLE_AXIS_E4() ENABLE_STEPPER_E4()
  #else
    #define  ENABLE_AXIS_E4() NOOP
  #endif
#endif
#ifndef DISABLE_AXIS_E4
  #if E_STEPPERS > 4 && HAS_E4_ENABLE
    #define DISABLE_AXIS_E4() DISABLE_STEPPER_E4()
  #else
    #define DISABLE_AXIS_E4() NOOP
  #endif
#endif

#ifndef ENABLE_AXIS_E5
  #if E_STEPPERS > 5 && HAS_E5_ENABLE
    #define  ENABLE_AXIS_E5() ENABLE_STEPPER_E5()
  #else
    #define  ENABLE_AXIS_E5() NOOP
  #endif
#endif
#ifndef DISABLE_AXIS_E5
  #if E_STEPPERS > 5 && HAS_E5_ENABLE
    #define DISABLE_AXIS_E5() DISABLE_STEPPER_E5()
  #else
    #define DISABLE_AXIS_E5() NOOP
  #endif
#endif

#ifndef ENABLE_AXIS_E6
  #if E_STEPPERS > 6 && HAS_E6_ENABLE
    #define  ENABLE_AXIS_E6() ENABLE_STEPPER_E6()
  #else
    #define  ENABLE_AXIS_E6() NOOP
  #endif
#endif
#ifndef DISABLE_AXIS_E6
  #if E_STEPPERS > 6 && HAS_E6_ENABLE
    #define DISABLE_AXIS_E6() DISABLE_STEPPER_E6()
  #else
    #define DISABLE_AXIS_E6() NOOP
  #endif
#endif

#ifndef ENABLE_AXIS_E7
  #if E_STEPPERS > 7 && HAS_E7_ENABLE
    #define  ENABLE_AXIS_E7() ENABLE_STEPPER_E7()
  #else
    #define  ENABLE_AXIS_E7() NOOP
  #endif
#endif
#ifndef DISABLE_AXIS_E7
  #if E_STEPPERS > 7 && HAS_E7_ENABLE
    #define DISABLE_AXIS_E7() DISABLE_STEPPER_E7()
  #else
    #define DISABLE_AXIS_E7() NOOP
  #endif
#endif
