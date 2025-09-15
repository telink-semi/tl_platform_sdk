/********************************************************************************************************
 * @file    main.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#include "common.h"
#include "calibration.h"
#if (TEST_DEMO == BQB_DEMO)
    #include "BQB/bqb.h"
#endif


#if TEST_DEMO == EMI_DEMO && EMI_SUPPORT_SETTING
extern void          emi_setting_init(void);
extern emi_setting_t g_emi_setting;
#endif

extern void user_init(void);
extern void main_loop(void);
#if ((TEST_DEMO == BQB_DEMO) && (SUPPORT_CONFIGURATION))
extern void rd_usr_definition(unsigned char _s);
#endif

#if ((TEST_DEMO == EMI_DEMO) && (!EMI_SUPPORT_SETTING))
    #define POWER_MODE_LDO      0
    #define POWER_MODE_DCDC     1
    #define POWER_MODE_DCDC_LDO 2

    /**
 * @brief        This is macro used to set the initialize power mode.
 */
    #define POWER_MODE_SELECT POWER_MODE_LDO
#endif

#if defined(MCU_CORE_B91)
    //#define PLATFORM_INIT_DCDC         platform_init(DCDC_1P4_DCDC_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6,1)  //Because DCDC mode has been deleted, it is temporarily unavailable here.
    #define PLATFORM_INIT_LDO      platform_init(LDO_1P4_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M, 0)
    #define PLATFORM_INIT_DCDC_LDO platform_init(DCDC_1P4_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M, 0)
#elif defined(MCU_CORE_B92)
    #define PLATFORM_INIT_DCDC     platform_init(DCDC_1P4_DCDC_2P0, VBAT_MAX_VALUE_GREATER_THAN_3V6, GPIO_VOLTAGE_3V3, INTERNAL_CAP_XTAL24M, 0);
    #define PLATFORM_INIT_LDO      platform_init(LDO_1P4_LDO_2P0, VBAT_MAX_VALUE_GREATER_THAN_3V6, GPIO_VOLTAGE_3V3, INTERNAL_CAP_XTAL24M, 0);
    #define PLATFORM_INIT_DCDC_LDO platform_init(DCDC_1P4_LDO_2P0, VBAT_MAX_VALUE_GREATER_THAN_3V6, GPIO_VOLTAGE_3V3, INTERNAL_CAP_XTAL24M, 0);
#elif defined(MCU_CORE_TL721X)
    #define PLATFORM_INIT_DCDC     platform_init(DCDC_0P94_DCDC_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M, 0)
    #define PLATFORM_INIT_LDO      platform_init(LDO_0P94_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M, 0)
    #define PLATFORM_INIT_DCDC_LDO platform_init(DCDC_0P94_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M, 0)
#elif defined(MCU_CORE_TL321X)
    #define PLATFORM_INIT_LDO      platform_init(LDO_1P25_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M, 0)
    #define PLATFORM_INIT_DCDC_LDO platform_init(DCDC_1P25_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M, 0)
#elif defined(MCU_CORE_TL751X)
    #define PLATFORM_INIT_DCDC     platform_init(DCDC_AVDD_DCDC_DVDD_PEAK_CUR_800MA, VBAT_MAX_VALUE_GREATER_THAN_3V6,0)
    #define PLATFORM_INIT_LDO      platform_init(LDO_AVDD_LDO_DVDD, VBAT_MAX_VALUE_GREATER_THAN_3V6,0)
#elif defined(MCU_CORE_TL322X)
    #define PLATFORM_INIT_LDO      platform_init(LDO_1P25_LDO_1P8,VBAT_MAX_VALUE_GREATER_THAN_3V6,INTERNAL_CAP_XTAL24M,0)
    #define PLATFORM_INIT_DCDC_LDO platform_init(DCDC_1P25_LDO_1P8,VBAT_MAX_VALUE_GREATER_THAN_3V6,INTERNAL_CAP_XTAL24M,0)
#endif


/**
 * @brief       This is main function
 * @param[in]   none
 * @return      none
 */
int main(void)
{
#if (TEST_DEMO == BQB_DEMO)

    #if (SUPPORT_CONFIGURATION)
    rd_usr_definition(1);
    if (usr_config.power_mode == 0) {
        PLATFORM_INIT_LDO;
    } else if (usr_config.power_mode == 1) {
        PLATFORM_INIT_DCDC_LDO;
    } else {
        PLATFORM_INIT_DCDC;
    }
    #else

        #if (SWITCH_POWER_MODE)
    PLATFORM_INIT_LDO;
        #else
    PLATFORM_INIT_DCDC;
        #endif
    #endif

#else //TEST_DEMO==EMI_DEMO

    #if (EMI_SUPPORT_SETTING)
    emi_setting_init();
    if (g_emi_setting.general_setting.power_mode == 1) {
        PLATFORM_INIT_DCDC_LDO;
    } else if (g_emi_setting.general_setting.power_mode == 2) {
        #if (!defined(MCU_CORE_B91))
        {
            PLATFORM_INIT_DCDC;
        }
        #else
        {
            PLATFORM_INIT_DCDC_LDO;
        }
        #endif
    } else {
        PLATFORM_INIT_LDO;
    }
    #else
        #if POWER_MODE_SELECT == POWER_MODE_LDO
    PLATFORM_INIT_LDO;
        #elif POWER_MODE_SELECT == POWER_MODE_DCDC
    PLATFORM_INIT_DCDC;
        #elif POWER_MODE_SELECT == POWER_MODE_DCDC_LDO
    PLATFORM_INIT_DCDC_LDO;
        #endif
    #endif

#endif

    CLOCK_INIT;

#if(defined(MCU_CORE_TL751X))||(defined(MCU_CORE_TL322X))
    //TL751X and tl322x chip rf module power-up method and digital module power-up method need to call the following interface realization
    sys_n22_init(0x20080000);
    rf_n22_dig_init();
    rf_clr_irq_mask(FLD_RF_IRQ_ALL);
    rf_mode_init();
#endif

    user_init();
    while (1) {
        main_loop();
    }
    return 0;
}
