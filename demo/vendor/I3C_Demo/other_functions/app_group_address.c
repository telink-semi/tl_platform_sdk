/********************************************************************************************************
 * @file    app_group_address.c
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
#if(I3C_MODE    ==       GROUP_ADDRESS)
#define CONTROLLER    0
#define TARGET        1
#define MODE          TARGET

#if(MODE     ==     CONTROLLER)

i3c_master_config_t g_master_config;
i3c_master_transfer_t g_master_transfer;
#define EXAMPLE_I2C_BAUDRATE        1000000
#define EXAMPLE_I3C_PP_BAUDRATE     6000000
#define EXAMPLE_I3C_OD_BAUDRATE     1000000

unsigned char g_address_list[8] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
i3c_common_return_status_e result = I3C_STATUS_SUCCESS;

typedef struct{
    unsigned char group_address;
    unsigned char target_count;
    unsigned char target_buff[4];
}i3c_group_list_t;

i3c_group_list_t group_list[]={
        {0x08,0,{0}},
        {0x0a,0,{0}},
        {0x0c,0,{0}},
};

unsigned char i3c_write_buff[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
void user_init(void)
{
    i3c_master_set_pin(I3C0,GPIO_FC_PE0,GPIO_FC_PE2,GPIO_NONE_PIN);

    g_master_config.master_en                      = I3C_MASTER_ON;
    g_master_config.timeout_dis                    = 1;
    g_master_config.baudrate_hz.i2c_baud           = EXAMPLE_I2C_BAUDRATE;
    g_master_config.baudrate_hz.i3c_pushpull_baud  = EXAMPLE_I3C_PP_BAUDRATE;
    g_master_config.baudrate_hz.i3c_opendrain_baud = EXAMPLE_I3C_OD_BAUDRATE;
    g_master_config.opendrain_stop_en              = false;
    g_master_config.clk_src.clk_src                = CLK_BASEBAND_PLL_144M;
    g_master_config.clk_src.clk_src_div            = 6;
    i3c_master_init(I3C0,&g_master_config);
    i3c_master_set_irq_mask(I3C0,I3C_MASTER_SLAVESTART_FLAG|I3C_MASTER_ARBITRATIONWON_FLAG|I3C_MASTER_COMPLETE_FLAG|I3C_MASTER_SLAVE2MASTER_FLAG);
    i3c_master_set_watermarks(I3C0, I3C_TX_TRIGGER_UNTIL_ONE_LESS_THAN_FULL, I3C_RX_TRIGGER_ON_NOT_EMPTY);
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_I3C0);

    result      = i3c_master_process_daa(I3C0, g_address_list, 8);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }
    //SETGRPA: format:(0x9b)  re/start + 0x7e/w/ack + direct setgrpa ccc + restart + target addr/w/ack + 7-bit group address<<1 + is_stop
    for(unsigned char i=0;i<3;i++){
        unsigned char subaddress[1] = {0x9b};
        g_master_transfer.slave_address = 0x7e;
        g_master_transfer.data         = subaddress;
        g_master_transfer.data_size     = sizeof(subaddress);
        g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
        g_master_transfer.flags        = I3C_TRANSFER_NOSTOP_FLAG;
        g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
        g_master_transfer.direction     = I3C_WRITE;
        result = i3c_master_write(I3C0,&g_master_transfer);
        if (result != I3C_STATUS_SUCCESS)
        {
            while(1);
        }

        g_master_transfer.slave_address = g_address_list[0];
        g_master_transfer.data         = (unsigned char*)&group_list[i].group_address;
        g_master_transfer.data_size     = 1;
        g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
        g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
        g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
        g_master_transfer.direction     = I3C_WRITE;
        result = i3c_master_write(I3C0,&g_master_transfer);
        if (result != I3C_STATUS_SUCCESS)
        {
            while(1);
        }
        group_list[i].target_buff[group_list[i].target_count] = g_address_list[0];
        group_list[i].target_count++;

    }
    g_master_transfer.slave_address = (group_list[0].group_address)>>1;
    g_master_transfer.data         = i3c_write_buff;
    g_master_transfer.data_size     = sizeof(i3c_write_buff);
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    g_master_transfer.direction     = I3C_WRITE;
    result                  = i3c_master_write(I3C0, &g_master_transfer);
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

}


_attribute_ram_code_sec_ void i3c0_irq_handler(void){

}
PLIC_ISR_REGISTER(i3c0_irq_handler, IRQ_I3C0)


#elif( MODE     ==  TARGET)
#define TRANSFER_LEN     16

#define I3C_MASTER_SLAVE_ADDR_7BIT 0x1E
i3c_slave_config_t g_slave_config;
volatile unsigned char g_slave_rx_completion_flag=0;
volatile unsigned char g_slave_tx_completion_flag=0;
volatile unsigned char g_slave_request_flag =0;
volatile unsigned char g_slave_address_match_flag=0;
volatile unsigned char g_transfer_rx_size=0;
volatile unsigned char g_transfer_tx_size=0;
volatile unsigned char g_slave_txbuff[16];
volatile unsigned char g_slave_rxbuff[16];
volatile unsigned char g_txfifo_size;
volatile unsigned char g_address_match_flag=0;
volatile unsigned char g_ccc_receives_flag=0;
volatile unsigned char g_ccc_buff[256];
volatile unsigned char g_dynamic_addr_flag=0;
volatile unsigned char g_tx_ready_flag=0;
void user_init(void)
{
    i3c_slave_set_pin(I3C0,GPIO_FC_PE0,GPIO_FC_PE2);
    g_slave_config.is_master_capable =0;
    g_slave_config.static_addr = I3C_MASTER_SLAVE_ADDR_7BIT;
    g_slave_config.offline    = 0;
    g_slave_config.clk_src.clk_src = CLK_BASEBAND_PLL_144M;
    g_slave_config.clk_src.clk_src_div =6;
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
#endif












