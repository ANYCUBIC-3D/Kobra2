#include "startup.h"


uint32_t F_CPU;

volatile uint32_t _millis = 0;

uint32_t millis()
{
    return _millis;
}

extern "C" void SysTick_IrqHandler(void)
{
    SysTick_IncTick();
    _millis++;
}

void setup_systick(void)
{   
	stc_clk_freq_t   stcClkFreq;
	MEM_ZERO_STRUCT(stcClkFreq);
	CLK_GetClockFreq(&stcClkFreq);
	SysTick_Config(stcClkFreq.sysclkFreq/ OS_TICKS_PER_SEC); 
}

void delay(uint32_t ms)
{
    volatile uint32_t i = 0ul;
    uint32_t u32Cyc = 0ul;

    u32Cyc = 168000000;//SystemCoreClock
    u32Cyc = u32Cyc / 7000ul;
    while (ms-- > 0ul)
    {
        yield();
        i = u32Cyc;
        while (i-- > 0ul)
        {
            ;
        }
    }
}

void delayMicroseconds(uint32_t us)
{
    Ddl_Delay1us(us);
}

static void __empty() {
	// Empty
}
void yield(void) __attribute__ ((weak, alias("__empty")));

