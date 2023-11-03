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

#include "../inc/MarlinConfig.h"

#include "../module/motion.h"

#include "buttons.h"

#if HAS_SOUND
  #include "../libs/buzzer.h"
#endif

#if ENABLED(SDSUPPORT)
  #include "../sd/cardreader.h"
#endif


#if HAS_DISPLAY
  #include "../module/printcounter.h"
#endif



#if PREHEAT_COUNT
  typedef struct {
    TERN_(HAS_HOTEND,     uint16_t hotend_temp);
    TERN_(HAS_HEATED_BED, uint16_t bed_temp   );
    TERN_(HAS_FAN,        uint16_t fan_speed  );
  } preheat_t;
#endif

////////////////////////////////////////////
//////////// MarlinUI Singleton ////////////
////////////////////////////////////////////
typedef bool (*statusResetFunc_t)();

class MarlinUI {
public:

  MarlinUI() {
    TERN_(HAS_LCD_MENU, currentScreen = status_screen);
  }

    static constexpr bool sound_on = true;

  #if HAS_SOUND
    static void buzz(const long duration, const uint16_t freq);
  #endif

  FORCE_INLINE static void chirp() {
    TERN_(HAS_CHIRP, buzz(LCD_FEEDBACK_FREQUENCY_DURATION_MS, LCD_FEEDBACK_FREQUENCY_HZ));
  }

  // LCD implementations
  static void clear_lcd();

  #if ENABLED(SDSUPPORT)
    #define MEDIA_MENU_GATEWAY TERN(PASSWORD_ON_SD_PRINT_MENU, password.media_gatekeeper, menu_media)
    static void media_changed(const uint8_t old_stat, const uint8_t stat);
  #endif

  #if ENABLED(DWIN_CREALITY_LCD)
    static void refresh();
  #else
    FORCE_INLINE static void refresh() {
      TERN_(HAS_WIRED_LCD, refresh(LCDVIEW_CLEAR_CALL_REDRAW));
    }
  #endif

    static inline bool detected() { return true; }
    static inline void init_lcd() {}

  #if HAS_PRINT_PROGRESS
    #if HAS_PRINT_PROGRESS_PERMYRIAD
      typedef uint16_t progress_t;
      #define PROGRESS_SCALE 100U
      #define PROGRESS_MASK 0x7FFF
    #else
      typedef uint8_t progress_t;
      #define PROGRESS_SCALE 1U
      #define PROGRESS_MASK 0x7F
    #endif
    static progress_t _get_progress();
    #if HAS_PRINT_PROGRESS_PERMYRIAD
      FORCE_INLINE static uint16_t get_progress_permyriad() { return _get_progress(); }
    #endif
    static uint8_t get_progress_percent() { return uint8_t(_get_progress() / (PROGRESS_SCALE)); }
  #endif

  #if HAS_STATUS_MESSAGE
    static char status_message[];
    static uint8_t alert_level; // Higher levels block lower levels

    static bool has_status();
    static void reset_status(const bool no_welcome=false);
    static void set_status(const char* const message, const bool persist=false);
    static void set_status_P(PGM_P const message, const int8_t level=0);
    static void status_printf_P(const uint8_t level, PGM_P const fmt, ...);
    static void set_alert_status_P(PGM_P const message);
    static inline void reset_alert_level() { alert_level = 0; }
  #else
    static constexpr bool has_status() { return false; }
    static inline void reset_status(const bool=false) {}
    static void set_status(const char* message, const bool=false);
    static void set_status_P(PGM_P message, const int8_t=0);
    static void status_printf_P(const uint8_t, PGM_P message, ...);
    static inline void set_alert_status_P(PGM_P const) {}
    static inline void reset_alert_level() {}
  #endif
    static statusResetFunc_t status_reset_callback;
    static void set_status_reset_fn(const statusResetFunc_t fn=nullptr) { status_reset_callback = fn; }
    static void flow_fault();
  static void _pause_show_message() {}
#define pause_show_message(...) _pause_show_message()

  #if HAS_DISPLAY

    static void init();
    static void param_init();
    static void update();

    static void abort_print();
    static void pause_print();
    static void resume_print();

    #if HAS_MARLINUI_U8GLIB
      static bool drawing_screen, first_page;
    #else
      static constexpr bool drawing_screen = false, first_page = true;
    #endif

    static bool get_blink();
    static void kill_screen(PGM_P const lcd_error, PGM_P const lcd_component);
    static void draw_kill_screen();

  #else // No LCD

    static inline void init() {}
    static inline void update() {}
    static inline void return_to_status() {}

  #endif

  #if ENABLED(SDSUPPORT)
    static const char * scrolled_filename(CardReader &theCard, const uint8_t maxlen, uint8_t hash, const bool doScroll);
  #endif

  #if PREHEAT_COUNT
    static preheat_t material_preset[PREHEAT_COUNT];
    static PGM_P get_preheat_label(const uint8_t m);
  #endif

  //
  // EEPROM: Reset / Init / Load / Store
  //

  #if ENABLED(EEPROM_SETTINGS)
    #if DISABLED(EEPROM_AUTO_INIT)
      static void eeprom_alert(const uint8_t msgid);
      static inline void eeprom_alert_crc()     { eeprom_alert(0); }
      static inline void eeprom_alert_index()   { eeprom_alert(1); }
      static inline void eeprom_alert_version() { eeprom_alert(2); }
    #endif
  #endif

  #if ENABLED(PREHEAT_BEFORE_LEVELING)
    static void probe_preheating_start();
    static void probe_preheating_stop();
  #endif

    static constexpr bool wait_for_move = false;
    static constexpr bool external_control = false;

    static inline void update_buttons() {}

private:

  #if HAS_STATUS_MESSAGE
    static void finish_status(const bool persist);
  #endif
};

extern MarlinUI ui;

#define LCD_MESSAGE_F(S)       ui.set_status_P(PSTR(S))
#define LCD_ALERTMESSAGE(M)    ui.set_alert_status_P(GET_TEXT(M))

#define LCD_MESSAGE(M)         LCD_MESSAGE_F(GET_TEXT(M))
#define LCD_ALERTMESSAGE_F(S)  LCD_ALERTMESSAGE(S)

