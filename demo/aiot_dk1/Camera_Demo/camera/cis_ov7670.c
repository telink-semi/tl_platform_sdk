/********************************************************************************************************
 * @file    cis_ov7670.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"
#include "../lcd/lcd_2inch_drv.h"

#define CIS_USB_DISPLAY_EN 0
#define I2C1_M_CLK_SPEED   200000

extern void lcd_spi_cfg(void);
extern void lcd_spi_cfg_disable(void);
extern void lcd_spi_display(int x, int y, unsigned char *image, int width, int height);

#define LSPI_RX_DMA_CHN  DMA0
#define LSPI_TX_DMA_CHN  DMA1
#define GSPI_RX_DMA_CHN  DMA2
#define GSPI_TX_DMA_CHN  DMA3

#define CIS_IMAGE_WIDTH  LCD_2IN_HEIGHT
#define CIS_IMAGE_HEIGHT LCD_2IN_WIDTH
#define CIS_RX_BUFF_LEN  (CIS_IMAGE_WIDTH * 5)
#define CIS_FRAME_SIZE   (CIS_IMAGE_WIDTH * CIS_IMAGE_HEIGHT * 2)

#define TEST_PIN  PIN_J4_TX
#define TEST_PIN1  PIN_J4_RX


const unsigned char c_bitmap_lspi[4] = {7, 5, 3, 1};
const unsigned char c_bitmap_gspi[4] = {6, 4, 2, 0};

unsigned char tbl_nib_lspi[16], tbl_nib_gspi[16];

int                                                       cis_rx_buff_idx = 0;
int                                                       cis_dat_cnt     = 0;
int                                                       cis_rd_cnt      = CIS_FRAME_SIZE + 2;
int                                                       cis_wr_cnt      = 0;
__attribute__((section(".retention_data"))) unsigned char cis_rx_buff[4][CIS_RX_BUFF_LEN + 0] __attribute__((aligned(4)));
unsigned char                                             cis_frame[CIS_FRAME_SIZE];
int                                                       cis_capture_busy = 0;
int                                                       cis_capture      = 0;
unsigned int                                              cis_bulk_irq_cnt = 0;
unsigned int                                              cis_bulk_wr_cnt  = 0;
unsigned                                                  cis_image_sent_time;

dma_chain_config_t  lspi_chain[2];
dma_chain_config_t  gspi_chain[2];
extern dma_config_t gspi_slave_rx_dma_config;
extern dma_config_t lspi_slave_rx_dma_config;

int cis_vs_cnt = 0;

unsigned char *get_capture_buff(void)
{
    return cis_frame;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// OV7670 camera module
//  PE0 PE7: VS        HS
//    PE1 PF0: PCK        XCK
//    PE2 PF1: D7        D6
//    PE3 PF2: D5        D4
//    PE4 PF5: D3        D2
//    PE5 PG4: D1        D0(x)
//    PE6 PG5: RSTB    PWDN(x)
//    PF3 PG3: PCK2
//    PF4 PG2: SDA
//    PF6 PG1: SCL
//  PF7    : D0
//  PA0    : PWDN
//  PA1    : HS2
/////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    gpio_func_pin_e pin_xclk;
    gpio_func_pin_e pin_scl;
    gpio_func_pin_e pin_sda;

    gpio_pin_e pin_pclk;
    gpio_pin_e pin_pclk2;
    gpio_pin_e pin_pwdn;
    gpio_pin_e pin_rstb;
    gpio_pin_e pin_vs;
    gpio_pin_e pin_hs;
    gpio_pin_e pin_hs2;
    gpio_pin_e pin_d7;
    gpio_pin_e pin_d6;
    gpio_pin_e pin_d5;
    gpio_pin_e pin_d4;
    gpio_pin_e pin_d3;
    gpio_pin_e pin_d2;
    gpio_pin_e pin_d1;
    gpio_pin_e pin_d0;
} cis_pin_config_t;

cis_pin_config_t cis_cfg = {

    .pin_xclk = (gpio_func_pin_e)CAMERA_PIN_CIS_XCLK,
    .pin_sda  = (gpio_func_pin_e)CAMERA_PIN_CIS_SDA,
    .pin_scl  = (gpio_func_pin_e)CAMERA_PIN_CIS_SCL,

    .pin_vs   = CAMERA_PIN_CIS_VS,
    .pin_rstb = CAMERA_PIN_CIS_RSTB, 
    .pin_pwdn = CAMERA_PIN_CIS_PWDN, 

    .pin_hs   = CAMERA_PIN_CIS_HS,
    .pin_pclk = CAMERA_PIN_CIS_PCLK,
    .pin_d0   = CAMERA_PIN_CIS_D0,
    .pin_d1   = CAMERA_PIN_CIS_D1,
    .pin_d2   = CAMERA_PIN_CIS_D2,
    .pin_d3   = CAMERA_PIN_CIS_D3,

    .pin_hs2   = CAMERA_PIN_CIS_HS2,
    .pin_pclk2 = CAMERA_PIN_CIS_PCLK2,
    .pin_d4    = CAMERA_PIN_CIS_D4,
    .pin_d5    = CAMERA_PIN_CIS_D5,
    .pin_d6    = CAMERA_PIN_CIS_D6,
    .pin_d7    = CAMERA_PIN_CIS_D7,

};

#if defined(MCU_CORE_TL322X)
typedef gpio_func_pin_e lspi_pin_def_e;
#define I2C_CHN                                                            I2C1
#define i2c1_m_master_init()                                               i2c_master_init(I2C_CHN)
#define i2c1_m_master_write(id, wr_data, wr_len)                           i2c_master_write(I2C_CHN, id, wr_data, wr_len) 
#define i2c1_m_set_master_clk(clk)                                         i2c_set_master_clk(I2C_CHN, clk)  
#define i2c1_m_set_pin(scl, sda)                                           i2c_set_pin(I2C_CHN, scl, sda)
#define i2c1_m_master_write_read(id, wr_data, wr_len, rd_data, rd_len)     i2c_master_write_read(I2C_CHN, id, wr_data, wr_len, rd_data, rd_len)
#define FLD_GPIO_IRQ                                                       GPIO_IRQ_IRQ0
#define FLD_GPIO_IRQ_MASK                                                  GPIO_IRQ_IRQ0
#define IRQ_GPIO                                                           IRQ_GPIO_IRQ0
#define IRQ_USB_ENDPOINT                                                   IRQ_USB1_ENDPOINT
#define _gpio_set_irq(pin, intr)                                           gpio_set_irq(GPIO_IRQ0, pin, intr)
#elif defined(MCU_CORE_TL721X)
#define _gpio_set_irq(pin, intr)                                           gpio_set_irq(pin, intr)
#define FLD_GPIO_IRQ                                                       FLD_GPIO_IRQ_CLR
#define FLD_GPIO_IRQ_MASK                                                  GPIO_IRQ_MASK_GPIO
#endif

lspi_pin_config_t lspi_pin_config = {
    .spi_csn_pin      = (lspi_pin_def_e)CAMERA_PIN_SPI0_CSN,
    .spi_clk_pin      = (lspi_pin_def_e)CAMERA_PIN_SPI0_CLK,
    .spi_mosi_io0_pin = (lspi_pin_def_e)CAMERA_PIN_SPI0_MOSI,
    .spi_miso_io1_pin = (lspi_pin_def_e)CAMERA_PIN_SPI0_MISO, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = (lspi_pin_def_e)CAMERA_PIN_SPI0_IO2,  //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = (lspi_pin_def_e)CAMERA_PIN_SPI0_IO3,  //quad  mode is required, otherwise it is NONE_PIN.
};

gspi_pin_config_t gspi_pin_config = {
    .spi_csn_pin      = (gpio_func_pin_e)CAMERA_PIN_SPI1_CSN,
    .spi_clk_pin      = (gpio_func_pin_e)CAMERA_PIN_SPI1_CLK,
    .spi_mosi_io0_pin = (gpio_func_pin_e)CAMERA_PIN_SPI1_MOSI,
    .spi_miso_io1_pin = (gpio_func_pin_e)CAMERA_PIN_SPI1_MISO, //3line mode is required, otherwise it is NONE_PIN.
    .spi_io2_pin      = (gpio_func_pin_e)CAMERA_PIN_SPI1_IO2,  //quad  mode is required, otherwise it is NONE_PIN.
    .spi_io3_pin      = (gpio_func_pin_e)CAMERA_PIN_SPI1_IO3,  //quad  mode is required, otherwise it is NONE_PIN.
};

unsigned char ov7670_reg_tbl[] = {
    0x3a, 0x04, 0x40, 0xd0, 0x12, 0x14, 0x32, 0x80, 0x17, 0x16, 0x18, 0x04, 0x19, 0x02, 0x1a,
    0x7a, //0x7b,            // 0x7a
    0x03,
    0x0a, //0x06,            // 0x0a (480)
    0x0c, 0x04, 0x3e, 0x00, 0x70, 0x3a, 0x71, 0x35, 0x72, 0x11, 0x73, 0x00, 0xa2, 0x02, 0x11, 0x81,

    0x7a, 0x20, 0x7b, 0x1c, 0x7c, 0x28, 0x7d, 0x3c, 0x7e, 0x55, 0x7f, 0x68, 0x80, 0x76, 0x81, 0x80, 0x82, 0x88, 0x83, 0x8f, 0x84, 0x96, 0x85, 0xa3, 0x86, 0xaf,
    0x87, 0xc4, 0x88, 0xd7, 0x89, 0xe8,

    0x13, 0xe0, 0x00, 0x00,

    0x10, 0x00, 0x0d, 0x00, 0x14, 0x28, 0xa5, 0x05, 0xab, 0x07, 0x24, 0x75, 0x25, 0x63, 0x26, 0xA5, 0x9f, 0x78, 0xa0, 0x68, 0xa1, 0x03, 0xa6, 0xdf, 0xa7, 0xdf,
    0xa8, 0xf0, 0xa9, 0x90, 0xaa, 0x94, 0x13, 0xe5,

    0x0e, 0x61, 0x0f, 0x4b, 0x16, 0x02, 0x1e, 0x07, 0x21, 0x02, 0x22, 0x91, 0x29, 0x07, 0x33, 0x0b, 0x35, 0x0b, 0x37, 0x1d, 0x38, 0x71, 0x39, 0x2a, 0x3c, 0x78,
    0x4d, 0x40, 0x4e, 0x20, 0x69, 0x00, 0x6b, 0x60, 0x74, 0x19, 0x8d, 0x4f, 0x8e, 0x00, 0x8f, 0x00, 0x90, 0x00, 0x91, 0x00, 0x92, 0x00, 0x96, 0x00, 0x9a, 0x80,
    0xb0, 0x84, 0xb1, 0x0c, 0xb2, 0x0e, 0xb3, 0x82, 0xb8, 0x0a,


    0x43, 0x14, 0x44, 0xf0, 0x45, 0x34, 0x46, 0x58, 0x47, 0x28, 0x48, 0x3a, 0x59, 0x88, 0x5a, 0x88, 0x5b, 0x44, 0x5c, 0x67, 0x5d, 0x49, 0x5e, 0x0e, 0x64, 0x04,
    0x65, 0x20, 0x66, 0x05, 0x94, 0x04, 0x95, 0x08, 0x6c, 0x0a, 0x6d, 0x55, 0x6e, 0x11, 0x6f, 0x9f, 0x6a, 0x40, 0x01, 0x40, 0x02, 0x40, 0x13, 0xe7, 0x15,
    0x08, //bit3: reverse HREF    //0x00


    0x4f, 0x80, 0x50, 0x80, 0x51, 0x00, 0x52, 0x22, 0x53, 0x5e, 0x54, 0x80, 0x58, 0x9e,

    0x41, 0x08, 0x3f, 0x00, 0x75, 0x05, 0x76, 0xe1, 0x4c, 0x00, 0x77, 0x01, 0x3d, 0xc2, 0x4b, 0x09, 0xc9, 0x60, 0x41, 0x38, 0x56, 0x40,

    0x34, 0x11, 0x3b, 0x02,

    0xa4, 0x89, 0x96, 0x00, 0x97, 0x30, 0x98, 0x20, 0x99, 0x30, 0x9a, 0x84, 0x9b, 0x29, 0x9c, 0x03, 0x9d, 0x4c, 0x9e, 0x3f, 0x78, 0x04,

    0x79, 0x01, 0xc8, 0xf0, 0x79, 0x0f, 0xc8, 0x00, 0x79, 0x10, 0xc8, 0x7e, 0x79, 0x0a, 0xc8, 0x80, 0x79, 0x0b, 0xc8, 0x01, 0x79, 0x0c, 0xc8, 0x0f, 0x79, 0x0d,
    0xc8, 0x20, 0x79, 0x09, 0xc8, 0x80, 0x79, 0x02, 0xc8, 0xc0, 0x79, 0x03, 0xc8, 0x40, 0x79, 0x05, 0xc8, 0x30, 0x79, 0x26, 0x09, 0x00,
};

void lspi_pin_gpio_en(int en)
{
    (void)en;
#if SPI0_MODULE_ON
    if (!en) {
        gpio_function_dis((gpio_pin_e)lspi_pin_config.spi_csn_pin);
        gpio_function_dis((gpio_pin_e)lspi_pin_config.spi_clk_pin);
        gpio_function_dis((gpio_pin_e)lspi_pin_config.spi_mosi_io0_pin);
        gpio_function_dis((gpio_pin_e)lspi_pin_config.spi_miso_io1_pin);
        gpio_function_dis((gpio_pin_e)lspi_pin_config.spi_io2_pin);
        gpio_function_dis((gpio_pin_e)lspi_pin_config.spi_io3_pin);
    } else {
        gpio_function_en((gpio_pin_e)lspi_pin_config.spi_csn_pin);
        gpio_function_en((gpio_pin_e)lspi_pin_config.spi_clk_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_mosi_io0_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_miso_io1_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_io2_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_io3_pin);
    }
#endif
}

void gspi_pin_gpio_en(int en)
{
    (void)en;
#if SPI1_MODULE_ON
    if (!en) {
        gpio_function_dis((gpio_pin_e)gspi_pin_config.spi_csn_pin);
        gpio_function_dis((gpio_pin_e)gspi_pin_config.spi_clk_pin);
        gpio_function_dis((gpio_pin_e)gspi_pin_config.spi_mosi_io0_pin);
        gpio_function_dis((gpio_pin_e)gspi_pin_config.spi_miso_io1_pin);
        gpio_function_dis((gpio_pin_e)gspi_pin_config.spi_io2_pin);
        gpio_function_dis((gpio_pin_e)gspi_pin_config.spi_io3_pin);
    } else {
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_clk_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_csn_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_mosi_io0_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_miso_io1_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_io2_pin);
        gpio_function_en((gpio_pin_e)gspi_pin_config.spi_io3_pin);
    }
#endif
}

void lspi_gspi_input_en(void)
{
#if SPI1_MODULE_ON
    gpio_input_en((gpio_pin_e)gspi_pin_config.spi_csn_pin);
#if defined(MCU_CORE_TL322X)
    gpio_set_up_down_res((gpio_pin_e)gspi_pin_config.spi_csn_pin, GPIO_PIN_PULLUP_10K);
#endif
    gpio_input_en((gpio_pin_e)gspi_pin_config.spi_clk_pin);
    gpio_input_en((gpio_pin_e)gspi_pin_config.spi_mosi_io0_pin);
    gpio_input_en((gpio_pin_e)gspi_pin_config.spi_miso_io1_pin);
    gpio_input_en((gpio_pin_e)gspi_pin_config.spi_io2_pin);
    gpio_input_en((gpio_pin_e)gspi_pin_config.spi_io3_pin);
#endif

#if SPI0_MODULE_ON
    gpio_input_en((gpio_pin_e)lspi_pin_config.spi_csn_pin);
#if defined(MCU_CORE_TL322X)
    gpio_set_up_down_res((gpio_pin_e)lspi_pin_config.spi_csn_pin, GPIO_PIN_PULLUP_10K);
#endif
    gpio_input_en((gpio_pin_e)lspi_pin_config.spi_clk_pin);
    gpio_input_en((gpio_pin_e)lspi_pin_config.spi_mosi_io0_pin);
    gpio_input_en((gpio_pin_e)lspi_pin_config.spi_miso_io1_pin);
    gpio_input_en((gpio_pin_e)lspi_pin_config.spi_io2_pin);
    gpio_input_en((gpio_pin_e)lspi_pin_config.spi_io3_pin);
#endif
}

#if defined(MCU_CORE_TL721X)
/**
 * BIT[0:3]  the transfer mode.slave only.
 * the transfer sequence could be:
 * 0x0:write and read at the same time(must enable CmdEn).
 * 0x1:write only.
 * 0x2:read only(must enable CmdEn).
 * 0x3:write,read.
 * 0x4:read,write.
 * 0x5:write,dummy,read.
 * 0x6:read,dummy,write(must enable CmdEn).
 * 0x7:None Data(must enable CmdEn).
 * 0x8:Dummy,write.
 * 0x9:Dummy,read.
 * 0xa:Dummy,write and read.
 * 0xb~0xf:reserved.
 */
#define reg_spi_slv_trans_mode(i) REG_ADDR8(LSPI_BASE_ADDR + 0x29 + (i) * BASE_ADDR_DIFF)

enum
{
    FLD_SPI_SLV_TRANS_MODE = BIT_RNG(0, 3),
};

/**
 * @brief       This function servers to set spi transfer mode(slave only).
 * @param[in]   spi_sel - the spi module.
 * @param[in]   mode    - transfer mode.
 * @return      none.
 */
static void spi_set_slave_transmode(spi_sel_e spi_sel, spi_tans_mode_e mode)
{
    reg_spi_slv_trans_mode(spi_sel) = ((reg_spi_slv_trans_mode(spi_sel) & (~FLD_SPI_SLV_TRANS_MODE)) | (mode & 0xf));
}

#endif

static void ov7670_i2c_write(uint8_t reg, uint8_t value)
{
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = value;
    i2c1_m_master_write(0x42, buf, 2);
}

static void ov7670_config_window(uint16_t startx, uint16_t starty, uint16_t width, uint16_t height)
{
    uint16_t endx = (startx + width * 2) % 784; // VREF cycle is 784
    uint16_t endy = starty + height * 2;

    // config HREF
    ov7670_i2c_write(0x32, (endx & 0x7) << 3 | (startx & 0x7));
    ov7670_i2c_write(0x17, (startx & 0x7F8) >> 3);
    ov7670_i2c_write(0x18, (endx & 0x7F8) >> 3);

    // config VREF
    ov7670_i2c_write(0x03, (endy & 0x3) << 2 | (starty & 0x3));
    ov7670_i2c_write(0x19, (starty & 0x3FC) >> 2);
    ov7670_i2c_write(0x1A, (endy & 0x3FC) >> 2);
}

void spi_dma_init(spi_sel_e spi, int chn)
{
#if defined(MCU_CORE_TL322X)
    //GSPI clk pin will affect the pclk pin of camera, so we need to set slave mode firstly.
    spi_slave_init(spi, SPI_MODE0);
#endif
    spi_cmd_dis(spi);
    spi_addr_dis(spi);
    spi_set_io_mode(spi, SPI_QUAD_MODE);
    //TL751X, TL721X supports up to 256 clk cycle dummy.
    spi_set_dummy_cnt(spi, 0);
    spi_set_tx_dma_config(spi, chn + 1);
    spi_set_transmode(spi, SPI_MODE_READ_ONLY);
    spi_set_slave_transmode(spi, SPI_MODE_READ_ONLY);
    spi_set_slave_rx_dma_config(spi, chn);

    dma_set_irq_mask(chn, TC_MASK);
    dma_set_llp_irq_mode(chn, DMA_INTERRUPT_MODE);

    if (spi == CAMERA_SPI0_MODULE) {
        lspi_slave_rx_dma_config.write_num_en = 0;
#if defined(MCU_CORE_TL721X)
        lspi_pin_gpio_en(1); 
        gpio_set_up_down_res((gpio_pin_e)lspi_pin_config.spi_csn_pin, GPIO_PIN_PULLUP_10K);
        reg_gpio_func_mux(lspi_pin_config.spi_csn_pin) = CAMERA_PIN_FUNC_SPI0_CSN; 
#elif defined(MCU_CORE_TL322X)
        lspi_set_pin_mux((gpio_func_pin_e)lspi_pin_config.spi_clk_pin, CAMERA_PIN_FUNC_SPI0_CLK);
        reg_gpio_func_mux(lspi_pin_config.spi_csn_pin) = CAMERA_PIN_FUNC_SPI0_CSN;
        lspi_set_pin_mux((gpio_func_pin_e)lspi_pin_config.spi_mosi_io0_pin, CAMERA_PIN_FUNC_SPI0_MOSI);
        lspi_set_pin_mux((gpio_func_pin_e)lspi_pin_config.spi_miso_io1_pin, CAMERA_PIN_FUNC_SPI0_MISO);
        lspi_set_pin_mux((gpio_func_pin_e)lspi_pin_config.spi_io2_pin, CAMERA_PIN_FUNC_SPI0_IO2);
        lspi_set_pin_mux((gpio_func_pin_e)lspi_pin_config.spi_io3_pin, CAMERA_PIN_FUNC_SPI0_IO3);
        lspi_pin_gpio_en(1);
#endif
#if !SWITCH_DMA_BUFFER
        spi_set_slave_rx_dma_chain_llp(spi, chn, cis_rx_buff[0], CIS_RX_BUFF_LEN, &lspi_chain[0]);
        spi_rx_dma_add_list_element(spi, chn, &lspi_chain[0], &lspi_chain[1], cis_rx_buff[1], CIS_RX_BUFF_LEN);
        spi_rx_dma_add_list_element(spi, chn, &lspi_chain[1], &lspi_chain[0], cis_rx_buff[0], CIS_RX_BUFF_LEN);
#else
        spi_set_slave_rx_dma_chain_llp(spi, chn, cis_rx_buff[2], CIS_RX_BUFF_LEN, &lspi_chain[0]);
        spi_rx_dma_add_list_element(spi, chn, &lspi_chain[0], &lspi_chain[1], cis_rx_buff[3], CIS_RX_BUFF_LEN);
        spi_rx_dma_add_list_element(spi, chn, &lspi_chain[1], &lspi_chain[0], cis_rx_buff[2], CIS_RX_BUFF_LEN);
#endif
    } else {
        gspi_slave_rx_dma_config.write_num_en = 0;
#if defined(MCU_CORE_TL721X)
        gspi_pin_gpio_en(1);
        reg_gpio_func_mux(gspi_pin_config.spi_clk_pin) = (gpio_func_pin_e)CAMERA_PIN_FUNC_SPI1_CLK;

        gpio_set_up_down_res((gpio_pin_e)gspi_pin_config.spi_csn_pin, GPIO_PIN_PULLUP_10K);
        reg_gpio_func_mux(gspi_pin_config.spi_csn_pin) = (gpio_func_pin_e)CAMERA_PIN_FUNC_SPI1_CSN;

        reg_gpio_func_mux(gspi_pin_config.spi_mosi_io0_pin) = (gpio_func_pin_e)CAMERA_PIN_FUNC_SPI1_MOSI;
        reg_gpio_func_mux(gspi_pin_config.spi_miso_io1_pin) = (gpio_func_pin_e)CAMERA_PIN_FUNC_SPI1_MISO;
        reg_gpio_func_mux(gspi_pin_config.spi_io2_pin)      = (gpio_func_pin_e)CAMERA_PIN_FUNC_SPI1_IO2;
        reg_gpio_func_mux(gspi_pin_config.spi_io3_pin)      = (gpio_func_pin_e)CAMERA_PIN_FUNC_SPI1_IO3;
#elif defined(MCU_CORE_TL322X)
        gspi_set_pin_mux(gspi_pin_config.spi_clk_pin, CAMERA_PIN_FUNC_SPI1_CLK);
        reg_gpio_func_mux(gspi_pin_config.spi_csn_pin) = CAMERA_PIN_FUNC_SPI1_CSN;
        gspi_set_pin_mux(gspi_pin_config.spi_mosi_io0_pin, CAMERA_PIN_FUNC_SPI1_MOSI);
        gspi_set_pin_mux(gspi_pin_config.spi_miso_io1_pin, CAMERA_PIN_FUNC_SPI1_MISO);
        gspi_set_pin_mux(gspi_pin_config.spi_io2_pin, CAMERA_PIN_FUNC_SPI1_IO2);
        gspi_set_pin_mux(gspi_pin_config.spi_io3_pin, CAMERA_PIN_FUNC_SPI1_IO3);
        gspi_pin_gpio_en(1);

#endif
#if !SWITCH_DMA_BUFFER
        spi_set_slave_rx_dma_chain_llp(spi, chn, cis_rx_buff[2], CIS_RX_BUFF_LEN, &gspi_chain[0]);
        spi_rx_dma_add_list_element(spi, chn, &gspi_chain[0], &gspi_chain[1], cis_rx_buff[3], CIS_RX_BUFF_LEN);
        spi_rx_dma_add_list_element(spi, chn, &gspi_chain[1], &gspi_chain[0], cis_rx_buff[2], CIS_RX_BUFF_LEN);
#else
        spi_set_slave_rx_dma_chain_llp(spi, chn, cis_rx_buff[0], CIS_RX_BUFF_LEN, &gspi_chain[0]);
        spi_rx_dma_add_list_element(spi, chn, &gspi_chain[0], &gspi_chain[1], cis_rx_buff[1], CIS_RX_BUFF_LEN);
        spi_rx_dma_add_list_element(spi, chn, &gspi_chain[1], &gspi_chain[0], cis_rx_buff[0], CIS_RX_BUFF_LEN);
#endif

    }

    spi_slave_init(spi, SPI_MODE0);
}


unsigned int cis_init(void)
{
    int pid = 0x0a;
    gpio_function_en(TEST_PIN);
    gpio_output_en(TEST_PIN);
    gpio_set_level(TEST_PIN, 0);

    gpio_function_en(TEST_PIN1);
    gpio_output_en(TEST_PIN1);
    gpio_set_level(TEST_PIN1, 0);
    lspi_gspi_input_en();


#if CIS_OV7670_INIT_ON

    for (int i = 0; i < 16; i++) {
        tbl_nib_lspi[i] = (i & 1 ? BIT(c_bitmap_lspi[0]) : 0) + (i & 2 ? BIT(c_bitmap_lspi[1]) : 0) + (i & 4 ? BIT(c_bitmap_lspi[2]) : 0) + (i & 8 ? BIT(c_bitmap_lspi[3]) : 0);

        tbl_nib_gspi[i] = (i & 1 ? BIT(c_bitmap_gspi[0]) : 0) + (i & 2 ? BIT(c_bitmap_gspi[1]) : 0) + (i & 4 ? BIT(c_bitmap_gspi[2]) : 0) + (i & 8 ? BIT(c_bitmap_gspi[3]) : 0);
    }


    /////////////////////////////////////////////////////////////////////////
    //pwdn = 0; rstb = 1;
    pwm_set_pin(cis_cfg.pin_xclk, CAMERA_PIN_FUNC_PWM);
    pwm_set_clk(0);
    pwm_set_tcmp(CAMERA_XTAL_PWM_ID, CAMERA_XTAL_PWM_CMP);
    pwm_set_tmax(CAMERA_XTAL_PWM_ID, CAMERA_XTAL_PWM_MAX);
    pwm_start(CAMERA_XTAL_PWM_FLD);

    gpio_function_en(cis_cfg.pin_rstb);
    gpio_output_en(cis_cfg.pin_rstb);
    gpio_set_level(cis_cfg.pin_rstb, 1);

    gpio_function_en(cis_cfg.pin_pwdn);
    gpio_output_en(cis_cfg.pin_pwdn);
    gpio_set_level(cis_cfg.pin_pwdn, 0);


    //i2c configuration for CSI control
    i2c1_m_set_pin(cis_cfg.pin_sda, cis_cfg.pin_scl);

    i2c1_m_master_init();
    i2c1_m_set_master_clk((unsigned char)(sys_clk.pclk * 1000 * 1000 / (4 * I2C1_M_CLK_SPEED)));

    if(1){
    unsigned int t = stimer_get_tick();
    while (!clock_time_exceed(t, 1500)); //need 300us for ov7670 ready

    i2c1_m_master_write_read(0x42, (unsigned char *)&pid, 1, ((unsigned char *)&pid + 1), 2);

    for (unsigned int i = 0; i < sizeof(ov7670_reg_tbl); i += 2) {
        i2c1_m_master_write(0x42, ov7670_reg_tbl + i, 2);
    }
  

  /*The starting point needs to be adjusted in conjunction with the lens field of view*/
    ov7670_config_window(184, 10, CIS_IMAGE_WIDTH, CIS_IMAGE_HEIGHT);
#endif

#if CIS_USB_DISPLAY_EN
    reg_usb_ep_irq_mask = FLD_USB_EDP8_IRQ;
    plic_interrupt_enable(IRQ_USB_ENDPOINT);
#endif

}
    gpio_function_en(cis_cfg.pin_vs);
    gpio_output_dis(cis_cfg.pin_vs);
    gpio_input_en(cis_cfg.pin_vs);
    _gpio_set_irq(cis_cfg.pin_vs, INTR_RISING_EDGE); //When SW2 is pressed, the falling edge triggers the interrupt.
    gpio_set_irq_mask(FLD_GPIO_IRQ_MASK);
    gpio_clr_irq_status(FLD_GPIO_IRQ);

   // plic_set_priority(IRQ_USB_ENDPOINT, IRQ_PRI_LEV3);
    plic_set_priority(IRQ_GPIO, IRQ_PRI_LEV2);
    plic_set_priority(IRQ_DMA, IRQ_PRI_LEV1);

    plic_preempt_feature_en(CORE_PREEMPT_PRI_MODE0);

    plic_interrupt_enable(IRQ_DMA);
    plic_interrupt_enable(IRQ_GPIO);

    return pid;
}

void cis_sccb(int type, int read, unsigned int adr, int n, unsigned char *p)
{
    if (type < 4) {
        return;
    }
    unsigned char buff[128];
    buff[0] = adr;
    if (n > 64) {
        n = 64;
    }

    if (read) {
        i2c1_m_master_write_read(0x42, buff, 1, p, n);
    } else {
        memcpy(buff + 1, p, n);

        i2c1_m_master_write(0x42, buff, n + 1);
    }
}

////////////////////////////////////////////////////////////////////////////////
///  Combine data from LSPI/GSPI
////////////////////////////////////////////////////////////////////////////////
uint8_t bit_rev_table[16] = {
    0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE,
    0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF
};

#define REVERSE_NIBBLES(byte)  (byte)//(bit_rev_table[(byte >> 4) & 0x0F] << 4 | bit_rev_table[byte & 0x0F])
_attribute_ram_code_sec_noinline_ void cis_dma2frame(void)
{
    if (cis_wr_cnt) {
        return;
    }

#if !SWITCH_PINS_SPI0_SPI1
    unsigned char *pl = cis_rx_buff[cis_rx_buff_idx & 1];
    unsigned char *pg = cis_rx_buff[2 + (cis_rx_buff_idx & 1)];
#else
    unsigned char *pg = cis_rx_buff[cis_rx_buff_idx & 1];
    unsigned char *pl = cis_rx_buff[2 + (cis_rx_buff_idx & 1)];
#endif

#if SWITCH_DMA_BUFFER
    unsigned char *temp = pg;
    pg = pl;
    pl = temp;
#endif

    int            c  = cis_dat_cnt / CIS_IMAGE_WIDTH;
    for (int l = 0; l < CIS_RX_BUFF_LEN / CIS_IMAGE_WIDTH; l++) {
        int idx = c + l * 2 + CIS_IMAGE_HEIGHT * (CIS_IMAGE_WIDTH - 1) * 2;
        for (int i = 0; i < CIS_IMAGE_WIDTH; i++) {  
#if 0
            unsigned short s;
            s = tbl_nib_lspi[*pl & 15] + tbl_nib_gspi[*pg & 15];
            cis_frame[cis_dat_cnt++] = s;
            s = (tbl_nib_lspi[(*pl >> 4) & 15] + tbl_nib_gspi[(*pg >> 4) & 15]);
            cis_frame[cis_dat_cnt++] = s;
#elif 0
            unsigned short s;
            s                  = tbl_nib_lspi[*pg & 15] + tbl_nib_gspi[*pl & 15];
            cis_frame[idx]     = s;
            s                  = (tbl_nib_lspi[(*pg >> 4)] + tbl_nib_gspi[(*pl >> 4)]);
            cis_frame[idx + 1] = s;
            idx -= CIS_IMAGE_HEIGHT * 2;
            cis_dat_cnt += 2;
#else
            unsigned short s;
            (void)s;
            s                  = REVERSE_NIBBLES((*pl & 15) + (*pg << 4));
            cis_frame[idx]     = s;
            s                  = REVERSE_NIBBLES((*pl >> 4) + (*pg & 0xf0));
            cis_frame[idx + 1] = s;
            idx -= CIS_IMAGE_HEIGHT * 2;
            cis_dat_cnt += 2;
#endif
            pl++;
            pg++;
        }
    }
    if (cis_dat_cnt >= CIS_FRAME_SIZE) {
        cis_wr_cnt = cis_dat_cnt;
    }
}

void cis_frame2usb(void)
{
    if (!cis_wr_cnt) {
        return;
    }

#if CIS_USB_DISPLAY_EN
    while (reg_usb_addr && (unsigned int)(cis_bulk_wr_cnt - cis_bulk_irq_cnt) < 15 && cis_rd_cnt < CIS_FRAME_SIZE) {
        for (int i = 0; i < 64; i++) {
            reg_usb_ep8_dat = cis_frame[cis_rd_cnt++];
        }
        cis_bulk_wr_cnt++;
        if (0 && cis_bulk_wr_cnt == 15) {
            unsigned int val = usbhw_get_ep_ptr(8) | (usbhw_get_ctrl_ep_irq() << 16) | (reg_usb_addr << 24);
            my_dump_str_u32s(1, "[APP]:to usb", cis_bulk_wr_cnt, cis_bulk_irq_cnt, val, 0);
        }
    }

    //if (cis_rd_cnt == CIS_FRAME_SIZE && cis_bulk_wr_cnt == cis_bulk_irq_cnt)
    if (cis_rd_cnt == CIS_FRAME_SIZE && cis_bulk_wr_cnt == cis_bulk_irq_cnt) {
        unsigned int val = reg_usb_ep8_ptr | (reg_usb_ep8_ptrh << 8);
        my_dump_str_u32s(1, "[APP]:CIS frame sent", cis_bulk_wr_cnt, cis_bulk_irq_cnt, val, 0);

        cis_rd_cnt += 2;
    }
#endif
}

static void cis_capture_start(void)
{
    cis_capture_busy = 1;
    cis_capture      = 0;
}

static int cis_capture_done(void)
{
    return cis_capture && !cis_capture_busy;
}

static int cis_capture_idle(void)
{
#if CIS_USB_DISPLAY_EN
    return !cis_capture_busy && cis_rd_cnt > CIS_FRAME_SIZE;
#else
    return !cis_capture_busy;
#endif
}

_attribute_ram_code_sec_noinline_ void cis_sta_machine(void)
{
    static uint32_t cis_cnt = 0;
    cis_cnt++;
    if (cis_capture_idle()) {
        if (cis_capture_done()) {
            //do nothing temporarily
        }
        cis_capture_start();
    }
}

////////////////////////////////////////////////////////////////////////////////
///  GPIO - VSYNC
////////////////////////////////////////////////////////////////////////////////
volatile uint32_t image_test_cnt = 0;
void lcd_display_image(void)
{
#if SPI0_MODULE_ON
    lspi_pin_gpio_en(1);
#endif
#if SPI1_MODULE_ON
    gspi_pin_gpio_en(1);
#endif
    image_test_cnt++;
    
    lcd_spi_cfg();
    lcd_spi_display(0, 0, cis_frame, CIS_IMAGE_HEIGHT, CIS_IMAGE_WIDTH);
}

typedef struct
{
    uint8_t b, g, r; // b, g, r is same with tenseor
} RGB;

_attribute_data_retention_sec_ RGB dst[32 * 32];

volatile uint32_t gpio_irq_cnt = 0;
volatile uint32_t display_cnt = 0;
_attribute_ram_code_sec_noinline_ void gpio_irq_handler(void)
{
    gpio_irq_cnt++;

    gpio_clr_irq_status(FLD_GPIO_IRQ);
    dma_chn_dis(LSPI_RX_DMA_CHN);
    dma_chn_dis(GSPI_RX_DMA_CHN);
#if 1
    cis_vs_cnt = 0;
    if (cis_capture_busy && !cis_capture) {

        cis_capture = 1;
        cis_rd_cnt  = 0;
        cis_wr_cnt  = 0;
        cis_dat_cnt = 0;

        lcd_spi_cfg_disable();
#if SPI0_MODULE_ON
        spi_dma_init(CAMERA_SPI0_MODULE, LSPI_RX_DMA_CHN);
#endif
#if SPI1_MODULE_ON
        spi_dma_init(CAMERA_SPI1_MODULE, GSPI_RX_DMA_CHN);
#endif

#if SPI0_MODULE_ON
        lspi_pin_gpio_en(0);
#endif
#if SPI1_MODULE_ON
        gspi_pin_gpio_en(0);
#endif

#if SPI0_MODULE_ON
        dma_chn_en(LSPI_RX_DMA_CHN);
#endif
#if SPI1_MODULE_ON
        dma_chn_en(GSPI_RX_DMA_CHN);
#endif
    } else if (cis_capture && cis_capture_busy) {
        cis_capture_busy = 0;
        lcd_display_image();
        display_cnt++;
    }
#endif

}

PLIC_ISR_REGISTER(gpio_irq_handler, IRQ_GPIO)


////////////////////////////////////////////////////////////////////////////////
///  LSPI
////////////////////////////////////////////////////////////////////////////////

#if 0
_attribute_ram_code_sec_noinline_ void lspi_irq_handler(void)
{
    if(spi_get_irq_status(LSPI_MODULE,SPI_END_INT))
    {
        spi_clr_irq_status(LSPI_MODULE, SPI_END_INT);
        my_dump_str_data (1, "[IRQ]:lspi_irq_handler", &cis_rx_buff[0], 8);
    }
}
PLIC_ISR_REGISTER(lspi_irq_handler, IRQ_LSPI)
#endif

////////////////////////////////////////////////////////////////////////////////
///  DMA
////////////////////////////////////////////////////////////////////////////////
#include "test_stripes.h"
volatile uint32_t dma_lspi_irq_cnt = 0;
volatile uint32_t dma_gspi_irq_cnt = 0;
_attribute_ram_code_sec_noinline_ void dma_irq_handler(void)
{

#if SPI0_MODULE_ON && SPI1_MODULE_ON
    if (dma_get_tc_irq_status(BIT(LSPI_RX_DMA_CHN))) {
        gpio_set_level(TEST_PIN, 1);
        dma_clr_tc_irq_status(BIT(LSPI_RX_DMA_CHN));
        cis_vs_cnt++;
#if LCD_DISPLAY_DEBUG_IMAGE
        if(image_test_cnt < 30) {
            cis_dma2frame();
        } else if (image_test_cnt == 30) {
#if LCD_DISPLAY_COLOR_BAR
            memcpy(cis_frame, test_stripes_rgb565, CIS_FRAME_SIZE);
#endif
        }
#else
        cis_dma2frame();
#endif
        cis_rx_buff_idx++;
        dma_lspi_irq_cnt++;
        gpio_set_level(TEST_PIN, 0);
    }

    if (dma_get_tc_irq_status(BIT(GSPI_RX_DMA_CHN))) {
        dma_clr_tc_irq_status(BIT(GSPI_RX_DMA_CHN));
        gpio_set_level(TEST_PIN1, 1);
        
        cis_vs_cnt += 0x10000;
        dma_gspi_irq_cnt++;

        gpio_set_level(TEST_PIN1, 0);
    }
#else
    if (dma_get_tc_irq_status(BIT(LSPI_RX_DMA_CHN)) || dma_get_tc_irq_status(BIT(GSPI_RX_DMA_CHN))) {
        dma_clr_tc_irq_status(BIT(LSPI_RX_DMA_CHN));
        dma_clr_tc_irq_status(BIT(GSPI_RX_DMA_CHN));
#if LCD_DISPLAY_DEBUG_IMAGE
        if(image_test_cnt < 30) {
            cis_dma2frame();
        } else if (image_test_cnt == 30) {
#if LCD_DISPLAY_COLOR_BAR
            memcpy(cis_frame, test_stripes_rgb565, CIS_FRAME_SIZE);
#endif
        }
#else
        cis_dma2frame();
#endif
        cis_rx_buff_idx++;
    }
#endif

}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)


////////////////////////////////////////////////////////////////////////////////
///  USB
////////////////////////////////////////////////////////////////////////////////
#if CIS_USB_DISPLAY_EN
_attribute_ram_code_sec_noinline_ void usb_irq_handler(void)
{
    reg_usb_ep_irq_status = FLD_USB_EDP8_IRQ;
    cis_bulk_irq_cnt++;
}

PLIC_ISR_REGISTER(usb_irq_handler, IRQ_USB_ENDPOINT)
#endif
