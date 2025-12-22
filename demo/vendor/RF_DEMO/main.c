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

extern void user_init(void);
extern void main_loop(void);

/**
 * @brief       This is main function
 * @param[in]   none
 * @return      none
 */
int main(void)
{
#if ((defined(MCU_CORE_TL751X_N22)) || (defined(MCU_CORE_TL322X_N22)))
    rf_n22_dig_init();
    rf_clr_irq_mask(FLD_RF_IRQ_ALL);
#else
    PLATFORM_INIT;
    CLOCK_INIT;
#if(defined(MCU_CORE_TL751X))||(defined(MCU_CORE_TL322X))
    #if (defined(MCU_CORE_TL751X))
    sys_n22_init(0x20080000);
    #elif(defined(MCU_CORE_TL322X))
    pm_set_dig_module_power_switch(FLD_PD_ZB_EN,PM_POWER_UP);
    #endif
    rf_n22_dig_init();
    rf_clr_irq_mask(FLD_RF_IRQ_ALL);
#endif
#endif
    rf_mode_init();

#if (defined(MCU_CORE_TL322X))
#if RF_HIGH_PER_MODE
    rf_modem_hp_path(1);
#endif
#endif

#if (RF_MODE == RF_BLE_1M)         //1
    rf_set_ble_1M_mode();
#elif (RF_MODE == RF_BLE_1M_NO_PN) //2
    rf_set_ble_1M_NO_PN_mode();
#elif (RF_MODE == RF_BLE_2M)       //3
    rf_set_ble_2M_mode();
#elif (RF_MODE == RF_BLE_2M_NO_PN) //4
    rf_set_ble_2M_NO_PN_mode();
#elif (RF_MODE == RF_LR_S2_500K)   //5
    rf_set_ble_500K_mode();
#elif (RF_MODE == RF_LR_S8_125K)   //6
    rf_set_ble_125K_mode();
#elif (RF_MODE == RF_ZIGBEE_250K)  //TODO:TL7518 and tl751x are temporarily unavailable, available versions will be updated in the future
    rf_set_zigbee_250K_mode();
#elif (RF_MODE == RF_PRIVATE_1M)   //TODO:TL7518 and tl751x are temporarily unavailable, available versions will be updated in the future
    rf_set_pri_1M_mode();
#elif (RF_MODE == RF_PRIVATE_2M)   //TODO:TL7518 and tl751x are temporarily unavailable, available versions will be updated in the future
    rf_set_pri_2M_mode();
#elif (RF_MODE == RF_BLE_STX2RX)
    rf_set_ble_1M_mode();
#elif (RF_MODE == RF_BLE_SDK_TEST)
    rf_set_ble_1M_mode();
#endif

#if ((!defined(MCU_CORE_TL7518)) || (!defined(MCU_CORE_TL751X)))
    #if (RF_MODE == RF_PRIVATE_250K)
    rf_set_pri_250K_mode();
    #elif (RF_MODE == RF_PRIVATE_500K)
    rf_set_pri_500K_mode();
    #elif (RF_MODE == RF_HYBEE_500K)//TODO:TL322X Currently only validated in FPGA, not in chip; available after subsequent validation
    rf_set_hybee_500K_mode();
    #elif (RF_MODE == RF_HYBEE_1M)//TODO:TL322X Currently only validated in FPGA, not in chip; available after subsequent validation
    rf_set_hybee_1M_mode();
    #elif (RF_MODE == RF_HYBEE_2M)//TODO:TL322X Currently only validated in FPGA, not in chip; available after subsequent validation
    rf_set_hybee_2M_mode();
    #elif (RF_MODE == RF_ANT) //TODO:TL721X  Currently only validated in FPGA, not in chip; available after subsequent validation
    rf_set_ant_mode();
    #endif
#endif

#if defined(MCU_CORE_B92)
    #if (RF_MODE == RF_USER_DEFINE_PKT)
    rf_set_ble_1M_NO_PN_mode();
    #endif
#endif

#if defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X)
    #if (RF_MODE == RF_BLE_1M_HYPER_LENGTH)
    rf_set_ble_1M_mode();
    #endif
#endif

#if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    //TODO:TL721X,TL322X  Currently only validated in FPGA, not in chip; available after subsequent validation
    #if (RF_MODE == RF_PRI_GENERIC_1M)
    rf_set_pri_generic_1M_mode();
    #elif (RF_MODE == RF_PRI_GENERIC_2M)
    rf_set_pri_generic_2M_mode();
    #elif (RF_MODE == RF_PRI_GENERIC_250K)
    rf_set_pri_generic_250K_mode();
    #elif (RF_MODE == RF_PRI_GENERIC_500K)
    rf_set_pri_generic_500K_mode();
    //TODO:TL321X The above mode has been verified currently.
    #endif
#endif

#if defined(MCU_CORE_TL322X)
    #if (RF_MODE == RF_BLE_4M)
    rf_modem_rate_mode(RF_48M_MODEM_RATE);//When using 4 Mbps or 6 Mbps data rates, the 48 MHz modem rate must be applied.
    rf_set_ble_4M_mode();//TODO:TL322X Currently only validated in FPGA, not in chip; available after subsequent validation
    #elif (RF_MODE == RF_BLE_6M)
    rf_modem_rate_mode(RF_48M_MODEM_RATE);//When using 4 Mbps or 6 Mbps data rates, the 48 MHz modem rate must be applied.
    rf_set_ble_6M_mode();
    #elif (RF_MODE == RF_BLE_4M_NO_PN)
    rf_modem_rate_mode(RF_48M_MODEM_RATE);//When using 4 Mbps or 6 Mbps data rates, the 48 MHz modem rate must be applied.
    rf_set_ble_4M_NO_PN_mode();//TODO:TL322X Currently only validated in FPGA, not in chip; available after subsequent validation
    #elif (RF_MODE == RF_BLE_6M_NO_PN)
    rf_modem_rate_mode(RF_48M_MODEM_RATE);//When using 4 Mbps or 6 Mbps data rates, the 48 MHz modem rate must be applied.
    rf_set_ble_6M_NO_PN_mode();
    #endif
#endif

    user_init();

    while (1) {
        main_loop();
    }
    return 0;
}
