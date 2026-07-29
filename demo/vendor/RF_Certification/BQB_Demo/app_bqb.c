/********************************************************************************************************
 * @file    app_bqb.c
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
#include "bqb.h"

bqb_setting_t g_bqb_setting = {
    .access_code = ACCESS_CODE,
    .baud_rate   = BQB_UART_BAUD,
    .uart_tx     = BQB_UART_TX_PORT,
    .uart_rx     = BQB_UART_RX_PORT,
#ifdef RF_CERTIFICATION_CGF_EN
    .pa_addr = 0,
#endif
    .cal_pos              = SWITCH_CALI_POSITION,
    .power_mode           = SWITCH_POWER_MODE,
    .io_voltage           = SWITCH_GPIO_VOLTAGE,
    .power                = BQB_TX_POWER,
    .voltage_type         = BQB_VOLTAGE_TYPE,
    .cap                  = SWITCH_INTERNAL_CAP,
    .swire_through_usb_en = SWIRE_THROUGH_USB_ENABLE,
    .pa_en                = PA_FUNCTION_ENABLE,
    .pa_bypass_en         = PA_BYPASS_ENABLE,
    .power_slice_en       = POWER_SLICE_EN,

};

/**
 * @brief       This function serves to read the calibration value from flash.
 * @param[in]   none
 * @return      none
 * @note       Attention:For TL751X and TL7518 chips, this function call must be made after rf_rode_init
 */
void read_bqb_calibration(void)
{
    if (!g_bqb_setting.cap) {
        if (g_bqb_setting.cal_pos == 1) {
            //OTP:need to be added.
        } else {
#if defined(MCU_CORE_B91)
            user_read_flash_value_calib();
#elif defined(MCU_CORE_B92)
            calibration_func(g_bqb_setting.io_voltage);
#elif defined(MCU_CORE_TL322X)
#elif defined(MCU_CORE_TL753X)
            rf_update_internal_cap(0x1f);//TODO:need to be checked.
#else
            calibration_func();
#endif
        }
    }
    else{
        rf_turn_off_internal_cap();
    }
}


#if defined(MCU_CORE_B91)
uart_num_redef_e get_uart_num(uart_tx_pin_e tx_pin, uart_rx_pin_e rx_pin)
{
    uart_num_redef_e tx_flag = UART_NONE, rx_flag = UART_NONE;
    if (tx_pin == UART0_TX_PA3 || tx_pin == UART0_TX_PB2 || tx_pin == UART0_TX_PD2) {
        tx_flag = UART_NUM0;
    } else if (tx_pin == UART1_TX_PC6 || tx_pin == UART1_TX_PD6 || tx_pin == UART1_TX_PE0) {
        tx_flag = UART_NUM1;
    } else {
        return UART_NONE;
    }

    if (rx_pin == UART0_RX_PA4 || rx_pin == UART0_RX_PB3 || rx_pin == UART0_RX_PD3) {
        rx_flag = UART_NUM0;
    } else if (rx_pin == UART1_RX_PC7 || rx_pin == UART1_RX_PD7 || rx_pin == UART1_RX_PE2) {
        rx_flag = UART_NUM1;
    } else {
        return UART_NONE;
    }

    if (rx_flag == tx_flag) {
        return rx_flag;
    } else {
        return UART_NONE;
    }
}

uart_num_redef_e uart_setup(uart_tx_pin_e tx_pin, uart_rx_pin_e rx_pin, unsigned int baudrate, unsigned int pclk, uart_parity_e parity, uart_stop_bit_e stop_bit)
{
    unsigned short   div      = 0;
    unsigned char    bwpc     = 0;
    uart_num_redef_e uart_num = UART_NONE;
    uart_num                  = get_uart_num(tx_pin, rx_pin);
    if (uart_num == UART_NONE) {
        return UART_NONE;
    }
    uart_set_pin(tx_pin, rx_pin);
    uart_reset(uart_num);
    uart_cal_div_and_bwpc(baudrate, pclk, &div, &bwpc);
    uart_set_rx_timeout(uart_num, bwpc, 12, UART_BW_MUL1);
    uart_init(uart_num, div, bwpc, parity, stop_bit);

    return uart_num;
}
#elif defined(MCU_CORE_B92)
uart_num_redef_e uart_setup(gpio_func_pin_e tx_pin, gpio_func_pin_e rx_pin, unsigned int baudrate, unsigned int pclk, uart_parity_e parity, uart_stop_bit_e stop_bit)
{
    unsigned short   div      = 0;
    unsigned char    bwpc     = 0;
    uart_num_redef_e uart_num = UART_NUM0;
    uart_set_pin((uart_num_e)uart_num, tx_pin, rx_pin);
    uart_reset((uart_num_e)uart_num);
    uart_cal_div_and_bwpc(baudrate, pclk, &div, &bwpc);
    uart_set_rx_timeout((uart_num_e)uart_num, bwpc, 12, UART_BW_MUL1);
    uart_init((uart_num_e)uart_num, div, bwpc, parity, stop_bit);

    return uart_num;
}
#elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL751X) || defined(MCU_CORE_TL322X) || defined(MCU_CORE_TL323X) || defined(MCU_CORE_TL521X)|| defined(MCU_CORE_TL753X)
uart_num_redef_e uart_setup(gpio_func_pin_e tx_pin, gpio_func_pin_e rx_pin, unsigned int baudrate, unsigned int pclk, uart_parity_e parity, uart_stop_bit_e stop_bit)
{
    unsigned short   div      = 0;
    unsigned char    bwpc     = 0;
    uart_num_redef_e uart_num = UART_NUM0;
    uart_set_pin((uart_num_e)uart_num, tx_pin, rx_pin);
    uart_reset((uart_num_e)uart_num);
    uart_cal_div_and_bwpc(baudrate, pclk, &div, &bwpc);
    uart_set_rx_timeout_with_exp((uart_num_e)uart_num, bwpc, 12, UART_BW_MUL1, 0);
    uart_init((uart_num_e)uart_num, div, bwpc, parity, stop_bit);

    return uart_num;
}
#endif


void user_init(void)
{
#ifdef RF_CERTIFICATION_CGF_EN
    config_obj_init();
    bqb_config_data_t bqb_cfg_data;
    if (get_config_data(TLK_CONFIG_TYPE_BQB, (unsigned char *)&bqb_cfg_data, sizeof(bqb_cfg_data))) {
        g_bqb_setting.uart_tx = get_pin(bqb_cfg_data.uart_tx);
        g_bqb_setting.uart_rx = get_pin(bqb_cfg_data.uart_rx);

        g_bqb_setting.cap            = bqb_cfg_data.cap;
        g_bqb_setting.cal_pos        = bqb_cfg_data.cal_pos;
        g_bqb_setting.voltage_type   = bqb_cfg_data.voltage_type;
        g_bqb_setting.io_voltage     = bqb_cfg_data.io_voltage;
        g_bqb_setting.power_slice_en = bqb_cfg_data.power_slice_en & 0x01;

#if defined(MCU_CORE_TL751X)
        switch (bqb_cfg_data.power_mode) {
        case 0:
            g_bqb_setting.power_mode = 0x00; //TL751X:LDO_AVDD_LDO_DVDD
            break;
        case 1:
            g_bqb_setting.power_mode = 0x11; //TL751X:DCDC_AVDD_DCDC_DVDD_PEAK_CUR_400MA
            break;
        case 2:
            g_bqb_setting.power_mode = 0x33; //TL751X:DCDC_AVDD_DCDC_DVDD_PEAK_CUR_600MA
            break;
        case 3:
            g_bqb_setting.power_mode = 0x77; //TL751X:DCDC_AVDD_DCDC_DVDD_PEAK_CUR_800MA
            break;
        default:
            g_bqb_setting.power_mode = 0x00;
            break;
        }
#else
        switch (bqb_cfg_data.power_mode) {
        case 0:
            g_bqb_setting.power_mode = 0x00; //B91:LDO_1P4_LDO_1P8; B92:LDO_1P4_LDO_2P0; TL721X:LDO_0P94_LDO_1P8; TL321X:LDO_1P25_LDO_1P8
            break;
        case 1:
            g_bqb_setting.power_mode = 0x01; //B91:DCDC_1P4_LDO_1P8; B92:DCDC_1P4_LDO_2P0; TL721X:DCDC_0P94_LDO_1P8; TL321X:DCDC_1P25_LDO_1P8
            break;
        case 2:
            g_bqb_setting.power_mode = 0x03; //B91:DCDC_1P4_DCDC_1P8; B92:DCDC_1P4_DCDC_2P0; TL721X:DCDC_0P94_DCDC_1P8; TL321X:DCDC_1P25_DCDC_1P8
            break;
        default:
            g_bqb_setting.power_mode = 0x00;
            break;
        }
#endif

        if (g_bqb_setting.power_slice_en == 1) {
            if (g_bqb_setting.voltage_type == 1) {
                g_bqb_setting.power = (bqb_cfg_data.power_slice == 0) ? BQB_TX_POWER : (bqb_cfg_data.power_slice | BIT(7));
            } else {
                g_bqb_setting.power = (bqb_cfg_data.power_slice == 0) ? BQB_TX_POWER : bqb_cfg_data.power_slice;
            }

        } else {
            g_bqb_setting.power = (bqb_cfg_data.power_index == 0) ? BQB_TX_POWER : rf_power_Level_list[bqb_cfg_data.power_index - 1];
        }
        g_bqb_setting.swire_through_usb_en = bqb_cfg_data.swire_through_usb_en;
        g_bqb_setting.pa_en                = bqb_cfg_data.pa_en;
        g_bqb_setting.access_code          = bqb_cfg_data.access_code;
        g_bqb_setting.baud_rate            = bqb_cfg_data.baud_rate;
    }
#endif
#if defined(MCU_CORE_B91)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, g_bqb_setting.cap, 0);
#elif defined(MCU_CORE_B92)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, g_bqb_setting.io_voltage, g_bqb_setting.cap, 0);
#elif defined(MCU_CORE_TL721X)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, g_bqb_setting.cap, 0);
#elif defined(MCU_CORE_TL321X)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, g_bqb_setting.cap, 0);
#elif defined(MCU_CORE_TL751X)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, 0);
#elif defined(MCU_CORE_TL322X)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, g_bqb_setting.cap, 0);
#elif defined(MCU_CORE_TL323X)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, g_bqb_setting.cap, 0);
#elif defined(MCU_CORE_TL521X)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, g_bqb_setting.cap, 0);
#elif defined(MCU_CORE_TL753X)
    platform_init(g_bqb_setting.power_mode, VBAT_MAX_VALUE_GREATER_THAN_3V6, 0);
#endif

    CLOCK_INIT;
#if(defined(MCU_CORE_TL751X))||(defined(MCU_CORE_TL322X)||(defined(MCU_CORE_TL753X)))
    //TL751X and tl322x chip rf module power-up method and digital module power-up method need to call the following interface realization
    #if(defined(MCU_CORE_TL751X))||(defined(MCU_CORE_TL753X))
    sys_n22_init(0x20080000);
    #endif
    rf_n22_dig_init();
    rf_clr_irq_mask(FLD_RF_IRQ_ALL);
#endif
#if (defined(MCU_CORE_TL322X))||(defined(MCU_CORE_TL753X))
    rf_modem_hp_path(1);
#endif
    read_bqb_calibration();

    if (g_bqb_setting.swire_through_usb_en) {
#if defined(MCU_CORE_TL322X)
        //The swire through USB function requires the use of internal USB1, which is currently not available
#else

#if defined(MCU_CORE_TL751X)
        usbhw_init();
#endif
#if (defined(MCU_CORE_TL323X))||(defined(MCU_CORE_TL521X))||(defined(MCU_CORE_TL753X))

#else
        usb_set_pin(1);
#endif
#endif
    }

#if defined(MCU_CORE_B91)
    uart_tx_pin_e bqb_uart_tx_port = g_bqb_setting.uart_tx;
    uart_rx_pin_e bqb_uart_rx_port = g_bqb_setting.uart_rx;
#elif defined(MCU_CORE_B92)|| defined(MCU_CORE_TL721X)|| defined(MCU_CORE_TL321X)|| defined(MCU_CORE_TL751X)|| defined(MCU_CORE_TL322X)|| defined(MCU_CORE_TL323X)|| defined(MCU_CORE_TL521X)|| defined(MCU_CORE_TL753X)
    gpio_func_pin_e bqb_uart_tx_port = g_bqb_setting.uart_tx;
    gpio_func_pin_e bqb_uart_rx_port = g_bqb_setting.uart_rx;
#endif


    uart_using = uart_setup(bqb_uart_tx_port, bqb_uart_rx_port, g_bqb_setting.baud_rate, sys_clk.pclk * 1000 * 1000, UART_PARITY_NONE, UART_STOP_BIT_ONE);
    uart_set_irq_mask((uart_num_e)uart_using, UART_RX_IRQ_MASK);
    uart_clr_irq_mask((uart_num_e)uart_using, UART_TX_IRQ_MASK);
    uart_rx_irq_trig_level((uart_num_e)uart_using, 1);
    bqb_pa_init();
    bqbtest_init();
}

void main_loop(void)
{
    bqb_serviceloop();
}
