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
#include "tl_chip.h"

extern void user_init(void);
extern void main_loop(void);

#define RXADDR          0x50090000  // channel 1
#define TXADDR          0x50091000  // channel 0

unsigned char *ble_tx_packet1  = (unsigned char *)TXADDR;
unsigned char *rx_packet1      = (unsigned char *)RXADDR;

/**
 * @brief       This is main function
 * @param[in]   none
 * @return      none
 */
int main(void)
{

#if !defined(MCU_CORE_TL752X_N22)
    PLATFORM_INIT;
    CLOCK_INIT;
    sys_n22_init(0x50000000);//The N22 related clock initialization must be completed  before initializing the RF module.
#endif
    rf_subsys_init(RF_BLE_MODE,RF_MODEM_24M);

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
#elif (RF_MODE == RF_PRIVATE_1M)
    rf_set_pri_1M_mode();
#elif (RF_MODE == RF_PRIVATE_2M)
    rf_set_pri_2M_mode();
#endif

#if ((!defined(MCU_CORE_TL7518)) || (!defined(MCU_CORE_TL751X)))
    #if (RF_MODE == RF_PRIVATE_250K)
    rf_set_pri_250K_mode();
    #elif (RF_MODE == RF_PRIVATE_500K)
    rf_set_pri_500K_mode();
    #elif (RF_MODE == RF_ANT) //TODO:TL721X  Currently only validated in FPGA, not in chip; available after subsequent validation
    rf_set_ant_mode();
    #endif
#endif

    user_init();

    while (1) {
        main_loop();
    }
    return 0;
}
