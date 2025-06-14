/********************************************************************************************************
 * @file    hal_nau8821.c
 *
 * @brief   This is the source file for TL7518/TL721X/TL321X
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
#include "hal_nau8821.h"
#include "hal_alsa.h"

#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_nau8821)
#define DAC_CHANNAL_2_EN 1
#define ADC_CHANNAL_2_EN 1

static const Alsa_Device Nau8821_Everest = {
    I2C_NAU8821_ADD,
};

tlkdrv_nau8821_config_t nau8821_sys_clk_config;

int nau8821_digital_mute(int mute, int direction)
{
    (void)direction;

    uint16_t val = 0;

    if (mute) {
        val = NAU8821_DAC_SOFT_MUTE;
    }

    regmap_write_nau8821(Nau8821_Everest.regmap, NAU8821_R31_MUTE_CTRL, val);
    return 0;
}

static void nau8821_reset_chip(void)
{
    regmap_write_nau8821(Nau8821_Everest.regmap, NAU8821_R00_RESET, 0xffff);
    regmap_write_nau8821(Nau8821_Everest.regmap, NAU8821_R00_RESET, 0xffff);
}

uint16_t table_REG[][2] = {
    {0x0000, 0x0000},
    //        {0x0001, 0x0FD6}, //demo config
    //        {0x0001, 0x0396}, //demo config ADC LR
    {0x0001, 0x0FD6}, //config ADC L

    {0x0003, 0x0450},

    ///FLL
    {0x0004, 0x1881},
    {0x0005, 0x00BC},
    {0x0006, 0x0820},
    {0x0007, 0x0010},
    {0x0008, 0x1000},
    {0x0009, 0x0000},
    {0x000A, 0x0000},
    {0x000B, 0x0000},

    ///JAck_det
    {0x000D, 0xC000},
    {0x000F, 0x0000},
    {0x0010, 0x0000},
    {0x0011, 0x0000},
    {0x0012, 0xFFFF},
    {0x0013, 0x0000},
    {0x001A, 0x0000},

    ///TDM
    {0x001B, 0x0000},

    ///I2S CTRL
    //If IIS needs to change the sampling rate and depth, it is necessary to modify the 1C/1D registers according to the datasheet
    {0x001C, 0x0002}, //0002--16bit 2channel///0x000A
    {0x001D, 0x2012},

    {0x001E, 0x2000},
    {0x001F, 0x0000},

    ///BIQ config
    {0x0021, 0x0000},
    {0x0022, 0x0000},
    {0x0023, 0x0000},
    {0x0024, 0x0000},
    {0x0025, 0x0000},
    {0x0026, 0x0000},
    {0x0027, 0x0000},
    {0x0028, 0x0000},
    {0x0029, 0x0000},
    {0x002A, 0x0000},

    {0x002B, 0x0002},
    {0x002C, 0x0082},
    {0x002D, 0x0000},
    {0x002F, 0x0000},
    {0x0030, 0x0000},
    {0x0031, 0x0000},
    {0x0032, 0x0000},
    //DAC_CTRL  setting yingliang
    {0x0034, 0xCFCF}, ///all on 0db
    {0x0035, 0xCFCF},

    ///DR ADC CTRL
    {0x0036, 0x1486},
    {0x0037, 0x0F12},
    {0x0038, 0x25FF},
    {0x0039, 0x3457},

    ///DR DAC CTRL
    {0x003A, 0x1406}, ///0x1486,        ///0x1406,
    {0x003B, 0x3712}, ///0x0f12,        ///0x3712,
    {0x003C, 0x31FF}, ///0x25f9,        ///0x31FF,
    {0x003D, 0x3450}, ///0x3457,        ///0x3450

    ///EQ Setting
    {0x0041, 0x0000},
    {0x0042, 0x0000},
    {0x0043, 0x0000},
    {0x0044, 0x0000},
    {0x0045, 0x0000},
    {0x0046, 0x0000},
    {0x0047, 0x0000},
    {0x0048, 0x0000},
    {0x0049, 0x0000},
    {0x004A, 0x0000},
    ///CLASS G setting threshold for DAC Signal= 1/16 FULL Scale
    {0x004B, 0x2007}, ///0x2037,    1/4
    ///test
    {0x004C, 0x0000},

    {0x004D, 0x0000},
    //only read DATA
    {0x0053, 0xB0E8},
    {0x0054, 0x0000},
    //ADC to DAC loop
    {0x0055, 0x0000},

    //IC ID+MIC_DET
    {0x0058, 0x1B23},
    {0x0059, 0x2000},

    //BIAS_ADJ VMID_EN 125K impedance
    {0x0066, 0x0060},

    ///ADC DAC GPIO TEST
    {0x0068, 0x0000},
    {0x0069, 0x0000},

    //HP ctrl
    {0x006A, 0x1003},

    //mute MIC
    {0x006B, 0x0000},

    ///ANALog_ADC
    //MIC Detection Power Down
    {0x0071, 0x0011},
    //ADC VREF =1.55 ADC ctrl en
    //        {0x0072, 0x0170},    //Demo
    {0x0072, 0x0170}, //ADC L en
    //DAC VREF =1.55 DAC ctrl en
    {0x0073, 0x3308}, //demo
    //        {0x0073, 0x1108},    //L

    //MIC_BIAS 1.4X
    {0x0074, 0x0505},
    //BOOST
    {0x0076, 0x3140}, ///DEMO
    //        {0x0076, 0x1040},    ///DEMO
    //FEPGA
    {0x0077, 0x0000},
    //PGA GAIN_LR
    {0x007E, 0x0101}, ///demo
    //        {0x007E, 0x0100},
    //POWER_UP
    {0x007F, 0xC03F}, ///DEMO setting
    //        {0x007F, 0x8000},    ///L en

    //charge Pump
    {0x0080, 0x0720}, //demo
    {0x0081, 0x0008},
    {0x0082, 0x0060},
};

static void nau8821_init1_regs(void)
{
    delay_ms(150);
    for (unsigned int i = 1; i < (sizeof(table_REG) / (2 * sizeof(uint16_t))); i++) {
        regmap_write_nau8821(Nau8821_Everest.regmap, table_REG[i][0], table_REG[i][1]);
        delay_ms(15);
    }
}

int nau8821_i2c_probe(void)
{
    int     value;
    uint8_t ret = 0;

    nau8821_reset_chip();
    delay_ms(100);

    ret = regmap_read_nau8821(Nau8821_Everest.regmap, NAU8821_R58_I2C_DEVICE_ID, (uint16_t *)&value);

    if (ret) {
        return ret;
    }

    nau8821_digital_mute(1, 0);

    nau8821_init1_regs();

    return ret;
}

#endif
