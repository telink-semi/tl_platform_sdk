/********************************************************************************************************
 * @file    hal_flash.h
 *
 * @brief   This is the header file for tl752x
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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


#ifndef __HAL_FLASH_H__
#define __HAL_FLASH_H__
#include <stdbool.h>
#include <stdint.h>
#include "tl_chip.h"
#include "inc/drv_dwc_ssi.h"
#include "inc/drv_nor_flash.h"

#ifdef __cplusplus
extern "C" {
#endif


#define PAGE_SIZE     256
typedef void (*flash_handler_t)(unsigned long, unsigned long, unsigned char *);

extern nor_flash_dev_t driver_flash_dev;
extern dwc_ssi_handle_t driver_dwc_ssi_handle;
extern flash_handler_t flash_read_page;
extern flash_handler_t flash_write_page;

/**
 * @brief     flash vendor and technology definition
 */
typedef enum
{
    FLASH_ETOX_ZB    = 0x0100325E, // 325E          bit[24]:ETOX: Byte Program Time != Page Programming Time
    FLASH_ETOX_GD    = 0x010060C8, // 60C8/4051
    FLASH_SONOS_PUYA = 0x02006085, // 6085          bit[25]:SONOS:Byte Program Time == Page Programming Time
    FLASH_SONOS_TH   = 0x020060EB, // 60EB
    FLASH_SST_TH     = 0x040060CD, // 60CD/71CD     bit[26]:SST:  Byte Program Time != Page Programming Time
} flash_vendor_e;

/**
 * @brief   flash capacity definition
 *          Call flash_read_mid function to get the size of flash capacity.
 *          Example is as follows:
 *          unsigned int mid = flash_read_mid();
 *          The value of (mid&0x00ff0000)>>16 reflects flash capacity.
 */
typedef enum
{
    FLASH_SIZE_64K  = 0x10,
    FLASH_SIZE_128K = 0x11,
    FLASH_SIZE_256K = 0x12,
    FLASH_SIZE_512K = 0x13,
    FLASH_SIZE_1M   = 0x14,
    FLASH_SIZE_2M   = 0x15,
    FLASH_SIZE_4M   = 0x16,
    FLASH_SIZE_8M   = 0x17,
    FLASH_SIZE_16M  = 0x18,
} flash_capacity_e;

/**
 * @brief     flash command definition
 */
typedef enum
{
    //The command called by the flash_mspi_read_ram() function.
    /* attention: The maximum frequency of some flash single line reads may be smaller than the mspi frequency configured by the chip, it is not recommended to use the function of single line reads,
 * if you have to use it, please refer to the flash datasheet to ensure that the maximum frequency of flash single line reads is larger than the mspi frequency configured by the chip.(added by xiaobin.huang 20240717)
 */
    FLASH_DREAD_CMD                   = 0x3B,
    FLASH_X4READ_CMD                  = 0xEB,
    FLASH_READ_SECURITY_REGISTERS_CMD = 0x48,
    FLASH_READ_UID_CMD_GD_PUYA_ZB_TH  = 0x4B, //Flash Type = GD/PUYA/ZB/TH
    FLASH_GET_JEDEC_ID                = 0x9F,
    FLASH_READ_STATUS_CMD_LOWBYTE     = 0x05,
    FLASH_READ_STATUS_CMD_HIGHBYTE    = 0x35,
    FLASH_READ_CONFIGURE_CMD          = 0x15, //Flash Type = PUYA  in GD is read Read Status Register-3
    FLASH_READ_STATUS_CMD             = 0x15,
    //The command called by the flash_mspi_write_ram() function.
    FLASH_WRITE_CMD                    = 0x02,
    FLASH_QUAD_PAGE_PROGRAM_CMD        = 0x32, //may different for different flash
    FLASH_SECT_ERASE_CMD               = 0x20,
    FLASH_WRITE_SECURITY_REGISTERS_CMD = 0x42,
    FLASH_ERASE_SECURITY_REGISTERS_CMD = 0x44,
    FLASH_WRITE_STATUS_CMD_LOWBYTE     = 0x01,
    FLASH_WRITE_STATUS_CMD_HIGHBYTE    = 0x31, // Flash Type = P25Q16SU/P25Q32SU/PY25Q128H for write status register-1;
    FLASH_WRITE_CONFIGURE_CMD_1        = 0x31, // Flash Type = P25Q80U  for write configure register;
    FLASH_WRITE_STATUS_CMD_LOWBYTE_HIGHBYTE   = 0x01, // Flash Type = TH25Q32UB for write status register-1 and status register-2;
    FLASH_WRITE_CONFIGURE_CMD_2        = 0x11, // Flash Type = P25Q16SU/P25Q32SU/PY25Q128H  for write configure register;
    //other command
    FLASH_WRITE_DISABLE_CMD = 0x04,
    FLASH_WRITE_ENABLE_CMD  = 0x06,
} flash_command_e;

/**
 * @brief       This function serves to the interrupt protection of flash interface.
 * @return      none.
 * @note        _always_inline:the function is inlined to ensure security.
 */
_attribute_ram_code_sec_ void flash_reg_access_protect(void);

/**
 * @brief       This function serves to the interrupt restore of flash interface.
 * @return      none.
 * @note        _always_inline:the function is inlined to ensure security.
 */
_attribute_ram_code_sec_ void flash_reg_access_restore(void);

/**
 * @brief       This function use to configure the mspi clock source.
 * @param[in]   div - the mspi clk source divider
 * @return      none.
 */
_attribute_ram_code_sec_noinline_ void clock_mspi_clk_config(unsigned char div);

/**
 * @brief       This function use to initialization related to calling flash interfaces.
 * @param[in]   dma_chn - dma chn
 * @return      none.
 */
_attribute_text_sec_ void flash_init(unsigned char dma_chn);

/**
 * @brief       This function serves to erase a sector.
 * @param[in]   addr    - slave base address + the access address of flash(must be 0 or a multiple of 0x1000).The base address of device0 is 0.
 * @return      none.
 * @note        Attention: The block erase takes a long time, please pay attention to feeding the dog in advance.
 *              The maximum block erase time is listed at the beginning of this document and is available for viewing.
 *
 *              Attention: Before calling the FLASH function, please check the power supply voltage of the chip.
 *              Only if the detected voltage is greater than the safe voltage value, the FLASH function can be called.
 *              Taking into account the factors such as power supply fluctuations, the safe voltage value needs to be greater
 *              than the minimum chip operating voltage. For the specific value, please make a reasonable setting according
 *              to the specific application and hardware circuit.
 *
 *              Risk description: When the chip power supply voltage is relatively low, due to the unstable power supply,
 *              there may be a risk of error in the operation of the flash (especially for the write and erase operations.
 *              If an abnormality occurs, the firmware and user data may be rewritten, resulting in the final Product failure)
 */
_attribute_text_sec_ void flash_erase_sector(unsigned long addr);

/**
 * @brief       This function serves to erase a block of 32k.
 * @param[in]   addr    - must be 0 or a multiple of 0x8000.
 * @return      none.
 * @note        Attention: The block erase takes a long time, please pay attention to feeding the dog in advance.
 *              The maximum block erase time is listed at the beginning of this document and is available for viewing.
 *
 *              Attention: Before calling the FLASH function, please check the power supply voltage of the chip.
 *              Only if the detected voltage is greater than the safe voltage value, the FLASH function can be called.
 *              Taking into account the factors such as power supply fluctuations, the safe voltage value needs to be greater
 *              than the minimum chip operating voltage. For the specific value, please make a reasonable setting according
 *              to the specific application and hardware circuit.
 *
 *              Risk description: When the chip power supply voltage is relatively low, due to the unstable power supply,
 *              there may be a risk of error in the operation of the flash (especially for the write and erase operations.
 *              If an abnormality occurs, the firmware and user data may be rewritten, resulting in the final Product failure)
 */
_attribute_text_sec_ void flash_erase_block_32k(unsigned long addr);

/**
 * @brief       This function serves to erase a block of 64k.
 * @param[in]   addr    - must be 0 or a multiple of 0x10000.
 * @return      none.
 * @note        Attention: The block erase takes a long time, please pay attention to feeding the dog in advance.
 *              The maximum block erase time is listed at the beginning of this document and is available for viewing.
 *
 *              Attention: Before calling the FLASH function, please check the power supply voltage of the chip.
 *              Only if the detected voltage is greater than the safe voltage value, the FLASH function can be called.
 *              Taking into account the factors such as power supply fluctuations, the safe voltage value needs to be greater
 *              than the minimum chip operating voltage. For the specific value, please make a reasonable setting according
 *              to the specific application and hardware circuit.
 *
 *              Risk description: When the chip power supply voltage is relatively low, due to the unstable power supply,
 *              there may be a risk of error in the operation of the flash (especially for the write and erase operations.
 *              If an abnormality occurs, the firmware and user data may be rewritten, resulting in the final Product failure)
 */
_attribute_text_sec_ void flash_erase_block_64k(unsigned long addr);

/**
 * @brief       This function reads the content from a page to the buf with 4*IO read mode.
 * @param[in]   addr    - slave base address + the access address of flash.The base address of device0 is 0.
 *                      If there are multiple devices, the base address of other devices is determined by the mspi_slave_device_addr_space_config() function.
 * @param[in]   len     - the length(in byte, must be above 0 and below 4095) of content needs to read out from the page.
 * @param[out]  buf     - the start address of the buffer(ram address).
 * @return      none.
 * @note        cmd:1x, addr:4x, data:4x, dummy:6
 *              Attention: Before calling the FLASH function, please check the power supply voltage of the chip.
 *              Only if the detected voltage is greater than the safe voltage value, the FLASH function can be called.
 *              Taking into account the factors such as power supply fluctuations, the safe voltage value needs to be greater
 *              than the minimum chip operating voltage. For the specific value, please make a reasonable setting according
 *              to the specific application and hardware circuit.
 *
 *              Risk description: When the chip power supply voltage is relatively low, due to the unstable power supply,
 *              there may be a risk of error in the operation of the flash (especially for the write and erase operations.
 *              If an abnormality occurs, the firmware and user data may be rewritten, resulting in the final Product failure)
 */
_attribute_text_sec_ void flash_4read(unsigned long addr, unsigned long len, unsigned char *buf);

/**
 * @brief       This function writes the buffer's content to the flash with single mode.It is necessary to confirm whether this area
 *              has been erased before writing. If not, you need to erase and then write, otherwise the write may be unsuccessful
 *              and the data will become the wrong value. Note that when erasing, the minimum is erased by sector (4k bytes).
 *              Do not erase the useful information in other locations of the sector during erasing.
 * @param[in]   addr    - slave base address + the access address of flash.The base address of device0 is 0.
 * @param[in]   len     - the length(in byte, must be above 0) of content needs to write into the flash.
 * @param[in]   buf     - the start address of the content needs to write into(ram address).
 * @return      none.
 * @note        cmd:1x, addr:1x, data:1x
 *              the function support cross-page writing,which means the len of buf can bigger than 256.
 *
 *              Attention: Before calling the FLASH function, please check the power supply voltage of the chip.
 *              Only if the detected voltage is greater than the safe voltage value, the FLASH function can be called.
 *              Taking into account the factors such as power supply fluctuations, the safe voltage value needs to be greater
 *              than the minimum chip operating voltage. For the specific value, please make a reasonable setting according
 *              to the specific application and hardware circuit.
 *
 *              Risk description: When the chip power supply voltage is relatively low, due to the unstable power supply,
 *              there may be a risk of error in the operation of the flash (especially for the write and erase operations.
 *              If an abnormality occurs, the firmware and user data may be rewritten, resulting in the final Product failure)
 */
_attribute_text_sec_ void flash_page_program(unsigned long addr, unsigned long len, unsigned char *buf);

/**
 * @brief       This function serves to read MID of flash(MAC id). Before reading UID of flash,
 *              you must read MID of flash. and then you can look up the related table to select
 *              the idcmd and read UID of flash.
 * @return      MID of the flash.
 * @note        Attention: Before calling the FLASH function, please check the power supply voltage of the chip.
 *              Only if the detected voltage is greater than the safe voltage value, the FLASH function can be called.
 *              Taking into account the factors such as power supply fluctuations, the safe voltage value needs to be greater
 *              than the minimum chip operating voltage. For the specific value, please make a reasonable setting according
 *              to the specific application and hardware circuit.
 *
 *              Risk description: When the chip power supply voltage is relatively low, due to the unstable power supply,
 *              there may be a risk of error in the operation of the flash (especially for the write and erase operations.
 *              If an abnormality occurs, the firmware and user data may be rewritten, resulting in the final Product failure)
 */
_attribute_text_sec_ unsigned int flash_read_mid(void);

/**
 * @brief       This function serves to get flash vendor.
 * @param[in]   flash_mid - MID of the flash(4 bytes).
 * @return      0 - err, other - flash vendor.
 */
unsigned int flash_get_vendor(unsigned int flash_mid);

/**
 * @brief       This function serves to read UID of flash.Before reading UID of flash, you must read MID of flash.
 *              and then you can look up the related table to select the idcmd and read UID of flash.
 * @param[in]   idcmd   - different flash vendor have different read-uid command. E.g: GD/PUYA:0x4B; XTX: 0x5A.
 * @param[in]   buf     - store UID of flash.
 * @return      none.
 * @note        Attention: Before calling the FLASH function, please check the power supply voltage of the chip.
 *              Only if the detected voltage is greater than the safe voltage value, the FLASH function can be called.
 *              Taking into account the factors such as power supply fluctuations, the safe voltage value needs to be greater
 *              than the minimum chip operating voltage. For the specific value, please make a reasonable setting according
 *              to the specific application and hardware circuit.
 *
 *              Risk description: When the chip power supply voltage is relatively low, due to the unstable power supply,
 *              there may be a risk of error in the operation of the flash (especially for the write and erase operations.
 *              If an abnormality occurs, the firmware and user data may be rewritten, resulting in the final Product failure)
 */
_attribute_text_sec_ void flash_read_uid(unsigned char idcmd, unsigned char *buf);

/**
 * @brief       This function serves to initialize flash in n22/dsp.
 * @return      none.
 */
_attribute_text_sec_ void flash_init_n22_dsp(unsigned char dma_chn);

static inline int flash_read_mid_uid_with_check(unsigned int *flash_mid, unsigned char *flash_uid)
{
    (void)flash_mid;
    (void)flash_uid;
    return 1;
}

static inline unsigned char flash_4line_en(unsigned int flash_mid)
{
    (void)flash_mid;
    return 1;
}

static inline unsigned char flash_4line_dis(unsigned int flash_mid)
{
    (void)flash_mid;
    return 1;
}

#ifdef __cplusplus
}
#endif

#endif /* __DRV_NOR_FLASH_H__ */
