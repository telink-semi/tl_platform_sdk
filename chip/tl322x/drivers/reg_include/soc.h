/********************************************************************************************************
 * @file    soc.h
 *
 * @brief   This is the header file for tl322x
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#pragma once

#include "bit.h"

/*Attention: for all the 2-byte address operation (like REG_ADDR16,write_reg16,read_reg16) ,
 *           the address parameter should  be multiple of 2. For example:REG_ADDR16(0x2),REG_ADDR16(0x4).
 *
 *           for all the 4-byte address operation (like REG_ADDR32,write_reg32,read_reg32) ,
 *           the address parameter should  be multiple of 4. For example:write_reg32(0x4),write_reg32(0x8).
*/
#define FLASH_R_BASE_ADDR     0x20000000
#define REG_RW_BASE_ADDR      0x80000000

#define REG_ADDR8(a)          (*(volatile unsigned char *)(REG_RW_BASE_ADDR | (a)))
#define REG_ADDR16(a)         (*(volatile unsigned short *)(REG_RW_BASE_ADDR | (a)))
#define REG_ADDR32(a)         (*(volatile unsigned long *)(REG_RW_BASE_ADDR | (a)))

#define write_reg8(addr, v)   (*(volatile unsigned char *)(REG_RW_BASE_ADDR | (addr)) = (unsigned char)(v))
#define write_reg16(addr, v)  (*(volatile unsigned short *)(REG_RW_BASE_ADDR | (addr)) = (unsigned short)(v))
#define write_reg32(addr, v)  (*(volatile unsigned long *)(REG_RW_BASE_ADDR | (addr)) = (unsigned long)(v))

#define read_reg8(addr)       (*(volatile unsigned char *)(REG_RW_BASE_ADDR | (addr)))
#define read_reg16(addr)      (*(volatile unsigned short *)(REG_RW_BASE_ADDR | (addr)))
#define read_reg32(addr)      (*(volatile unsigned long *)(REG_RW_BASE_ADDR | (addr)))

#define write_sram8(addr, v)  (*(volatile unsigned char *)((addr)) = (unsigned char)(v))
#define write_sram16(addr, v) (*(volatile unsigned short *)((addr)) = (unsigned short)(v))
#define write_sram32(addr, v) (*(volatile unsigned long *)((addr)) = (unsigned long)(v))

#define read_sram8(addr)      (*(volatile unsigned char *)((addr)))
#define read_sram16(addr)     (*(volatile unsigned short *)((addr)))
#define read_sram32(addr)     (*(volatile unsigned long *)((addr)))

#define ILM_BASE              (0x00000)
#define DLM_BASE              (0x80000)

#define SC_BASE_ADDR          0x140800


#define reg_mspi_mode         REG_ADDR8(SC_BASE_ADDR)

enum
{
    FLD_MSPI_MOD        = BIT_RNG(0, 3),
    FLD_MSPI_DIV_IN_SEL = BIT_RNG(4, 5),
};

#define reg_lspi_clk_set REG_ADDR8(SC_BASE_ADDR + 0x01)

enum
{
    FLD_LSPI_CLK_MOD    = BIT_RNG(0, 3),
    FLD_LSPI_DIV_IN_SEL = BIT_RNG(4, 5), //0:rc24m   1:xtl 24m  2:pll
};

#define reg_gspi_clk_set REG_ADDR16(SC_BASE_ADDR + 0x2)

enum
{
    FLD_GSPI_CLK_MOD    = BIT_RNG(0, 7),
    FLD_GSPI_DIV_IN_SEL = BIT_RNG(8, 9), //0:rc24m;   1:xtl24m;  2:pll;
};

#define reg_i3c0_clk_set REG_ADDR8(SC_BASE_ADDR + 0x04)

enum
{
    FLD_I3C0_CLK_MOD    = BIT_RNG(0, 3),
    FLD_I3C0_DIV_IN_SEL = BIT_RNG(4, 5), //0:rc24m   1:xtl 24m  2:pll
};

#define reg_i3c1_clk_set REG_ADDR8(SC_BASE_ADDR + 0x05)

enum
{
    FLD_I3C1_CLK_MOD    = BIT_RNG(0, 3),
    FLD_I3C1_DIV_IN_SEL = BIT_RNG(4, 5), //0:rc24m   1:xtl 24m  2:pll
};

#define reg_i2s0_step REG_ADDR16(SC_BASE_ADDR + 0x06)

enum
{
    FLD_I2S0_STEP = BIT_RNG(0, 14),
    FLD_I2S0_EN   = BIT(15),
};

#define reg_i2s2_step REG_ADDR16(SC_BASE_ADDR + 0x08)

enum
{
    FLD_I2S2_STEP = BIT_RNG(0, 14),
    FLD_I2S2_EN   = BIT(15),
};

#define reg_i2s2_mod      REG_ADDR16(SC_BASE_ADDR + 0x0a)
#define reg_i2s0_mod      REG_ADDR16(SC_BASE_ADDR + 0x2a)


#define reg_d25f_sram_cfg REG_ADDR8(SC_BASE_ADDR + 0x0c)

enum
{
    FLD_D25F_DLM_SIZE = BIT_RNG(0, 5),
};

#define reg_n22_sram_cfg REG_ADDR8(SC_BASE_ADDR + 0x0d)

enum
{
    FLD_N22_DLM_SIZE = BIT_RNG(0, 3),
    FLD_N22_RAM_SIZE = BIT_RNG(4, 7),
};

#define reg_cache_init REG_ADDR8(SC_BASE_ADDR + 0x10)

enum
{
    FLD_CACHE_I_DISABLE_INIT = BIT(6),
    FLD_CACHE_D_DISABLE_INIT = BIT(7),
};

#define reg_clkks_mode REG_ADDR8(SC_BASE_ADDR + 0x11)

enum
{
    FLD_CLKKEYS_MOD        = BIT_RNG(0, 4),
    FLD_CLKKEYS_DIV_IN_SEL = BIT_RNG(5, 6),
};

#define reg_mcu_ctrl  REG_ADDR32(SC_BASE_ADDR + 0x14)
#define reg_mcu_ctrl0 REG_ADDR8(SC_BASE_ADDR + 0x14)

enum
{
    FLD_MCU_REBOOT = BIT(7),
};

#define reg_mcu_reset_vector_r1 REG_ADDR8(SC_BASE_ADDR + 0x15)
#define reg_mcu_reset_vector_r2 REG_ADDR8(SC_BASE_ADDR + 0x16)
#define reg_mcu_reset_vector_r3 REG_ADDR8(SC_BASE_ADDR + 0x17)


#define reg_busclk_ratio        REG_ADDR8(SC_BASE_ADDR + 0x18)

enum
{
    FLD_BUSCLK_RATIO = BIT_RNG(0, 2),
};

#define reg_probe_clk_sel REG_ADDR8(SC_BASE_ADDR + 0x1a)

enum
{
    FLD_PROBE_CLK_SEL = BIT_RNG(0, 5),
};

#define reg_adcdig_clk_set(num) REG_ADDR8(SC_BASE_ADDR + (((num) == 0) ? 0x1b : 0x66))

enum
{
    FLD_ADCDIG_CLK_MOD    = BIT_RNG(0, 3),
    FLD_ADCDIG_DIV_IN_SEL = BIT_RNG(4, 5), //0:rc24m   1:xtl 24m  2:pll
};

#define reg_rst  REG_ADDR32(SC_BASE_ADDR + 0x20)

#define reg_rst0 REG_ADDR8(SC_BASE_ADDR + 0x20)

enum
{
    FLD_RST0_LSPI      = BIT(0),
    FLD_RST0_I2C       = BIT(1),
    FLD_RST0_UART0     = BIT(2),
    FLD_RST0_USB       = BIT(3),
    FLD_RST0_PWM       = BIT(4),
    FLD_RST0_TIMER_N22 = BIT(5),
    FLD_RST0_UART1     = BIT(6),
    FLD_RST0_SWIRE     = BIT(7),
};

#define reg_rst1 REG_ADDR8(SC_BASE_ADDR + 0x21)

enum
{
    FLD_RST1_UART3      = BIT(0),
    FLD_RST1_SYS_STIMER = BIT(1),
    FLD_RST1_DMA        = BIT(2),
    FLD_RST1_ALGM       = BIT(3),
    FLD_RST1_PKE        = BIT(4),
    /* RSVD */
    FLD_RST1_GSPI   = BIT(6),
    FLD_RST1_SPISLV = BIT(7),
};

#define reg_rst2 REG_ADDR8(SC_BASE_ADDR + 0x22)

enum
{
    FLD_RST2_TIMER           = BIT(0),
    FLD_RST2_AUDIO           = BIT(1),
    FLD_RST2_I2C1            = BIT(2),
    FLD_RST2_REST_MCU_DIS    = BIT(3),
    FLD_RST2_MCU_REST_ENABLE = BIT(4),
    FLD_RST2_LM              = BIT(5),
    FLD_RST2_TRNG            = BIT(6),
};

#define reg_rst3 REG_ADDR8(SC_BASE_ADDR + 0x23)
enum
{
    FLD_RST3_QDEC1 = BIT(0),
    FLD_RST3_TRACE = BIT(1),
    FLD_RST3_BROM  = BIT(2),
    /* RSVD */
    FLD_RST3_MSPI   = BIT(4),
    FLD_RST3_QDEC   = BIT(5),
    FLD_RST3_SARADC = BIT(6),
    FLD_RST3_ALG    = BIT(7),
};

#define reg_clk_en  REG_ADDR32(SC_BASE_ADDR + 0x24)

#define reg_clk_en0 REG_ADDR8(SC_BASE_ADDR + 0x24)

enum
{
    FLD_CLK0_LSPI_EN  = BIT(0),
    FLD_CLK0_I2C_EN   = BIT(1),
    FLD_CLK0_UART0_EN = BIT(2),
    FLD_CLK0_USB_EN   = BIT(3),
    FLD_CLK0_PWM_EN   = BIT(4),

    FLD_CLK0_UART1_EN = BIT(6),
    FLD_CLK0_SWIRE_EN = BIT(7),
};

#define reg_clk_en1 REG_ADDR8(SC_BASE_ADDR + 0x25)

enum
{
    FLD_CLK1_UART3_EN      = BIT(0),
    FLD_CLK1_SYS_STIMER_EN = BIT(1),
    FLD_CLK1_DMA_EN        = BIT(2),
    FLD_CLK1_ALGM_EN       = BIT(3),
    FLD_CLK1_PKE_EN        = BIT(4),
    FLD_CLK1_MACHINETIME   = BIT(5),
    FLD_CLK1_GSPI_EN       = BIT(6),
    FLD_CLK1_SPISLV_EN     = BIT(7),
};

#define reg_clk_en2 REG_ADDR8(SC_BASE_ADDR + 0x26)

enum
{
    FLD_CLK2_TIMER_EN = BIT(0),
    FLD_CLK2_AUDIO_EN = BIT(1),
    FLD_CLK2_I2C1_EN  = BIT(2),
    //RSVD
    FLD_CLK2_MCU_EN  = BIT(4),
    FLD_CLK2_LM_EN   = BIT(5),
    FLD_CLK2_TRNG_EN = BIT(6),
};

#define reg_clk_en3 REG_ADDR8(SC_BASE_ADDR + 0x27)

enum
{
    FLD_CLK3_QDEC1_EN  = BIT(0),
    FLD_CLK3_TRACE_EN  = BIT(1),
    FLD_CLK3_BROM_EN   = BIT(2),
    FLD_CLK3_EFUSE     = BIT(3),
    FLD_CLK3_MSPI_EN   = BIT(4),
    FLD_CLK3_QDEC_EN   = BIT(5),
    FLD_CLK3_SARADC_EN = BIT(6),
    /* RSVD */
};

#define reg_cclk_sel REG_ADDR8(SC_BASE_ADDR + 0x28)

enum
{
    FLD_CLK_SCLK_DIV = BIT_RNG(0, 3),
    FLD_CLK_SCLK_SEL = BIT_RNG(4, 5),
};

#define reg_dmic_step REG_ADDR16(SC_BASE_ADDR + 0x2c)

enum
{
    FLD_DMIC_STEP = BIT_RNG(0, 14),
    FLD_DMIC_SEL  = BIT(15),
};

#define reg_wakeup_en REG_ADDR8(SC_BASE_ADDR + 0x2e)

enum
{
    FLD_USB_PWDN_I     = BIT(0),
    FLD_GPIO_WAKEUP_I  = BIT(1),
    FLD_QDEC_RESUME    = BIT(2),
    FLD_KS_WAKEUP_I    = BIT(3),
    FLD_QDEC1_WAKEUP_I = BIT(4),
    FLD_USB_RESUME     = BIT(6),
    FLD_STANDBY_EX     = BIT(7),
};

#define reg_pwdn_en REG_ADDR8(SC_BASE_ADDR + 0x2f)

enum
{
    FLD_SUSPEND_EN_O     = BIT(0),
    FLD_RAMCRC_CLREN_TGL = BIT(4),
    FLD_RST_ALL          = BIT(5),
    FLD_STALL_EN_TRG     = BIT(7),
};

#define reg_clk_div REG_ADDR8(SC_BASE_ADDR + 0x30)

enum
{
    FLD_S7816_MOD    = BIT_RNG(4, 6),
    FLD_S7816_CLK_EN = BIT(7),
};

#define reg_rram_div REG_ADDR8(SC_BASE_ADDR + 0x31)

enum
{
    FLD_RRAM_DIV = BIT_RNG(0, 3),
};

#define reg_ram_crc REG_ADDR8(SC_BASE_ADDR + 0x32)

enum
{
    FLD_RAM_CRC_ERR          = BIT(1),
    FLD_RST_ALL_STATUS       = BIT(4),
    FLD_WATCH_DOG_RST_STATUS = BIT(5),
    FLD_RST_MCU_STATUS       = BIT(6),
};

#define reg_sel_jtag REG_ADDR8(SC_BASE_ADDR + 0x33)

enum
{
    FLD_JTAG_SEL = BIT(0),
};

#define reg_dmic_mod   REG_ADDR16(SC_BASE_ADDR + 0x36)

#define reg_rram_ctrl0 REG_ADDR8(SC_BASE_ADDR + 0x38)

enum
{
    FLD_REG_EN_IO_RRAM = BIT(0),
};

#define reg_usb_div REG_ADDR8(SC_BASE_ADDR + 0x3b)

enum
{
    FLD_USB_DIV = BIT_RNG(0, 2),
};

#define reg_rst_1      REG_ADDR32(SC_BASE_ADDR + 0x40)
#define reg_rst4       REG_ADDR8(SC_BASE_ADDR + 0x40)

enum
{
    FLD_RST4_DC        = BIT(0),
    FLD_RST4_UART4     = BIT(2),
    FLD_RST4_SKE       = BIT(4),
    FLD_RST4_HASH      = BIT(5),
    /* RSVD */
    FLD_RST4_ZB        = BIT(7),
};

#define reg_rst5 REG_ADDR8(SC_BASE_ADDR + 0x41)

enum
{
    FLD_RST5_UART2 = BIT(1),
    /* RSVD */
    FLD_RST5_MAILBOX  = BIT(3),
    FLD_RST5_IR_LEARN = BIT(4),
    FLD_RST5_KEY_SCAN = BIT(5),
    FLD_RST5_PEM      = BIT(6),
    FLD_RST5_SAR1ADC  = BIT(7),
};

#define reg_rst6 REG_ADDR8(SC_BASE_ADDR + 0x42)

enum
{
    FLD_RST6_RZ    = BIT(0),
    FLD_RST6_GSPI1 = BIT(1),
    FLD_RST6_GSPI2 = BIT(2),
    FLD_RST6_GSPI3 = BIT(3),
    FLD_RST6_GSPI4 = BIT(4),
    FLD_RST6_LIN0  = BIT(5),
    FLD_RST6_LIN1  = BIT(6),
    FLD_RST6_RRAM  = BIT(7),
};

#define reg_rst7 REG_ADDR8(SC_BASE_ADDR + 0x43)

enum
{
    FLD_RST7_USB1 = BIT(0),
    FLD_RST7_CAN0 = BIT(1),
    FLD_RST7_CAN1 = BIT(2),
    FLD_RST7_I3C0 = BIT(3),
    FLD_RST7_I3C1 = BIT(4),
    FLD_RST7_N22  = BIT(5),
    FLD_RST7_DMA1 = BIT(7),
};

#define reg_clk_en_1 REG_ADDR32(SC_BASE_ADDR + 0x44)
#define reg_clk_en4  REG_ADDR8(SC_BASE_ADDR + 0x44)

enum
{
    FLD_CLK4_DC_EN    = BIT(0),
    FLD_CLK4_UART4_EN = BIT(2),
    FLD_CLK4_SKE_EN   = BIT(4),
    FLD_CLK4_HASH_EN  = BIT(5),
    FLD_CLK4_CCLK_EN  = BIT(6),
    FLD_CLK4_ZB_EN    = BIT(7),
};

#define reg_clk_en5 REG_ADDR8(SC_BASE_ADDR + 0x45)

enum
{
    //RSVD
    FLD_CLK5_UART2_EN = BIT(1),
    //RSVD
    FLD_CLK5_MAILBOX_EN  = BIT(3),
    FLD_CLK5_IR_LEARN_EN = BIT(4),
    FLD_CLK5_KEYSCAN_EN  = BIT(5),
    FLD_CLK5_PEM_EN      = BIT(6),
    FLD_CLK5_SARADC1_EN  = BIT(7),
};

#define reg_clk_en6 REG_ADDR8(SC_BASE_ADDR + 0x46)

enum
{
    FLD_CLK6_RZ_EN    = BIT(0),
    FLD_CLK6_GSPI1_EN = BIT(1),
    FLD_CLK6_GSPI2_EN = BIT(2),
    FLD_CLK6_GSPI3_EN = BIT(3),
    FLD_CLK6_GSPI4_EN = BIT(4),
    FLD_CLK6_LIN0_EN  = BIT(5),
    FLD_CLK6_LIN1_EN  = BIT(6),
    FLD_CLK6_RRAM_EN  = BIT(7),

};

#define reg_clk_en7 REG_ADDR8(SC_BASE_ADDR + 0x47)

enum
{
    FLD_CLK7_USB1_EN    = BIT(0),
    FLD_CLK7_CAN0_EN    = BIT(1),
    FLD_CLK7_CAN1_EN    = BIT(2),
    FLD_CLK7_I3C0_EN    = BIT(3),
    FLD_CLK7_I3C1_EN    = BIT(4),
    FLD_CLK7_N22_EN     = BIT(5),
    FLD_CLK7_N22PLMT_EN = BIT(6), //n22 mtimer clk en
    FLD_CLK7_DMA1_EN    = BIT(7),
};

#define reg_gspi1_clk_set REG_ADDR16(SC_BASE_ADDR + 0x48)

enum
{
    FLD_GSPI1_CLK_MOD    = BIT_RNG(0, 7),
    FLD_GSPI1_DIV_IN_SEL = BIT_RNG(8, 9), //0:rc24m;   1:xtl24m;  2:pll;
};

#define reg_gspi2_clk_set REG_ADDR16(SC_BASE_ADDR + 0x4a)

enum
{
    FLD_GSPI2_CLK_MOD    = BIT_RNG(0, 7),
    FLD_GSPI2_DIV_IN_SEL = BIT_RNG(8, 9), //0:rc24m;   1:xtl24m;  2:pll;
};

#define reg_gspi3_clk_set REG_ADDR16(SC_BASE_ADDR + 0x4c)

enum
{
    FLD_GSPI3_CLK_MOD    = BIT_RNG(0, 7),
    FLD_GSPI3_DIV_IN_SEL = BIT_RNG(8, 9), //0:rc24m;   1:xtl24m;  2:pll;
};

#define reg_gspi4_clk_set REG_ADDR16(SC_BASE_ADDR + 0x4e)

enum
{
    FLD_GSPI4_CLK_MOD    = BIT_RNG(0, 7),
    FLD_GSPI4_DIV_IN_SEL = BIT_RNG(8, 9),                         //0:rc24m;   1:xtl24m;  2:pll;
};

#define BOOT_IDCODE_ADDR     (SC_BASE_ADDR + 0x5c)

#define reg_boot_idcode(i)   REG_ADDR8(SC_BASE_ADDR + 0x5c + (i)) /* i[0-8] */

#define reg_dma_set_l        REG_ADDR32(SC_BASE_ADDR + 0x50)
#define reg_dma_set_h        REG_ADDR32(SC_BASE_ADDR + 0x54)


#define reg_adc1dig_clk_set  REG_ADDR8(SC_BASE_ADDR + 0x66)


#define reg_dma_set_index(i) REG_ADDR8(SC_BASE_ADDR + 0x50 + (i)) /* i[0-7] */

#define SRAM_INTF_CFG_0              (SC_BASE_ADDR + 0x68)
#define SRAM_INTF_CFG_1              (SC_BASE_ADDR + 0x69)

#define reg_sram_intf_cfg_0          REG_ADDR8(SC_BASE_ADDR + 0x68)
#define reg_sram_intf_cfg_1          REG_ADDR8(SC_BASE_ADDR + 0x69)
