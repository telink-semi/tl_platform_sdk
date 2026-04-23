/*******************************************************************************************************
 *
 * @file    drv_i2c.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
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
#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__
#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

#include "tl_chip.h"
#include "reg/i2c.h"
#define I2C_EN_RD_REQ  (0x1 << 5)
#define I2C_EN_RX_FULL (0x1 << 2)

typedef enum {
    MASTER_MODE = 0,
    SLAVE_MODE,
} i2c_mode_t;

typedef enum {
    I2C_7BITADDR = 0,
    I2C_10BITADDR = 1,
} i2c_addr_width_t;

typedef enum {
    I2C_STD_MODE = 1, // 100Kbit/s
    I2C_FST_MODE = 2, // fast mode <=400Kbit/s and fast mode plus <= 1000Kbit/s
    I2C_HS_MODE = 3,  // 3.4Mbit/s
} i2c_speed_t;

typedef struct {
    i2c_mode_t i2c_mode;
    i2c_addr_width_t master_addr_width;
    i2c_addr_width_t slave_addr_width;
    i2c_speed_t speed_mode;
    uint32_t device_speed;
    uint32_t device_addr;
    _Bool restart_en;
    uint32_t int_mask;
} i2c_init_t;

typedef enum {
    DEV_I2C_STATE_RESET = 0,
    DEV_I2C_STATE_START,
    DEV_I2C_STATE_TX_BUSY,
    DEV_I2C_STATE_RX_WRITE_BUSY,
    DEV_I2C_STATE_RX_READ_BUSY,
    DEV_I2C_STATE_SUCCESS,
    DEV_I2C_STATE_ERROR,
} i2c_state_t;
typedef struct __i2c_handle_t {
    i2c_reg_t *instance;
    i2c_init_t init;
    i2c_state_t state;
    uint8_t reg_addr;
    uint8_t *tx_buff;
    volatile uint32_t tx_cnt;
    volatile uint32_t tx_idx;
    volatile uint32_t repeat_cnt;
    uint8_t *rx_buff;
    volatile uint32_t rx_cnt;
    volatile uint32_t rx_idx;
    volatile uint32_t read_idx;
    void (*tx_cplt_cb)(struct __i2c_handle_t *hi2c);
    void (*rx_cplt_cb)(struct __i2c_handle_t *hi2c);
} i2c_handle_t;

void i2c_master_send_stop(i2c_handle_t *hi2c,unsigned char en);
/**
 * @description: i2c init
 * @param {i2c_handle_t} port
 * @return {none}
 */
extern void drv_i2c_init(i2c_handle_t *drv_i2c);

/**
 * @description: i2c deinit
 * @param {i2c_handle_t} port
 * @return {none}
 */
extern void drv_i2c_deinit(i2c_handle_t *drv_i2c);

/**
 * @description: i2c master sync send
 * @param {i2c_handle_t} port
 * @param {uint16_t} tar
 * @param {uint8_t} regShift
 * @param {uint8_t} *pTxBuf
 * @param {uint32_t} bufLen
 * @return {int} send data num
 */
extern int drv_i2c_master_sync_send(i2c_handle_t *drv_i2c, uint16_t tar, uint8_t regShift, uint8_t *pTxBuf, uint32_t bufLen);
extern int drv_i2c_master_send(i2c_handle_t *hi2c, uint16_t tar, uint8_t *pTxBuf, uint32_t bufLen);
/**
 * @description: i2c master sync receive
 * @param {i2c_handle_t} port
 * @param {uint16_t} tar
 * @param {uint8_t} regShift
 * @param {uint8_t} *pRxBuf
 * @param {uint32_t} bufLen
 * @return {int} receive data num
 */
extern int drv_i2c_master_sync_receive(i2c_handle_t *drv_i2c, uint16_t tar, uint8_t regShift, uint8_t *pRxBuf, uint32_t bufLen);
extern int drv_i2c_master_receive(i2c_handle_t *hi2c, uint16_t tar, uint8_t *pRxBuf, uint32_t bufLen);


extern void drv_i2c_master_write_read(i2c_handle_t *hi2c,uint16_t tar, uint8_t *pTxBuf, uint32_t tx_bufLen, uint8_t *pRxBuf, uint32_t rx_bufLen);
/**
 * @description: i2c irq public handle
 * @param {i2c_handle_t} drv_i2c
 * @return {none}
 */
extern void drv_i2c_irq_public_handle(i2c_handle_t *drv_i2c);
/**
* @brief  Set the mclk divider
*
* @param  div: 0-0xff
* @return none
* @note   none
*/
extern void drv_i2c_set_mclk(uint32_t div);
/**
 * @description: get i2c mclk divider
 * @param {none}
 * @return {uint32_t} mclk divider
 */
extern uint32_t drv_i2c_get_mclk(void);
/**
 * @description: i2c slave sync send
 * @param {i2c_handle_t} port
 * @param {uint8_t} *pRxBuf
 * @param {uint32_t} bufLen
 * @return {int} receive data num
 */
extern void drv_i2c_slave_sync_send(i2c_handle_t *hi2c, uint8_t *pTxBuf, uint32_t len);
/**
 * @description: i2c slave sync receive
 * @param {i2c_handle_t} port
 * @param {uint8_t} *pRxBuf
 * @param {uint32_t} bufLen
 * @return {int} receive data num
 */
extern void drv_i2c_slave_sync_receive(i2c_handle_t *hi2c, uint8_t *pRxBuf, uint32_t len);
/**
 * @description: i2c master interrupt write
 * @param {i2c_handle_t} port
 * @param {uint16_t} tar
 * @param {uint8_t} regShift
 * @param {uint8_t} *pTxBuf
 * @param {uint32_t} bufLen
 * @return {none}
 */
extern void drv_i2c_master_interrupt_write(i2c_handle_t *hi2c, uint16_t tar, uint8_t regShift, uint8_t *pTxBuf, uint32_t bufLen);
/**
 * @description: i2c master interrupt read
 * @param {i2c_handle_t} port
 * @param {uint16_t} tar
 * @param {uint8_t} regShift
 * @param {uint8_t} *pTxBuf
 * @param {uint32_t} bufLen
 * @return {none}
 */
extern void drv_i2c_master_interrupt_read(i2c_handle_t *hi2c, uint16_t tar, uint8_t regShift, uint8_t *pTxBuf, uint32_t bufLen);
/**
 * @description: i2c slave interrupt read
 * @param {i2c_handle_t} port
 * @param {uint8_t} *pTxBuf
 * @param {uint32_t} bufLen
 * @return {none}
 */
extern void drv_i2c_slave_interrupt_read(i2c_handle_t *hi2c, uint8_t *pBuf, uint32_t bufLen);
/**
 * @description: i2c slave interrupt write
 * @param {i2c_handle_t} port
 * @param {uint8_t} *pTxBuf
 * @param {uint32_t} bufLen
 * @return {none}
 */
extern void drv_i2c_slave_interrupt_write(i2c_handle_t *hi2c, uint8_t *pBuf, uint32_t bufLen);
#ifdef __cplusplus
}
#endif

#endif
