#include "hc32f46x.h"

#include "bsp_timer.h"
#include "bsp_irq.h"
#include "bsp_init.h"
#include "SoftwareSerial.h"


static void Timer01B_CallBack(void){
    HAL_TONE_TIMER_ISR();
}

void timer01B_init(void)
{
    stc_clk_freq_t stcClkTmp;

    uint32_t u32Pclk1;

    stc_tim0_base_init_t stcTimerCfg;

    MEM_ZERO_STRUCT(stcTimerCfg);

    PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIM01, Enable);

// Get pclk1
    CLK_GetClockFreq(&stcClkTmp);
    u32Pclk1 = stcClkTmp.pclk1Freq;

    stcTimerCfg.Tim0_CounterMode = Tim0_Sync;
    stcTimerCfg.Tim0_SyncClockSource = Tim0_Pclk1;
    stcTimerCfg.Tim0_ClockDivision = Tim0_ClkDiv1024;
    stcTimerCfg.Tim0_CmpValue = (uint16_t)(u32Pclk1/1024ul/1000);
    TIMER0_BaseInit(M4_TMR01, Tim0_ChannelB, &stcTimerCfg);

    stc_irq_regi_conf_t stcIrqRegiConf;

    MEM_ZERO_STRUCT(stcIrqRegiConf);

    /* Register TMR_INI_GCMB Int to Vect.No.002 */
    stcIrqRegiConf.enIRQn = IRQ_INDEX_INT_TMR01_GCMB;
    /* Select I2C Error or Event interrupt function */
    stcIrqRegiConf.enIntSrc = INT_TMR01_GCMB;
    /* Callback function */
    stcIrqRegiConf.pfnCallback = &Timer01B_CallBack;
    /* Registration IRQ */
    enIrqRegistration(&stcIrqRegiConf);
    /* Clear Pending */
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    /* Set priority */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_15);
    /* Enable NVIC */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

    TIMER0_IntCmd(M4_TMR01, Tim0_ChannelB, Enable);

//    TIMER0_Cmd(M4_TMR01, Tim0_ChannelB, Enable);
}

static void Timer01A_CallBack(void)
{
//    mySerial.handleInterrupt();
//    SWSerial->handleInterrupt();
    SoftwareSerial::handleInterrupt();
}

void timer01A_init(void)
{
    stc_clk_freq_t stcClkTmp;

    stc_tim0_base_init_t stcTimerCfg;

    MEM_ZERO_STRUCT(stcTimerCfg);

    PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIM01, Enable);
 
// Get pclk1
    CLK_GetClockFreq(&stcClkTmp);
    //uint32_t  u32Pclk1 = stcClkTmp.pclk1Freq;

    stcTimerCfg.Tim0_CounterMode = Tim0_Sync;
    stcTimerCfg.Tim0_SyncClockSource = Tim0_Pclk1;
    stcTimerCfg.Tim0_ClockDivision = Tim0_ClkDiv0;
//   stcCntInit.u16Cycle = get_pclk1Freq() / (1 << stcCntInit.enClkDiv) * period;
    stcTimerCfg.Tim0_CmpValue = 290;
    TIMER0_BaseInit(M4_TMR01, Tim0_ChannelA, &stcTimerCfg);

    stc_irq_regi_conf_t stcIrqRegiConf;

    MEM_ZERO_STRUCT(stcIrqRegiConf);

    /* Register TMR_INI_GCMB Int to Vect.No.002 */
    stcIrqRegiConf.enIRQn = IRQ_INDEX_INT_TMR01_GCMA;
    /* Select I2C Error or Event interrupt function */
    stcIrqRegiConf.enIntSrc = INT_TMR01_GCMA;
    /* Callback function */
    stcIrqRegiConf.pfnCallback = &Timer01A_CallBack;
    /* Registration IRQ */
    enIrqRegistration(&stcIrqRegiConf);
    /* Clear Pending */
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    /* Set priority */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_15);
    /* Enable NVIC */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

    TIMER0_IntCmd(M4_TMR01, Tim0_ChannelA, Enable);

    TIMER0_Cmd(M4_TMR01, Tim0_ChannelA, Disable);
}

