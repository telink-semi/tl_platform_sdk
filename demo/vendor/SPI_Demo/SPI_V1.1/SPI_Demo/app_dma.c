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
#include "app_config.h"

#if(SPI_MODE == SPI_DMA_MODE)
/**********************************************************************************************************************
 *                                         SPI device  selection                                                     *
 *********************************************************************************************************************/
#define SPI_MASTER_DEVICE                   1
#define SPI_SLAVE_DEVICE                    2

#define SPI_DEVICE                     SPI_MASTER_DEVICE

/**********************************************************************************************************************
 *                                         SPI protocol demo selection                                                *
 *********************************************************************************************************************/
#define B85M_SLAVE_PROTOCOL                 1 // B85m as slave
#define B91M_SLAVE_PROTOCOL                 2 // Telink RISC-V MCU hspi/pspi/gspi/lspi slave mode as slave
#define B91M_SPI_SLAVE_PROTOCOL             3 // Telink RISC-V MCU spi slave as slave

#define SPI_PROTOCOL                   B91M_SLAVE_PROTOCOL

/**********************************************************************************************************************
 *                                         SPI module selection                                                       *
 *********************************************************************************************************************/
/* Note:TL321X only supports gspi!!!*/
#define LSPI_MODULE                              0
#define GSPI_MODULE                              1

#define SPI_MODULE_SEL                          GSPI_MODULE
/**********************************************************************************************************************
 *                                         SPI multiple slave
 *********************************************************************************************************************/
#define ONE_SLAVE                                0
#define MULTI_SLAVE                              1

#define SPI_SLAVE_NUM                        ONE_SLAVE
/**********************************************************************************************************************
 *                                         3line SPI  enable                                                      *
 *********************************************************************************************************************/
#define SPI_NORMAL_SLAVE                            0
#define SPI_3LINE_SLAVE                             1

#define SPI_SLAVE_MODE                       SPI_NORMAL_SLAVE
/**********************************************************************************************************************
 *                                          SPI slave ready test
 *When the slave_ready bit of the slave is 1, the master sends read status cmd, and the slave will reply 0x5a.
 *When the slave_ready bit of the slave is 0, the master sends read status cmd, and the slave will reply 0x00.
 *********************************************************************************************************************/
#define SPI_SLAVE_READY_TEST                            0
/**********************************************************************************************************************
*                                         TL751X(256 bit dummy)SPI clock set
* * When sclk and hclk are set to 24MHz, the SPI_CLK[use DMA] range are as follows
* B85M_SLAVE_PROTOCOL           LSPI_MODULE             max:depend on spi slave  min:48000
*                               GSPI_MODULE             max:depend on spi slave  min:48000
* B91M_SLAVE_PROTOCOL           LSPI_MODULE  single io  max:6000000   min:48000
*                                            dual io    max:6000000   min:48000
*                                            quad io    max:6000000   min:48000
*                                            octal io   max:6000000   min:48000
*                               GSPI_MODULE  single io  max:6000000   min:48000
*                                            3_line io  max:6000000   min:48000
*                                            dual io    max:6000000   min:48000
*                                            quad io    max:6000000   min:48000
*                                            octal io   max:6000000   min:48000
* B91M_SPI_SLAVE_PROTOCOL       LSPI_MODULE single io   max:12000000  min:48000
*                                            dual io    max:12000000  min:48000
*                               GSPI_MODULE single io   max:10000000   min:48000
*                                            dual io    max:10000000   min:48000                                                      *
*********************************************************************************************************************/

#define SPI_CLK                             400000



/**********************************************************************************************************************
 *                                        SPI  pin  define                                                        *
 *********************************************************************************************************************/
#if (SPI_MODULE_SEL == GSPI_MODULE)
#if defined(MCU_CORE_B92)||defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
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
    .spi_io6_pin        = GSPI_IO6_PF3_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_io7_pin        = GSPI_IO7_PF4_PIN,//octal mode is required, otherwise it is NONE_PIN.
    .spi_dm_pin         = GSPI_NONE_PIN,//opi psram is required,otherwise it is NONE_PIN.
};
#endif
#if (SPI_SLAVE_NUM == MULTI_SLAVE)
#if defined(MCU_CORE_B92)
//39 GPIOs can be multiplexed as PIN for GSPI_CSN0_IO function.Only a part of IO is listed here.
#define SLAVE_CSN_PIN_NUM    8
gpio_func_pin_e slave_csn_pin[SLAVE_CSN_PIN_NUM] = {GPIO_FC_PA0, GPIO_FC_PB2, GPIO_FC_PB3, GPIO_FC_PB4, GPIO_FC_PB5, GPIO_FC_PB6, GPIO_FC_PB7};
#endif
#if defined(MCU_CORE_TL751X)
//4 GPIOs can be multiplexed as PIN for GSPI_CSN0_IO function.Only a part of IO is listed here.
#define SLAVE_CSN_PIN_NUM    4
gspi_pin_def_e slave_csn_pin[SLAVE_CSN_PIN_NUM] = {GSPI_CSN0_PA0_PIN, GSPI_CSN0_PB7_PIN, GSPI_CSN0_PG1_PIN, GSPI_CSN0_PJ2_PIN};
#endif
#endif
#elif (SPI_MODULE_SEL == LSPI_MODULE)
#if defined(MCU_CORE_B92)||defined(MCU_CORE_TL721X)
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
volatile unsigned char end_irq_flag = 0;
volatile unsigned char rx_dma_flag = 0;
#define     DATA_BYTE_LEN     16
unsigned char spi_rx_buff[DATA_BYTE_LEN] __attribute__((aligned(4))) = {0x00};
#if (SPI_PROTOCOL == B85M_SLAVE_PROTOCOL)
#define SPI_B85M_READ_CMD           0x80
#define SPI_B85M_WRITE_CMD          0x00

typedef struct {
    unsigned char address[3];
    unsigned char cmd;
    unsigned char data[DATA_BYTE_LEN];
} spi_b85m_slave_protocol_t;

spi_b85m_slave_protocol_t __attribute__((aligned(4))) spi_tx_buff = {
    .address = {0x04, 0x40, 0x00},
    .cmd = SPI_B85M_WRITE_CMD,
    .data = {0xAA, 0x10, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xBB},
};

#elif(SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
#if(SPI_SLAVE_READY_TEST == 1)
volatile unsigned char spi_b91m_slave_io_mode;
#endif
spi_wr_rd_config_t spi_b91m_slave_protocol_config = {
    .spi_io_mode        = SPI_SINGLE_MODE,/*IO mode set to SPI_3_LINE_MODE when SPI_3LINE_SLAVE.*/
    .spi_dummy_cnt      = 32,//B92 supports up to 32 clk cycle dummy, and TL751X, TL721X,TL321X supports up to 256 clk cycle dummy.
    .spi_cmd_en         = 1,
    .spi_addr_en        = 0,
    .spi_addr_len       = 0,//when spi_addr_en = 0,invalid set.
    .spi_cmd_fmt_en     = 0,//when spi_cmd_en = 0,invalid set.
    .spi_addr_fmt_en    = 0,//when spi_addr_en = 0,invalid set.
};

typedef struct
{
    unsigned char address[4];
    unsigned char data_len;
    unsigned char data[DATA_BYTE_LEN + 3];
}  spi_b91m_slave_protocol_t;

spi_b91m_slave_protocol_t __attribute__((aligned(4))) spi_tx_buff =
{
    .address = {0xc0, 0x20, 0x04, 0x00},
    .data_len = DATA_BYTE_LEN + 3,
    .data = {0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
};
#elif(SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)
#define spi_slave_address   0xc0200400
spi_wr_rd_config_t spi_b91m_spi_slave_protocol_config = {
    .spi_io_mode        = SPI_SINGLE_MODE,
    .spi_dummy_cnt      = 8,
    .spi_cmd_en         = 1,
    .spi_addr_en        = 1,
    .spi_addr_len       = 4,//when hspi_addr_en = 0,invalid set.
    .spi_cmd_fmt_en     = 0,//when hspi_cmd_en = 0,invalid set.
    .spi_addr_fmt_en    = 0,//when hspi_addr_en=0,invalid set.
};
typedef struct
    {
        unsigned char data[DATA_BYTE_LEN];
    }  spi_b91m_spi_slave_protocol_t;
    spi_b91m_spi_slave_protocol_t __attribute__((aligned(4)))  spi_tx_buff =
    {
        .data = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
    };
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

    spi_master_init(SPI_MODULE_SEL, sys_clk.pll_clk * 1000000/SPI_CLK, SPI_MODE0);
    spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);//clr
    spi_set_irq_mask(SPI_MODULE_SEL, SPI_END_INT_EN);//endint_en
    spi_set_tx_dma_config(SPI_MODULE_SEL,SPI_TX_DMA_CHN);
    spi_set_master_rx_dma_config(SPI_MODULE_SEL,SPI_RX_DMA_CHN);
#if (SPI_MODULE_SEL == GSPI_MODULE)
    gspi_set_pin(&gspi_pin_config);
    plic_interrupt_enable(IRQ_GSPI);
#elif(SPI_MODULE_SEL == LSPI_MODULE)
    lspi_set_pin(&lspi_pin_config);
    plic_interrupt_enable(IRQ_LSPI);
#endif

#if (SPI_PROTOCOL == B85M_SLAVE_PROTOCOL)
    spi_master_config(SPI_MODULE_SEL,SPI_NOMAL);
#elif(SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
    spi_master_config_plus(SPI_MODULE_SEL, &spi_b91m_slave_protocol_config);
#if(SPI_SLAVE_READY_TEST == 1)
    spi_b91m_slave_io_mode = spi_b91m_slave_protocol_config.spi_io_mode;
#endif

#elif(SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)
    spi_master_config_plus(SPI_MODULE_SEL, &spi_b91m_spi_slave_protocol_config);
#endif

    dma_set_irq_mask(SPI_RX_DMA_CHN,TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
}
#if(SPI_SLAVE_READY_TEST == 1)
/**
 * @brief       This function servers to get lspi/gspi slave ready status. When slave is ready, slave ready reply a byte data:0x5a.
 * slave reply a byte data: 0x00.indicating that slave is not ready for data transmission.
 * @param[in]   spi_sel     - the spi module.
 * @param[in]   mode        - the spi master io mode.
 * @return      1:Indicates that the slave is ready. others:Indicates that slave is not ready.
 */
drv_api_status_e spi_master_get_slave_ready(spi_sel_e spi_sel,spi_io_mode_e mode)
{
    unsigned char slave_ready_flag = 0;

    switch (mode)
    {
        case SPI_SINGLE_MODE:
            spi_master_read_plus(spi_sel, SPI_READ_STATUS_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)(&slave_ready_flag), 1, SPI_MODE_RD_DUMMY_READ);
            break;
        case SPI_DUAL_MODE:
            spi_master_read_plus(spi_sel, SPI_READ_STATUS_DUAL_CMD, (unsigned int)NULL, (unsigned char*)(&slave_ready_flag), 1, SPI_MODE_RD_DUMMY_READ);
            break;
        case SPI_QUAD_MODE:
            spi_master_read_plus(spi_sel, SPI_READ_STATUS_QUAD_CMD, (unsigned int)NULL, (unsigned char*)(&slave_ready_flag), 1, SPI_MODE_RD_DUMMY_READ);
            break;
#if defined(MCU_CORE_TL751X)
        case SPI_OCTAL_MODE:
            spi_master_read_plus(spi_sel, SPI_READ_STATUS_OCTAL_CMD, (unsigned int)NULL, (unsigned char*)(&slave_ready_flag), 1, SPI_MODE_RD_DUMMY_READ);
            break;
#endif
        case SPI_3_LINE_MODE:
            spi_master_read_plus(spi_sel, SPI_READ_STATUS_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)(&slave_ready_flag), 1, SPI_MODE_RD_DUMMY_READ);
            break;
    }
    if(SPI_WAIT(spi_is_busy,spi_sel,g_spi_timeout_error[spi_sel].g_spi_error_timeout_us,g_spi_timeout_error[spi_sel].spi_timeout_handler,SPI_API_ERROR_TIMEOUT_BUS_BUSY)){
        return DRV_API_TIMEOUT;
    }
    if (slave_ready_flag == 0x5a)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
#endif
void main_loop (void)
{
    delay_ms(200);
    gpio_toggle(LED1);
#if (SPI_PROTOCOL == B85M_SLAVE_PROTOCOL)
    spi_tx_buff.cmd = SPI_B85M_WRITE_CMD;
    spi_master_write_dma(SPI_MODULE_SEL, (unsigned char*)&spi_tx_buff, sizeof(spi_tx_buff));
    while(!end_irq_flag);//Wait for spi transmission end interrupt.
    end_irq_flag = 0;
    spi_clr_irq_mask(SPI_MODULE_SEL,SPI_END_INT_EN);

    spi_tx_buff.cmd = SPI_B85M_READ_CMD;
    //Write address and command first, then read.
    spi_master_write_read_dma(SPI_MODULE_SEL, (unsigned char*)&spi_tx_buff, sizeof(spi_tx_buff.address)+ sizeof(spi_tx_buff.cmd), (unsigned char*)spi_rx_buff , DATA_BYTE_LEN);
    while(!rx_dma_flag);//Wait for rx dma transmission complete interrupt.
    rx_dma_flag = 0;
    spi_set_irq_mask(SPI_MODULE_SEL,SPI_END_INT_EN);

    for (unsigned char i = 0; i < DATA_BYTE_LEN; i++)
    {
        if(spi_tx_buff.data[i] != (spi_rx_buff[i]))
        {
            gpio_set_high_level(LED2);//LED on indicate data error
            while(1);
        }
    }
    spi_tx_buff.data[0]++;
#elif(SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
#if(SPI_SLAVE_READY_TEST == 1)
    while(1)
    {
        if(spi_master_get_slave_ready(SPI_MODULE_SEL,spi_b91m_slave_io_mode) == 0)
        {
            gpio_set_high_level(LED2);//If the LED is always on, the slave ready function is abnormal.
        }
        else if(spi_master_get_slave_ready(SPI_MODULE_SEL,spi_b91m_slave_io_mode) == 1)
        {
            gpio_toggle(LED2);//The flashing LED indicates that the slave ready function is normal.
            break;
        }
        else if(spi_master_get_slave_ready(SPI_MODULE_SEL,spi_b91m_slave_io_mode) == DRV_API_TIMEOUT)
        {
            spi_hw_fsm_reset(SPI_MODULE_SEL);//the wait for slave ready function has timed out,reset spi module.
            break;
        }
    }
#else
    end_irq_flag = 0;
    spi_master_write_dma_plus(SPI_MODULE_SEL,   SPI_WRITE_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)&spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_DUMMY_WRITE);
    while(!end_irq_flag);//Wait for spi transmission end interrupt.
    end_irq_flag = 0;
    spi_clr_irq_mask(SPI_MODULE_SEL,SPI_END_INT_EN);
    rx_dma_flag = 0;
    spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, (unsigned int)NULL, (unsigned char*)(spi_rx_buff), DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    while(!rx_dma_flag);//Wait for rx dma transmission complete interrupt.
    rx_dma_flag = 0;
    spi_set_irq_mask(SPI_MODULE_SEL,SPI_END_INT_EN);

    for (unsigned char i = 0; i < DATA_BYTE_LEN; i++)
    {
        if(spi_tx_buff.data[3 + i] != (spi_rx_buff[i]))
        {
            gpio_set_high_level(LED2);//LED on indicate data error
            while(1);
        }
    }
    spi_tx_buff.data[3]++;
#endif
#elif(SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)

    spi_master_write_dma_plus(SPI_MODULE_SEL, SPI_SLAVE_WRITE_DATA_AND_ADDR_DUL_4CYC_CMD, spi_slave_address, (unsigned char*)&spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_WRITE_ONLY);
    while(!end_irq_flag);//Wait for spi transmission end interrupt.
    end_irq_flag = 0;

    spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_SLAVE_READ_DATA_AND_ADDR_DUL_4CYC_CMD, spi_slave_address, (unsigned char*)spi_rx_buff, DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
    while(!end_irq_flag);//Wait for spi transmission end interrupt.
    end_irq_flag = 0;

    for (unsigned char i = 0; i < DATA_BYTE_LEN; i++)
    {
        if(spi_tx_buff.data[i] != (spi_rx_buff[i]))
        {
            gpio_set_high_level(LED2);//LED on indicate data error
            while(1);
        }
    }
    spi_tx_buff.data[0]++;
#endif
#if (SPI_SLAVE_NUM == MULTI_SLAVE)
#if (SPI_MODULE_SEL == GSPI_MODULE)
for(unsigned char i = 0;i < SLAVE_CSN_PIN_NUM-1; i++)
{
    if (gspi_pin_config.spi_csn_pin == slave_csn_pin[i])
    {
        gspi_change_csn_pin(slave_csn_pin[i],slave_csn_pin[i+1]);
        gspi_pin_config.spi_csn_pin = slave_csn_pin[i+1];
        break;
    }
}
#endif
#endif
}
#if(SPI_MODULE_SEL == GSPI_MODULE)
_attribute_ram_code_sec_noinline_ void gspi_irq_handler(void)
#elif(SPI_MODULE_SEL == LSPI_MODULE)
_attribute_ram_code_sec_noinline_ void lspi_irq_handler(void)
#endif
{
    if(spi_get_irq_status(SPI_MODULE_SEL,SPI_END_INT))
    {

        spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);//clr
        end_irq_flag = 1;
    }
}

#if(SPI_MODULE_SEL == GSPI_MODULE)
PLIC_ISR_REGISTER(gspi_irq_handler, IRQ_GSPI)
#elif(SPI_MODULE_SEL == LSPI_MODULE)
PLIC_ISR_REGISTER(lspi_irq_handler, IRQ_LSPI)
#endif

_attribute_ram_code_sec_noinline_ void dma_irq_handler(void)
{
    if(dma_get_tc_irq_status(BIT(SPI_RX_DMA_CHN)))
    {
        dma_clr_tc_irq_status(BIT(SPI_RX_DMA_CHN));
        rx_dma_flag = 1;
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
/**********************************************************************************************************************
    *                                         SPI slave setting                                                           *
    *********************************************************************************************************************/
#elif(SPI_DEVICE == SPI_SLAVE_DEVICE)
#if(SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
/**********************************************************************************************************************
 *                                          global variable                                                         *
 *********************************************************************************************************************/
#define SPI_RX_BUFF_LEN     24
#define DATA_BYTE_LEN       16
#define DATA_BYTE_OFFSET    8 //must be a multiple 4
unsigned char spi_slave_rx_buff[SPI_RX_BUFF_LEN+4] __attribute__((aligned(4))) = {0x00};

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
    
#if(SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)

    spi_slave_init(SPI_MODULE_SEL, SPI_MODE0);

    //B92 supports up to 32 clk cycle dummy, and TL751X supports up to 256 clk cycle dummy.
    spi_set_dummy_cnt(SPI_MODULE_SEL, 32);
    spi_clr_irq_status(SPI_MODULE_SEL, FLD_SPI_SLV_CMD_EN |FLD_SPI_END_INT_EN);
    spi_set_irq_mask(SPI_MODULE_SEL,SPI_SLV_CMD_EN |SPI_END_INT_EN);//endint_en txfifoint_en rxfifoint_en

#if defined(MCU_CORE_B92)
    /**
     * In order to solve the logic bug of GSPI rx DMA (LSPI tx/rx dma,GSPI tx DMA does not affect),
     * spi_hw_fsm_reset(GSPI_MODULE); must be called every time the DMA transfer is complete when using GSPI rx DMA,
     * changed by pengxiang.hong 20230328.
     */
    dma_set_irq_mask(SPI_RX_DMA_CHN,TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
#endif
#if (SPI_MODULE_SEL == GSPI_MODULE)
    gspi_set_pin(&gspi_pin_config);
    plic_interrupt_enable(IRQ_GSPI);
#elif(SPI_MODULE_SEL == LSPI_MODULE)
    lspi_set_pin(&lspi_pin_config);
    plic_interrupt_enable(IRQ_LSPI);
#endif
    spi_set_tx_dma_config(SPI_MODULE_SEL, SPI_TX_DMA_CHN);
    spi_set_slave_rx_dma_config(SPI_MODULE_SEL, SPI_RX_DMA_CHN);
#if(SPI_SLAVE_MODE == SPI_3LINE_SLAVE)
    spi_set_io_mode(SPI_MODULE_SEL,SPI_3_LINE_MODE);
#endif

    core_interrupt_enable();
#elif(SPI_PROTOCOL == B91M_SPI_SLAVE_PROTOCOL)
#if defined(MCU_CORE_B92)
    spi_slave_set_pin();//spi slave only need set pin.
#else
    sspi_pin_config_t  sspi_pin_config =
    {
        .spi_clk_pin        = GPIO_FC_PA0,
        .spi_csn_pin        = GPIO_FC_PA1,
        .spi_mosi_io0_pin   = GPIO_FC_PA2,
        .spi_miso_io1_pin   = GPIO_FC_PA3,
    };
    spi_slave_set_pin(&sspi_pin_config);//spi slave only need set pin.
#endif
#endif
}

void main_loop (void)
{
    delay_ms(200);
#if(SPI_SLAVE_READY_TEST == 1)
    spi_slave_ready_en(SPI_MODULE_SEL);
#endif
    gpio_toggle(LED1);
}

#if(SPI_PROTOCOL == B91M_SLAVE_PROTOCOL)
#if(SPI_MODULE_SEL == GSPI_MODULE)
_attribute_ram_code_sec_noinline_ void gspi_irq_handler(void)
#elif(SPI_MODULE_SEL == LSPI_MODULE)
_attribute_ram_code_sec_noinline_ void lspi_irq_handler(void)
#endif
{
    if (spi_get_irq_status(SPI_MODULE_SEL,SPI_SLV_CMD_INT))
    {
        switch (spi_slave_get_cmd(SPI_MODULE_SEL))
        {
            case SPI_WRITE_DATA_SINGLE_CMD:
            case SPI_WRITE_DATA_DUAL_CMD:
            case SPI_WRITE_DATA_QUAD_CMD:
#if defined(MCU_CORE_TL751X)
            case SPI_WRITE_DATA_OCTAL_CMD:
#endif
#if defined(MCU_CORE_B92)
            spi_set_rx_dma(SPI_MODULE_SEL, (unsigned char*)spi_slave_rx_buff+4);
#else
            spi_set_rx_dma(SPI_MODULE_SEL, (unsigned char*)(spi_slave_rx_buff+4),SPI_RX_BUFF_LEN);
#endif
            break;

            case SPI_READ_DATA_SINGLE_CMD:
            case SPI_READ_DATA_DUAL_CMD:
            case SPI_READ_DATA_QUAD_CMD:
#if defined(MCU_CORE_TL751X)
            case SPI_READ_DATA_OCTAL_CMD:
#endif
                spi_set_tx_dma(SPI_MODULE_SEL, (unsigned char*)spi_slave_rx_buff+4+DATA_BYTE_OFFSET,DATA_BYTE_LEN);
            break;
        }
        spi_clr_irq_status(SPI_MODULE_SEL,SPI_SLV_CMD_INT);//clr
    }
    if(spi_get_irq_status(SPI_MODULE_SEL,SPI_END_INT))
    {
#if(SPI_SLAVE_READY_TEST == 1)
            if((0 == spi_get_txfifo_num(SPI_MODULE_SEL)) && (0 == spi_get_rxfifo_num(SPI_MODULE_SEL))){
                spi_slave_ready_en(SPI_MODULE_SEL);
            }
#endif
        spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);//clr
    }
}
#if(SPI_MODULE_SEL == GSPI_MODULE)
PLIC_ISR_REGISTER(gspi_irq_handler, IRQ_GSPI)
#elif(SPI_MODULE_SEL == LSPI_MODULE)
PLIC_ISR_REGISTER(lspi_irq_handler, IRQ_LSPI)
#endif
#endif

#if defined(MCU_CORE_B92)

/**
 * Bugfix: reset GSPI RXDMA in DMA transfer completion interrupt(this is a hardware bug already confirmed with jianzhi)
 * changed by pengxiang.hong 20230328.
 */
_attribute_ram_code_sec_noinline_ void dma_irq_handler(void)
{
    if(dma_get_tc_irq_status(BIT(SPI_RX_DMA_CHN)))
    {
        dma_clr_tc_irq_status(BIT(SPI_RX_DMA_CHN));
        if(SPI_MODULE_SEL == GSPI_MODULE)
        {
            spi_hw_fsm_reset(GSPI_MODULE);
        }
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
#endif
#endif
#endif
