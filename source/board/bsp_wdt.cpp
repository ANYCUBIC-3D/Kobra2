#include "bsp_wdt.h"


// pclk = system_clock/div4 = 50M
// max cycle = 65536
// max feed interval = 65536 / (50000000/8192) = 2.68s
void bsp_wdt_init(void)
{
    stc_wdt_init_t stcWdtInit;

    /* configure structure initialization */
    MEM_ZERO_STRUCT(stcWdtInit);

    stcWdtInit.enClkDiv = WdtPclk3Div2048;
    stcWdtInit.enCountCycle = WdtCountCycle65536;
    stcWdtInit.enRefreshRange = WdtRefresh100Pct;
    stcWdtInit.enSleepModeCountEn = Disable;
    stcWdtInit.enRequestType = WdtTriggerResetRequest;
    WDT_Init(&stcWdtInit);
    /* First refresh to start WDT */
    WDT_RefreshCounter();
    /* Wait for WDT module to complete initial load */
     Ddl_Delay1ms(200u);
}

void bsp_wdt_refresh(void)
{
    WDT_RefreshCounter();
}

