/*******************************************************************************************************
 *
 * @file    gpadc.h
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
#ifndef __GPADC_H__
#define __GPADC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

// offsetaddress : 0x0000
#define GPADC_ALG_ADC_EN_Pos      (0U)
#define GPADC_ALG_ADC_EN_Msk      (0x1UL << GPADC_ALG_ADC_EN_Pos) /*!< GPADC module switch 0: Off; 1: On*/
#define GPADC_DMAS_ON_Pos         (1U)
#define GPADC_DMAS_ON_Msk         (0x1UL << GPADC_DMAS_ON_Pos) /*!< DMAS_ON function switch 0: Off; 1: On*/
#define GPADC_AUTO_SW_Pos         (2U)
#define GPADC_AUTO_SW_Msk         (0x1UL << GPADC_AUTO_SW_Pos) /*!< Automatic switching function of GPADC input channel 0: Off; 1: On*/
#define GPADC_EDGE_SEL_Pos        (3U)
#define GPADC_EDGE_SEL_Msk        (0x1UL << GPADC_EDGE_SEL_Pos) /*!< Data sampling edge selection 0: Falling edge; 1: Rising edge*/
#define GPADC_VREF_TRIM_Pos       (4U)
#define GPADC_VREF_TRIM_Msk       (0x7UL << GPADC_VREF_TRIM_Pos) /*!< Reference voltage calibration step 10mV 100:0.9V*/
#define GPADC_CLK_EN_Pos          (7U)
#define GPADC_CLK_EN_Msk          (0x1UL << GPADC_CLK_EN_Pos)
#define GPADC_READ_REQ_THRESH_Pos (8U)
#define GPADC_READ_REQ_THRESH_Msk (0xFUL << GPADC_READ_REQ_THRESH_Pos) /*!< Read request interrupt threshold*/
#define GPADC_CLK_ASYN_SEL_Pos    (12U)
#define GPADC_CLK_ASYN_SEL_Msk    (0x1UL << GPADC_CLK_ASYN_SEL_Pos) /*!< GPADC asynchronous clock selection 0: 20MHz 1: 10MHz*/
#define GPADC_GAIN_Pos            (13U)
#define GPADC_GAIN_Msk            (0x1UL << GPADC_GAIN_Pos) /*!< Single-ended differential gain 0:6dB 1:0dB*/
#define GPADC_ENP_GP_ADC_AZ_Pos   (14U)
#define GPADC_ENP_GP_ADC_AZ_Msk   (0x1UL << GPADC_ENP_GP_ADC_AZ_Pos) /*!< GP_ADC CMP auto-zero enable 0: disable 1: enable */
#define GPADC_ENP_BYPCHBUFF_Pos   (15U)
#define GPADC_ENP_BYPCHBUFF_Msk   (0x1UL << GPADC_ENP_BYPCHBUFF_Pos) /*!< Buffer bypass 0: disable 1: enable */
#define GPADC_ENP_CH_RESDIV_Pos   (16U)
#define GPADC_ENP_CH_RESDIV_Msk   (0x1FFFUL << GPADC_ENP_CH_RESDIV_Pos) /*!< Input resistance voltage divider (1/2) of channels 0-12 is enabled 0: disable 1: enable*/
#define GPADC_FIFO_FLUSH_Pos      (29U)
#define GPADC_FIFO_FLUSH_Msk      (0x1UL << GPADC_FIFO_FLUSH_Pos) /*!< Clear FIFO 0: Not clear; 1: Clear*/

// offsetaddress : 0x0004
#define GPADC_CHAN_SW_Pos   (0U)
#define GPADC_CHAN_SW_Msk   (0xFUL << GPADC_CHAN_SW_Pos)
#define GPADC_CHAN_AUTO_Pos (8U)
#define GPADC_CHAN_AUTO_Msk (0xFFFFUL << GPADC_CHAN_AUTO_Pos) /*!< Select the channel participating in automatic switching, and each 1 bit corresponds to one channel. 0: No selection; 1: Select*/

// offsetaddress : 0x0008
#define GPADC_SW_WAIT_CNT_Pos (0U)
#define GPADC_SW_WAIT_CNT_Msk (0xFFFFFFFFUL << GPADC_SW_WAIT_CNT_Pos) /*!< Channel switching waiting time = bus clock cycle *SW_WAIT_CNT; default value is 0us*/

// offsetaddress : 0x000c
/*!< Waveform selection during fpga test wave sel=1 represents square wave, sel=2 represents triangle wave AUTO_SW_CNT = { wave_sel15[1:0],wave_sel14[1:0], ......,wave_sel1[1:0],wave_sel0[1:0]}*/
#define GPADC_AUTO_SW_CNT_Pos (0U)
#define GPADC_AUTO_SW_CNT_Msk (0xFFFFFFFFUL << GPADC_AUTO_SW_CNT_Pos)

// offsetaddress : 0x0010
#define GPADC_INT_DATA_RDY_Pos   (0U)
#define GPADC_INT_DATA_RDY_Msk   (0x1UL << GPADC_INT_DATA_RDY_Pos) /*!< ADC data ready interrupt status bit, write 1, this register and the corresponding original status register are cleared 0.*/
#define GPADC_INT_FIFO_OF_Pos    (1U)
#define GPADC_INT_FIFO_OF_Msk    (0x1UL << GPADC_INT_FIFO_OF_Pos) /*!< FIFO overflow interrupt status bit, write 1, this register and the corresponding original status register are cleared 0.*/
#define GPADC_INT_FIFO_UF_Pos    (2U)
#define GPADC_INT_FIFO_UF_Msk    (0x1UL << GPADC_INT_FIFO_UF_Pos) /*!< FIFO underflow interrupt status bit, write 1, this register and the corresponding original status register are cleared 0.*/
#define GPADC_INT_FIFO_EMPTY_Pos (3U)
#define GPADC_INT_FIFO_EMPTY_Msk (0x1UL << GPADC_INT_FIFO_EMPTY_Pos) /*!< FIFO empty */
#define GPADC_INT_FIFO_FULL_Pos  (4U)
#define GPADC_INT_FIFO_FULL_Msk  (0x1UL << GPADC_INT_FIFO_FULL_Pos) /*!< FIFO full */
#define GPADC_INT_FIFO_AE_Pos    (5U)
#define GPADC_INT_FIFO_AE_Msk    (0x1UL << GPADC_INT_FIFO_AE_Pos) /*!< FIFO almost empty */
#define GPADC_INT_FIFO_AF_Pos    (6U)
#define GPADC_INT_FIFO_AF_Msk    (0x1UL << GPADC_INT_FIFO_AF_Pos) /*!< FIFO almost full */

// offsetaddress : 0x0014
#define GPADC_INT_RAW_DATA_RDY_RAW_Pos (0U)
#define GPADC_INT_RAW_DATA_RDY_RAW_Msk (0x1UL << GPADC_INT_RAW_DATA_RDY_RAW_Pos) /*!< ADC data ready interrupts the original status register*/
#define GPADC_INT_RAW_FIFO_OF_RAW_Pos  (1U)
#define GPADC_INT_RAW_FIFO_OF_RAW_Msk  (0x1UL << GPADC_INT_RAW_FIFO_OF_RAW_Pos) /*!< FIFO overflow interrupts the original status register*/
#define GPADC_INT_RAW_FIFO_UF_RAW_Pos  (2U)
#define GPADC_INT_RAW_FIFO_UF_RAW_Msk  (0x1UL << GPADC_INT_RAW_FIFO_UF_RAW_Pos) /*!< FIFO underflow interrupts the original status register*/
#define GPADC_INT_RAW_FIFO_EMPTY_Pos   (3U)
#define GPADC_INT_RAW_FIFO_EMPTY_Msk   (0x1UL << GPADC_INT_RAW_FIFO_EMPTY_Pos) /*!< FIFO empty original status register*/
#define GPADC_INT_RAW_FIFO_FULL_Pos    (4U)
#define GPADC_INT_RAW_FIFO_FULL_Msk    (0x1UL << GPADC_INT_RAW_FIFO_FULL_Pos) /*!< FIFO full original status register*/
#define GPADC_INT_RAW_FIFO_AE_Pos      (5U)
#define GPADC_INT_RAW_FIFO_AE_Msk      (0x1UL << GPADC_INT_RAW_FIFO_AE_Pos) /*!< FIFO almost empty original status register*/
#define GPADC_INT_RAW_FIFO_AF_Pos      (6U)
#define GPADC_INT_RAW_FIFO_AF_Msk      (0x1UL << GPADC_INT_RAW_FIFO_AF_Pos) /*!< FIFO almost full original status register*/

// offsetaddress : 0x0018
#define GPADC_DATA_RDY_EN_Pos (0U)
#define GPADC_DATA_RDY_EN_Msk (0x1UL << GPADC_DATA_RDY_EN_Pos) /*!< ADC data ready interrupt enable*/
#define GPADC_FIFO_OF_EN_Pos  (1U)
#define GPADC_FIFO_OF_EN_Msk  (0x1UL << GPADC_FIFO_OF_EN_Pos) /*!< FIFO overflow interrupt enable*/
#define GPADC_FIFO_UF_EN_Pos  (2U)
#define GPADC_FIFO_UF_EN_Msk  (0x1UL << GPADC_FIFO_UF_EN_Pos) /*!< FIFO underflow interrupt enable*/

// offsetaddress : 0x001c
#define GPADC_FIFO_DOUT_Pos (0U)
#define GPADC_FIFO_DOUT_Msk (0xFFFFFFFFUL << GPADC_FIFO_DOUT_Pos)

// offsetaddress : 0x0020
#define GPADC_SE2DIFF_IB_SEL_Pos (0U)
#define GPADC_SE2DIFF_IB_SEL_Msk (0x7UL << GPADC_SE2DIFF_IB_SEL_Pos) /*!< GPADC single-ended differential current bias current setting control bit. (0.125Ua/step) 000: 0.5Ua 100: 1Ua (default) 111: 1.375Ua*/

// offsetaddress : 0x0024
#define GPADC_IPCLK_DIV2MCLK_Pos  (0U)
#define GPADC_IPCLK_DIV2MCLK_Msk  (0xFFUL << GPADC_IPCLK_DIV2MCLK_Pos) /*!< MCLK clock cycle = bus clock cycle *PCLK_DIV2MCLK*/
#define GPADC_FPCLK_DIV2IPCLK_Pos (8U)
#define GPADC_FPCLK_DIV2IPCLK_Msk (0xFFUL << GPADC_FPCLK_DIV2IPCLK_Pos) /*!< IPCLK clock cycle = CLK/(IPCLK_DIV2MCLK 1)*/

// offsetaddress : 0x0028
/*!< GPADC SE2DIFF offset eliminate Step: 0.7mv <6>: 1,trim enable;0,disable <5>: 1, positive vos trim enable; 0,negative vos trim <4:0> trim value */
#define GPADC_SE2DIFF_OS_TRIM_Pos (0U)
#define GPADC_SE2DIFF_OS_TRIM_Msk (0x7FUL << GPADC_SE2DIFF_OS_TRIM_Pos)

// offsetaddress : 0x0030
#define GPADC_DUTY_CYCLE_Pos (0U)
#define GPADC_DUTY_CYCLE_Msk (0xFFFFFFFFUL << GPADC_DUTY_CYCLE_Pos) /*!< MCLK clock duty cycle = (PCLK_DIV2MCLK - DUTY_CYCLE)/PCLK_DIV2MCLK*/

typedef struct {
    volatile uint32_t GPADC_MAIN_CTL;  // offsetaddress : 0x0000
    volatile uint32_t GPADC_CHAN_CTL;  // offsetaddress : 0x0004
    volatile uint32_t GPADC_TIMER0;    // offsetaddress : 0x0008
    volatile uint32_t GPADC_TIMER1;    // offsetaddress : 0x000c
    volatile uint32_t GPADC_INT;       // offsetaddress : 0x0010
    volatile uint32_t GPADC_INT_RAW;   // offsetaddress : 0x0014
    volatile uint32_t GPADC_EN;        // offsetaddress : 0x0018
    volatile uint32_t GPADC_FIFO;      // offsetaddress : 0x001c
    volatile uint32_t SE2DIFF_IB_SEL;  // offsetaddress : 0x0020
    volatile uint32_t GPADC_CLK_DIV;   // offsetaddress : 0x0024
    volatile uint32_t SE2DIFF_OS_TRIM; // offsetaddress : 0x0028
    volatile uint32_t rev_0[(0x0030 - 0x0028) / 4 - 1];
    volatile uint32_t DUTY_CYCLE; // offsetaddress : 0x0030
} gpadc_t;

#ifdef __cplusplus
}
#endif

#endif