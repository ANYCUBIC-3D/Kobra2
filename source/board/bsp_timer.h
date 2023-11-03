#pragma once

#include "hc32_ddl.h"
#include "../cores/libmaple_types.h"
#include "../cores/wirish_types.h"

#ifdef __cplusplus
extern "C"{
#endif


#define TMR_SSERIAL_STOP()  TIMER0_Cmd(M4_TMR01, Tim0_ChannelA, Disable)
#define TMR_SSERIAL_RESUM() TIMER0_Cmd(M4_TMR01, Tim0_ChannelA, Enable)

static inline __always_inline uint32_t get_pclk1Freq(void){
    stc_clk_freq_t stcClkTmp;
    CLK_GetClockFreq(&stcClkTmp);
    return (stcClkTmp.pclk1Freq);
}
/******************************/
void timer01B_init(void);
static inline __always_inline void timer01B_set_overflow(uint16_t ms){
    uint32_t u32Pclk1;
    stc_clk_freq_t stcClkTmp;
    CLK_GetClockFreq(&stcClkTmp);
    u32Pclk1 = stcClkTmp.pclk1Freq;
    M4_TMR01->CMPBR_f.CMPB = (uint16_t)(u32Pclk1/1024ul/1000*ms);
    TIMER0_Cmd(M4_TMR01, Tim0_ChannelB, Enable);
}
static inline __always_inline void timer01B_enable(void){
    TIMER0_Cmd(M4_TMR01, Tim0_ChannelB, Enable);
}
static inline __always_inline void timer01B_disable(void){
    TIMER0_Cmd(M4_TMR01, Tim0_ChannelB, Disable);
    M4_TMR01->CNTBR = 0;
}
/******************************/
void timer01A_init(void);
/******************************/

#ifdef __cplusplus
} // extern "C"
#endif

