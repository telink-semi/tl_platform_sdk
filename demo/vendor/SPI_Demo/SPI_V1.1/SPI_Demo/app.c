/********************************************************************************************************
 * @file    app.c
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
#include "common.h"

#if (SPI_MODE == SPI_NDMA_MODE)
    /**********************************************************************************************************************
 *                                         SPI device  selection                                                     *
 *********************************************************************************************************************/
    #define SPI_MASTER_DEVICE 1
    #define SPI_SLAVE_DEVICE  2

    #define SPI_DEVICE        SPI_MASTER_DEVICE

    /**********************************************************************************************************************
 *                                         SPI protocol demo selection                                                *
 *********************************************************************************************************************/
    #define B85M_SLAVE_PROTOCOL     1 // B85m as slave
    #define B91M_SLAVE_PROTOCOL     2 // Telink RISC-V MCU hspi/pspi/gspi/lspi slave mode as slave
    #define B91M_SPI_SLAVE_PROTOCOL 3 // Telink RISC-V MCU spi slave as slave

    #define SPI_PROTOCOL            B91M_SLAVE_PROTOCOL

    /**********************************************************************************************************************
*                                         SPI data mode selection                                                *
*********************************************************************************************************************/
    #define ONLY_DATA_MODE 1 // Only data is available for spi communication
    #define NORMAL_MODE    2 // Spi communication format: cmd+dummy+data


    #define DATA_MODE      NORMAL_MODE

    /**********************************************************************************************************************
*                                         SPI module selection                                                       *
*********************************************************************************************************************/
/* Note:TL321X/TL323X only supports gspi!!!*/
    #if !defined(MCU_CORE_TL323X) && !defined(MCU_CORE_TL321X)
        #define LSPI_MODULE 0
    #endif
    #define GSPI_MODULE 1
    #if defined(MCU_CORE_TL322X)
        #define GSPI1_MODULE 2
        #define GSPI2_MODULE 3
        #define GSPI3_MODULE 4
        #define GSPI4_MODULE 5
    #endif

    #if defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL323X)
        #define SPI_MODULE_SEL GSPI_MODULE
    #else
        #define SPI_MODULE_SEL GSPI_MODULE
    #endif
    /**********************************************************************************************************************
 *                                         SPI multiple slave                                                                                             *
 *********************************************************************************************************************/
    #define ONE_SLAVE     0
    #define MULTI_SLAVE   1

    #define SPI_SLAVE_NUM ONE_SLAVE
    /**********************************************************************************************************************
 *                                         3line SPI  enable                                                      *
 *********************************************************************************************************************/
    #define SPI_NORMAL_SLAVE 0
    #define SPI_3LINE_SLAVE  1

    #define SPI_SLAVE_MODE   SPI_NORMAL_SLAVE
    /**********************************************************************************************************************
 *                                          SPI slave ready test
 *When the slave_ready bit of the slave is 1, the master sends read status cmd, and the slave will reply 0x5a.
 *When the slave_ready bit of the slave is 0, the master sends read status cmd, and the slave will reply 0x00.                                        *
 *********************************************************************************************************************/
    #define SPI_SLAVE_READY_TEST 0

    /**********************************************************************************************************************
*                                         SPI clock set
*********************************************************************************************************************/
    #define SPI_CLK 4000000

    /**********************************************************************************************************************
*                                         SPI pin set                                                     *
*********************************************************************************************************************/
    #if (SPI_MODULE_SEL == GSPI_MODULE)
        #if defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL323X)
gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0,
    .spi_io2_pin      = GPIO_FC_PA3, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PA4, //quad  mode is required, otherwise it is NONE_PIN.
};
        #endif
#if  defined(MCU_CORE_TL322X)
gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PF2,
    .spi_clk_pin      = GPIO_FC_PF3,
    .spi_mosi_io0_pin = GPIO_FC_PF4,
    .spi_miso_io1_pin = GPIO_FC_PF5,
    .spi_io2_pin      = GPIO_FC_PF6, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PF7, //quad  mode is required, otherwise it is NONE_PIN.
};
 #endif

        #if defined(MCU_CORE_TL751X)
gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0,
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
    .spi_miso_io1_pin = GSPI_MISO_PA3_PIN,
    .spi_io2_pin      = GSPI_IO2_PA4_PIN,  //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GSPI_IO3_PA5_PIN,  //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io4_pin      = GSPI_IO4_PA6_PIN,  //octal mode is required, otherwise it is NONE_PIN.
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
    .spi_csn_pin      = GPIO_FC_PF2,
    .spi_clk_pin      = GPIO_FC_PF4,
    .spi_mosi_io0_pin = GPIO_FC_PG0,
    .spi_miso_io1_pin = GPIO_FC_PF7,
    .spi_io2_pin      = GPIO_FC_PF6, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PF5,
};
        #endif
        #if (SPI_MODULE_SEL == GSPI2_MODULE)
gspi_pin_config_t gspi2_pin_config = {
    .spi_csn_pin      = GPIO_FC_PF2,
    .spi_clk_pin      = GPIO_FC_PG1,
    .spi_mosi_io0_pin = GPIO_FC_PG5,
    .spi_miso_io1_pin = GPIO_FC_PG4,
    .spi_io2_pin      = GPIO_FC_PG3, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PG2, //quad  mode is required, otherwise it is NONE_PIN.
};
        #endif
        #if (SPI_MODULE_SEL == GSPI3_MODULE)
gspi_pin_config_t gspi3_pin_config = {
    .spi_csn_pin      = GPIO_FC_PF2,
    .spi_clk_pin      = GPIO_FC_PG6,
    .spi_mosi_io0_pin = GPIO_FC_PH2,
    .spi_miso_io1_pin = GPIO_FC_PH1,
    .spi_io2_pin      = GPIO_FC_PH0, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PG7, //quad  mode is required, otherwise it is NONE_PIN.
};
        #endif
        #if (SPI_MODULE_SEL == GSPI4_MODULE)
gspi_pin_config_t gspi4_pin_config = {
    .spi_csn_pin      = GPIO_FC_PF2,
    .spi_clk_pin      = GPIO_FC_PH3,
    .spi_mosi_io0_pin = GPIO_FC_PH7,
    .spi_miso_io1_pin = GPIO_FC_PH6,
    .spi_io2_pin      = GPIO_FC_PH5, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PH4, //quad  mode is required, otherwise it is NONE_PIN.
};
        #endif
    #endif

    #if (SPI_SLAVE_NUM == MULTI_SLAVE)
        #if defined(MCU_CORE_B92)
            //39 GPIOs can be multiplexed as PIN for GSPI_CSN0_IO function.Only a part of IO is listed here.
            #define SLAVE_CSN_PIN_NUM 8
gpio_func_pin_e slave_csn_pin[SLAVE_CSN_PIN_NUM] = {GPIO_FC_PA0, GPIO_FC_PA4, GPIO_FC_PB2, GPIO_FC_PB3, GPIO_FC_PB4, GPIO_FC_PB5, GPIO_FC_PB6, GPIO_FC_PB7};
        #endif
        #if defined(MCU_CORE_TL7518)
            //4 GPIOs can be multiplexed as PIN for GSPI_CSN0_IO function.Only a part of IO is listed here.
            #define SLAVE_CSN_PIN_NUM 4
gspi_pin_def_e slave_csn_pin[SLAVE_CSN_PIN_NUM] = {GSPI_CSN0_PA0_PIN, GSPI_CSN0_PB7_PIN, GSPI_CSN0_PG1_PIN, GSPI_CSN0_PJ2_PIN};
        #endif
        #if defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X) || defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL323X)
            // MCU_CORE_TL321X have 37 GPIOs,MCU_CORE_TL322X have 60 GPIOs and MCU_CORE_TL721X have 42 GPIOs can be multiplexed as PIN for GSPI_CSN0_IO function.Only a part of IO is listed here.
            #define SLAVE_CSN_PIN_NUM 8
gpio_func_pin_e slave_csn_pin[SLAVE_CSN_PIN_NUM] = {
    GPIO_FC_PA0,
    GPIO_FC_PA1,
    GPIO_FC_PA2,
    GPIO_FC_PA3,
    GPIO_FC_PA4,
    GPIO_FC_PB0,
    GPIO_FC_PB1,
    GPIO_FC_PB2,
};
        #endif
        #if defined(MCU_CORE_TL751X)
            //55 GPIOs can be multiplexed as PIN for GSPI_CSN0_IO function.Only a part of IO is listed here.
            #define SLAVE_CSN_PIN_NUM 8
gpio_func_pin_e slave_csn_pin[SLAVE_CSN_PIN_NUM] = {GPIO_FC_PA0, GPIO_FC_PA1, GPIO_FC_PA2, GPIO_FC_PA3, GPIO_FC_PA4, GPIO_FC_PA5, GPIO_FC_PA6, GPIO_FC_PB0};
        #endif
    #endif
    #if !defined(MCU_CORE_TL323X) && !defined(MCU_CORE_TL321X)
        #if (SPI_MODULE_SEL == LSPI_MODULE)
            #if defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin      = LSPI_CSN_PE0_PIN,
    .spi_clk_pin      = LSPI_CLK_PE1_PIN,
    .spi_mosi_io0_pin = LSPI_MOSI_IO0_PE2_PIN,
    .spi_miso_io1_pin = LSPI_MISO_IO1_PE3_PIN,
    .spi_io2_pin      = LSPI_IO2_PE4_PIN,      //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = LSPI_IO3_PE5_PIN,      //quad  mode is required, otherwise it is NONE_PIN.
};
            #endif
#if defined(MCU_CORE_TL322X)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PF2,
    .spi_clk_pin      = GPIO_FC_PA0,
    .spi_mosi_io0_pin = GPIO_FC_PB2,
    .spi_miso_io1_pin = GPIO_FC_PB1,
    .spi_io2_pin      = GPIO_FC_PA2, //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = GPIO_FC_PA1, //quad  mode is required, otherwise it is NONE_PIN.
};
#endif
            #if defined(MCU_CORE_TL751X)
lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin      = GPIO_FC_PA0,
    .spi_clk_pin      = GPIO_FC_PA1,
    .spi_mosi_io0_pin = GPIO_FC_PA2,
    .spi_miso_io1_pin = GPIO_FC_PB0,
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
    .spi_miso_io1_pin = LSPI_MISO_IO1_PE2_PIN,
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

    #if (SPI_DEVICE == SPI_MASTER_DEVICE)
        /**********************************************************************************************************************
*                                         SPI master setting                                                        *
*********************************************************************************************************************/
        #define DATA_BYTE_LEN 16
unsigned char spi_rx_buff[DATA_BYTE_LEN] __attribute__((aligned(4))) = {0x00};
        #if (SPI_PROTOCOL == B85M_SLAVE_PROTOCOL)
            #define SPI_B85M_READ_CMD  0x80
            #define SPI_B85M_WRITE_CMD 0x00

typedef struct
{
    unsigned char address[3];
    unsigned char cmd;
    unsigned char data[DATA_BYTE_LEN];
} spi_b85m_slave_protocol_t;

spi_b85m_slave_protocol_t __attribute__((aligned(4))) spi_tx_buff = {
    .address = {0x04, 0x40, 0x00},
    .cmd     = SPI_B85M_WRITE_CMD,
    .data    = {0xAA, 0x10, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xBB},
};

        #elif (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
            #if (SPI_SLAVE_READY_TEST == 1)
volatile unsigned char spi_b91m_slave_io_mode;
            #endif
            #if (DATA_MODE == NORMAL_MODE)
spi_wr_rd_config_t spi_b91m_slave_protocol_config = {
    .spi_io_mode   = SPI_SINGLE_MODE, /*IO mode set to SPI_3_LINE_MODE when SPI_3LINE_SLAVE.*/
    .spi_dummy_cnt = 32,              //B92 supports up to 32 clk cycle dummy, and TL751X,TL7518,TL721X,TL321X,tl322x supports up to 256 clk cycle dummy.
                #if defined(MCU_CORE_TL322X)
    .spi_dummy_hold = 0,
                #endif
    .spi_cmd_en      = 1,
    .spi_addr_en     = 0,
    .spi_addr_len    = 0, //when spi_addr_en = 0,invalid set.
    .spi_cmd_fmt_en  = 0, //when spi_cmd_en = 0,invalid set.
    .spi_addr_fmt_en = 0, //when spi_addr_en = 0,invalid set.
};
            #elif (DATA_MODE == ONLY_DATA_MODE)
spi_wr_rd_config_t spi_b91m_slave_protocol_config = {
    .spi_io_mode   = SPI_SINGLE_MODE, /*IO mode set to SPI_3_LINE_MODE when SPI_3LINE_SLAVE.*/
    .spi_dummy_cnt = 0,               //B92 supports up to 32 clk cycle dummy, and TL751X,TL7518,TL721X,TL321X,tl322x supports up to 256 clk cycle dummy.
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

typedef struct
{
    unsigned char address[4];
    unsigned char data_len;
    unsigned char data[DATA_BYTE_LEN + 3];
} spi_b91m_slave_protocol_t;

spi_b91m_slave_protocol_t __attribute__((aligned(4))) spi_tx_buff =
    {
        .address  = {0xc0, 0x20, 0x04, 0x00}, /*.address = {0xc0, 0x00, 0x00, 0x00},*/
        .data_len = DATA_BYTE_LEN + 3,
        .data     = {0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
};

        #elif (SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)
            #define spi_slave_address 0x0008001c //When master and slave spi communicate, first compile the slave demo to get the value of spi_sspi_slave_rx_buff as the address of spi_slave_address.
spi_wr_rd_config_t spi_b91m_spi_slave_protocol_config = {
    .spi_io_mode     = SPI_SINGLE_MODE,
    .spi_dummy_cnt   = 8,
    .spi_cmd_en      = 1,
    .spi_addr_en     = 1,
    .spi_addr_len    = 4, //when hspi_addr_en = 0,invalid set.
    .spi_cmd_fmt_en  = 0, //when hspi_cmd_en = 0,invalid set.
    .spi_addr_fmt_en = 0, //when hspi_addr_en=0,invalid set.
};

typedef struct
{
    unsigned char data[DATA_BYTE_LEN];
} spi_b91m_spi_slave_protocol_t;

spi_b91m_spi_slave_protocol_t __attribute__((aligned(4))) spi_tx_buff =
    {
        .data = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
};
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
        #if defined(MCU_CORE_TL7518) || defined(MCU_CORE_TL751X)
    spi_master_init(SPI_MODULE_SEL, SRC_CLK_XTAL_48M, SRC_CLK_XTAL_48M / SPI_CLK, SPI_MODE0);
        #else
    spi_master_init(SPI_MODULE_SEL, sys_clk.pll_clk * 1000000 / SPI_CLK, SPI_MODE0);
        #endif
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
        #if !defined(MCU_CORE_TL323X) && !defined(MCU_CORE_TL321X)
            #if (SPI_MODULE_SEL == LSPI_MODULE)
    lspi_set_pin(&lspi_pin_config);
            #endif
        #endif
        #if (SPI_PROTOCOL == B85M_SLAVE_PROTOCOL)
    spi_master_config(SPI_MODULE_SEL, SPI_NORMAL);

        #elif (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
    spi_master_config_plus(SPI_MODULE_SEL, &spi_b91m_slave_protocol_config);
            #if (SPI_SLAVE_READY_TEST == 1)
    spi_b91m_slave_io_mode = spi_b91m_slave_protocol_config.spi_io_mode;
            #endif
        #elif (SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)
    spi_master_config_plus(SPI_MODULE_SEL, &spi_b91m_spi_slave_protocol_config);
        #endif
}
        #if (SPI_SLAVE_READY_TEST == 1)
/**
 * @brief       This function servers to get lspi/gspi slave ready status. When slave is ready, slave ready reply a byte data:0x5a.
 * slave reply a byte data: 0x00.indicating that slave is not ready for data transmission.
 * @param[in]   spi_sel     - the spi module.
 * @param[in]   mode        - the spi master io mode.
 * @return      1:Indicates that the slave is ready. others:Indicates that slave is not ready.
 */
drv_api_status_e spi_master_get_slave_ready(spi_sel_e spi_sel, spi_io_mode_e mode)
{
    unsigned char slave_ready_flag[1] = {0};

    switch (mode) {
    case SPI_SINGLE_MODE:
        spi_master_read_plus(spi_sel, SPI_READ_STATUS_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)slave_ready_flag, 1, SPI_MODE_RD_DUMMY_READ);
        break;
    case SPI_DUAL_MODE:
        spi_master_read_plus(spi_sel, SPI_READ_STATUS_DUAL_CMD, (unsigned int)NULL, (unsigned char *)slave_ready_flag, 1, SPI_MODE_RD_DUMMY_READ);
        break;
    case SPI_QUAD_MODE:
        spi_master_read_plus(spi_sel, SPI_READ_STATUS_QUAD_CMD, (unsigned int)NULL, (unsigned char *)slave_ready_flag, 1, SPI_MODE_RD_DUMMY_READ);
        break;
            #if defined(MCU_CORE_TL7518) || defined(MCU_CORE_TL751X)
    case SPI_OCTAL_MODE:
        spi_master_read_plus(spi_sel, SPI_READ_STATUS_OCTAL_CMD, (unsigned int)NULL, (unsigned char *)(&slave_ready_flag), 1, SPI_MODE_RD_DUMMY_READ);
        break;
            #endif
    case SPI_3_LINE_MODE:
        spi_master_read_plus(spi_sel, SPI_READ_STATUS_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)slave_ready_flag, 1, SPI_MODE_RD_DUMMY_READ);
        break;
    }
    if (SPI_WAIT(spi_is_busy, spi_sel, g_spi_timeout_error[spi_sel].g_spi_error_timeout_us, g_spi_timeout_error[spi_sel].spi_timeout_handler, SPI_API_ERROR_TIMEOUT_BUS_BUSY)) {
        return DRV_API_TIMEOUT;
    }
    if (slave_ready_flag[0] == 0x5a) {
        return 1;
    } else {
        return 0;
    }
}
        #endif

void main_loop(void)
{
    delay_ms(200);
    gpio_toggle(LED1);
        #if (SPI_PROTOCOL == B85M_SLAVE_PROTOCOL)
    spi_tx_buff.cmd = SPI_B85M_WRITE_CMD;
    spi_master_write(SPI_MODULE_SEL, (unsigned char *)&spi_tx_buff, sizeof(spi_tx_buff));
    spi_tx_buff.cmd = SPI_B85M_READ_CMD;
    spi_master_write_read(SPI_MODULE_SEL, (unsigned char *)&spi_tx_buff, sizeof(spi_tx_buff.address) + sizeof(spi_tx_buff.cmd), (unsigned char *)spi_rx_buff, DATA_BYTE_LEN);
    for (unsigned char i = 0; i < DATA_BYTE_LEN; i++) {
        if (spi_tx_buff.data[i] != (spi_rx_buff[i])) {
            gpio_set_high_level(LED2); //LED on indicate data error
        }
    }
    spi_tx_buff.data[0]++;

        #elif (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
            #if (SPI_SLAVE_READY_TEST == 1)
    while (1) {
        if (spi_master_get_slave_ready(SPI_MODULE_SEL, spi_b91m_slave_io_mode) == 0) {
            gpio_set_high_level(LED2);        //If the LED2 is always on, the slave ready function is abnormal.
        } else if (spi_master_get_slave_ready(SPI_MODULE_SEL, spi_b91m_slave_io_mode) == 1) {
            gpio_toggle(LED2);                //The flashing LED2 indicates that the slave ready function is normal.
            break;
        } else if (spi_master_get_slave_ready(SPI_MODULE_SEL, spi_b91m_slave_io_mode) == DRV_API_TIMEOUT) {
            spi_hw_fsm_reset(SPI_MODULE_SEL); //the wait for slave ready function has timed out,reset spi module.
            break;
        }
    }
            #else
                #if (DATA_MODE == NORMAL_MODE)
    spi_master_write_plus(SPI_MODULE_SEL, SPI_WRITE_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)&spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_DUMMY_WRITE);
    spi_master_read_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char *)spi_rx_buff, DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
                #elif (DATA_MODE == ONLY_DATA_MODE)
    spi_master_write_plus(SPI_MODULE_SEL, (unsigned char)0, (unsigned int)NULL, (unsigned char *)&spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_WRITE_ONLY);
    spi_master_read_plus(SPI_MODULE_SEL, (unsigned char)0, (unsigned int)NULL, (unsigned char *)spi_rx_buff, DATA_BYTE_LEN, SPI_MODE_RD_READ_ONLY);
                #endif
    for (unsigned char i = 0; i < DATA_BYTE_LEN; i++) {
        if (spi_tx_buff.data[3 + i] != (spi_rx_buff[i])) {
            gpio_set_high_level(LED2); //LED on indicate data error
            while (1)
                ;
        }
    }
    spi_tx_buff.data[3]++;
            #endif
        #elif (SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)
    spi_master_write_plus(SPI_MODULE_SEL, SPI_SLAVE_WRITE_DATA_CMD, spi_slave_address, (unsigned char *)&spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_WRITE_ONLY);
    spi_master_read_plus(SPI_MODULE_SEL, SPI_SLAVE_READ_DATA_CMD, spi_slave_address, (unsigned char *)spi_rx_buff, DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    for (unsigned char i = 0; i < DATA_BYTE_LEN; i++) {
        if (spi_tx_buff.data[i] != (spi_rx_buff[i])) {
            gpio_set_high_level(LED2); //LED on indicate data error
            while (1)
                ;
        }
    }
    spi_tx_buff.data[0]++;
        #endif
        #if (SPI_SLAVE_NUM == MULTI_SLAVE)
            #if defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL323X)
                #if (SPI_MODULE_SEL == TL321X_GSPI_MODULE)
    for (unsigned char i = 0; i < SLAVE_CSN_PIN_NUM - 1; i++) {
        if (gspi_pin_config.spi_csn_pin == slave_csn_pin[i]) {
            gspi_change_csn_pin(slave_csn_pin[i], slave_csn_pin[i + 1]);
            gspi_pin_config.spi_csn_pin = slave_csn_pin[i + 1];
            break;
        }
    }
                #endif
            #else
                #if (SPI_MODULE_SEL == GSPI_MODULE)

    for (unsigned char i = 0; i < SLAVE_CSN_PIN_NUM - 1; i++) {
        if (gspi_pin_config.spi_csn_pin == slave_csn_pin[i]) {
            gspi_change_csn_pin(slave_csn_pin[i], slave_csn_pin[i + 1]);
            gspi_pin_config.spi_csn_pin = slave_csn_pin[i + 1];
            break;
        }
    }
                #endif
            #endif
        #endif
}


    #elif (SPI_DEVICE == SPI_SLAVE_DEVICE)
    /**********************************************************************************************************************
    *                                         SPI slave setting                                                           *
    *********************************************************************************************************************/
        #if (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
            #define SPI_RX_BUFF_LEN  24
            #define DATA_BYTE_LEN    16
            #define DATA_BYTE_OFFSET 4 //must be a multiple 4
unsigned char         spi_slave_rx_buff[SPI_RX_BUFF_LEN + 4] __attribute__((aligned(4))) = {0x00};
volatile unsigned int spi_irq_rx_cnt                                                     = 0;
volatile unsigned int spi_tx_cntn                                                        = 0;
volatile unsigned int spi_tx_num                                                         = 0;

            #if (DATA_MODE == ONLY_DATA_MODE)
volatile unsigned int spi_slave_flag = 0;
            #endif
        #endif
        #if (SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)
            #define DATA_BYTE_LEN 16
volatile unsigned char spi_sspi_slave_rx_buff[DATA_BYTE_LEN + 4] __attribute__((aligned(4))) = {0x00};
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

        #if (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
            #if defined(MCU_CORE_TL751X)
    spi_slave_init(SPI_MODULE_SEL, SRC_CLK_XTAL_48M, SPI_MODE0);
            #else
    spi_slave_init(SPI_MODULE_SEL, SPI_MODE0);
            #endif
    spi_clr_irq_status(SPI_MODULE_SEL, SPI_SLV_CMD_INT | SPI_RXF_INT | SPI_END_INT);
            #if (DATA_MODE == NORMAL_MODE)
    spi_set_irq_mask(SPI_MODULE_SEL, SPI_SLV_CMD_EN | SPI_RXFIFO_INT_EN | SPI_END_INT_EN); //endint_en txfifoint_en rxfifoint_en
            #elif (DATA_MODE == ONLY_DATA_MODE)
    spi_set_irq_mask(SPI_MODULE_SEL, SPI_RXFIFO_INT_EN | SPI_END_INT_EN); //endint_en txfifoint_en rxfifoint_en
            #endif
            //B92 supports up to 32 clk cycle dummy, and TL751X,TL7518,TL721X,TL321X,tl322x supports up to 256 clk cycle dummy.
            //When B92 and B91 communicate with SPI, B91 as slave supports up to 8 clk cycle dummy. When B91 is master, invalid data can be added before tx_buff to act as dummy.
            #if (DATA_MODE == NORMAL_MODE)
    spi_set_dummy_cnt(SPI_MODULE_SEL, 32);
            #elif (DATA_MODE == ONLY_DATA_MODE)
    spi_cmd_dis(SPI_MODULE_SEL);
    spi_addr_dis(SPI_MODULE_SEL);
    spi_set_dummy_cnt(SPI_MODULE_SEL, 0);
    spi_set_io_mode(SPI_MODULE_SEL, SPI_SINGLE_MODE);
    spi_set_transmode(SPI_MODULE_SEL, SPI_MODE_READ_ONLY);
            #endif
            #if (SPI_SLAVE_MODE == SPI_3LINE_SLAVE)
    spi_set_io_mode(SPI_MODULE_SEL, SPI_3_LINE_MODE);
            #endif

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
                    #if (SPI_MODULE_SEL == GSPI3_MODULE)
    gspi3_set_pin(&gspi3_pin_config);
    plic_interrupt_enable(IRQ_GSPI3);
                    #endif
                    #if (SPI_MODULE_SEL == GSPI4_MODULE)
    gspi4_set_pin(&gspi4_pin_config);
    plic_interrupt_enable(IRQ_GSPI4);
                    #endif
                #endif
                #if !defined(MCU_CORE_TL323X) && !defined(MCU_CORE_TL321X)
                    #if (SPI_MODULE_SEL == LSPI_MODULE)
    lspi_set_pin(&lspi_pin_config);
    plic_interrupt_enable(IRQ_LSPI);
                    #endif
                #endif
            #endif 
            #elif (SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)
                #if defined(MCU_CORE_B92)
    spi_slave_set_pin(); //spi slave only need set pin.
                #else
    sspi_pin_config_t sspi_pin_config =
        {
            .spi_csn_pin      = GPIO_FC_PA0,
            .spi_clk_pin      = GPIO_FC_PA1,
            .spi_mosi_io0_pin = GPIO_FC_PA2,
            .spi_miso_io1_pin = GPIO_FC_PB0,
        };
    spi_slave_set_pin(&sspi_pin_config); //spi slave only need set pin.
                #endif
             #endif// #if (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)

    core_interrupt_enable();


}

void main_loop(void)
{
    delay_ms(200);
            #if (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
    spi_slave_rx_buff[DATA_BYTE_LEN + 3] = 0x5a;
            #endif

    gpio_toggle(LED1);
}


            #if (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
/*  handle cmd  interrupt when received read cmd enable txfifo interrupt */
_attribute_ram_code_sec_noinline_ void spi_irq_slv_cmd_process(void)
{
    switch (spi_slave_get_cmd(SPI_MODULE_SEL)) {
    case SPI_READ_DATA_SINGLE_CMD:
    case SPI_READ_DATA_DUAL_CMD:
    case SPI_READ_DATA_QUAD_CMD:
                #if defined(MCU_CORE_TL7518) || defined(MCU_CORE_TL751X)
    case SPI_READ_DATA_OCTAL_CMD:
                #endif
        spi_set_irq_mask(SPI_MODULE_SEL, SPI_TXFIFO_INT_EN); //enable txfifo_int
        break;
    }
}

/*  handle txfifo  interrupt to return data that received from data master */
_attribute_ram_code_sec_noinline_ void spi_irq_tx_fifo_process(void)
{
    spi_tx_num = spi_slave_rx_buff[4] - 3;                   // return data number to master.
    if ((spi_tx_num - spi_tx_cntn) < 4) {
        spi_write(SPI_MODULE_SEL, (unsigned char *)(spi_slave_rx_buff + 4 + DATA_BYTE_OFFSET + spi_tx_cntn), spi_tx_num - spi_tx_cntn);
        spi_clr_irq_mask(SPI_MODULE_SEL, SPI_TXFIFO_INT_EN); //disable txfifo_int
        spi_tx_cntn = 0;                                     //reset
        spi_tx_num  = 0;
    }

    else {
        spi_write(SPI_MODULE_SEL, (unsigned char *)(spi_slave_rx_buff + 4 + DATA_BYTE_OFFSET + spi_tx_cntn), 4);
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_TXF_INT); //clr
        spi_tx_cntn += 4;
    }
}

/*  handle rxfifo  interrupt to  received data from  master */
_attribute_ram_code_sec_noinline_ void spi_irq_rx_fifo_process(void)
{
    if (spi_irq_rx_cnt < (SPI_RX_BUFF_LEN - (SPI_RX_BUFF_LEN % 4))) {
        spi_read(SPI_MODULE_SEL, (unsigned char *)(spi_slave_rx_buff + spi_irq_rx_cnt), 4);
        spi_irq_rx_cnt += 4;
    } else {
        spi_read(SPI_MODULE_SEL, (unsigned char *)(spi_slave_rx_buff + spi_irq_rx_cnt), SPI_RX_BUFF_LEN % 4);
        spi_irq_rx_cnt += SPI_RX_BUFF_LEN % 4;
        spi_rx_fifo_clr(SPI_MODULE_SEL);
    }
}

/*  handle end  interrupt to  received remains data  from master */
_attribute_ram_code_sec_noinline_ void spi_irq_end_process(void)
{
    if (((spi_get_rxfifo_num(SPI_MODULE_SEL)) != 0) && (spi_irq_rx_cnt < SPI_RX_BUFF_LEN)) {
        spi_read(SPI_MODULE_SEL, (unsigned char *)(spi_slave_rx_buff + spi_irq_rx_cnt), spi_get_rxfifo_num(SPI_MODULE_SEL));
    }
    spi_tx_fifo_clr(SPI_MODULE_SEL);
    spi_rx_fifo_clr(SPI_MODULE_SEL);
    spi_irq_rx_cnt = 0;
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
                #if !defined(MCU_CORE_TL323X) && !defined(MCU_CORE_TL321X)
                    #if (SPI_MODULE_SEL == LSPI_MODULE)
                    _attribute_ram_code_sec_noinline_ void lspi_irq_handler(void)
                    #endif
                #endif
{
    if (spi_get_irq_status(SPI_MODULE_SEL, SPI_SLV_CMD_INT)) {
        spi_irq_slv_cmd_process();
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_SLV_CMD_INT); //clr
    }

    if (spi_get_irq_status(SPI_MODULE_SEL, SPI_RXF_INT)) {
        spi_irq_rx_fifo_process();
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_RXF_INT); //clr
    }

    if (spi_get_irq_status(SPI_MODULE_SEL, SPI_END_INT)) {
        spi_irq_end_process();
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT | SPI_RXF_INT); //clr
                #if (DATA_MODE == ONLY_DATA_MODE)
        if (!spi_slave_flag) {
            spi_set_transmode(SPI_MODULE_SEL, SPI_MODE_WRITE_ONLY);
            spi_set_irq_mask(SPI_MODULE_SEL, SPI_TXFIFO_INT_EN);
        } else {
            spi_set_transmode(SPI_MODULE_SEL, SPI_MODE_READ_ONLY);
        }
        spi_slave_flag = !spi_slave_flag;
                #endif
    }

    if (spi_get_irq_mask(SPI_MODULE_SEL, SPI_TXFIFO_INT_EN) && spi_get_irq_status(SPI_MODULE_SEL, SPI_TXF_INT)) {
        spi_irq_tx_fifo_process();
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_TXF_INT); //clr
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
                #if defined(MCU_CORE_TL322X)
                    #if (SPI_MODULE_SEL == LSPI_MODULE)
PLIC_ISR_REGISTER(lspi_irq_handler, IRQ_LSPI)
                    #endif
                #endif
            #endif// #if (SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
    #endif // #elif (SPI_DEVICE == SPI_SLAVE_DEVICE)
#endif
