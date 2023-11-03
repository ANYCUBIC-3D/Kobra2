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

#include "../inc/MarlinConfig.h"

// All displays share the MarlinUI class
#include "marlinui.h"
MarlinUI ui;

#if HAS_DISPLAY
  #include "../module/printcounter.h"
  #include "../MarlinCore.h"
  #include "../gcode/queue.h"
  #include "fontutils.h"
  #include "../sd/cardreader.h"
  #if EITHER(EXTENSIBLE_UI, DWIN_CREALITY_LCD)
    #define START_OF_UTF8_CHAR(C) (((C) & 0xC0u) != 0x80U)
  #endif
#endif

#if ANY(PARK_HEAD_ON_PAUSE, SDSUPPORT)
  #include "../gcode/queue.h"
#endif

//constexpr uint8_t epps = ENCODER_PULSES_PER_STEP;

#if HAS_WIRED_LCD
#elif EITHER(EXTENSIBLE_UI, DWIN_CREALITY_LCD)
  constexpr uint8_t MAX_MESSAGE_LENGTH = 63;
#endif

#if EITHER(HAS_WIRED_LCD, EXTENSIBLE_UI)
  uint8_t MarlinUI::alert_level; // = 0
  char MarlinUI::status_message[MAX_MESSAGE_LENGTH + 1];
#endif

#if EITHER(PCA9632_BUZZER, HAS_BEEPER)
  #include "../libs/buzzer.h" // for BUZZ() macro
  #if ENABLED(PCA9632_BUZZER)
    #include "../feature/leds/pca9632.h"
  #endif
  void MarlinUI::buzz(const long duration, const uint16_t freq) {
    if (!sound_on) return;
    #if HAS_BEEPER
      buzzer.tone(duration, freq);
    #endif
  }
#endif


#if HAS_STATUS_MESSAGE

  statusResetFunc_t MarlinUI::status_reset_callback; // = nullptr

  ////////////////////////////////////////////
  ////////////// Status Message //////////////
  ////////////////////////////////////////////

  #if ENABLED(EXTENSIBLE_UI)
    #include "extui/ui_api.h"
  #endif

  bool MarlinUI::has_status() { return (status_message[0] != '\0'); }

  void MarlinUI::set_status(const char * const message, const bool persist) {
    if (alert_level) return;

    TERN_(HOST_PROMPT_SUPPORT, host_action_notify(message));

    // Here we have a problem. The message is encoded in UTF8, so
    // arbitrarily cutting it will be a problem. We MUST be sure
    // that there is no cutting in the middle of a multibyte character!

    // Get a pointer to the null terminator
    const char* pend = message + strlen(message);

    //  If length of supplied UTF8 string is greater than
    // our buffer size, start cutting whole UTF8 chars
    while ((pend - message) > MAX_MESSAGE_LENGTH) {
      --pend;
      while (!START_OF_UTF8_CHAR(*pend)) --pend;
    };

    // At this point, we have the proper cut point. Use it
    uint8_t maxLen = pend - message;
    strncpy(status_message, message, maxLen);
    status_message[maxLen] = '\0';

    finish_status(persist);
  }

  /**
   * Reset the status message
   */
  void MarlinUI::reset_status(const bool no_welcome) {
    PGM_P msg;
    if (printingIsPaused())
      msg = GET_TEXT(MSG_PRINT_PAUSED);
    #if ENABLED(SDSUPPORT)
      else if (IS_SD_PRINTING())
        return set_status(card.longest_filename(), true);
    #endif
    else if (print_job_timer.isRunning())
      msg = GET_TEXT(MSG_PRINTING);
    else if (!no_welcome)
      msg = GET_TEXT(WELCOME_MSG);
    else
      return;

    set_status_P(msg, -1);
  }

  void MarlinUI::set_status_P(PGM_P const message, int8_t level) {
    if (level < 0) level = alert_level = 0;
    if (level < alert_level) return;
    alert_level = level;

    TERN_(HOST_PROMPT_SUPPORT, host_action_notify_P(message));

    // Since the message is encoded in UTF8 it must
    // only be cut on a character boundary.

    // Get a pointer to the null terminator
    PGM_P pend = message + strlen_P(message);

    // If length of supplied UTF8 string is greater than
    // the buffer size, start cutting whole UTF8 chars
    while ((pend - message) > MAX_MESSAGE_LENGTH) {
      --pend;
      while (!START_OF_UTF8_CHAR(pgm_read_byte(pend))) --pend;
    };

    // At this point, we have the proper cut point. Use it
    uint8_t maxLen = pend - message;
    strncpy_P(status_message, message, maxLen);
    status_message[maxLen] = '\0';

    finish_status(level > 0);
  }

  void MarlinUI::set_alert_status_P(PGM_P const message) {
    set_status_P(message, 1);
    TERN_(HAS_LCD_MENU, return_to_status());
  }

  #include <stdarg.h>

  void MarlinUI::status_printf_P(const uint8_t level, PGM_P const fmt, ...) {
    if (level < alert_level) return;
    alert_level = level;
    va_list args;
    va_start(args, fmt);
    vsnprintf_P(status_message, MAX_MESSAGE_LENGTH, fmt, args);
    va_end(args);
    finish_status(level > 0);
  }
  
  void MarlinUI::finish_status(const bool persist) {
      UNUSED(persist);
    TERN_(EXTENSIBLE_UI, ExtUI::onStatusChanged(status_message));
  }
#endif

#if HAS_DISPLAY

  #if ENABLED(SDSUPPORT)
    extern bool wait_for_user, wait_for_heatup;
  #endif

  void MarlinUI::abort_print() {
    #if ENABLED(SDSUPPORT)
      wait_for_heatup = wait_for_user = false;
      card.flag.abort_sd_printing = true;
      did_pause_print = 0;
      //card.abortFilePrintSoon();
    #endif
    #ifdef ACTION_ON_CANCEL
      host_action_cancel();
    #endif
    TERN_(HOST_PROMPT_SUPPORT, host_prompt_open(PROMPT_INFO, PSTR("UI Aborted"), DISMISS_STR));
    print_job_timer.stop();
    LCD_MESSAGE(MSG_PRINT_ABORTED);
    TERN_(HAS_LCD_MENU, return_to_status());
  }
  void MarlinUI::flow_fault() {
    LCD_ALERTMESSAGE(MSG_FLOWMETER_FAULT);
    BUZZ(1000, 440);
    TERN_(HAS_MARLINUI_MENU, return_to_status());
  }
  void MarlinUI::pause_print() {
    TERN_(HOST_PROMPT_SUPPORT, host_prompt_open(PROMPT_PAUSE_RESUME, PSTR("UI Pause"), PSTR("Resume")));

    LCD_MESSAGE(MSG_PRINT_PAUSED);

    #if ENABLED(PARK_HEAD_ON_PAUSE)
      TERN_(HAS_WIRED_LCD, lcd_pause_show_message(PAUSE_MESSAGE_PARKING, PAUSE_MODE_PAUSE_PRINT)); // Show message immediately to let user know about pause in progress
      queue.inject_P(PSTR("M25 \nM24"));
    #elif ENABLED(SDSUPPORT)
      queue.inject_P(PSTR("M25"));
    #elif defined(ACTION_ON_PAUSE)
    #endif
  }

  void MarlinUI::resume_print() {
    reset_status();
    TERN_(PARK_HEAD_ON_PAUSE, wait_for_heatup = wait_for_user = false);
    if (IS_SD_PAUSED()) queue.inject_P(M24_STR);
    print_job_timer.start(); // Also called by M24
  }

  #if HAS_PRINT_PROGRESS

    MarlinUI::progress_t MarlinUI::_get_progress() {
      return (
        TERN0(LCD_SET_PROGRESS_MANUALLY, (progress_override & PROGRESS_MASK))
        #if ENABLED(SDSUPPORT)
          ?: TERN(HAS_PRINT_PROGRESS_PERMYRIAD, card.permyriadDone(), card.percentDone())
        #endif
      );
    }

  #endif
#endif // !HAS_DISPLAY

#if ENABLED(SDSUPPORT)

  #if ENABLED(EXTENSIBLE_UI)
    #include "extui/ui_api.h"
  #endif

  void MarlinUI::media_changed(const uint8_t old_status, const uint8_t status) {
    if (old_status == status) {
      TERN_(EXTENSIBLE_UI, ExtUI::onMediaError()); // Failed to mount/unmount
      return;
    }

    if (status) {
      if (old_status < 2) {
        TERN_(EXTENSIBLE_UI, ExtUI::onMediaInserted()); // ExtUI response
         LCD_MESSAGE(MSG_MEDIA_INSERTED);
      }
    }
    else {
      if (old_status < 2) {
        TERN_(EXTENSIBLE_UI, ExtUI::onMediaRemoved()); // ExtUI response
        #if PIN_EXISTS(SD_DETECT)
          LCD_MESSAGE(MSG_MEDIA_REMOVED);
        #endif
      }
    }

    #if PIN_EXISTS(SD_DETECT) && DISABLED(NO_LCD_REINIT)
      init_lcd(); // Revive a noisy shared SPI LCD
    #endif

    refresh();
  }

#endif // SDSUPPORT

#if ENABLED(EEPROM_SETTINGS)

  #if ENABLED(PREHEAT_BEFORE_LEVELING)
    void MarlinUI::probe_preheating_start()
    {
//        TERN_(EXTENSIBLE_UI, ExtUI::onStatusChanged(status_message));
        TERN_(EXTENSIBLE_UI, ExtUI::onStatusChanged("Probe preheat start"));
    }

    void MarlinUI::probe_preheating_stop()
    {
        TERN_(EXTENSIBLE_UI, ExtUI::onStatusChanged("Probe preheat stop"));
    }
  #endif
  
#endif // EEPROM_SETTINGS
