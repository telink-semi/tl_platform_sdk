/********************************************************************************************************
 * @file    app_transfer_bus_control.c
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
#if(I3C_MODE    ==       TRANSFER_BUS_CONTROL)
#define CONTROLLER                 0
#define CONTROLLER_CAPABLE_TARGET  1

#define  CONTROLLER_MODE          CONTROLLER_CAPABLE_TARGET

i3c_master_config_t g_master_config;
i3c_master_transfer_t g_master_transfer;
#define EXAMPLE_I2C_BAUDRATE        1000000
#define EXAMPLE_I3C_PP_BAUDRATE     6000000
#define EXAMPLE_I3C_OD_BAUDRATE     1000000
unsigned char g_address_list[8] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
volatile i3c_common_return_status_e result = I3C_STATUS_SUCCESS;
#if(CONTROLLER_MODE == CONTROLLER)
unsigned char cap_byte[4];
unsigned char vtcap_byte[1];
unsigned char status_byte[2];
unsigned char disec_byte[1]= {0x01};
unsigned char target_id_byte[1];

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
//1. getcaps  re/start + 0x7e/w/ack + direct getcaps ccc + restart + target addr/r/ack + 4 getcap byte + is_stop
    unsigned char sub_address_caps1[1] = {0x95};
    g_master_transfer.slave_address = 0x7e;
    g_master_transfer.data         = sub_address_caps1;
    g_master_transfer.data_size     = sizeof(sub_address_caps1);
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
    g_master_transfer.data         = cap_byte;
    g_master_transfer.data_size     = sizeof(cap_byte);
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    g_master_transfer.direction     = I3C_READ;
    result = i3c_master_read(I3C0,&g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }
//2.getcaps format 2 VTCAPS  re/start + 0x7e/w/ack + direct getcaps ccc + defining byte + restart + target addr/r/ack + n byte_n + is_stop
    unsigned char sub_address_caps[2] = {0x95,0x93};
    g_master_transfer.slave_address = 0x7e;
    g_master_transfer.data         = sub_address_caps;
    g_master_transfer.data_size     = sizeof(sub_address_caps);
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
    g_master_transfer.data         = vtcap_byte;
    g_master_transfer.data_size     = sizeof(vtcap_byte);
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    g_master_transfer.direction     = I3C_READ;
    result = i3c_master_read(I3C0,&g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }

//3.ccc getstatus : re/start + 0x7e/w/ack + direct getstatus ccc + restart + target addr /r/ack + msb + lsb + is_stop
    unsigned char sub_address_status[1] = {0x90};
    g_master_transfer.slave_address = 0x7e;
    g_master_transfer.data         = sub_address_status;
    g_master_transfer.data_size     = sizeof(sub_address_status);
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
    g_master_transfer.data         = status_byte;
    g_master_transfer.data_size     = sizeof(status_byte);
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    g_master_transfer.direction     = I3C_READ;
    result = i3c_master_read(I3C0,&g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }

//ccc disec re/start + 0x7e/w/ ack + direct enec/disec ccc + restart + target addr/w/ack + enable/disable target event byte  + is_stop
    unsigned char sub_address_disec[1] = {0x81};
    g_master_transfer.slave_address = 0x7e;
    g_master_transfer.data         = sub_address_disec;
    g_master_transfer.data_size     = sizeof(sub_address_disec);
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
    g_master_transfer.data         = disec_byte;
    g_master_transfer.data_size     = sizeof(disec_byte);
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    g_master_transfer.direction     = I3C_WRITE;
    result = i3c_master_write(I3C0,&g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }

    delay_us(10);

//DEFTGTS
//re/start + 0x7e/w/ack + broadcast DEFTGTS ccc + count +(define buff: (describes active controller: dynamic addr + dcr + bcr +static addr ) + (describes first target or group: target or group addr + dcr +bcr + static addr) )+ is_stop
   extern i3c_device_info_t g_dev_list[2][I3C_MAX_DEVCNT];
   extern unsigned char  g_dev_count[2];
   unsigned char sub_address_deftgts[2] = {0x08, g_dev_count[I3C0]};
   g_master_transfer.slave_address = 0x7e;
   g_master_transfer.subaddress   = sub_address_deftgts;
   g_master_transfer.subaddress_size = sizeof(sub_address_deftgts);
   g_master_transfer.data         = (unsigned char*)g_dev_list[I3C0];
   g_master_transfer.data_size     = sizeof(i3c_device_info_t)*g_dev_count[I3C0];
   g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
   g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
   g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
   g_master_transfer.direction     = I3C_WRITE;
   result = i3c_master_write(I3C0,&g_master_transfer);

   while(!g_is_ibi_master_req_flag){}
   g_is_ibi_master_req_flag=0;

 //GETACCCR CCC format(0x91):re/start + 0x7e/w/ack + direct getacccr ccc + restart + target addr(secondary controller)/r/ack + 7-bit dynamic address<<1 + is_stop
    unsigned char sub_address_cccr[1] = {0x91};
    g_master_transfer.slave_address = 0x7e;
    g_master_transfer.subaddress   = NULL;
    g_master_transfer.subaddress_size = 0;
    g_master_transfer.data         = sub_address_cccr;
    g_master_transfer.data_size     = sizeof(sub_address_cccr);
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
    g_master_transfer.data         = target_id_byte;
    g_master_transfer.data_size     = sizeof(target_id_byte);
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    g_master_transfer.direction     = I3C_READ;
    result = i3c_master_read(I3C0,&g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }
    delay_us(100);
    reg_i3c_config(I3C0) = reg_i3c_config(I3C0)|(FLD_I3C_S_TGTENA);
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{

}

_attribute_ram_code_sec_ void i3c0_irq_handler(void){
  unsigned int status_flags = i3c_master_get_irq_status(I3C0);
  unsigned char rx_count =0;
  i3c_master_get_fifo_count(I3C0,&rx_count,NULL);
  i3c_ibi_type_e ibi_type;
  /* handle ibi event*/
  if(status_flags &I3C_MASTER_ARBITRATIONWON_FLAG){
      i3c_master_clr_irq_status(I3C0,I3C_MASTER_ARBITRATIONWON_FLAG);
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
          /* In this example directly ack the IBI event need master to do manual operation */
          i3c_master_emit_ibi_response(I3C0,I3C_IBI_RESPACK);
      }else{
          if((rx_count ==0) && (status_flags &I3C_MASTER_COMPLETE_FLAG)) {
            i3c_master_clr_irq_status(I3C0,I3C_MASTER_COMPLETE_FLAG);
            switch (ibi_type)
            {
                case I3C_IBI_NORMAL:
                    i3c_master_emit_request(I3C0, I3C_REQUEST_EMITSTOP);
                    g_is_ibi_normal_flag=1;
                    g_ibi_normal_is_ack = i3c_master_get_ibi_response(I3C0);
                    break;
                case I3C_IBI_HOTJOIN:
                    i3c_master_emit_request(I3C0, I3C_REQUEST_EMITSTOP);
                    g_is_ibi_hotjoin_flag=1;
                    g_ibi_hotjoin_is_ack = i3c_master_get_ibi_response(I3C0);
                    break;
                case I3C_IBI_MASTERREQUEST:
                    i3c_master_emit_request(I3C0, I3C_REQUEST_EMITSTOP);
                    g_is_ibi_master_req_flag=1;
                    g_ibi_master_req_flag_is_ack = i3c_master_get_ibi_response(I3C0);
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
         g_ibiwon_has_data=0;
         g_ibi_buff_size=0;
         i3c_master_clr_irq_mask(I3C0,I3C_MASTER_RXREADY_FLAG);
     }
}
PLIC_ISR_REGISTER(i3c0_irq_handler, IRQ_I3C0)
#elif(CONTROLLER_MODE == CONTROLLER_CAPABLE_TARGET)
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
    g_slave_config.is_master_capable =1;
    g_slave_config.static_addr = I3C_MASTER_SLAVE_ADDR_7BIT;
    g_slave_config.offline    = 0;
    g_slave_config.clk_src.clk_src = CLK_BASEBAND_PLL_144M;
    g_slave_config.clk_src.clk_src_div =6;
    i3c_slave_init(I3C0,&g_slave_config);
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_I3C0);

    i3c_slave_set_irq_mask(I3C0, I3C_SLAVE_RXREADY_FLAG|I3C_SLAVE_DYNAMIC_ADDRCHANGED_FLAG|I3C_SLAVE_MATCHED_FLAG|I3C_SLAVE_EVENTSENT_FLAG|I3C_SLAVE_BUSSTOP_FLAG);

    g_txfifo_size =i3c_get_txfifo_size(I3C0);
    while(!g_dynamic_addr_flag){}
    g_dynamic_addr_flag=0;


    delay_ms(5);
    i3c_slave_request_event(I3C0,I3C_SLAVE_EVENT_MASTER_REQ);

    while(!(i3c_master_get_irq_status(I3C0)&I3C_MASTER_SLAVE2MASTER_FLAG)){

    }
    reg_i3c_config(I3C0) = reg_i3c_config(I3C0)&(~FLD_I3C_S_TGTENA);
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












