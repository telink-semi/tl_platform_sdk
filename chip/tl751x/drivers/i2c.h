/********************************************************************************************************
 * @file    i2c.h
 *
 * @brief   This is the header file for tl751x
 *
 * @author  Driver Group
 * @date    2023
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
/** @page I2C
 *
 *  Header File: i2c.h
 *
 *  How to use this driver
 *  ==============
 The i2c has two modules: i2c/i2c1_m
- i2c(It can be used as a master or slave)
 -# i2c Master
  -# Initialization and Configuration
     -# nodma/dma:
        - Initialize the sda/scl pin by i2c_set_pin() API;
        - Configure the speed by i2c_set_master_clk() API;
        - Enable master function by i2c_master_init() API;
     -# dma
        - dma initial configuration by i2c_set_rx_dma_config() / i2c_set_tx_dma_config() API;
  -# Interrupts Configuration and Response
     -# interrupt initial configuration:
        - nodma_write
           - polling write, it does not need to configure interrupt;
        - nodma_read
           - polling read, it does not need to configure interrupt;
        - dma_write/dma_read
           - i2c_set_irq_mask() : I2C_MASTER_NAK_MASK;
        - plic_interrupt_enable() / core_interrupt_enable() API;
     -# interrupt response(for details, see the enumeration i2c_irq_status_e):
        - dma_write/dma_read
          - i2c_get_irq_status() : I2C_MASTER_NAK_STATUS;
          - i2c_clr_irq_status() : I2C_MASTER_NAK_STATUS;
  -# TX and RX(note: during write/read, if nack is detected, send a stop signal,and abort the current write/read)
     -# nodma_write
        - polling write by i2c_master_write() API;
     -# nodma_read
        - polling send by i2c_master_read() API;
     -# dma_write
        - write data by i2c_master_write_dma() API,check whether write is complete by polling i2c_master_busy() API;
     -# dma_read
        - read data by i2c_master_read_dma() API,check whether read is complete by polling i2c_master_busy() API;
 -# i2c Slave(the slave can be divided into two cases, whether to combine the stretch function or not)
    -# no stretch
       -# Initialization and Configuration
          -# nodma/dma:
            - Initialize the sda/scl pin by i2c_set_pin() API;
            - Enable slave function and set id by i2c_slave_init() API;
          -# dma
            - dma initial configuration by i2c_set_rx_dma_config() / i2c_set_tx_dma_config() API;
       -# Interrupts Configuration and Response
          -# interrupts initial configuration:
            - nodma_write
              - no associated interrupt is used;
            - nodma_read
              - i2c_rx_irq_trig_cnt() / i2c_set_irq_mask() : I2C_RX_BUF_MASK|I2C_RX_END_MASK;
            - dma_write
              - dma_set_irq_mask() : TC_MASK;
            - dma_read
              - i2c_set_irq_mask() : I2C_TX_END_MASK;
            - plic_interrupt_enable() / core_interrupt_enable() API;
       -# interrupt response(for details, see the enumeration i2c_irq_status_e):
          - i2c_get_irq_status() ;
          - i2c_clr_irq_status() ;
          - nodma_read
            - I2C_RX_BUF_STATUS/I2C_RX_END_STATUS
          - dma_write/read
            - See the TC_MASK note for details;
       -# TX and RX
          - nodma_write
             - polling write by i2c_slave_write() API;
          - nodma_read
             - The data is read via I2C_RX_BUF_MASK and I2C_RX_END_MASK interrupt,the data is read in the interrupt by i2c_slave_read() API;
          - dma_write
             - write data by i2c_slave_set_tx_dma() API;
          - dma_read
             - read data by i2c_slave_set_rx_dma() API;

    -# enable stretch
       -# Initialization and Configuration
          -# nodma/dma:
            - Initialize the sda/scl pin by i2c_set_pin() API;
            - Enable slave function and set id by i2c_slave_init() API;
            - Enable stretch function by i2c_slave_stretch_en() API;
          -# dma
            - dma initial configuration by i2c_set_rx_dma_config() / i2c_set_tx_dma_config() API;
       -# Interrupts Configuration and Response
          -# interrupts initial configuration:
            - nodma_write
              - i2c_set_irq_mask() : I2C_SLAVE_WR_MASK;
            - nodma_read
              - i2c_rx_irq_trig_cnt() / i2c_set_irq_mask() : I2C_RX_BUF_MASK|I2C_RX_END_MASK;
            - dma_write
              - i2c_set_irq_mask() : I2C_SLAVE_WR_MASK;
            - dma_read
              - i2c_set_irq_mask() : I2C_RX_END_MASK;
            - plic_interrupt_enable() / core_interrupt_enable() API;
       -# interrupt response(for details, see the enumeration i2c_irq_status_e):
          - i2c_get_irq_status() ;
          - i2c_clr_irq_status() ;
          - nodma_write
            - I2C_SLAVE_WR_STATUS
          - nodma_read
            - I2C_RX_BUF_STATUS/I2C_RX_END_STATUS
          - dma_write
            - I2C_SLAVE_WR_STATUS
          - dma_read
            - I2C_RX_END_STATUS
       -# TX and RX
        -# nodma_write
         - polling write by i2c_slave_write() API;
        -# nodma_read
         - The data is read via I2C_RX_BUF_MASK and I2C_RX_END_MASK interrupt,the data is read in the interrupt by i2c_slave_read() API;
        -# dma_write
         - write data by i2c_slave_set_tx_dma() API;
        -# dma_read
         - read data by i2c_slave_set_rx_dma() API;
    -# the attention:
      - when the slave is used with the stretch function, Determine when the master reads the data and then use the fill data by interrupting I2C_SLAVE_WR_MASK (nodma:i2c_slave_write() dma:i2c_slave_set_tx_dma());
      - When the slave is not used with stretch function, if I2C_SLAVE_WR_MASK is used to interrupt to judge when the master reads and fills the data, the mcu cannot handle it. Therefore, it is necessary to fill the data in advance before the master read data (nodma:i2c_slave_write() dma:i2c_slave_set_tx_dma());
      - The i2c_master_send_stop() API is used to determine whether the master sends a stop signal after the sending or receiving is complete
- i2c1_m(Only as master,only nodma)
     -# Initialization and Configuration
       - Initialize the sda/scl pin by i2c1_m_set_pin() API;
       - Configure the speed by i2c1_m_set_master_clk() API;
       - Enable master function by i2c1_m_master_init() API;
     -# TX and RX(For write and read, you can optionally add an address)
       - i2c1_m_master_write() API,if send the address, just put the address in the txbuff and send it together as data;
       - i2c1_m_master_write_read() API;
     -# the attention:
       - The i2c1_m_master_send_stop() API is used to determine whether the master sends a stop signal after the sending or receiving is complete;
 */

#ifndef I2C_H
#define I2C_H
#include <stdbool.h>
#include "lib/include/analog.h"
#include "dma.h"
#include "gpio.h"
#include "reg_include/i2c_reg.h"

/**********************************************************************************************************************
 *                                         global constants                                                           *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           global macro                                                             *
 *********************************************************************************************************************/
extern unsigned char i2c_slave_rx_index;

/**
 *  @brief  select pin as SDA and SCL of i2c
 */
typedef enum
{
    I2C_GPIO_SDA_A1 = GPIO_PA1,
    I2C_GPIO_SDA_A3 = GPIO_PA3,
    I2C_GPIO_SDA_A5 = GPIO_PA5,
    I2C_GPIO_SDA_B0 = GPIO_PB0,
    I2C_GPIO_SDA_B2 = GPIO_PB2,
    I2C_GPIO_SDA_B4 = GPIO_PB4,
    I2C_GPIO_SDA_B6 = GPIO_PB6,
    I2C_GPIO_SDA_C0 = GPIO_PC0,
    I2C_GPIO_SDA_C2 = GPIO_PC2,
    I2C_GPIO_SDA_C4 = GPIO_PC4,
    I2C_GPIO_SDA_C6 = GPIO_PC6,
    I2C_GPIO_SDA_D0 = GPIO_PD0,
    I2C_GPIO_SDA_D2 = GPIO_PD2,
    I2C_GPIO_SDA_D4 = GPIO_PD4,
    I2C_GPIO_SDA_D6 = GPIO_PD6,
    I2C_GPIO_SDA_E0 = GPIO_PE0,
    I2C_GPIO_SDA_E2 = GPIO_PE2,
    I2C_GPIO_SDA_E4 = GPIO_PE4,
    I2C_GPIO_SDA_E6 = GPIO_PE6,
    I2C_GPIO_SDA_F4 = GPIO_PF4,
    I2C_GPIO_SDA_F6 = GPIO_PF6,
    I2C_GPIO_SDA_G0 = GPIO_PG0,
    I2C_GPIO_SDA_G2 = GPIO_PG2,
    I2C_GPIO_SDA_G4 = GPIO_PG4,
    I2C_GPIO_SDA_G6 = GPIO_PG6,
} i2c_sda_pin_e;

typedef enum
{
    I2C_GPIO_SCL_A0 = GPIO_PA0,
    I2C_GPIO_SCL_A2 = GPIO_PA2,
    I2C_GPIO_SCL_A4 = GPIO_PA4,
    I2C_GPIO_SCL_A6 = GPIO_PA6,
    I2C_GPIO_SCL_B1 = GPIO_PB1,
    I2C_GPIO_SCL_B3 = GPIO_PB3,
    I2C_GPIO_SCL_B5 = GPIO_PB5,
    I2C_GPIO_SCL_B7 = GPIO_PB7,
    I2C_GPIO_SCL_C1 = GPIO_PC1,
    I2C_GPIO_SCL_C3 = GPIO_PC3,
    I2C_GPIO_SCL_C5 = GPIO_PC5,
    I2C_GPIO_SCL_C7 = GPIO_PC7,
    I2C_GPIO_SCL_D1 = GPIO_PD1,
    I2C_GPIO_SCL_D3 = GPIO_PD3,
    I2C_GPIO_SCL_D5 = GPIO_PD5,
    I2C_GPIO_SCL_D7 = GPIO_PD7,
    I2C_GPIO_SCL_E1 = GPIO_PE1,
    I2C_GPIO_SCL_E3 = GPIO_PE3,
    I2C_GPIO_SCL_E5 = GPIO_PE5,
    I2C_GPIO_SCL_E7 = GPIO_PE7,
    I2C_GPIO_SCL_F5 = GPIO_PF5,
    I2C_GPIO_SCL_F7 = GPIO_PF7,
    I2C_GPIO_SCL_G1 = GPIO_PG1,
    I2C_GPIO_SCL_G3 = GPIO_PG3,
    I2C_GPIO_SCL_G5 = GPIO_PG5,
} i2c_scl_pin_e;

/**
 *  @brief  select pin as SDA and SCL of i2c
 */
typedef enum
{
    I2C1_GPIO_SDA_A1 = GPIO_PA1,
    I2C1_GPIO_SDA_A3 = GPIO_PA3,
    I2C1_GPIO_SDA_A5 = GPIO_PA5,
    I2C1_GPIO_SDA_B0 = GPIO_PB0,
    I2C1_GPIO_SDA_B2 = GPIO_PB2,
    I2C1_GPIO_SDA_B4 = GPIO_PB4,
    I2C1_GPIO_SDA_B6 = GPIO_PB6,
    I2C1_GPIO_SDA_C0 = GPIO_PC0,
    I2C1_GPIO_SDA_C2 = GPIO_PC2,
    I2C1_GPIO_SDA_C4 = GPIO_PC4,
    I2C1_GPIO_SDA_C6 = GPIO_PC6,
    I2C1_GPIO_SDA_D0 = GPIO_PD0,
    I2C1_GPIO_SDA_D2 = GPIO_PD2,
    I2C1_GPIO_SDA_D4 = GPIO_PD4,
    I2C1_GPIO_SDA_D6 = GPIO_PD6,
    I2C1_GPIO_SDA_E0 = GPIO_PE0,
    I2C1_GPIO_SDA_E2 = GPIO_PE2,
    I2C1_GPIO_SDA_E4 = GPIO_PE4,
    I2C1_GPIO_SDA_E6 = GPIO_PE6,
    I2C1_GPIO_SDA_F4 = GPIO_PF4,
    I2C1_GPIO_SDA_F6 = GPIO_PF6,
    I2C1_GPIO_SDA_G0 = GPIO_PG0,
    I2C1_GPIO_SDA_G2 = GPIO_PG2,
    I2C1_GPIO_SDA_G4 = GPIO_PG4,
    I2C1_GPIO_SDA_G6 = GPIO_PG6,
} i2c1_m_sda_pin_e;

typedef enum
{
    I2C1_GPIO_SCL_A0 = GPIO_PA0,
    I2C1_GPIO_SCL_A2 = GPIO_PA2,
    I2C1_GPIO_SCL_A4 = GPIO_PA4,
    I2C1_GPIO_SCL_A6 = GPIO_PA6,
    I2C1_GPIO_SCL_B1 = GPIO_PB1,
    I2C1_GPIO_SCL_B3 = GPIO_PB3,
    I2C1_GPIO_SCL_B5 = GPIO_PB5,
    I2C1_GPIO_SCL_B7 = GPIO_PB7,
    I2C1_GPIO_SCL_C1 = GPIO_PC1,
    I2C1_GPIO_SCL_C3 = GPIO_PC3,
    I2C1_GPIO_SCL_C5 = GPIO_PC5,
    I2C1_GPIO_SCL_C7 = GPIO_PC7,
    I2C1_GPIO_SCL_D1 = GPIO_PD1,
    I2C1_GPIO_SCL_D3 = GPIO_PD3,
    I2C1_GPIO_SCL_D5 = GPIO_PD5,
    I2C1_GPIO_SCL_D7 = GPIO_PD7,
    I2C1_GPIO_SCL_E1 = GPIO_PE1,
    I2C1_GPIO_SCL_E3 = GPIO_PE3,
    I2C1_GPIO_SCL_E5 = GPIO_PE5,
    I2C1_GPIO_SCL_E7 = GPIO_PE7,
    I2C1_GPIO_SCL_F5 = GPIO_PF5,
    I2C1_GPIO_SCL_F7 = GPIO_PF7,
    I2C1_GPIO_SCL_G1 = GPIO_PG1,
    I2C1_GPIO_SCL_G3 = GPIO_PG3,
    I2C1_GPIO_SCL_G5 = GPIO_PG5,
} i2c1_m_scl_pin_e;

typedef enum
{
    I2C_SLAVE_WR_MASK   = BIT(0), /**<
                                          <pre> the slave parsing master cmd interrupt,when received the master read or write cmd, will generate interrupt.
                                          Combined with the stretch function i2c_slave_stretch_en(),it is generally used to inform the i2c slave when to fill txfifo to write data.</pre>
                                         */
    I2C_MASTER_NAK_MASK = BIT(1), /**< master detect to the nack, will generate interrupt */
    I2C_RX_BUF_MASK     = BIT(2), /**< rxfifo_cnt >= FLD_I2C_RX_IRQ_TRIG_LEV generates an interrupt */
    I2C_TX_BUF_MASK     = BIT(3), /**< txfifo_cnt <= FLD_I2C_TX_IRQ_TRIG_LEV, generate interrupt */
    I2C_RX_DONE_MASK    = BIT(4), /**< when the stop signal is detected, an interrupt occurs */
    I2C_TX_DONE_MASK    = BIT(5), /**< when the stop signal is detected, an interrupt occurs */
    I2C_RX_END_MASK     = BIT(6), /**< An interrupt is generated when one frame of data is received(the stop signal has been sent) */
    I2C_TX_END_MASK     = BIT(7), /**< An interrupt is generated when one frame of data is sent(the stop signal has been sent) */
    I2C_STRETCH_IRQ     = BIT(8), /**< Combined with the stretch function i2c_slave_stretch_en(),the slave stretch interrupt,when tx_fifo is empty or rx_fifo is full,will generate interrupt */
} i2c_irq_mask_e;

/**
 *  @brief  Define I2C IRQ bit status and explain what needs to be done in the interrupt.
 */
typedef enum
{
    I2C_SLAVE_WR_STATUS   = BIT(0), /**<
                                                <pre>get interrupt status:i2c_get_irq_status(), clr interrupt status:i2c_clr_irq_status().
                                                in nodma mode,i2c slave writes data by i2c_slave_write() API;
                                                in dma mode,i2c slave writes data by i2c_slave_set_tx_dma() API;</pre>
                                             */
    I2C_MASTER_NAK_STATUS = BIT(1), /**<
                                               <pre>
                                               get interrupt status:i2c_get_irq_status(), clr interrupt status:i2c_clr_irq_status().
                                               in nodma mode,nodma does not need this interrupt;
                                               for master,in dma mode:
                                                  When write data, reg_i2c_sct1 = (FLD_I2C_LS_STOP)-> while(i2c_master_busy())-> dma_chn_dis(I2C_TX_DMA_CHN)-> i2c_clr_irq_status(I2C_TX_BUF_STATUS);
                                                  when read data,reg_i2c_sct1 = (FLD_I2C_LS_STOP)-> while(i2c_master_busy())-> dma_chn_dis(I2C_TX_DMA_CHN);
                                               </pre>
                                         */

    I2C_RX_BUF_STATUS  = BIT(2),    /**<
                                                <pre>get interrupt status:i2c_get_irq_status(), clr interrupt status: automatically cleared.
                                                if using the i2c_clr_irq_status(), will clear the clear RX FIFO pointer.
                                                in nodma mode,i2c slave read data by i2c_get_rx_buf_cnt() / i2c_slave_read().
                                                in dma mode,dma does not need this interrupt.</pre>
                                             */
    I2C_TX_BUF_STATUS  = BIT(3),    /**<  <pre>in general, this interrupt is not required</pre> */
    I2C_RX_DONE_STATUS = BIT(4),    /**<  <pre>usually don't use this interrupt,use I2C_RX_END_STATUS instead</pre> */
    I2C_TX_DONE_STATUS = BIT(5),    /**<  <pre>usually don't use this interrupt,use I2C_TX_END_STATUS instead</pre> */
    I2C_RX_END_STATUS  = BIT(6),    /**<
                                           <pre>
                                              get interrupt status:i2c_get_irq_status(), clr interrupt status: i2c_clr_irq_status().
                                              Generally speaking, it is used for i2c slaves.
                                             in no dma,i2c slave read data by i2c_get_rx_buf_cnt() / i2c_slave_read().
                                            </pre>
                                        */

    I2C_TX_END_STATUS  = BIT(7),    /**<  <pre>get interrupt status:i2c_get_irq_status(), clr interrupt status: i2c_clr_irq_status()</pre>  */
    I2C_STRETCH_STATUS = BIT(8),    /**<  <pre>get interrupt status:i2c_get_irq_status(), clr interrupt status: i2c_clr_irq_status()</pre>  */
} i2c_irq_status_e;

/**
 * this register is use to get slave relevant status
 * BIT[1] slave stretch indicate.
 * BIT[2] judge slave tx_fifo is empty.
 * BIT[3] judge slave rx_fifo is full.
 */
typedef enum
{
    I2C_SLAVER_STRETCH_INDICATE = BIT(1),
    I2C_SLAVER_TX_EMPTY         = BIT(2),
    I2C_SLAVE_RX_FULL           = BIT(3),
} i2c_slave_status1_e;

/**
 *  judge the read and write status of slave.
 */
typedef enum
{
    I2C_SLAVE_WRITE = 1,
    I2C_SLAVE_READ  = 0,
} i2c_slave_wr_e;

/**
 * judge the read and write status of master.
 */
typedef enum
{
    I2C_MASTER_WRITE = 0,
    I2C_MASTER_READ  = 1,
} i2c_master_wr_e;

/**
 * @brief      This function reset i2c module
 * @return     none
 */
static inline void i2c_reset(void)
{
    reg_rst0 &= (~FLD_RST0_I2C);
    reg_rst0 |= FLD_RST0_I2C;
}

/**
 * @brief      The function of this API is to determine whether the bus is busy.
 * @return     1:Indicates that the bus is busy. 0:Indicates that the bus is free
 */
static inline _Bool i2c_master_busy(void)
{
    return reg_i2c_mst & FLD_I2C_MST_BUSY;
}

/**
 * @brief      This function serves to get the txfifo cnt,FLD_I2C_TX_BUFCNT is decremented when there are outgoing sent data in the txfifo,
 *             when there is write data in the tx_fifo, this register is increased.
 * @return     The actual number of bytes in txfifo.
 */
static inline unsigned char i2c_get_tx_buf_cnt(void)
{
    return (reg_i2c_buf_cnt & FLD_I2C_TX_BUFCNT) >> 4;
}

/**
 * @brief      This function serves to get the rxfifo cnt,FLD_I2C_RX_BUFCNT is increased when there are incoming received data rxfifo,
 *             when there is read data in the rxfifo, FLD_I2C_RX_BUFCNT is decremented.
 * @return     The actual number of bytes in rxfifo.
 */
static inline unsigned char i2c_get_rx_buf_cnt(void)
{
    return (reg_i2c_buf_cnt & FLD_I2C_RX_BUFCNT);
}

/**
 * @brief      The function of this API is to set the number of bytes to triggered the receive interrupt.
 *             Its default value is 4. We recommend setting it to 1 or 4.
 * @param[in]  cnt - the interrupt trigger level,the range is less than 8.
 * @return     none
 */
static inline void i2c_rx_irq_trig_cnt(unsigned char cnt)
{
    /*
       in the i2c_rx_irq_trig_cnt interface,originally first set i2c_rc_irq_trig_cnt to 0 and then assign,
       if the rx_buff mask is opened first, when set i2c_rc_irq_trig_cnt to 0,rx_fifo is empty, an interrupt will be triggered by mistake.
    */
    reg_i2c_trig = (((reg_i2c_trig) & (~FLD_I2C_RX_IRQ_TRIG_LEV)) | (cnt & 0x0f));
}

/**
 * @brief      This function serves to enable i2c interrupt function.
 * @param[in]  mask - to select interrupt type.
 * @return     none
 */
static inline void i2c_set_irq_mask(i2c_irq_mask_e mask)
{
    if (mask & I2C_STRETCH_IRQ) {
        reg_i2c_ctrl2 |= FLD_I2C_MASK_STRETCH;
    }

    reg_i2c_mask0 |= mask;
}

/**
 * @brief      This function serves to disable i2c interrupt function.
 * @param[in]  mask - to select Interrupt type.
 * @return     none
 */
static inline void i2c_clr_irq_mask(i2c_irq_mask_e mask)
{
    if (mask & I2C_STRETCH_IRQ) {
        reg_i2c_ctrl2 &= (~FLD_I2C_MASK_STRETCH);
    }

    reg_i2c_mask0 &= (~mask);
}

/**
 * @brief      This function serves to get i2c interrupt status.
 * @param[in]  status     - to select Interrupt status type.
 * @retval     non-zero       - the interrupt occurred.
 * @retval     zero   - the interrupt did not occur.
 *
 */
static inline unsigned char i2c_get_irq_status(i2c_irq_status_e status)
{
    if (status & I2C_STRETCH_IRQ) {
        return i2c_slave_status1 & FLD_I2C_SS_SCL_IRQ;
    }
    return reg_i2c_status0 & status;
}

/**
 * @brief     This function is used to set the 'i2c_slave_rx_index' to 0,
 *            'i2c_slave_rx_index' is used to synchronize the rxfifo hardware pointer in no_dma mode.
 * @return    none.
 * @note      note the following:
 *            -# After calling the i2c reset interface, i2c_slave_clr_rx_index must be called to clear the read pointer,
 *               after the i2c reset interface is invoked, the hardware read pointers are cleared to zero.
 *               Therefore, the software write pointers are cleared to ensure logical correctness.
 *            -# After suspend wakes up, you must call i2c_slave_clr_rx_index to clear read pointers,
 *               because after suspend wakes up, the chip is equivalent to performing a i2c_reset,
 *               so the software read pointer also needs to be cleared to zero.
 */
static inline void i2c_slave_clr_rx_index(void)
{
    i2c_slave_rx_index = 0;
}

/**
 * @brief      This function serves to clear i2c irq status.
 * @param[in]  status - to select interrupt status type.
 * @return     none
 */
static inline void i2c_clr_irq_status(i2c_irq_status_e status)
{
    if (status & I2C_STRETCH_STATUS) {
        i2c_slave_status1 = FLD_I2C_SS_SCL_IRQ;
    } else {
        reg_i2c_status0 = status;
    }
    if (status & I2C_RX_BUF_STATUS) {
        i2c_slave_clr_rx_index();
    }
}

/**
 * @brief      This function serves to enable slave mode.
 * @param[in]  id - the id of slave device.it contains write or read bit,the laster bit is write or read bit.
 *                       ID|0x01 indicate read. ID&0xfe indicate write.
 * @return     none
 */
void i2c_slave_init(unsigned char id);

/**
 * @brief      The function of this API is to ensure that the data can be successfully sent out.
 *             can choose whether to send stop,if i2c stop is not configured, the next time a start signal is sent, it will be a restart signal,
 *             but if a nack exception is received in id or data phase, during exception handling, a stop signal will be sent.
 *             1.in the id phase,detect nack,stop sending.
 *             2.in the data phase,detect nack,stop sending.
 * @param[in]  id   - to set the slave ID.
 * @param[in]  data - The data to be sent.
 * @param[in]  len  - This length is the total length, including both the length of the slave RAM address and the length of the data to be sent.
 * @return     0:received nack in id or data phase,and then stop, 1:write successfully
 */
unsigned char i2c_master_write(unsigned char id, unsigned char *data, unsigned int len);

/**
 * @brief      This function serves to read a packet of data from the specified address of slave device.
 *             can choose whether to send stop,if i2c stop is not configured, the next time a start signal is sent, it will be a restart signal,
 *             but if a nack exception is received in id phase, during exception handling, a stop signal will be sent.
 *             only in id phase, detect nack,stop receiving.
 * @param[in]  id   - to set the slave ID.
 * @param[in]  data - Store the read data
 * @param[in]  len  - The total length of the data read back.
 * @return     0 : the master receive NACK after sending out the id and then send stop.  1: the master receive the data successfully.
 */
unsigned char i2c_master_read(unsigned char id, unsigned char *data, unsigned int len);

/**
 * @brief      This function serves to write data and read data,
 *             can choose whether to send stop or not,If i2c stop is not configured,the master between writing and reading, it will be a restart signal,
 *             and after reading and writing, a stop signal is sent,but the stop configure,stays in its original state,
 *             when a nack exception signal is received, during exception handling, a stop signal will be sent.
 * @param[in]  id - to set the slave ID.
 * @param[in]  wr_data - The data to be sent.
 * @param[in]  wr_len -  This length is the total length, including both the length of the slave RAM address and the length of the data to be sent.
 * @param[in]  rd_data - Store the read data
 * @param[in]  rd_len -  The total length of the data read back.
 * @return     0: the master detect nack in the id or data when the master write,stop sending,and return.
 *                or the master detect nack in the id when the master read,stop receiving,and return.
 *             1: the master receive the data successfully.
 */
unsigned char i2c_master_write_read(unsigned char id, unsigned char *wr_data, unsigned int wr_len, unsigned char *rd_data, unsigned int rd_len);

/**
 * @brief      The function of this API is just to write data to the i2c tx_fifo by DMA.
 *             can choose whether to send stop,if i2c stop is not configured, the next time a start signal is sent, it will be a restart signal,
 *             but if a nack exception is received in id or data phase, during exception handling, a stop signal will be sent.
 * @param[in]  id   - to set the slave ID.
 * @param[in]  data - The data to be sent,must be aligned by word (4 bytes).
 * @param[in]  len  - This length is the total length, including both the length of the slave RAM address and the length of the data to be sent,
 *                    the maximum transmission length of DMA is 0xFFFFFC bytes, so dont'n over this length.
 * @return     none.
 * @note       After the DMA transfer is complete, the interface needs to be re-invoked to write the next batch of data.
 */
void i2c_master_write_dma(unsigned char id, unsigned char *data, unsigned int len);

/**
 * @brief      This function serves to read a packet of data from the specified address of slave device by dma.
 *             can choose whether to send stop,if i2c stop is not configured, the next time a start signal is sent, it will be a restart signal,
 *             but if a nack exception is received in id phase, during exception handling, a stop signal will be sent.
 * @param[in]  id      - to set the slave ID.
 * @param[in]  rx_data - Store the read data,must be aligned by word (4 bytes).
 * @param[in]  len     - The total length of the data read back,the maximum transmission length of DMA is 0xFFFFFC bytes, so dont'n over this length.
 * @return     none
 * @note       After the DMA transfer is complete, the interface needs to be re-invoked to read the next batch of data.
 */
void i2c_master_read_dma(unsigned char id, unsigned char *rx_data, unsigned int len);

/**
 * @brief      This function serves to write a packet of data to master device in DMA mode.
 * @param[in]  data -  Pointer to data buffer, it must be 4-bytes aligned address
 * @param[in]  len  -  Amount of data to be sent in bytes, range from 1 to 0xFFFFFC
 * @return     none.
 * @note       After the DMA transfer is complete, the interface needs to be re-invoked to write the next batch of data.
 */
void i2c_slave_set_tx_dma(unsigned char *data, unsigned int len);

/**
@brief         This function serves to receive a packet of data from master device.
@param[in]     data - the pointer of rx_buff, it must be 4-bytes aligned address
@param[in]     len - length in bytes, must be a multiple of 4, with a maximum value of 0xFFFFFC.
@return        none.
@note
               -# If write_num is enabled, the length of data received by DMA will be written into the first four bytes of the address.
               -# A length greater than XX_len itself and a multiple of 4 is denoted as CEILING(XX_len,4). For example: XX_len=3 ,CEILING(XX_len,4)=4; XX_len=21 ,CEILING(Tx_length, 4)=24.
                  The actual length sent by master  is denoted as Tx_len, The length (param[in]-len) of the interface configuration is denoted as Rx_len.
                  when CEILING(Tx_len,4) > CEILING(Rx_len,4), When the length of the DMA carry reaches Rx_len, the DMA will not stop working and the excess data will not be carried into the buff.
                  for example:Tx_len=21,Rx_len=20,When the DMA stops working the buff is written with a length of 21 and only 20 bytes of data are stored.It is recommended to configure the appropriate Rx_len to avoid this situation.
                -# After DMA transfer completion, the interface needs to be invoked again to read the next batch of data.
*/
void i2c_slave_set_rx_dma(unsigned char *data, unsigned int len);

/**
 * @brief     This function serves to receive data .
 * @param[in]  data - the data need read.
 * @param[in]  len - The total length of the data
 * @return    none
 */
void i2c_slave_read(unsigned char *data, unsigned int len);

/**
 * @brief     This function serves to receive i2c data by byte with not DMA method.
 * @param[in]  data - the data need send.
 * @param[in]  len - The total length of the data.
 * @return    none
 */
void i2c_slave_write(unsigned char *data, unsigned int len);

/**
 * @brief      This function serves to set the i2c clock frequency.The i2c clock is consistent with the system clock.
 *             Currently, the default system clock is 48M, and the i2c clock is also 48M.
 * @param[in]  clock - the division factor of I2C clock,
 *             I2C frequency = System_clock / (4*DivClock).
 * @return     none
 */
void i2c_set_master_clk(unsigned char clock);

/**
 * @brief     This function serves to set i2c tx_dma channel and config dma tx default.
 * @param[in] chn: dma channel.
 * @return    none
 */
void i2c_set_tx_dma_config(dma_chn_e chn);

/**
 * @brief     This function serves to set i2c rx_dma channel and config dma rx default.
 * @param[in] chn: dma channel.
 * @return    none
 */
void i2c_set_rx_dma_config(dma_chn_e chn);

/*
 *@brief     enable i2c slave stretch function,conjunction with Stretch function of master,
 *           this stretch function is usually used in combination with I2C_SLAVER_WR_IRQ interrupt,
 *           when TX_FIFO of slave terminal is empty or RX_FIFO of slave terminal is full, the interrupt state is up and the clock line is pulled down.
 *@return    none.
 */
static inline void i2c_slave_stretch_en(void)
{
    reg_i2c_ctrl3 |= FLD_I2C_SLAVE_STRETCH_EN;
}

/**
 *@brief     This function serves to disable i2c slave stretch function.
 *@return    none.
 */
static inline void i2c_slave_stretch_dis(void)
{
    reg_i2c_ctrl3 &= ~FLD_I2C_SLAVE_STRETCH_EN;
}

/**
 *@brief     This function serves to enable i2c master stretch function,
 *           If stretch is enabled on the slave, it needs to be enabled,by default, it is enabled on the interface i2c_master_init.
 *@return    none.
 */
static inline void i2c_master_stretch_en(void)
{
    reg_i2c_ctrl2 |= FLD_I2C_MASTER_STRETCH_EN;
}

/**
 *@brief     This function serves to disable i2c master stretch function.
 *@return    none.
 */
static inline void i2c_master_stretch_dis(void)
{
    reg_i2c_ctrl2 &= ~(FLD_I2C_MASTER_STRETCH_EN);
}

/**
 * @brief      this function serves to:
 *             -# when the nack detect function is used on the master, need to enable;
 *             -# during the sending and receiving of data, if the master detects nack,turn on the function that sends the stop signal,
 *                otherwise, the stop signal cannot be sent, resulting in the busy state of the master,this interface is enabled by default on the i2c_master_init interface.
 * @return     none.
 */
static inline void i2c_master_detect_nack_en(void)
{
    reg_i2c_ctrl2 |= FLD_I2C_MASTER_NAK_STOP_EN;
}

/**
 * @brief      This function serves to disable i2c master nack stop function.
 * @return     none.
 */
static inline void i2c_master_detect_nack_dis(void)
{
    reg_i2c_ctrl2 &= ~(FLD_I2C_MASTER_NAK_STOP_EN);
}

/**
 * @brief     This function serves to configure the master i2c send and receive byte length,the hardware needs to know what the length is.
 * @param[in] len - the maximum transmission length of i2c is 0xffffff bytes, so dont'n over this length.
 * @return    none
 */
void i2c_master_set_len(unsigned int len);

/**
 *@brief     in slave ,judge whether the master is sending a read cmd or a write cmd.
 *@return    1:if return 1,it means that the slave is to get master read cmd.
 *           0:if return 0,it means that the slave is to get master write cmd.
 */
i2c_slave_wr_e i2c_slave_get_cmd(void);

/**
 * @brief     in master,judge whether master is to read or write
 * @return    1:if return 1,it means that the state of the master is read status.
 *            0:if return 0,it means that the state of the master is not read status.
 */
i2c_master_wr_e i2c_get_master_wr_status(void);

/**
 * @brief      The function of this interface is equivalent to that after the user finishes calling the write or read interface, the stop signal is not sent,
 *             and then the write or read command is executed again. The driver defaults that every write or read API will send a stop command at the end
 * @param[in]  en - Input parameters.Decide whether to disable the stop function after each write or read interface
 * @return     none
 */
void i2c_master_send_stop(unsigned char en);

/**
 * @brief      This function selects a pin port for I2C interface.
 * @param[in]  sda_pin - the pin port selected as I2C sda pin port.
 * @param[in]  scl_pin - the pin port selected as I2C scl pin port.
 * @return     none
 */
void i2c_set_pin(i2c_sda_pin_e sda_pin, i2c_scl_pin_e scl_pin);

/**
 * @brief      This function serves to enable i2c master function.
 * @return     none.
 */
void i2c_master_init(void);

/********************************************************************************************
 *****|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|*****
 *****|                             i2c1_m.h                                           |*****
 *****|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|*****
 ********************************************************************************************/

/**
 * @brief      The function of this API is to determine whether the bus is busy.
 * @return     1:Indicates that the bus is busy. 0:Indicates that the bus is free
 */
static inline _Bool i2c1_m_master_busy(void)
{
    return reg_i2c1_m_mst & FLD_I2C1_M_MST_BUSY;
}

/**
 * @brief      The function of this interface is equivalent to that after the user finishes calling the write or read interface, the stop signal is not sent,
 *             and then the write or read command is executed again. The driver defaults that every write or read API will send a stop command at the end
 * @param[in]  en - Input parameters.Decide whether to disable the stop function after each write or read interface
 * @return     none
 */
void i2c1_m_master_send_stop(unsigned char en);

/**
 * @brief      This function selects a pin port for I2C interface.
 * @param[in]  sda_pin - the pin port selected as I2C sda pin port.
 * @param[in]  scl_pin - the pin port selected as I2C scl pin port.
 * @return     none
 */
void i2c1_m_set_pin(i2c1_m_sda_pin_e sda_pin, i2c1_m_scl_pin_e scl_pin);

/**
 * @brief      This function serves to enable i2c1_m master function.
 * @return     none.
 */
void i2c1_m_master_init(void);

/**
 * @brief      This function serves to set the i2c1_m clock frequency.The i2c1_m clock is consistent with the system clock.
 * @param[in]  clock - the division factor of i2c1_m clock,
 *             i2c1_m frequency = system_clock / (4*clock).
 * @return     none
 */
void i2c1_m_set_master_clk(unsigned char clock);

/**
 *  @brief      This function serves to write a packet of data to the specified address of slave device
 *  @param[in]  id      - to set the slave ID.
 *  @param[in]  data_buf - the first SRAM buffer address to write data to slave in.
 *  @param[in]  data_len - the length of data master write to slave.
 *  @return     0:During sending id or data, the master receives the nack returned by the slave, and stops sending.
 *              1:Master sent data successfully.
 */
unsigned char i2c1_m_master_write(unsigned char id, unsigned char *data_buf, unsigned int data_len);

/**
 * @brief      This function serves to read a packet of data.
 * @param[in]  id      - to set the slave ID.
 * @param[in]  data_buf - the first address of SRAM buffer master store data in.
 * @param[in]  data_len - the length of data master read from slave.
 * @return     0:During sending id, the master receives the nack returned by the slave, and stops sending.
 *             1:Master receive data successfully.
 */
unsigned char i2c1_m_master_read(unsigned char id, unsigned char *data_buf, unsigned int data_len);

/**
 * @brief      This function serves to read a packet of data from the specified address of slave device.
 *             the master between writing and reading, it will be a restart signal,and after reading and writing, a stop signal is sent,
 *             but the stop configure,stays in its original state,when a nack exception signal is received, during exception handling, a stop signal will be sent.
 * @param[in]  id      - to set the slave ID.
 * @param[in]  wr_data - specifies the SRAM address of the slave to send data.
 * @param[in]  wr_len - the length of register. enum 0 or 1 or 2 or 3 based on the demand of i2c slave.
 * @param[in]  rd_data - the first address of SRAM buffer master store data in.
 * @param[in]  rd_len - the length of data master read from slave.
 * @return     0:During sending id+address, the master receives the nack returned by the slave, and stops sending.
 *             1:Master receive data successfully.
 */
unsigned char i2c1_m_master_write_read(unsigned char id, unsigned char *wr_data, unsigned int wr_len, unsigned char *rd_data, unsigned int rd_len);

#endif
