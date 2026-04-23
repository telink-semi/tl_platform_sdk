/********************************************************************************************************
 * @file    hal_audio.h
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



#ifndef __HAL_AUDIO_H__
#define __HAL_AUDIO_H__

#include "inc/drv_audio_adc.h"
#include "inc/drv_audio_anc.h"
#include "inc/drv_audio_dac.h"
#include "inc/drv_audio_dump.h"
#include "inc/drv_codec.h"
#include "inc/drv_dmac.h"
#include "inc/drv_soc_codec.h"
#include "hal/hal_gpio.h"

/**
 *  @brief      This function serves to get dma tx buff pointer.
 *  @param[in]  chn - dma channel.
 *  @return  the result of tx read pointer.
 */
static inline unsigned int audio_get_tx_dma_rptr(dmac_handle_t *hdma)
{
    return drv_dmac_get_src_address(hdma);
}

/**
 *  @brief      This function serves to get dma rx buff pointer.
 *  @param[in]  chn - dma channel.
 *  @return     the result of rx write pointer.
 */
static inline unsigned int audio_get_rx_dma_wptr(dmac_handle_t *hdma)
{
    return drv_dmac_get_dst_address(hdma);
}

/**
 *  @brief      This function serves to set dma tx buff pointer.
 *  @param[in]  chn - dma channel.
 *  @return     None.
 */
static inline void audio_set_tx_dma_rptr(dmac_handle_t *hdma, uint32_t src_address)
{
    drv_dmac_set_src_address(hdma, src_address);
}

/**
 *  @brief      This function serves to set dma rx buff pointer.
 *  @param[in]  chn - dma channel.
 *  @return     None.
 */
static inline void audio_set_rx_dma_wptr(dmac_handle_t *hdma, uint32_t dst_address)
{
    drv_dmac_set_dst_address(hdma, dst_address);
}

/**
 *  @brief      This function serves to enable dma channel.
 *  @param[in]  chn - dma channel.
 *  @return     None.
 */
static inline void audio_dma_channel_enable(dmac_handle_t *hdma)
{
    DRV_ASSERT_PARAM(hdma);
    __DRV_DMAC_CHANNEL_ENABLE(hdma);
}

/**
 *  @brief      This function serves to disable dma channel.
 *  @param[in]  chn - dma channel.
 *  @return     None.
 */
static inline void audio_dma_channel_disable(dmac_handle_t *hdma)
{
    DRV_ASSERT_PARAM(hdma);
    __DRV_DMAC_CHANNEL_DISABLE(hdma);
}

/**
 *  @brief      This function serves to probe clkout0 as I2S mclk.
 *  @return     None
 *  @note       Only GPIO_PA2, mux function 6
 */
static inline void audio_probe_clkout0_clk_as_mclk(void)
{
    gpio_set_mux_function(GPIO_PA2, 6);
}


/*Note: Just For SDK compile with no actual use.*/
typedef enum
{
    AUDIO_RX_FIFO0 = BIT(0),
    AUDIO_RX_FIFO1 = BIT(1),
    AUDIO_TX_FIFO0 = BIT(0),
    AUDIO_TX_FIFO1 = BIT(1),
} audio_fifo_type_e;

/*Note: Just For SDK compile with no actual use.*/
static inline unsigned char audio_get_fifo_irq_status(audio_fifo_type_e fifo_type)
{
    (void) fifo_type;
    return -1;
}

/*Note: Just For SDK compile with no actual use.*/
static inline void audio_clr_fifo_irq_status(audio_fifo_type_e fifo_type)
{
    (void) fifo_type;
}
#endif
