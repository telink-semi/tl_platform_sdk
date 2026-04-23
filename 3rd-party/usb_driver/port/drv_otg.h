/*
 * @FilePath: \epm_driver\third_party\usb_driver\port\drv_otg.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __DRV_OTG__
#define __DRV_OTG__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "usb_conf.h"
#include "usb_regs.h"
#include "usb_defines.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/

/**************************** type definition ********************************/
typedef struct {
    uint8_t conidsts;
} usb_otg_dev_t;

/************************* variable definition *******************************/

/**************************** function declear *******************************/

/********************** function implementation ******************************/
/**
* @brief  usb_set_currentmode : Set ID line
* @param  mode :  (Host/device)
* @retval None
*/
void usb_otg_set_currentmode(uint8_t mode);
/**
* @brief  enable otg int
*
* @param  none
* @return none
* @note   none
*/
void usb_otg_enable_int(void);
/**
* @brief  otg init
*
* @param  none
* @return none
* @note   none
*/
//extern void usb_otg_init(void);
/**
* @brief  usb_otg_getconidsts : Get Connector ID Status
* @param  none
* @retval conidsts
*/
extern uint8_t usb_otg_getconidsts(void);

#endif

#ifdef __cplusplus
}
#endif

#endif //__DRV_USB_OTG__
