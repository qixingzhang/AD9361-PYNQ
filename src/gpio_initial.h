#include "parameters.h"
#include "platform.h"
void gpio_initial(){
gpio_direction(CDCM_SYNC      ,1);
gpio_direction(RF1_TXNRX      ,1);
gpio_direction(SYNC_IN        ,1);
gpio_direction(RF1_EN_AGC     ,1);
gpio_direction(REF_SELECT2    ,1);
gpio_direction(REF_SELECT     ,1);
gpio_direction(FDD_TDD_SEL    ,1);
gpio_direction(TRX_SW         ,1);
gpio_direction(RF1_ENABLE     ,1);
gpio_direction(RF1_RESETB     ,1);
mdelay(100);
gpio_set_value(RF1_RESETB     ,0);
gpio_set_value(RF1_ENABLE     ,1);
gpio_set_value(TRX_SW         ,1);
gpio_set_value(FDD_TDD_SEL    ,1);
gpio_set_value(REF_SELECT     ,1);
gpio_set_value(REF_SELECT2    ,0);
gpio_set_value(RF1_EN_AGC     ,0);
gpio_set_value(SYNC_IN        ,1);
gpio_set_value(RF1_TXNRX      ,1);
gpio_set_value(CDCM_SYNC      ,0);
}
