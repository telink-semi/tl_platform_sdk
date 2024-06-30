/********************************************************************************************************
 * @file    app_dma_llp.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2022
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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
#include "app_config.h"
#if !defined(MCU_CORE_B92)
#if(SPI_MODE == SPI_DMA_LLP_MODE)
/**********************************************************************************************************************
 *                                         SPI device  selection                                                     *
 *********************************************************************************************************************/
/*The master first generates data to the slave through the normal spi dma write interface function,
 * and then obtains the data through the normal spi dma read interface function,
 * comparing whether the sent data and the received data are the same.
 */
#define SPI_MASTER_DEVICE                   1
/*The slave side uses the spi's dma chain list mode hardware to automatically
 * receive the data sent by the master, and it also hardware automatically
 * sends the received data. 
 */
#define SPI_SLAVE_DEVICE                    2

#define SPI_DEVICE                     SPI_MASTER_DEVICE

/**********************************************************************************************************************
 *                                         SPI module selection                                                       *
 *********************************************************************************************************************/
/* Note:tl321x only supports gspi!!!*/
#define LSPI_MODULE                              0
#define GSPI_MODULE                              1

#define SPI_MODULE_SEL                          GSPI_MODULE
/**********************************************************************************************************************
 *                                         DMA chain mode
 *********************************************************************************************************************/

#define DMA_LLP_SINGLE_CHAIN      1
#define DMA_LLP_PINGPONG          2
#define DMA_LLP_MODE              DMA_LLP_PINGPONG

/**********************************************************************************************************************
 *                                         SPI multiple slave
 *********************************************************************************************************************/
#define SPI_CLK                             400000

/**********************************************************************************************************************
 *                                        SPI  pin  define                                                        *
 *********************************************************************************************************************/
#if (SPI_MODULE_SEL == GSPI_MODULE)
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin        = GPIO_FC_PA0,
    .spi_clk_pin        = GPIO_FC_PA3,
    .spi_mosi_io0_pin   = GPIO_FC_PB3,
    .spi_miso_io1_pin   = GPIO_FC_PB2,//3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin        = GPIO_FC_PB1,//quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin        = GPIO_FC_PB0,//quad  mode is required, otherwise it is NONE_PIN.
};
#endif
#if defined(MCU_CORE_TL751X)
gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin        = GSPI_CSN0_PA0_PIN,
    .spi_clk_pin        = GSPI_CLK_PA1_PIN,
    .spi_mosi_io0_pin   = GSPI_MOSI_PA2_PIN,
    .spi_miso_io1_pin   = GSPI_MISO_PA3_PIN,//3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin        = GSPI_IO2_PA4_PIN,//quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin        = GSPI_IO3_PA5_PIN,//quad  mode is required, otherwise it is NONE_PIN.
    .spi_io4_pin        = GSPI_IO4_PA6_PIN,//quad  mode is required, otherwise it is NONE_PIN.
    .spi_io5_pin        = GSPI_IO5_PB0_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_io6_pin        = GSPI_IO6_PB1_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_io7_pin        = GSPI_IO7_PB2_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_dm_pin         = GSPI_NONE_PIN,//opi psram is required,otherwise it is NONE_PIN.
};
#endif
#elif (SPI_MODULE_SEL == LSPI_MODULE)
#if defined(MCU_CORE_TL721X)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin        = LSPI_CSN_PE0_PIN,
    .spi_clk_pin        = LSPI_CLK_PE1_PIN,
    .spi_mosi_io0_pin   = LSPI_MOSI_IO0_PE2_PIN,
    .spi_miso_io1_pin   = LSPI_MISO_IO1_PE3_PIN,//3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin        = LSPI_IO2_PE4_PIN,//quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin        = LSPI_IO3_PE5_PIN,//quad  mode is required, otherwise it is NONE_PIN.
};
#endif
#if defined(MCU_CORE_TL751X)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin        = LSPI_CSN_PB0_PIN,
    .spi_clk_pin        = LSPI_CLK_PE0_PIN,
    .spi_mosi_io0_pin   = LSPI_MOSI_IO0_PE1_PIN,
    .spi_miso_io1_pin   = LSPI_MISO_IO1_PE2_PIN,//3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin        = LSPI_IO2_PE3_PIN,//quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin        = LSPI_IO3_PE4_PIN,//quad  mode is required, otherwise it is NONE_PIN.
    .spi_io4_pin        = LSPI_IO4_PE5_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_io5_pin        = LSPI_IO5_PE6_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_io6_pin        = LSPI_IO6_PE7_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_io7_pin        = LSPI_IO7_PF0_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_dm_pin         = LSPI_NONE_PIN,//opi psram is required,otherwise it is NONE_PIN.
};
#endif
#endif

/**********************************************************************************************************************
 *                                          dma  channel                                                      *
 *********************************************************************************************************************/
#define  SPI_TX_DMA_CHN  DMA1
#define  SPI_RX_DMA_CHN  DMA0
/**********************************************************************************************************************
*                                         SPI master setting                                                        *
*********************************************************************************************************************/
#if(SPI_DEVICE == SPI_MASTER_DEVICE)
/**********************************************************************************************************************
 *                                          global variable                                                   *
 *********************************************************************************************************************/
unsigned int i;
volatile unsigned char end_irq_flag = 0;
#define     DATA_BYTE_LEN     16
unsigned char spi_tx_buff[DATA_BYTE_LEN] __attribute__((aligned(4))) = {0x00};
unsigned char spi_rx_buff[DATA_BYTE_LEN+4] __attribute__((aligned(4))) = {0x00};
#if(DMA_LLP_MODE == DMA_LLP_PINGPONG)
volatile unsigned char tx_dma_flag = 0;
unsigned char spi_tx_buff1[DATA_BYTE_LEN] __attribute__((aligned(4))) = {0x00};
unsigned char spi_rx_buff1[DATA_BYTE_LEN+4] __attribute__((aligned(4))) = {0x00};
#endif

spi_wr_rd_config_t spi_b91m_slave_protocol_config = {
    .spi_io_mode        = SPI_SINGLE_MODE,/*IO mode set to SPI_3_LINE_MODE when SPI_3LINE_SLAVE.*/
    .spi_dummy_cnt      = 32,//B92 supports up to 32 clk cycle dummy, and TL751X,TL721X,TL321X supports up to 256 clk cycle dummy.
    .spi_cmd_en         = 1,
    .spi_addr_en        = 0,
    .spi_addr_len       = 0,//when spi_addr_en = 0,invalid set.
    .spi_cmd_fmt_en     = 0,//when spi_cmd_en = 0,invalid set.
    .spi_addr_fmt_en    = 0,//when spi_addr_en = 0,invalid set.
};

void user_init(void)
{
    delay_ms(200);
    gpio_output_en(LED1);       //enable output
    gpio_input_dis(LED1);       //disable input
    gpio_set_low_level(LED1);   //LED Off
    gpio_function_en(LED1);     //enable gpio
    gpio_output_en(LED2);       //enable output
    gpio_input_dis(LED2);       //disable input
    gpio_set_low_level(LED2);   //LED Off
    gpio_function_en(LED2);     //enable gpio

    for(i=0;i<DATA_BYTE_LEN;i++)
    {
        spi_tx_buff[i] = i;
#if(DMA_LLP_MODE == DMA_LLP_PINGPONG)
        spi_tx_buff1[i] = DATA_BYTE_LEN-i-1;
#endif
    }
    spi_master_init(SPI_MODULE_SEL, sys_clk.pll_clk * 1000000/SPI_CLK, SPI_MODE0);
    spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);//clr
    spi_set_irq_mask(SPI_MODULE_SEL, SPI_END_INT_EN);//endint_en
    spi_master_config_plus(SPI_MODULE_SEL, &spi_b91m_slave_protocol_config);
    spi_set_tx_dma_config(SPI_MODULE_SEL,SPI_TX_DMA_CHN);
    spi_set_master_rx_dma_config(SPI_MODULE_SEL,SPI_RX_DMA_CHN);
#if (SPI_MODULE_SEL == GSPI_MODULE)
    gspi_set_pin(&gspi_pin_config);
    plic_interrupt_enable(IRQ_GSPI);
#elif(SPI_MODULE_SEL == LSPI_MODULE)
    lspi_set_pin(&lspi_pin_config);
    plic_interrupt_enable(IRQ_LSPI);
#endif
    core_interrupt_enable();
}

void main_loop (void)
{
#if(DMA_LLP_MODE == DMA_LLP_SINGLE_CHAIN)
    spi_master_write_dma_plus(SPI_MODULE_SEL,SPI_WRITE_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_DUMMY_WRITE);
#elif(DMA_LLP_MODE == DMA_LLP_PINGPONG)
    spi_master_write_dma_plus(SPI_MODULE_SEL,SPI_WRITE_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_DUMMY_WRITE);
    while(!(end_irq_flag == 1));//Wait for the spi to finish sending the first packet of data.
    spi_master_write_dma_plus(SPI_MODULE_SEL,SPI_WRITE_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)spi_tx_buff1, sizeof(spi_tx_buff1), SPI_MODE_WR_DUMMY_WRITE);
#endif


#if(DMA_LLP_MODE == DMA_LLP_SINGLE_CHAIN)
    while(!(end_irq_flag == 1));//Wait for spi transmission end interrupt.
    spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)(spi_rx_buff+4), DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    while(!(end_irq_flag == 2));//Wait spi transmission complete interrupt.
#elif(DMA_LLP_MODE == DMA_LLP_PINGPONG)
    while(!(end_irq_flag == 2));//Wait for spi to finish sending data.
    spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)(spi_rx_buff+4), DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    while(!(end_irq_flag == 3));//Wait for spi to finish receiving the first packet.
    spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)(spi_rx_buff1+4), DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    while(!(end_irq_flag == 4));//Wait for spi to finish receiving the second packet.
#endif

#if(DMA_LLP_MODE == DMA_LLP_SINGLE_CHAIN)
    if(end_irq_flag == 2)
    {
        for(i=0;i<DATA_BYTE_LEN;i++)
        {
            if(spi_tx_buff[i] != (spi_rx_buff[i+4]))
            {
                gpio_set_high_level(LED2);//LED on indicate data error
                while(1);
            }
        }
        end_irq_flag = 0;
    }
    spi_tx_buff[0]++;
#elif(DMA_LLP_MODE == DMA_LLP_PINGPONG)
    if(end_irq_flag == 4)
    {
        for(i=0;i<DATA_BYTE_LEN;i++)
        {
            if((spi_tx_buff[i] != (spi_rx_buff[i+4]))&&(spi_tx_buff1[i] != (spi_rx_buff1[i+4])))
            {
                gpio_set_high_level(LED2);//LED on indicate data error
                while(1);
            }
        }
        spi_tx_buff[0]++;
        spi_tx_buff1[DATA_BYTE_LEN-1]++;
        end_irq_flag = 0;
    }
#endif
    delay_ms(200);
    gpio_toggle(LED1);
}

#if(SPI_MODULE_SEL == GSPI_MODULE)
_attribute_ram_code_sec_noinline_ void gspi_irq_handler(void)
#elif(SPI_MODULE_SEL == LSPI_MODULE)
_attribute_ram_code_sec_noinline_ void lspi_irq_handler(void)
#endif
{
    if(spi_get_irq_status(SPI_MODULE_SEL,SPI_END_INT))
    {
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);
        end_irq_flag++;
    }
}

#if(SPI_MODULE_SEL == GSPI_MODULE)
PLIC_ISR_REGISTER(gspi_irq_handler, IRQ_GSPI)
#elif(SPI_MODULE_SEL == LSPI_MODULE)
PLIC_ISR_REGISTER(lspi_irq_handler, IRQ_LSPI)
#endif

#elif(SPI_DEVICE == SPI_SLAVE_DEVICE)
/**********************************************************************************************************************
 *                                          global variable                                                         *
 *********************************************************************************************************************/
#define DATA_BYTE_LEN       16
unsigned char spi_slave_rx_buff[DATA_BYTE_LEN+4] __attribute__((aligned(4))) = {0x00};
#if(DMA_LLP_MODE == DMA_LLP_PINGPONG)
dma_chain_config_t rx_dma_list[2];
dma_chain_config_t tx_dma_list[2];
volatile unsigned char tx_dma_flag = 0;
unsigned char spi_slave_rx_buff1[DATA_BYTE_LEN+4] __attribute__((aligned(4))) = {0x00};
#endif
void user_init(void)
{
    gpio_output_en(LED1);       //enable output
    gpio_input_dis(LED1);       //disable input
    gpio_set_low_level(LED1);   //LED Off
    gpio_function_en(LED1);     //enable gpio
    gpio_output_en(LED2);       //enable output
    gpio_input_dis(LED2);       //disable input
    gpio_set_low_level(LED2);   //LED Off
    gpio_function_en(LED2);     //enable gpio

    spi_slave_init(SPI_MODULE_SEL, SPI_MODE0);
    //TL751X, TL721X supports up to 256 clk cycle dummy.
    spi_set_dummy_cnt(SPI_MODULE_SEL, 32);
    spi_set_tx_dma_config(SPI_MODULE_SEL, SPI_TX_DMA_CHN);
    spi_set_slave_rx_dma_config(SPI_MODULE_SEL, SPI_RX_DMA_CHN);
#if (SPI_MODULE_SEL == GSPI_MODULE)
    gspi_set_pin(&gspi_pin_config);
#elif(SPI_MODULE_SEL == LSPI_MODULE)
    lspi_set_pin(&lspi_pin_config);
#endif
#if(DMA_LLP_MODE == DMA_LLP_SINGLE_CHAIN)
    spi_slave_rx_dma_chain_init(SPI_MODULE_SEL,SPI_RX_DMA_CHN,spi_slave_rx_buff+4,DATA_BYTE_LEN);
    spi_slave_tx_dma_chain_init(SPI_MODULE_SEL,SPI_TX_DMA_CHN,spi_slave_rx_buff+4,DATA_BYTE_LEN);
#elif(DMA_LLP_MODE == DMA_LLP_PINGPONG)
    spi_set_slave_rx_dma_chain_llp(SPI_MODULE_SEL, SPI_RX_DMA_CHN, spi_slave_rx_buff+4, DATA_BYTE_LEN, &rx_dma_list[0]);
    spi_rx_dma_add_list_element(SPI_MODULE_SEL, SPI_RX_DMA_CHN, &rx_dma_list[0], &rx_dma_list[1], (unsigned char *)(spi_slave_rx_buff1+4), DATA_BYTE_LEN);
    spi_rx_dma_add_list_element(SPI_MODULE_SEL, SPI_RX_DMA_CHN, &rx_dma_list[1], &rx_dma_list[0], (unsigned char *)(spi_slave_rx_buff+4), DATA_BYTE_LEN);
    dma_chn_en(SPI_RX_DMA_CHN);

    spi_set_slave_tx_dma_chain_llp(SPI_MODULE_SEL, SPI_TX_DMA_CHN, spi_slave_rx_buff+4, DATA_BYTE_LEN, &tx_dma_list[0]);
    spi_tx_dma_add_list_element(SPI_MODULE_SEL, SPI_TX_DMA_CHN, &tx_dma_list[0], &tx_dma_list[1], (unsigned char *)(spi_slave_rx_buff1+4), DATA_BYTE_LEN);
    spi_tx_dma_add_list_element(SPI_MODULE_SEL, SPI_TX_DMA_CHN, &tx_dma_list[1], &tx_dma_list[0], (unsigned char *)(spi_slave_rx_buff+4), DATA_BYTE_LEN);
    dma_chn_en(SPI_TX_DMA_CHN);
#endif
}

void main_loop (void)
{
    delay_ms(200);
    gpio_toggle(LED1);
}
#endif
#endif
#endif


