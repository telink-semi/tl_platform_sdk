/********************************************************************************************************
 * @file    app_dma.c
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

/**
   @verbatim
   ===============================================================================
                        ##### how to test demo #####
   ===============================================================================
   master and slave end hardware connection:scl <-> scl,sda <-> sda,gnd <-> gnd,during the test, power on the slave and then the master.
   (+) I2C_DEVICE == I2C_MASTER_DEVICE(B91/B92/TL7518/TL721X)
       the bin is burned into the master, and the data flow situation:
       the master writes the data to the slave end, and then reads back to determine whether the written data is consistent with the read data;
   (+) I2C_DEVICE == I2C_SLAVE_DEVICE(B91/B92/TL7518/TL721X)
      (+) I2C_STRETCH_MODE == I2C_STRETCH_DIS(B91/B92/TL7518/TL721X)
           the bin is burned into the slave. data flow condition:
           the slave receives data from the master and then writes the received data back to the master.
      (+) I2C_STRETCH_MODE == I2C_STRETCH_EN(B92/TL7518/TL721X)
          (+)Another mechanism for communicating with the master,the bin is burned into the slave. data flow condition:
             the slave receives data from the master and then writes the received data back to the master.
   @endverbatim
 */
#include "app_config.h"

#if(I2C_MASTER_WRITE_READ_MODE == I2C_MASTER_WRITE_READ_DMA)
#define  I2C_TX_DMA_CHN             DMA1
#define  I2C_RX_DMA_CHN             DMA0

/************************************************  i2c_mode  **********************************/
#define  I2C_MASTER_DEVICE          1   //i2c master demo
#define  I2C_SLAVE_DEVICE           2   //i2c slave demo
#define  I2C_DEVICE                 I2C_MASTER_DEVICE

#if(I2C_DEVICE == I2C_MASTER_DEVICE)
#define  I2C_CLK_SPEED              200000 //i2c clock 200K.
/*In B91 and B92, the length of data received by the slave should not exceed the buffer size to avoid potential overflow risks.
 *In TL7518 and TL721X, the received data length will not result in a buffer address overflow. Refer to the detailed interface: i2c_slave_set_rx_dma().*/
#define  BUFF_DATA_LEN_DMA          32
#if !defined(MCU_CORE_B91)
volatile unsigned char i2c_master_read_nack_cnt=0;
volatile unsigned char i2c_master_write_nack_cnt=0;
#endif
unsigned char i2c_tx_buff[BUFF_DATA_LEN_DMA] __attribute__((aligned(4)))= {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                                                                           0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
                                                                           0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
                                                                           0x1F, 0x20};
unsigned char i2c_rx_buff[BUFF_DATA_LEN_DMA] __attribute__((aligned(4)));
#elif(I2C_DEVICE == I2C_SLAVE_DEVICE)

#if !defined(MCU_CORE_B91)
/*If the slave supports stretch when tx_fifo is 0, and the master supports stretch, then the slave can configure tx dma by referring to the demo with stretch enabled,
 *otherwise, refer to the demo of stretch dis. when the master read, the slave needs to fill data in advance.*/
#define  I2C_STRETCH_EN             1
#define  I2C_STRETCH_DIS            2
#define  I2C_STRETCH_MODE           I2C_STRETCH_EN
#endif

#define  BUFF_DATA_LEN_DMA          32

#if defined(MCU_CORE_B91)
unsigned char i2c_rx_buff[BUFF_DATA_LEN_DMA] __attribute__((aligned(4)));
#else
unsigned char i2c_rx_buff[BUFF_DATA_LEN_DMA+4] __attribute__((aligned(4)));
#endif
/* B91 DMA_REV_LEN configuration is consistent with the transmission length.
 * In B92, when DMA length is configured to the maximum, DMA has function write_num.
 * In TL7518 and TL721X, the DMA write_num function is unrelated to DMA_REV_LEN, but it needs to be aligned with 4.*/
#if defined(MCU_CORE_B91)
#define  DMA_REV_LEN                BUFF_DATA_LEN_DMA
#elif defined(MCU_CORE_B92)
#define  DMA_REV_LEN                0xFFFFFC
#else
#define  DMA_REV_LEN                32
#endif
#endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);       //enable output
    gpio_input_dis(LED1);       //disable input
    gpio_function_en(LED2);
    gpio_output_en(LED2);       //enable output
    gpio_input_dis(LED2);       //disable input
    gpio_function_en(LED3);
    gpio_output_en(LED3);       //enable output
    gpio_input_dis(LED3);       //disable input
    gpio_function_en(LED4);
    gpio_output_en(LED4);       //enable output
    gpio_input_dis(LED4);       //disable input
    i2c_set_pin(I2C_GPIO_SDA_PIN,I2C_GPIO_SCL_PIN);
    i2c_set_tx_dma_config(I2C_TX_DMA_CHN);
    i2c_set_rx_dma_config(I2C_RX_DMA_CHN);
#if(I2C_DEVICE == I2C_MASTER_DEVICE)
    i2c_master_init();
    i2c_set_master_clk((unsigned char)(sys_clk.pclk*1000*1000/(4*I2C_CLK_SPEED)));//set i2c frequency 200K.
#if !defined(MCU_CORE_B91)
    i2c_set_irq_mask(I2C_MASTER_NAK_MASK);
    plic_interrupt_enable(IRQ_I2C);
    core_interrupt_enable();
#endif
#elif(I2C_DEVICE == I2C_SLAVE_DEVICE)
    i2c_slave_init(0x5a);
#if(!defined(MCU_CORE_B91) &&(I2C_STRETCH_MODE == I2C_STRETCH_EN))
    i2c_slave_stretch_en();
    i2c_set_irq_mask(I2C_RX_END_MASK|I2C_SLAVE_WR_MASK);
#elif (defined(MCU_CORE_B91)||(I2C_STRETCH_MODE == I2C_STRETCH_DIS))
#if defined(MCU_CORE_B91)
    i2c_clr_irq_status(I2C_TX_DONE_CLR);
    i2c_set_irq_mask(I2C_TX_DONE_MASK);
#else
    i2c_set_irq_mask(I2C_TX_END_MASK);
#endif
    dma_set_irq_mask(I2C_RX_DMA_CHN, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
#endif

    plic_interrupt_enable(IRQ_I2C);
    core_interrupt_enable();

/*
 * Differences in DMA related configurations among chips::
 * B91: the DMA receive length must be set to be the same as the length of data sent by the master;
 * B92: 1.If the receiving length of DMA is set to max value:0xfffffc byte, and write_num is turned on,
 *        then The length of the data received by dma will be written to the first four bytes of addr;
 *      2.If the receiving length information of DMA is set to less than max value:0xfffffc byte, even if write_num is turned on,
 *         the length of data received by DMA will not be written to the first four bytes of addr;
 *      in b92 demo,it choose that the receiving length of DMA be set to the maximum value of the scenario.
 * TL7518 and TL721X:
 *      1.The receiving length of DMA can be any length aligned with 4 bytes.
 *      2.If write_num is turned on, the length of the data received by DMA will be written into the first four bytes of addr.
 */
#if defined(MCU_CORE_B91)
    i2c_slave_set_rx_dma((unsigned char*)(i2c_rx_buff),DMA_REV_LEN);
#else
    i2c_slave_set_rx_dma((unsigned char*)(i2c_rx_buff+4),DMA_REV_LEN);
#endif
#endif
}

void main_loop(void)
{
#if(I2C_DEVICE == I2C_MASTER_DEVICE)
#if defined(MCU_CORE_B91)
    delay_ms(10);
    i2c_master_write_dma(0x5a,(unsigned char *)i2c_tx_buff,BUFF_DATA_LEN_DMA);
    while(i2c_master_busy());
    delay_ms(10);
    i2c_master_read_dma(0x5a,(unsigned char *)i2c_rx_buff,BUFF_DATA_LEN_DMA);
    while(i2c_master_busy());

    for(volatile unsigned int i=0;i<BUFF_DATA_LEN_DMA;i++)
    {
        if( i2c_rx_buff[i] != i2c_tx_buff[i] )
        {
            gpio_toggle(LED2);
            delay_ms(50);
        }
    }
    i2c_tx_buff[0]++;
    gpio_toggle(LED1);
#else
    /*  The data length ranges from 1 to 32 bytes.
     *  After each data transmission, the device promptly receives a response from the slave device and compares it with the sent data.
     *  If there's an error, LED2 stays constant.*/
    for (volatile unsigned int packetSize = 1; packetSize <= BUFF_DATA_LEN_DMA; packetSize++)
    {
        delay_ms(100);
        i2c_master_write_dma(0x5a, (unsigned char *)i2c_tx_buff, packetSize);
        while (i2c_master_busy());
        delay_ms(10);
        i2c_master_read_dma(0x5a, (unsigned char *)i2c_rx_buff, packetSize);
        while (i2c_master_busy());
        for(volatile unsigned int i=0;i<packetSize;i++)
        {
            if(i2c_rx_buff[i] != i2c_tx_buff[i])
            {
                gpio_set_high_level(LED2);
                delay_ms(50);
            }
        }
        gpio_toggle(LED1);
    }
#endif
#endif
}

/* Enabling the i2c tc_mask dma interrupt, after the DMA completes the transfer of received data, the TC interrupt will be triggered.
 * when enabling dma transfers i2c receiving data, the internal working principle: when the i2c fifo each reach 4,
 * will send the dma requests, to move data from the fifo, if finally fifo data less than four,
 * through the i2c stop signal sends a request to the dma,move the fifo data away.*/
#if(I2C_DEVICE == I2C_SLAVE_DEVICE)
#if (defined(MCU_CORE_B91)||(I2C_STRETCH_MODE == I2C_STRETCH_DIS))
void dma_irq_handler(void)
{
    if(dma_get_tc_irq_status(BIT(I2C_RX_DMA_CHN)))
    {
        dma_clr_tc_irq_status(BIT(I2C_RX_DMA_CHN));
#if defined(MCU_CORE_B91)
        i2c_slave_set_tx_dma((unsigned char*)(i2c_rx_buff),BUFF_DATA_LEN_DMA);
#else
        i2c_slave_set_tx_dma((unsigned char*)(i2c_rx_buff+4),*(unsigned int *)i2c_rx_buff);
#endif
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
#endif
#endif

/* When the slave parsing ID does not match, the slave will return nack, but it will still receive the data sent from the master,
 * enter the rx_buff and rx_done interrupt normally, and reply nack.*/
void i2c_irq_handler(void)
{
#if(I2C_DEVICE==I2C_MASTER_DEVICE)
#if !defined(MCU_CORE_B91)
    if(i2c_get_irq_status(I2C_MASTER_NAK_STATUS))
    {
        i2c_clr_irq_status(I2C_MASTER_NAK_STATUS);
        reg_i2c_sct1 = (FLD_I2C_LS_STOP);
        while(i2c_master_busy());//wait for the STOP signal to finish sending.
        dma_chn_dis(I2C_TX_DMA_CHN);
        /* In B92, TL7518, and TL721X, when sending data in the master, whether in the ID stage or data stage, if NACK signal is received,
         * the processing in the interrupt is disable TX_DMA, clear FIFO, stop the transmission of data, record the number of exceptions,
         * after interrupt, and process the following operations.*/
        if(I2C_MASTER_WRITE == i2c_get_master_wr_status())
        {
            i2c_clr_irq_status(I2C_TX_BUF_STATUS);
            i2c_master_write_nack_cnt++;
        }
        /* When receiving data in the master, nack can be received only in the id stage,
         * After receiving nack, the rx_dma shall be disable to stop the data receiving and record the abnormal count,
         * If it is in the data stage the slave is abnormal, the master will not reply nack and detect abnormal problems,
         * so it continues to receive the data 0xFF.When an exception occurs, the data sent in the main_loop does not match the data received.*/
        if(I2C_MASTER_READ == i2c_get_master_wr_status())
        {
            i2c_master_read_nack_cnt++;
        }
     }
#endif
#endif
#if(I2C_DEVICE == I2C_SLAVE_DEVICE)
#if defined(MCU_CORE_B91)
    if(i2c_get_irq_status(I2C_TXDONE_STATUS))
    {
        i2c_clr_irq_status(I2C_TX_DONE_CLR);
        i2c_slave_set_rx_dma((unsigned char*)(i2c_rx_buff),DMA_REV_LEN);
    }
#else
#if(I2C_STRETCH_MODE == I2C_STRETCH_DIS)
    if(i2c_get_irq_status(I2C_TX_END_STATUS))
    {
        i2c_clr_irq_status(I2C_TX_END_STATUS);
        i2c_slave_set_rx_dma((unsigned char*)(i2c_rx_buff+4),DMA_REV_LEN);
    }

#elif(I2C_STRETCH_MODE == I2C_STRETCH_EN)
    if(i2c_get_irq_status(I2C_SLAVE_WR_STATUS))
    {
        i2c_clr_irq_status(I2C_SLAVE_WR_STATUS);
        if(I2C_SLAVE_WRITE == i2c_slave_get_cmd())
        {
         i2c_slave_set_tx_dma((unsigned char*)(i2c_rx_buff+4),*(unsigned int *)i2c_rx_buff);
        }
    }
    if((i2c_get_irq_status(I2C_RX_END_STATUS)))
    {
        i2c_clr_irq_status(I2C_RX_END_STATUS);
        i2c_slave_set_rx_dma((unsigned char*)(i2c_rx_buff+4),DMA_REV_LEN);
    }
#endif
#endif
#endif
}
PLIC_ISR_REGISTER(i2c_irq_handler, IRQ_I2C)
#endif


