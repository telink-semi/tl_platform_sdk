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
    #if (SPI_MODE == SPI_DMA_LLP_MODE)
        /**********************************************************************************************************************
 *                                         SPI device  selection                                                     *
 *********************************************************************************************************************/
        /*The master first generates data to the slave through the normal spi dma write interface function,
 * and then obtains the data through the normal spi dma read interface function,
 * comparing whether the sent data and the received data are the same.
 */
        #define SPI_MASTER_DEVICE 1
        /*The slave side uses the spi's dma chain list mode hardware to automatically
 * receive the data sent by the master, and it also hardware automatically
 * sends the received data. 
 */
        #define SPI_SLAVE_DEVICE 2

        #define SPI_DEVICE       SPI_MASTER_DEVICE

        /**********************************************************************************************************************
 *                                         SPI data mode selection                                                *
 *********************************************************************************************************************/
        /* Note:ONLY_DATA_SLAVE_SEND_MODE only tl322x supports!!!*/
        #define ONLY_DATA_SLAVE_SEND_MODE    1
        #define ONLY_DATA_SLAVE_REVEICE_MODE 2 // Only data is available for spi communication
        #define NORMAL_MODE                  3 // Spi communication format: cmd+dummy+data


        #define DATA_MODE                    NORMAL_MODE

        /**********************************************************************************************************************
 *                                         SPI module selection                                                       *
 *********************************************************************************************************************/
        /* Note:tl321x only supports gspi!!!*/
        #ifndef MCU_CORE_TL321X
            #define LSPI_MODULE 0
        #endif
        #define GSPI_MODULE 1
        #if defined(MCU_CORE_TL322X)
            #define GSPI1_MODULE 2
            #define GSPI2_MODULE 3
            #define GSPI3_MODULE 4
            #define GSPI4_MODULE 5
        #endif

        #if defined(MCU_CORE_TL321X)
            #define SPI_MODULE_SEL GSPI_MODULE
        #else
            #define SPI_MODULE_SEL LSPI_MODULE
        #endif

    /**********************************************************************************************************************
 *                                         DMA chain mode
 *********************************************************************************************************************/

        #define DMA_LLP_SINGLE_CHAIN 1
        #define DMA_LLP_PINGPONG     2
        #define DMA_LLP_MODE         DMA_LLP_PINGPONG

        /**********************************************************************************************************************
 *                                         SPI multiple slave
 *********************************************************************************************************************/
        #define SPI_CLK 4000000

        /**********************************************************************************************************************
 *                                        SPI  pin  define                                                        *
 *********************************************************************************************************************/
        #if (SPI_MODULE_SEL == GSPI_MODULE)
            #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GPIO_FC_PA3, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PA4, //quad  mode is required, otherwise it is NONE_PIN.
};
            #endif

            #if defined(MCU_CORE_TL751X)
gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0,   //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GPIO_FC_PE2,   //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PE3,   //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io4_pin      = GPIO_FC_PE4,   //octal mode is required, otherwise it is NONE_PIN.
    .spi_io5_pin      = GPIO_FC_PE5,   //octal mode is required, otherwise it is NONE_PIN.
    .spi_io6_pin      = GPIO_FC_PE6,   //octal mode is required, otherwise it is NONE_PIN.
    .spi_io7_pin      = GPIO_FC_PE7,   //octal mode is required, otherwise it is NONE_PIN.
    .spi_dm_pin       = GPIO_NONE_PIN, //opi psram is required,otherwise it is NONE_PIN.
};
            #endif

            #if defined(MCU_CORE_TL7518)
gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin      = GSPI_CSN0_PA0_PIN,
    .spi_clk_pin      = GSPI_CLK_PA1_PIN,
    .spi_mosi_io0_pin = GSPI_MOSI_PA2_PIN,
    .spi_miso_io1_pin = GSPI_MISO_PA3_PIN, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GSPI_IO2_PA4_PIN,  //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GSPI_IO3_PA5_PIN,  //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io4_pin      = GSPI_IO4_PA6_PIN,  //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io5_pin      = GSPI_IO5_PB0_PIN,  //octal mode is required, otherwise it is NONE_PIN.
    .spi_io6_pin      = GSPI_IO6_PF3_PIN,  //octal mode is required, otherwise it is NONE_PIN.
    .spi_io7_pin      = GSPI_IO7_PF4_PIN,  //octal mode is required, otherwise it is NONE_PIN.
    .spi_dm_pin       = GSPI_NONE_PIN,     //opi psram is required,otherwise it is NONE_PIN.
};
            #endif
        #endif

        #if defined(MCU_CORE_TL322X)
            #if (SPI_MODULE_SEL == GSPI1_MODULE)
gspi_pin_config_t gspi1_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GPIO_FC_PA3, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PA4, //quad  mode is required, otherwise it is NONE_PIN.
};
            #endif
            #if (SPI_MODULE_SEL == GSPI2_MODULE)
gspi_pin_config_t gspi2_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GPIO_FC_PA3, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PA4, //quad  mode is required, otherwise it is NONE_PIN.
};
            #endif
            #if (SPI_MODULE_SEL == GSPI3_MODULE)
gspi_pin_config_t gspi3_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GPIO_FC_PA3, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PA4, //quad  mode is required, otherwise it is NONE_PIN.
};
            #endif
            #if (SPI_MODULE_SEL == GSPI4_MODULE)
gspi_pin_config_t gspi4_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GPIO_FC_PA3, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PA4, //quad  mode is required, otherwise it is NONE_PIN.
};
            #endif
        #endif
        #ifndef MCU_CORE_TL321X
            #if (SPI_MODULE_SEL == LSPI_MODULE)
                #if defined(MCU_CORE_TL721X)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin      = LSPI_CSN_PE0_PIN,
    .spi_clk_pin      = LSPI_CLK_PE1_PIN,
    .spi_mosi_io0_pin = LSPI_MOSI_IO0_PE2_PIN,
    .spi_miso_io1_pin = LSPI_MISO_IO1_PE3_PIN, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = LSPI_IO2_PE4_PIN,      //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = LSPI_IO3_PE5_PIN,      //quad  mode is required, otherwise it is NONE_PIN.
};
                #endif

                #if defined(MCU_CORE_TL322X)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GPIO_FC_PA3, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PA4, //quad  mode is required, otherwise it is NONE_PIN.
};
                #endif

                #if defined(MCU_CORE_TL751X)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0,   //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = GPIO_FC_PE2,   //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PE3,   //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io4_pin      = GPIO_FC_PE4,   //octal mode is required, otherwise it is NONE_PIN.
    .spi_io5_pin      = GPIO_FC_PE5,   //octal mode is required, otherwise it is NONE_PIN.
    .spi_io6_pin      = GPIO_FC_PE6,   //octal mode is required, otherwise it is NONE_PIN.
    .spi_io7_pin      = GPIO_FC_PE7,   //octal mode is required, otherwise it is NONE_PIN.
    .spi_dm_pin       = GPIO_NONE_PIN, //opi psram is required,otherwise it is NONE_PIN.
};
                #endif

                #if defined(MCU_CORE_TL7518)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin      = LSPI_CSN_PB0_PIN,
    .spi_clk_pin      = LSPI_CLK_PE0_PIN,
    .spi_mosi_io0_pin = LSPI_MOSI_IO0_PE1_PIN,
    .spi_miso_io1_pin = LSPI_MISO_IO1_PE2_PIN, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = LSPI_IO2_PE3_PIN,      //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = LSPI_IO3_PE4_PIN,      //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io4_pin      = LSPI_IO4_PE5_PIN,      //octal mode is required, otherwise it is NONE_PIN.
    .spi_io5_pin      = LSPI_IO5_PE6_PIN,      //octal mode is required, otherwise it is NONE_PIN.
    .spi_io6_pin      = LSPI_IO6_PE7_PIN,      //octal mode is required, otherwise it is NONE_PIN.
    .spi_io7_pin      = LSPI_IO7_PF0_PIN,      //octal mode is required, otherwise it is NONE_PIN.
    .spi_dm_pin       = LSPI_NONE_PIN,         //opi psram is required,otherwise it is NONE_PIN.
};
                #endif
            #endif
        #endif

        /**********************************************************************************************************************
 *                                          dma  channel                                                      *
 *********************************************************************************************************************/
        #define SPI_TX_DMA_CHN DMA1
        #define SPI_RX_DMA_CHN DMA0
        /**********************************************************************************************************************
*                                         SPI master setting                                                        *
*********************************************************************************************************************/
        #if (SPI_DEVICE == SPI_MASTER_DEVICE)
/**********************************************************************************************************************
 *                                          global variable                                                   *
 *********************************************************************************************************************/
unsigned int           i;
volatile unsigned char end_irq_flag = 0;
            #define DATA_BYTE_LEN 16
unsigned char spi_tx_buff[DATA_BYTE_LEN] __attribute__((aligned(4)))     = {0x00};
unsigned char spi_rx_buff[DATA_BYTE_LEN + 4] __attribute__((aligned(4))) = {0x00};
            #if (DMA_LLP_MODE == DMA_LLP_PINGPONG)
volatile unsigned char tx_dma_flag                                                 = 0;
unsigned char          spi_tx_buff1[DATA_BYTE_LEN] __attribute__((aligned(4)))     = {0x00};
unsigned char          spi_rx_buff1[DATA_BYTE_LEN + 4] __attribute__((aligned(4))) = {0x00};
            #endif

            #if (DATA_MODE == NORMAL_MODE)
spi_wr_rd_config_t spi_b91m_slave_protocol_config = {
    .spi_io_mode   = SPI_SINGLE_MODE, /*IO mode set to SPI_3_LINE_MODE when SPI_3LINE_SLAVE.*/
    .spi_dummy_cnt = 32,              //B92 supports up to 32 clk cycle dummy, and TL751X,TL7518,TL721X,TL321X,TL322X supports up to 256 clk cycle dummy.
                #if defined(MCU_CORE_TL322X)
    .spi_dummy_hold = 0,
                #endif
    .spi_cmd_en      = 1,
    .spi_addr_en     = 0,
    .spi_addr_len    = 0, //when spi_addr_en = 0,invalid set.
    .spi_cmd_fmt_en  = 0, //when spi_cmd_en = 0,invalid set.
    .spi_addr_fmt_en = 0, //when spi_addr_en = 0,invalid set.
};
            #elif (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE || DATA_MODE == ONLY_DATA_SLAVE_REVEICE_MODE)
spi_wr_rd_config_t spi_b91m_slave_protocol_config = {
    .spi_io_mode   = SPI_SINGLE_MODE, /*IO mode set to SPI_3_LINE_MODE when SPI_3LINE_SLAVE.*/
    .spi_dummy_cnt = 0,               //B92 supports up to 32 clk cycle dummy, and TL751X,TL7518,TL721X,TL321X,TL322X supports up to 256 clk cycle dummy.
                #if defined(MCU_CORE_TL322X)
    .spi_dummy_hold = 0,
                #endif
    .spi_cmd_en      = 0,
    .spi_addr_en     = 0,
    .spi_addr_len    = 0, //when spi_addr_en = 0,invalid set.
    .spi_cmd_fmt_en  = 0, //when spi_cmd_en = 0,invalid set.
    .spi_addr_fmt_en = 0, //when spi_addr_en = 0,invalid set.
};
            #endif
void user_init(void)
{
    delay_ms(200);
    gpio_output_en(LED1);     //enable output
    gpio_input_dis(LED1);     //disable input
    gpio_set_low_level(LED1); //LED Off
    gpio_function_en(LED1);   //enable gpio
    gpio_output_en(LED2);     //enable output
    gpio_input_dis(LED2);     //disable input
    gpio_set_low_level(LED2); //LED Off
    gpio_function_en(LED2);   //enable gpio

    for (i = 0; i < DATA_BYTE_LEN; i++) {
        spi_tx_buff[i] = i;
            #if (DMA_LLP_MODE == DMA_LLP_PINGPONG)
        spi_tx_buff1[i] = DATA_BYTE_LEN - i - 1;
            #endif
    }
            #if defined(MCU_CORE_TL7518) || defined(MCU_CORE_TL751X)
    spi_master_init(SPI_MODULE_SEL, SRC_CLK_XTAL_48M, SRC_CLK_XTAL_48M / SPI_CLK, SPI_MODE0);
            #else
    spi_master_init(SPI_MODULE_SEL, sys_clk.pll_clk * 1000000 / SPI_CLK, SPI_MODE0);
            #endif
    spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);  //clr
    spi_set_irq_mask(SPI_MODULE_SEL, SPI_END_INT_EN); //endint_en
    spi_master_config_plus(SPI_MODULE_SEL, &spi_b91m_slave_protocol_config);
    spi_set_tx_dma_config(SPI_MODULE_SEL, SPI_TX_DMA_CHN);
    spi_set_master_rx_dma_config(SPI_MODULE_SEL, SPI_RX_DMA_CHN);

            #if (SPI_MODULE_SEL == GSPI_MODULE)
    gspi_set_pin(&gspi_pin_config);
    plic_interrupt_enable(IRQ_GSPI);
            #endif
            #if defined(MCU_CORE_TL322X)
                #if (SPI_MODULE_SEL == GSPI1_MODULE)
    gspi1_set_pin(&gspi1_pin_config);
    plic_interrupt_enable(IRQ_GSPI1);
                #endif
                #if (SPI_MODULE_SEL == GSPI2_MODULE)
    gspi2_set_pin(&gspi2_pin_config);
    plic_interrupt_enable(IRQ_GSPI2);
                #endif
                #if (SPI_MODULE_SEL == GSPI3_MODULE)
    gspi3_set_pin(&gspi3_pin_config);
    plic_interrupt_enable(IRQ_GSPI3);
                #endif
                #if (SPI_MODULE_SEL == GSPI4_MODULE)
    gspi4_set_pin(&gspi4_pin_config);
    plic_interrupt_enable(IRQ_GSPI4);
                #endif
            #endif
            #ifndef MCU_CORE_TL321X
                #if (SPI_MODULE_SEL == LSPI_MODULE)
    lspi_set_pin(&lspi_pin_config);
    plic_interrupt_enable(IRQ_LSPI);
                #endif
            #endif
    core_interrupt_enable();
}

void main_loop(void)
{
            #if (DMA_LLP_MODE == DMA_LLP_SINGLE_CHAIN)
    spi_master_write_dma_plus(SPI_MODULE_SEL, SPI_WRITE_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_DUMMY_WRITE);
            #elif (DMA_LLP_MODE == DMA_LLP_PINGPONG)
                #if (DATA_MODE == NORMAL_MODE)
    spi_master_write_dma_plus(SPI_MODULE_SEL, SPI_WRITE_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_DUMMY_WRITE);
    while (!(end_irq_flag == 1))
        ; //Wait for the spi to finish sending the first packet of data.
    spi_master_write_dma_plus(SPI_MODULE_SEL, SPI_WRITE_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)spi_tx_buff1, sizeof(spi_tx_buff1), SPI_MODE_WR_DUMMY_WRITE);
                #elif (DATA_MODE == ONLY_DATA_SLAVE_REVEICE_MODE)
    spi_master_write_dma_plus(SPI_MODULE_SEL, 0, (unsigned int)NULL, (unsigned char *)spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_WRITE_ONLY);
    while (!(end_irq_flag == 1))
        ; //Wait for the spi to finish sending the first packet of data.
    spi_master_write_dma_plus(SPI_MODULE_SEL, 0, (unsigned int)NULL, (unsigned char *)spi_tx_buff1, sizeof(spi_tx_buff1), SPI_MODE_WR_WRITE_ONLY);
    while (!(end_irq_flag == 2))
        ; //Wait for the spi to finish sending the first packet of data.
                #endif
            #endif


            #if (DMA_LLP_MODE == DMA_LLP_SINGLE_CHAIN)
    while (!(end_irq_flag == 1))
        ; //Wait for spi transmission end interrupt.
    spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)(spi_rx_buff + 4), DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    while (!(end_irq_flag == 2))
        ; //Wait spi transmission complete interrupt.
            #elif (DMA_LLP_MODE == DMA_LLP_PINGPONG)
                #if (DATA_MODE == NORMAL_MODE)
    while (!(end_irq_flag == 2))
        ; //Wait for spi to finish sending data.
    spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)(spi_rx_buff + 4), DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    while (!(end_irq_flag == 3))
        ; //Wait for spi to finish receiving the first packet.
    spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)(spi_rx_buff1 + 4), DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    while (!(end_irq_flag == 4))
        ; //Wait for spi to finish receiving the second packet.
                #elif (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE)
    spi_master_read_dma_plus(SPI_MODULE_SEL, 0, (unsigned int)NULL, (unsigned char *)(spi_rx_buff + 4), DATA_BYTE_LEN, SPI_MODE_RD_READ_ONLY);
    while (!(end_irq_flag == 1))
        ; //Wait for spi to finish receiving the first packet.
    spi_master_read_dma_plus(SPI_MODULE_SEL, 0, (unsigned int)NULL, (unsigned char *)(spi_rx_buff1 + 4), DATA_BYTE_LEN, SPI_MODE_RD_READ_ONLY);
    while (!(end_irq_flag == 2))
        ; //Wait for spi to finish receiving the second packet.
                #endif
            #endif
            #if (DMA_LLP_MODE == DMA_LLP_SINGLE_CHAIN)
    if (end_irq_flag == 2) {
        for (i = 0; i < DATA_BYTE_LEN; i++) {
            if (spi_tx_buff[i] != (spi_rx_buff[i + 4])) {
                gpio_set_high_level(LED2); //LED on indicate data error
                while (1)
                    ;
            }
        }
        end_irq_flag = 0;
    }
    spi_tx_buff[0]++;
            #elif (DMA_LLP_MODE == DMA_LLP_PINGPONG)
                #if (DATA_MODE == NORMAL_MODE)
    if (end_irq_flag == 4) {
        for (i = 0; i < DATA_BYTE_LEN; i++) {
            if ((spi_tx_buff[i] != (spi_rx_buff[i + 4])) && (spi_tx_buff1[i] != (spi_rx_buff1[i + 4]))) {
                gpio_set_high_level(LED2); //LED on indicate data error
                while (1)
                    ;
            }
        }
        spi_tx_buff[0]++;
        spi_tx_buff1[DATA_BYTE_LEN - 1]++;
        end_irq_flag = 0;
    }
                #elif ((DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE) || (DATA_MODE == ONLY_DATA_SLAVE_REVEICE_MODE))
    if (end_irq_flag == 2)
                #endif
    {
        end_irq_flag = 0;
        spi_tx_buff[0]++;
        spi_tx_buff1[DATA_BYTE_LEN - 1]++;
    }
            #endif
    delay_ms(200);
    gpio_toggle(LED1);
}


            #if (SPI_MODULE_SEL == GSPI_MODULE)
_attribute_ram_code_sec_noinline_ void gspi_irq_handler(void)
            #endif
            #if defined(MCU_CORE_TL322X)
                #if (SPI_MODULE_SEL == GSPI1_MODULE)
    _attribute_ram_code_sec_noinline_ void gspi1_irq_handler(void)
                #endif
                #if (SPI_MODULE_SEL == GSPI2_MODULE)
        _attribute_ram_code_sec_noinline_ void gspi2_irq_handler(void)
                #endif
                #if (SPI_MODULE_SEL == GSPI3_MODULE)
            _attribute_ram_code_sec_noinline_ void gspi3_irq_handler(void)
                #endif
                #if (SPI_MODULE_SEL == GSPI4_MODULE)
                _attribute_ram_code_sec_noinline_ void gspi4_irq_handler(void)
                #endif
            #endif
            #ifndef MCU_CORE_TL321X
                #if (SPI_MODULE_SEL == LSPI_MODULE)
                    _attribute_ram_code_sec_noinline_ void lspi_irq_handler(void)
                #endif
            #endif
{
    if (spi_get_irq_status(SPI_MODULE_SEL, SPI_END_INT)) {
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);
        end_irq_flag++;
    }
}


            #if (SPI_MODULE_SEL == GSPI_MODULE)
PLIC_ISR_REGISTER(gspi_irq_handler, IRQ_GSPI)
            #endif
            #if defined(MCU_CORE_TL322X)
                #if (SPI_MODULE_SEL == GSPI1_MODULE)
PLIC_ISR_REGISTER(gspi1_irq_handler, IRQ_GSPI1)
                #endif
                #if (SPI_MODULE_SEL == GSPI2_MODULE)
PLIC_ISR_REGISTER(gspi2_irq_handler, IRQ_GSPI2)
                #endif
                #if (SPI_MODULE_SEL == GSPI3_MODULE)
PLIC_ISR_REGISTER(gspi3_irq_handler, IRQ_GSPI3)
                #endif
                #if (SPI_MODULE_SEL == GSPI4_MODULE)
PLIC_ISR_REGISTER(gspi4_irq_handler, IRQ_GSPI4)
                #endif
            #endif
            #ifndef MCU_CORE_TL321X
                #if (SPI_MODULE_SEL == LSPI_MODULE)
PLIC_ISR_REGISTER(lspi_irq_handler, IRQ_LSPI)
                #endif
            #endif

        #elif (SPI_DEVICE == SPI_SLAVE_DEVICE)
            /**********************************************************************************************************************
 *                                          global variable                                                         *
 *********************************************************************************************************************/
            #define DATA_BYTE_LEN 16
unsigned char spi_slave_rx_buff[DATA_BYTE_LEN + 4] __attribute__((aligned(4))) = {0x00};
            #if (DMA_LLP_MODE == DMA_LLP_PINGPONG)
dma_chain_config_t     rx_dma_list[2];
dma_chain_config_t     tx_dma_list[2];
volatile unsigned char tx_dma_flag                                                       = 0;
unsigned char          spi_slave_rx_buff1[DATA_BYTE_LEN + 4] __attribute__((aligned(4))) = {0x00};
            #endif

            #if (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE)
volatile unsigned char tx_endirq_count = 0;

volatile unsigned char i;
unsigned char          spi_tx_buff[DATA_BYTE_LEN] __attribute__((aligned(4)))  = {0x00};
unsigned char          spi_tx_buff1[DATA_BYTE_LEN] __attribute__((aligned(4))) = {0x00};
            #elif (DATA_MODE == ONLY_DATA_SLAVE_REVEICE_MODE)
volatile unsigned char rx_dmairq_count = 0;
            #endif

void user_init(void)
{
    gpio_output_en(LED1);     //enable output
    gpio_input_dis(LED1);     //disable input
    gpio_set_low_level(LED1); //LED Off
    gpio_function_en(LED1);   //enable gpio
    gpio_output_en(LED2);     //enable output
    gpio_input_dis(LED2);     //disable input
    gpio_set_low_level(LED2); //LED Off
    gpio_function_en(LED2);   //enable gpio
            #if (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE)

    for (i = 0; i < DATA_BYTE_LEN; i++) {
        spi_tx_buff[i]  = i;
        spi_tx_buff1[i] = DATA_BYTE_LEN - i - 1;
    }
            #endif

            #if defined(MCU_CORE_TL751X)
    spi_slave_init(SPI_MODULE_SEL, SRC_CLK_XTAL_48M, SPI_MODE0);
            #else
    spi_slave_init(SPI_MODULE_SEL, SPI_MODE0);
            #endif
            //TL751X,TL7518,TL721X,TL321X,TL322X supports up to 256 clk cycle dummy.
            #if (DATA_MODE == NORMAL_MODE)
    spi_set_dummy_cnt(SPI_MODULE_SEL, 32);
            #endif
    spi_set_tx_dma_config(SPI_MODULE_SEL, SPI_TX_DMA_CHN);
    spi_set_slave_rx_dma_config(SPI_MODULE_SEL, SPI_RX_DMA_CHN);
            #if (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE)
    spi_cmd_dis(SPI_MODULE_SEL);
    spi_addr_dis(SPI_MODULE_SEL);
                #if defined(MCU_CORE_TL322X)
    spi_txdma_req_after_cmd_dis(SPI_MODULE_SEL);
                #endif
    spi_set_io_mode(SPI_MODULE_SEL, SPI_SINGLE_MODE);
    spi_set_dummy_cnt(SPI_MODULE_SEL, 0);
    spi_set_transmode(SPI_MODULE_SEL, SPI_MODE_WRITE_ONLY);
    spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);
    spi_set_irq_mask(SPI_MODULE_SEL, SPI_END_INT_EN); //endint_en txfifoint_en rxfifoint_en
            #elif (DATA_MODE == ONLY_DATA_SLAVE_REVEICE_MODE)
    spi_cmd_dis(SPI_MODULE_SEL);
    spi_addr_dis(SPI_MODULE_SEL);
                #if defined(MCU_CORE_TL7518) || defined(MCU_CORE_TL751X) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    spi_txdma_req_after_cmd_dis(SPI_MODULE_SEL);
                #endif
    spi_set_io_mode(SPI_MODULE_SEL, SPI_SINGLE_MODE);
    spi_set_dummy_cnt(SPI_MODULE_SEL, 0);
    spi_set_transmode(SPI_MODULE_SEL, SPI_MODE_READ_ONLY);
    dma_set_irq_mask(SPI_RX_DMA_CHN, TC_MASK);
    dma_set_llp_irq_mode(SPI_RX_DMA_CHN, DMA_INTERRUPT_MODE);
    plic_interrupt_enable(IRQ_DMA);
            #endif

            #if (SPI_MODULE_SEL == GSPI_MODULE)
    plic_interrupt_enable(IRQ_GSPI);
            #endif
            #if defined(MCU_CORE_TL322X)
                #if (SPI_MODULE_SEL == GSPI1_MODULE)
    plic_interrupt_enable(IRQ_GSPI1);
                #endif
                #if (SPI_MODULE_SEL == GSPI2_MODULE)
    plic_interrupt_enable(IRQ_GSPI2);
                #endif
                #if (SPI_MODULE_SEL == GSPI3_MODULE)
    plic_interrupt_enable(IRQ_GSPI3);
                #endif
                #if (SPI_MODULE_SEL == GSPI4_MODULE)
    plic_interrupt_enable(IRQ_GSPI4);
                #endif
            #endif
            #ifndef MCU_CORE_TL321X
                #if (SPI_MODULE_SEL == LSPI_MODULE)
    plic_interrupt_enable(IRQ_LSPI);
                #endif
            #endif
    core_interrupt_enable();

            #if (SPI_MODULE_SEL == GSPI_MODULE)
    gspi_set_pin(&gspi_pin_config);
            #endif
            #if defined(MCU_CORE_TL322X)
                #if (SPI_MODULE_SEL == GSPI1_MODULE)
    gspi1_set_pin(&gspi1_pin_config);
                #endif
                #if (SPI_MODULE_SEL == GSPI2_MODULE)
    gspi2_set_pin(&gspi2_pin_config);
                #endif
                #if (SPI_MODULE_SEL == GSPI3_MODULE)
    gspi3_set_pin(&gspi3_pin_config);
                #endif
                #if (SPI_MODULE_SEL == GSPI4_MODULE)
    gspi4_set_pin(&gspi4_pin_config);
                #endif
            #endif
            #ifndef MCU_CORE_TL321X
                #if (SPI_MODULE_SEL == LSPI_MODULE)
    lspi_set_pin(&lspi_pin_config);
                #endif
            #endif
            #if (DMA_LLP_MODE == DMA_LLP_SINGLE_CHAIN)
    spi_slave_rx_dma_chain_init(SPI_MODULE_SEL, SPI_RX_DMA_CHN, spi_slave_rx_buff + 4, DATA_BYTE_LEN);
    spi_slave_tx_dma_chain_init(SPI_MODULE_SEL, SPI_TX_DMA_CHN, spi_slave_rx_buff + 4, DATA_BYTE_LEN);
            #elif (DMA_LLP_MODE == DMA_LLP_PINGPONG)
                #if (DATA_MODE == NORMAL_MODE)
    spi_set_slave_rx_dma_chain_llp(SPI_MODULE_SEL, SPI_RX_DMA_CHN, spi_slave_rx_buff + 4, DATA_BYTE_LEN, &rx_dma_list[0]);
    spi_rx_dma_add_list_element(SPI_MODULE_SEL, SPI_RX_DMA_CHN, &rx_dma_list[0], &rx_dma_list[1], (unsigned char *)(spi_slave_rx_buff1 + 4), DATA_BYTE_LEN);
    spi_rx_dma_add_list_element(SPI_MODULE_SEL, SPI_RX_DMA_CHN, &rx_dma_list[1], &rx_dma_list[0], (unsigned char *)(spi_slave_rx_buff + 4), DATA_BYTE_LEN);
    dma_chn_en(SPI_RX_DMA_CHN);

    spi_set_slave_tx_dma_chain_llp(SPI_MODULE_SEL, SPI_TX_DMA_CHN, spi_slave_rx_buff + 4, DATA_BYTE_LEN, &tx_dma_list[0]);
    spi_tx_dma_add_list_element(SPI_MODULE_SEL, SPI_TX_DMA_CHN, &tx_dma_list[0], &tx_dma_list[1], (unsigned char *)(spi_slave_rx_buff1 + 4), DATA_BYTE_LEN);
    spi_tx_dma_add_list_element(SPI_MODULE_SEL, SPI_TX_DMA_CHN, &tx_dma_list[1], &tx_dma_list[0], (unsigned char *)(spi_slave_rx_buff + 4), DATA_BYTE_LEN);
    dma_chn_en(SPI_TX_DMA_CHN);
                #elif (DATA_MODE == ONLY_DATA_SLAVE_REVEICE_MODE)
    spi_set_slave_rx_dma_chain_llp(SPI_MODULE_SEL, SPI_RX_DMA_CHN, spi_slave_rx_buff + 4, DATA_BYTE_LEN, &rx_dma_list[0]);
    spi_rx_dma_add_list_element(SPI_MODULE_SEL, SPI_RX_DMA_CHN, &rx_dma_list[0], &rx_dma_list[1], (unsigned char *)(spi_slave_rx_buff1 + 4), DATA_BYTE_LEN);
    spi_rx_dma_add_list_element(SPI_MODULE_SEL, SPI_RX_DMA_CHN, &rx_dma_list[1], &rx_dma_list[0], (unsigned char *)(spi_slave_rx_buff + 4), DATA_BYTE_LEN);
    dma_chn_en(SPI_RX_DMA_CHN);
                #elif (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE)
    spi_set_slave_tx_dma_chain_llp(SPI_MODULE_SEL, SPI_TX_DMA_CHN, spi_tx_buff, DATA_BYTE_LEN, &tx_dma_list[0]);
    spi_tx_dma_add_list_element(SPI_MODULE_SEL, SPI_TX_DMA_CHN, &tx_dma_list[0], &tx_dma_list[1], (unsigned char *)(spi_tx_buff1), DATA_BYTE_LEN);
    spi_tx_dma_add_list_element(SPI_MODULE_SEL, SPI_TX_DMA_CHN, &tx_dma_list[1], &tx_dma_list[0], (unsigned char *)(spi_tx_buff), DATA_BYTE_LEN);
    dma_chn_en(SPI_TX_DMA_CHN);
                #endif
}

void main_loop(void)
{
    delay_ms(200);
    gpio_toggle(LED1);

                #if (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE)
    spi_tx_buff[0]++;
    spi_tx_buff1[DATA_BYTE_LEN - 1]++;
                #endif
}

                #if (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE)
                    #if (SPI_MODULE_SEL == GSPI_MODULE)
_attribute_ram_code_sec_noinline_ void gspi_irq_handler(void)
                    #endif
                    #if defined(MCU_CORE_TL322X)
                        #if (SPI_MODULE_SEL == GSPI1_MODULE)
    _attribute_ram_code_sec_noinline_ void gspi1_irq_handler(void)
                        #endif
                        #if (SPI_MODULE_SEL == GSPI2_MODULE)
        _attribute_ram_code_sec_noinline_ void gspi2_irq_handler(void)
                        #endif
                        #if (SPI_MODULE_SEL == GSPI3_MODULE)
            _attribute_ram_code_sec_noinline_ void gspi3_irq_handler(void)
                        #endif
                        #if (SPI_MODULE_SEL == GSPI4_MODULE)
                _attribute_ram_code_sec_noinline_ void gspi4_irq_handler(void)
                        #endif
                    #endif
                    #ifndef MCU_CORE_TL321X
                        #if (SPI_MODULE_SEL == LSPI_MODULE)
                    _attribute_ram_code_sec_noinline_ void lspi_irq_handler(void)
                        #endif
                    #endif
{
    if (spi_get_irq_status(SPI_MODULE_SEL, SPI_END_INT)) {
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);
                    #if (DATA_MODE == ONLY_DATA_SLAVE_SEND_MODE)
        tx_endirq_count++;
                    #endif
    }
}

                    #if (SPI_MODULE_SEL == GSPI_MODULE)
PLIC_ISR_REGISTER(gspi_irq_handler, IRQ_GSPI)
                    #endif
                    #if defined(MCU_CORE_TL322X)
                        #if (SPI_MODULE_SEL == GSPI1_MODULE)
PLIC_ISR_REGISTER(gspi1_irq_handler, IRQ_GSPI1)
                        #endif
                        #if (SPI_MODULE_SEL == GSPI2_MODULE)
PLIC_ISR_REGISTER(gspi2_irq_handler, IRQ_GSPI2)
                        #endif
                        #if (SPI_MODULE_SEL == GSPI3_MODULE)
PLIC_ISR_REGISTER(gspi3_irq_handler, IRQ_GSPI3)
                        #endif
                        #if (SPI_MODULE_SEL == GSPI4_MODULE)
PLIC_ISR_REGISTER(gspi4_irq_handler, IRQ_GSPI4)
                        #endif
                    #endif
                    #ifndef MCU_CORE_TL321X
                        #if (SPI_MODULE_SEL == LSPI_MODULE)
PLIC_ISR_REGISTER(lspi_irq_handler, IRQ_LSPI)
                        #endif
                    #endif
                #endif


                #if (DATA_MODE == ONLY_DATA_SLAVE_REVEICE_MODE)
_attribute_ram_code_sec_noinline_ void dma_irq_handler(void)
{
    if (dma_get_tc_irq_status(BIT(SPI_RX_DMA_CHN))) {
        dma_clr_tc_irq_status(BIT(SPI_RX_DMA_CHN));
                    #if (DATA_MODE == ONLY_DATA_SLAVE_REVEICE_MODE)
        tx_dma_flag++;
                    #endif
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)

                #endif
            #endif
        #endif
    #endif
#endif
