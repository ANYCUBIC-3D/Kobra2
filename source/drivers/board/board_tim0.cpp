#include "startup.h"
#include "../STM32/timers.h"
#include "../module/temperature.h"
#include "../module/stepper.h"


/***********************************************************************************/
/***********************************************************************************/
static void stepTC_Handler(void)
{  
	TIMER0_ClearFlag(TMR_UNIT,Tim0_ChannelB); 
	HAL_STEP_TIMER_ISR();
}
void setup_time2B(const uint32_t frequency)
{
	stc_tim0_base_init_t stcTimerCfg;
	stc_irq_regi_conf_t stcIrqRegiConf;
	uint32_t u32Pclk1;
	stc_clk_freq_t stcClkTmp;

	MEM_ZERO_STRUCT(stcTimerCfg);
	MEM_ZERO_STRUCT(stcIrqRegiConf);
	
	/*****************************************************************************/
	/* Get pclk1 */    
	CLK_GetClockFreq(&stcClkTmp);	
	u32Pclk1 = stcClkTmp.pclk1Freq;// 84MHZ
	
    	/* Timer0 peripheral enable */   
	PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIM02, Enable);
	
	/*config register for channel B */	  
	stcTimerCfg.Tim0_CounterMode = Tim0_Sync;    
	stcTimerCfg.Tim0_SyncClockSource = Tim0_Pclk1;	 
	stcTimerCfg.Tim0_ClockDivision = Tim0_ClkDiv32;	  
	stcTimerCfg.Tim0_CmpValue = (uint16_t)((u32Pclk1/STEPPER_TIMER_PRESCALE)/frequency);	
	TIMER0_BaseInit(TMR_UNIT,Tim0_ChannelB,&stcTimerCfg);	 
	/* Enable channel B interrupt */	 
	TIMER0_IntCmd(TMR_UNIT,Tim0_ChannelB,Enable);	 
	/* Register TMR_INI_GCMB Int to Vect.No.002 */	
	stcIrqRegiConf.enIRQn = IRQ_INDEX_INT_TMR02_GCMB;	
	/* Select I2C Error or Event interrupt function */	  
	stcIrqRegiConf.enIntSrc = TMR_INI_GCMB;	 
	/* Callback function */	
	stcIrqRegiConf.pfnCallback = &stepTC_Handler;    
	/* Registration IRQ */	 
	enIrqRegistration(&stcIrqRegiConf);	
	/* Clear Pending */    
	NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);   
	/* Set priority */	 
	NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_01);	  
	/* Enable NVIC */    
	NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);	 
	/*start timer0*/	 
	//TIMER0_Cmd(TMR_UNIT,Tim0_ChannelB,Enable);
}

static void tempTC_Handler(void)
{  
	TIMER0_ClearFlag(TMR_UNIT,Tim0_ChannelA);
        //Z_limit_query();
	HAL_TEMP_TIMER_ISR();
}
/***************************************************/
void setup_time2A(const uint32_t frequency)
{
	stc_tim0_base_init_t stcTimerCfg;
	stc_irq_regi_conf_t stcIrqRegiConf;
	uint32_t u32Pclk1;
	stc_clk_freq_t stcClkTmp;

	MEM_ZERO_STRUCT(stcTimerCfg);
	MEM_ZERO_STRUCT(stcIrqRegiConf);
	
	/*****************************************************************************/
	/* Get pclk1 */    
	CLK_GetClockFreq(&stcClkTmp);	
	u32Pclk1 = stcClkTmp.pclk1Freq;// 84MHZ

    	/* Timer0 peripheral enable */   
	PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIM02, Enable);

	/*config register for channel A */	  
	stcTimerCfg.Tim0_CounterMode = Tim0_Sync;    
	stcTimerCfg.Tim0_SyncClockSource = Tim0_Pclk1;	 
	stcTimerCfg.Tim0_ClockDivision = Tim0_ClkDiv16;	  
	stcTimerCfg.Tim0_CmpValue = (uint16_t)(((u32Pclk1/TEMP_TIMER_PRESCALE)/frequency)-1);	
	TIMER0_BaseInit(TMR_UNIT,Tim0_ChannelA,&stcTimerCfg);	 
	/* Enable channel A interrupt */	 
	TIMER0_IntCmd(TMR_UNIT,Tim0_ChannelA,Enable);	 
	/* Register TMR_INI_GCMA Int to Vect.No.002 */	
	stcIrqRegiConf.enIRQn = IRQ_INDEX_INT_TMR02_GCMA;	
	/* Select I2C Error or Event interrupt function */	  
	stcIrqRegiConf.enIntSrc = TMR_INI_GCMA;	 
	/* Callback function */	
	stcIrqRegiConf.pfnCallback = &tempTC_Handler;    
	/* Registration IRQ */	 
	enIrqRegistration(&stcIrqRegiConf);	
	/* Clear Pending */    
	NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);   
	/* Set priority */	 
	NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_02);	  
	/* Enable NVIC */    
	NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);	 
	/*start timer0*/	 
	//TIMER0_Cmd(TMR_UNIT,Tim0_ChannelA,Enable);    
}


extern en_result_t timer_preset_compare(en_tim0_channel_t enCh,const uint16_t compare){    
    TIMER0_WriteCmpReg(TMR_UNIT, enCh, compare);
    return(Ok);
}
extern en_result_t timer_set_compare(const uint8_t timer_num,const uint16_t compare){
    en_tim0_channel_t timer_channel; 
    timer_channel = (timer_num==STEP_TIMER_NUM)?Tim0_ChannelB:Tim0_ChannelA;
    return timer_preset_compare(timer_channel,compare);
}
extern uint16_t timer_get_count(const uint8_t timer_num){
    en_tim0_channel_t timer_channel; 
    timer_channel = (timer_num==STEP_TIMER_NUM)?Tim0_ChannelB:Tim0_ChannelA;
    return(TIMER0_GetCntReg(TMR_UNIT,timer_channel));
}
extern void timer_enable_irq(const uint8_t timer_num){
    en_tim0_channel_t timer_channel; 
    timer_channel = (timer_num==STEP_TIMER_NUM)?Tim0_ChannelB:Tim0_ChannelA;
    TIMER0_Cmd(TMR_UNIT,timer_channel,Enable);
}
extern void timer_disable_irq(const uint8_t timer_num){
    en_tim0_channel_t timer_channel; 
    timer_channel = (timer_num==STEP_TIMER_NUM)?Tim0_ChannelB:Tim0_ChannelA;
    TIMER0_Cmd(TMR_UNIT,timer_channel,Disable);
}
extern bool timer_irq_enabled(const uint8_t timer_num){
    switch (timer_num){
        case STEP_TIMER_NUM: return bool(TMR_UNIT->BCONR_f.CSTB);
        case TEMP_TIMER_NUM: return bool(TMR_UNIT->BCONR_f.CSTA);
    }
    return false;
}


