/********************************************************************************************************
 * @file    app_dma_master.c
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
#if(I3C_MODE    ==       DMA_MASTER)
i3c_master_config_t g_master_config;
i3c_master_transfer_t g_master_transfer;
#define EXAMPLE_I2C_BAUDRATE        1000000
#define EXAMPLE_I3C_PP_BAUDRATE     6000000
#define EXAMPLE_I3C_OD_BAUDRATE     1000000
unsigned char g_address_list[8] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
volatile i3c_common_return_status_e result = I3C_STATUS_SUCCESS;
unsigned char g_master_txbuff[16] __attribute__((aligned(4))) = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
unsigned char g_master_rxbuff[16+4] __attribute__((aligned(4)));

volatile unsigned char g_is_ibi_master_req_flag=0;
volatile unsigned char g_ibi_master_req_flag_is_ack=0;
volatile unsigned char g_ibi_master_req_address =0;
volatile unsigned char g_is_ibi_hotjoin_flag =0;
volatile unsigned char g_ibi_hotjoin_is_ack=0;
volatile unsigned char g_ibi_hotjoin_address=0;
volatile unsigned char g_is_ibi_normal_flag=0;
volatile unsigned char g_ibi_normal_is_ack=0;
volatile unsigned char g_ibi_normal_address=0;
volatile unsigned char g_ibiwon_has_data =0;
volatile unsigned char g_ibi_buff[8];
volatile unsigned char g_ibi_buff_size =0;
volatile unsigned char g_ibi_flag=0;
volatile unsigned char g_dma_completed_flag=0;


#define  I3C_TX_DMA_CHN             DMA0
#define  I3C_RX_DMA_CHN             DMA1

i3c_register_ibi_addr_t ibi_addr_rgst={
        .address = {0},
        .ibi_has_payload = 0,
};
void user_init(void)
{
    i3c_master_set_pin(I3C0,I3C_GPIO_SDA_PIN,I3C_GPIO_SCL_PIN,GPIO_NONE_PIN);

    g_master_config.master_en                      = I3C_MASTER_ON;
    g_master_config.baudrate_hz.i2c_baud           = EXAMPLE_I2C_BAUDRATE;
    g_master_config.baudrate_hz.i3c_pushpull_baud  = EXAMPLE_I3C_PP_BAUDRATE;
    g_master_config.baudrate_hz.i3c_opendrain_baud = EXAMPLE_I3C_OD_BAUDRATE;
    g_master_config.opendrain_stop_en              = 0;
#if defined(MCU_CORE_TL322X)
    g_master_config.clk_src.clk_src                = CLK_BASEBAND_PLL_144M;
    g_master_config.clk_src.clk_src_div            = 6;
#elif defined(MCU_CORE_TL521X)
    g_master_config.clk_src.clk_src                = CLK_BBPLL_144M;
    g_master_config.clk_src.clk_src_div            = 6;
#elif defined(MCU_CORE_TL753X)
    g_master_config.clk_src.clk_src                = CLK_BASEBAND_PLL_192M;
    g_master_config.clk_src.clk_src_div            = 4;
#endif
    i3c_master_init(I3C0,&g_master_config);
    i3c_master_set_irq_mask(I3C0,I3C_MASTER_SLAVESTART_FLAG|I3C_MASTER_ARBITRATIONWON_FLAG|I3C_MASTER_COMPLETE_FLAG|I3C_MASTER_SLAVE2MASTER_FLAG|I3C_MASTER_COMPLETE_FLAG);
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_I3C0);


    i3c_master_register_ibi(I3C0,&ibi_addr_rgst);

     //dma config
    i3c_set_tx_dma_config(I3C0,I3C_TX_DMA_CHN);
    i3c_set_rx_dma_config(I3C0,I3C_RX_DMA_CHN);

    result      = i3c_master_process_daa(I3C0, g_address_list, 8);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
    g_master_txbuff[0]++;
    g_master_transfer.slave_address = g_address_list[0];
    g_master_transfer.data          = g_master_txbuff;
    g_master_transfer.data_size     = sizeof(g_master_txbuff);
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    result                   = i3c_master_write_dma(I3C0, &g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }

    while(!g_dma_completed_flag);
    g_dma_completed_flag=0;
    /* Wait until the slave is ready for transmit.*/
    while(!g_is_ibi_normal_flag);
    g_is_ibi_normal_flag=0;

    delay_us(10);
    g_master_transfer.slave_address = g_address_list[0];
    g_master_transfer.data          = (g_master_rxbuff+4);
    g_master_transfer.data_size     = sizeof(g_master_rxbuff)-4;
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    result                   = i3c_master_read_dma(I3C0, &g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }
    while(!g_dma_completed_flag);
    g_dma_completed_flag=0;

    delay_us(5);
    for (volatile unsigned int i = 0; i < 16; i++)
    {
        if (g_master_rxbuff[i+4] != g_master_txbuff[i])
        {
            while(1);

        }
    }
    delay_us(10);
}


_attribute_ram_code_sec_ void i3c0_irq_handler(void){
  unsigned int status_flags = i3c_master_get_irq_status(I3C0);
  unsigned char rx_count =0;
  i3c_ibi_type_e ibi_type;
  i3c_master_get_fifo_count(I3C0,&rx_count,NULL);
  /* handle ibi event*/
  if(status_flags &I3C_MASTER_ARBITRATIONWON_FLAG){
      i3c_master_clr_irq_status(I3C0,I3C_MASTER_ARBITRATIONWON_FLAG);
      g_ibi_flag=1;
      ibi_type= i3c_master_get_ibi_type(I3C0);
      switch (ibi_type)
      {
            case I3C_IBI_NORMAL:
                g_ibi_normal_address = i3c_get_ibi_address(I3C0);
                break;
            case I3C_IBI_HOTJOIN:
                g_ibi_hotjoin_address = i3c_get_ibi_address(I3C0);
                break;
            case I3C_IBI_MASTERREQUEST:
                g_ibi_master_req_address = i3c_get_ibi_address(I3C0);
                break;
            default:
                break;
      }
      unsigned int master_status = i3c_master_get_state(I3C0);
      /* User could rewrite the logic to handle the IBI event need to do manual ACK/NACK */
      if(master_status == I3C_MASTER_STATE_IBIACK){
          /* In this example directly NAK the IBI event need master to do manual operation */
          i3c_master_emit_ibi_response(I3C0,I3C_IBI_RESPNACK);
      }else{
          if((rx_count ==0) && (status_flags &I3C_MASTER_COMPLETE_FLAG)) {
          i3c_master_clr_irq_status(I3C0,I3C_MASTER_COMPLETE_FLAG);
          g_ibi_flag=0;
          ibi_type = i3c_master_get_ibi_type(I3C0);

            switch (ibi_type)
            {
                case I3C_IBI_NORMAL:
                    g_is_ibi_normal_flag=1;
                    g_ibi_normal_is_ack = i3c_master_get_ibi_response(I3C0);
                    //g_ibi_normal_address = i3c_get_ibi_address(I3C0);
                    break;
                case I3C_IBI_HOTJOIN:
                    g_is_ibi_hotjoin_flag=1;
                    g_ibi_hotjoin_is_ack = i3c_master_get_ibi_response(I3C0);
                    //g_ibi_hotjoin_address = i3c_get_ibi_address(I3C0);
                    break;
                case I3C_IBI_MASTERREQUEST:
                    g_is_ibi_master_req_flag=1;
                    g_ibi_master_req_flag_is_ack = i3c_master_get_ibi_response(I3C0);
                    //g_ibi_master_req_address = i3c_get_ibi_address(I3C0);
                    break;
                default:
                    break;
            }
          }else{
              g_ibiwon_has_data =1;
              i3c_master_set_irq_mask(I3C0, I3C_MASTER_RXREADY_FLAG);
          }
      }
      return;
   }
   if ((status_flags & (unsigned int)I3C_MASTER_RXREADY_FLAG))
   {
         if (g_ibiwon_has_data)
         {
             while (rx_count != 0)
             {
                 g_ibi_buff[g_ibi_buff_size++] = reg_i3c_mrdatab_0(I3C0);
                 rx_count--;
             }
         }

    }

     /* Emit broadcast address to get slave IBI event */
     if ( (status_flags & (unsigned int)I3C_MASTER_SLAVESTART_FLAG))
     {
         i3c_master_clr_irq_status(I3C0,I3C_MASTER_SLAVESTART_FLAG);
         /* Emit start + 0x7E */
         i3c_master_emit_request(I3C0, I3C_REQUEST_AUTOIBI);
         return;
     }

     if (g_ibiwon_has_data && (status_flags &I3C_MASTER_COMPLETE_FLAG))
     {
         i3c_master_clr_irq_status(I3C0,I3C_MASTER_COMPLETE_FLAG);
         i3c_master_emit_request(I3C0, I3C_REQUEST_EMITSTOP);
         g_is_ibi_normal_flag=1;
         g_ibi_normal_is_ack = i3c_master_get_ibi_response(I3C0);
        // g_ibi_normal_address = i3c_get_ibi_address(I3C0);
         g_ibiwon_has_data=0;
         g_ibi_buff_size=0;
         i3c_master_clr_irq_mask(I3C0,I3C_MASTER_RXREADY_FLAG);
         g_ibi_flag=0;
     }
     if((g_ibi_flag==0) && (status_flags &I3C_MASTER_COMPLETE_FLAG)){
         i3c_master_clr_irq_status(I3C0,I3C_MASTER_COMPLETE_FLAG);
         i3c_master_emit_request(I3C0, I3C_REQUEST_EMITSTOP);
         g_dma_completed_flag=1;
     }
}
PLIC_ISR_REGISTER(i3c0_irq_handler, IRQ_I3C0)
#endif












