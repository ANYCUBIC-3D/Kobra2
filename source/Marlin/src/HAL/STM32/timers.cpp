/**
 * Marlin 3D Printer Firmware
 *
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 * Copyright (c) 2016 Bob Cousins bobcousins42@googlemail.com
 * Copyright (c) 2015-2016 Nico Tonnhofer wurstnase.reprap@gmail.com
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

/**
 * HAL for stm32duino.com based on Libmaple and compatible (STM32F1)
 */

#include "../../inc/MarlinConfig.h"

// ------------------------
// Local defines
// ------------------------

// ------------------------
// Public functions
// ------------------------

/**
 * Timer_clock1: Prescaler   2 ->  36    MHz
 * Timer_clock2: Prescaler   8 ->   9    MHz
 * Timer_clock3: Prescaler  32 ->   2.25 MHz
 * Timer_clock4: Prescaler 128 -> 562.5  kHz
 */

/**
 * TODO: Calculate Timer prescale value, so we get the 32bit to adjust
 */




#include "HAL.h"
#include "timers.h"

static hal_timer_t compare_hal=0x0;

void HAL_timer_start(const uint8_t timer_num, const uint32_t frequency) {
 	 switch (timer_num) {
    		case STEP_TIMER_NUM: setup_time2B(frequency);break;
    		case TEMP_TIMER_NUM: setup_time2A(frequency);break;
 	 }
}

void HAL_timer_enable_interrupt(const uint8_t timer_num) {
  switch (timer_num) {
    case STEP_TIMER_NUM: ENABLE_STEPPER_DRIVER_INTERRUPT(); break;
    case TEMP_TIMER_NUM: ENABLE_TEMPERATURE_INTERRUPT(); break;
  }
}

void HAL_timer_disable_interrupt(const uint8_t timer_num) {
  switch (timer_num) {
    case STEP_TIMER_NUM: DISABLE_STEPPER_DRIVER_INTERRUPT(); break;
    case TEMP_TIMER_NUM: DISABLE_TEMPERATURE_INTERRUPT(); break;
  }
}

bool HAL_timer_interrupt_enabled(const uint8_t timer_num) {
	return timer_irq_enabled(timer_num);
}

void HAL_timer_set_compare(const uint8_t timer_num, const hal_timer_t compare) {
        if(compare_hal != compare){
            compare_hal = compare;
            timer_set_compare(timer_num, compare);
        }
}

