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

#include "serial.h"
#include "../inc/MarlinConfig.h"

#if HAS_ETHERNET
  #include "../feature/ethernet.h"
#endif

uint8_t marlin_debug_flags = MARLIN_DEBUG_NONE;

// Commonly-used strings in serial output
PGMSTR(SP_A_STR, " A"); PGMSTR(SP_B_STR, " B"); PGMSTR(SP_C_STR, " C");
PGMSTR(SP_P_STR, " P"); PGMSTR(SP_T_STR, " T"); PGMSTR(NUL_STR,   "");

#define _N_STR(N) PGMSTR(N##_STR, STR_##N);
#define _N_LBL(N) PGMSTR(N##_LBL, STR_##N ":");
#define _SP_N_STR(N) PGMSTR(SP_##N##_STR, " " STR_##N);
#define _SP_N_LBL(N) PGMSTR(SP_##N##_LBL, " " STR_##N ":");
MAP(_N_STR, LOGICAL_AXIS_NAMES); MAP(_SP_N_STR, LOGICAL_AXIS_NAMES);
MAP(_N_LBL, LOGICAL_AXIS_NAMES); MAP(_SP_N_LBL, LOGICAL_AXIS_NAMES);

void serial_print_P(PGM_P str) {
  while (const char c = pgm_read_byte(str++)) SERIAL_CHAR(c);
}

void serial_echo_start()  { serial_print(F("echo:")); }
void serial_error_start() { serial_print(F("Error:")); }

void serial_spaces(uint8_t count) { count *= (PROPORTIONAL_FONT_RATIO); while (count--) SERIAL_CHAR(' '); }

void serial_offset(const_float_t v, const uint8_t sp/*=0*/) {
  if (v == 0 && sp == 1)
    SERIAL_CHAR(' ');
  else if (v > 0 || (v == 0 && sp == 2))
    SERIAL_CHAR('+');
  SERIAL_DECIMAL(v);
}

void serial_ternary(const bool onoff, FSTR_P const pre, FSTR_P const on, FSTR_P const off, FSTR_P const post/*=nullptr*/) {
  if (pre) serial_print(pre);
  serial_print(onoff ? on : off);
  if (post) serial_print(post);
}
void serialprint_onoff(const bool onoff) { serial_print(onoff ? F(STR_ON) : F(STR_OFF)); }
void serialprintln_onoff(const bool onoff) { serialprint_onoff(onoff); SERIAL_EOL(); }
void serialprint_truefalse(const bool tf) { serial_print(tf ? F("true") : F("false")); }

void print_bin(uint16_t val) {
  for (uint8_t i = 16; i--;) {
    SERIAL_CHAR('0' + TEST(val, i));
    if (!(i & 0x3) && i) SERIAL_CHAR(' ');
  }
}
void print_pos(const float &x, const float &y, const float &z, FSTR_P const prefix/*=nullptr*/, FSTR_P const suffix/*=nullptr*/) {
  if (prefix) serial_print(prefix);
  SERIAL_ECHOPGM_P(
    LIST_N(DOUBLE(NUM_AXES), SP_X_STR, x, SP_Y_STR, y, SP_Z_STR, z, SP_I_STR, i, SP_J_STR, j, SP_K_STR, k, SP_U_STR, u, SP_V_STR, v, SP_W_STR, w)
  );
  if (suffix) serial_print(suffix); else SERIAL_EOL();
}
