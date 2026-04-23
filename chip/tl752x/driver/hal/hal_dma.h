/********************************************************************************************************
 * @file    hal_dma.h
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



#ifndef __HAL_DMA_H__
#define __HAL_DMA_H__
#include "driver.h"
//////////////////////////////////////////////////////////////////////////////////////////////
////////////////                         Weak define                  ////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
/*Note: Just For SDK compile, it's only temporary, with no actual utility.*/
typedef enum
{
    DMA0 = 0,
    DMA1,
    DMA2,
    DMA3,
    DMA4,
    DMA5,
    DMA6,
    DMA7,
    DMA_CNT,
} dma_chn_e;
/*Note: Just For SDK compile, it's only temporary, with no actual utility.*/
typedef enum
{
    TC_MASK = 0,
    ERR_MASK,
    ABT_MASK,
} dma_irq_mask_e;
/*Note: Just For SDK compile, it's only temporary, with no actual utility.*/
typedef enum
{
    DMA_CHN0_IRQ = BIT(0),
    DMA_CHN1_IRQ = BIT(1),
    DMA_CHN2_IRQ = BIT(2),
    DMA_CHN3_IRQ = BIT(3),
    DMA_CHN4_IRQ = BIT(4),
    DMA_CHN5_IRQ = BIT(5),
    DMA_CHN6_IRQ = BIT(6),
    DMA_CHN7_IRQ = BIT(7),
} dma_irq_chn_e;

typedef dmac_init_t dma_config_t;

/*Note: Just For SDK compile, it's only temporary, with no actual utility.*/
__attribute__((weak)) void dma_clr_irq_mask(dma_chn_e chn, dma_irq_mask_e mask){
    (void)chn;
    (void)mask;
};
__attribute__((weak)) void dma_set_irq_mask(dma_chn_e chn, dma_irq_mask_e mask){
    (void)chn;
    (void)mask;
};
__attribute__((weak)) void dma_clr_tc_irq_status(dma_irq_chn_e tc_chn){
    (void)tc_chn;
};
__attribute__((weak)) void dma_chn_dis(dma_chn_e chn){
    (void)chn;
};
__attribute__((weak)) void dma_chn_en(dma_chn_e chn){
    (void)chn;
};
__attribute__((weak)) void dma_set_address(dma_chn_e chn, unsigned int src_addr, unsigned int dst_addr){
    (void)chn;
    (void)src_addr;
    (void)dst_addr;
}
__attribute__((weak)) void dma_set_size(dma_chn_e chn, unsigned int size_byte, dma_transfer_width_e byte_width){
    (void)chn;
    (void)size_byte;
    (void)byte_width;
}
__attribute__((weak)) void dma_config(dma_chn_e chn, dma_config_t *config){
    (void)chn;
    (void)config;
}

#endif
