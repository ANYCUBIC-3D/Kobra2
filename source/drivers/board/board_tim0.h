#pragma once

#include "hc32_common.h"

/* Define Timer Unit for example */
#define TMR_UNIT            (M4_TMR02)
#define TMR_INI_GCMA        (INT_TMR02_GCMA)
#define TMR_INI_GCMB        (INT_TMR02_GCMB)
#define OS_TICKS_PER_SEC   1000ul

#ifdef __cplusplus
extern "C"{
#endif

void setup_time2B(const uint32_t frequency);
void setup_time2A(const uint32_t frequency);

en_result_t timer_preset_compare(en_tim0_channel_t enCh,const uint16_t compare);
en_result_t timer_set_compare(const uint8_t timer_num,const uint16_t compare);
uint16_t timer_get_count(const uint8_t timer_num);
void timer_enable_irq(const uint8_t timer_num);
void timer_disable_irq(const uint8_t timer_num);
bool timer_irq_enabled(const uint8_t timer_num);

#ifdef __cplusplus
}
#endif



