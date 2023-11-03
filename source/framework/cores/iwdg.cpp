#include "iwdg.h"
#include "bsp_wdt.h"


void iwdg_init(void)
{
    bsp_wdt_init();
}

void iwdg_feed(void)
{
    bsp_wdt_refresh();
}

