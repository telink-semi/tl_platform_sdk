/********************************************************************************************************
 * @file    app_no_dma_slave.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"
#if(I3C_MODE    ==       NO_DMA_SLAVE)
#define TRANSFER_LEN     16

#define I3C_MASTER_SLAVE_ADDR_7BIT 0x1E
i3c_slave_config_t g_slave_config;
volatile unsigned char g_slave_rx_completion_flag=0;
volatile unsigned char g_slave_tx_completion_flag=0;
volatile unsigned char g_slave_request_flag =0;
volatile unsigned char g_slave_address_match_flag=0;
volatile unsigned char g_transfer_rx_size=0;
volatile unsigned char g_transfer_tx_size=0;
unsigned char g_slave_txbuff[16];
unsigned char g_slave_rxbuff[16];
volatile unsigned char g_txfifo_size;
volatile unsigned char g_address_match_flag=0;
volatile unsigned char g_ccc_receives_flag=0;
volatile unsigned char g_ccc_buff[256];
volatile unsigned char g_dynamic_addr_flag=0;
volatile unsigned char g_tx_ready_flag=0;
void user_init(void)
{
    i3c_slave_set_pin(I3C0,I3C_GPIO_SDA_PIN,I3C_GPIO_SCL_PIN);
    g_slave_config.is_master_capable =0;
    g_slave_config.static_addr = I3C_MASTER_SLAVE_ADDR_7BIT;
    g_slave_config.offline    = 0;
    g_slave_config.is_hotjoin =0;
#if defined(MCU_CORE_TL322X)
    g_slave_config.clk_src.clk_src                = CLK_BASEBAND_PLL_144M;
    g_slave_config.clk_src.clk_src_div            = 6;
#elif defined(MCU_CORE_TL521X)
    g_slave_config.clk_src.clk_src                = CLK_BBPLL_144M;
    g_slave_config.clk_src.clk_src_div            = 6;
#elif defined(MCU_CORE_TL753X)
    g_slave_config.clk_src.clk_src                = CLK_BASEBAND_PLL_192M;
    g_slave_config.clk_src.clk_src_div            = 4;
#endif
    i3c_slave_init(I3C0,&g_slave_config);

    i3c_slave_set_irq_mask(I3C0, I3C_SLAVE_RXREADY_FLAG|I3C_SLAVE_DYNAMIC_ADDRCHANGED_FLAG|I3C_SLAVE_MATCHED_FLAG|I3C_SLAVE_EVENTSENT_FLAG|I3C_SLAVE_BUSSTOP_FLAG);
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_I3C0);
    g_txfifo_size =i3c_get_txfifo_size(I3C0);

    while(!g_dynamic_addr_flag){}
    g_dynamic_addr_flag=0;

}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
    while(!g_slave_rx_completion_flag){}
    g_slave_rx_completion_flag=0;

    memcpy(g_slave_txbuff, g_slave_rxbuff, TRANSFER_LEN);

    /* Notify master that slave tx data is prepared, ibi data is the data size slave want to transmit. */
     unsigned char ibi_data = g_slave_rxbuff[0];
     i3c_slave_request_ibi_with_data(I3C0, &ibi_data, 1);
     while (!g_slave_request_flag)
     {
     }
     g_slave_request_flag = 0;
     i3c_slave_set_irq_mask(I3C0, I3C_SLAVE_TXREADY_FLAG);

     while(!g_slave_tx_completion_flag){}
     g_slave_tx_completion_flag=0;
}

_attribute_ram_code_sec_ void i3c0_irq_handler(void){
   unsigned int status_flags = i3c_slave_get_irq_status(I3C0);
   unsigned char tx_count, rx_count;
   i3c_slave_get_fifo_counts(I3C0,&rx_count,&tx_count);
   tx_count = g_txfifo_size - tx_count;
   /* Handle TXNOTFULL event to fill tx fifo. */
   if((status_flags & (unsigned int)I3C_SLAVE_TXREADY_FLAG)&&(i3c_slave_get_irq_mask(I3C0)&I3C_SLAVE_TXREADY_FLAG)){
       g_tx_ready_flag=0;
       while((tx_count !=0) && (g_transfer_tx_size < (TRANSFER_LEN -1))){
           i3c_slave_write_byte(I3C0,g_slave_txbuff[g_transfer_tx_size]);
           g_transfer_tx_size++;
           tx_count--;
           g_tx_ready_flag=1;
       }
       if((tx_count !=0)&&(g_tx_ready_flag==0)){
           i3c_slave_write_end_byte(I3C0,g_slave_txbuff[TRANSFER_LEN-1]);
           i3c_slave_clr_irq_mask(I3C0, (I3C_SLAVE_TXREADY_FLAG));
           i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_TXREADY_FLAG);
       }
   }

   /* Handle RXSEND event to read rx fifo. */
   if((status_flags & (unsigned int)I3C_SLAVE_RXREADY_FLAG)&&(status_flags & (unsigned int)I3C_SLAVE_RECEIVED_CCC_FLAG)){
       g_ccc_receives_flag=1;
   }
   if(status_flags & (unsigned int)I3C_SLAVE_RXREADY_FLAG){
      if(g_ccc_receives_flag==1){
         while (rx_count != 0)
         {
            g_ccc_buff[g_transfer_rx_size] = i3c_slave_read_byte(I3C0);
            g_transfer_rx_size++;
            rx_count--;
         }
      }else{
          while (rx_count != 0)
          {
            g_slave_rxbuff[g_transfer_rx_size] = i3c_slave_read_byte(I3C0);
            g_transfer_rx_size++;
            rx_count--;
          }
      }

   }

   /* Handle match address event. */
   if (0 != (status_flags & (unsigned int)I3C_SLAVE_MATCHED_FLAG))
   {
       i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_MATCHED_FLAG);
       g_address_match_flag = 1;
   }

   /* Handle bus stop event when bus is match. */
   if (g_address_match_flag && ((status_flags & (unsigned int)I3C_SLAVE_BUSSTOP_FLAG)))
   {
       i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_BUSSTOP_FLAG);
      if(g_transfer_rx_size){
          g_slave_rx_completion_flag = 1;
      }else if(g_transfer_tx_size){
           g_slave_tx_completion_flag =1;
      }
       if (g_slave_tx_completion_flag)
       {
           i3c_slave_clr_irq_mask(I3C0, (I3C_SLAVE_TXREADY_FLAG));
           i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_TXREADY_FLAG);
       }
       g_transfer_rx_size = 0;
       g_transfer_tx_size = 0;
       g_address_match_flag = 0;
       g_ccc_receives_flag = 0;
       return;
   }
   if ((status_flags & (unsigned int)I3C_SLAVE_BUSSTOP_FLAG)){
       i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_BUSSTOP_FLAG);
   }
   /* Report event sent. */
   if (status_flags & (unsigned int)I3C_SLAVE_EVENTSENT_FLAG)
   {
       i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_EVENTSENT_FLAG);
       g_slave_request_flag = 1;
   }
   if(status_flags & (unsigned int)I3C_SLAVE_DYNAMIC_ADDRCHANGED_FLAG){
       i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_DYNAMIC_ADDRCHANGED_FLAG);
       g_dynamic_addr_flag=1;
   }
}
PLIC_ISR_REGISTER(i3c0_irq_handler, IRQ_I3C0)
#endif












