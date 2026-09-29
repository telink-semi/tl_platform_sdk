/********************************************************************************************************
 * @file    app_target_reset.c
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
#if(I3C_MODE    ==       TARGET_RESET)

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

    //write: re/start + 0x7e/w/ack + direct rstact ccc + defining byte +restart + target addr/w/ack + is_stop
    unsigned char sub_address_reset[2] = {0x9a,0x01};
    g_master_transfer.slave_address = 0x7e;
    g_master_transfer.data         = sub_address_reset;
    g_master_transfer.data_size     = sizeof(sub_address_reset);
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
    g_master_transfer.data         = NULL;
    g_master_transfer.data_size     = 0;
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.flags        = I3C_TRANSFER_DEFAULT_FLAG;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    g_master_transfer.direction     = I3C_WRITE;
    result = i3c_master_write(I3C0,&g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }

    unsigned char sub_address_reset1[2] = {0x9a,0x01};
    g_master_transfer.slave_address = 0x7e;
    g_master_transfer.data         = sub_address_reset1;
    g_master_transfer.data_size     = sizeof(sub_address_reset1);
    g_master_transfer.bus_type      = I3C_TYPEI3CSDR;
    g_master_transfer.flags        = I3C_TRANSFER_NOSTOP_FLAG;
    g_master_transfer.ibi_response  = I3C_IBI_RESPACK_MANDATORY;
    g_master_transfer.direction     = I3C_WRITE;
    result = i3c_master_write(I3C0,&g_master_transfer);
    if (result != I3C_STATUS_SUCCESS)
    {
        while(1);
    }
    unsigned char cap_byte=0;
    g_master_transfer.slave_address = g_address_list[0];
    g_master_transfer.data         = &cap_byte;
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
    i3c_master_emit_request(I3C0,I3C_REQUEST_TARGETREST);
    i3c_master_wait_for_ctrl_done(I3C0,0);
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
#define I3C_MASTER_SLAVE_ADDR_7BIT 0x1E
i3c_slave_config_t g_slave_config;
volatile unsigned char g_txfifo_size;
volatile unsigned char g_dynamic_addr_flag;
void user_init(void)
{
    i3c_slave_set_pin(I3C0,GPIO_FC_PE0,GPIO_FC_PE2);
    g_slave_config.is_master_capable =0;
    g_slave_config.static_addr = I3C_MASTER_SLAVE_ADDR_7BIT;
    g_slave_config.offline    = 0;
    g_slave_config.clk_src.clk_src = CLK_BASEBAND_PLL_144M;
    g_slave_config.clk_src.clk_src_div =6;
    i3c_slave_init(I3C0,&g_slave_config);

    i3c_slave_set_irq_mask(I3C0, I3C_SLAVE_DYNAMIC_ADDRCHANGED_FLAG|I3C_SLAVE_TGTRST_FLAG);
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

volatile unsigned char target_reset=0;
_attribute_ram_code_sec_ void i3c0_irq_handler(void){
    if(i3c_slave_get_irq_status(I3C0)&I3C_SLAVE_DYNAMIC_ADDRCHANGED_FLAG){
        i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_DYNAMIC_ADDRCHANGED_FLAG);

    }
    if(i3c_slave_get_irq_status(I3C0)&I3C_SLAVE_TGTRST_FLAG){
        i3c_slave_clr_irq_status(I3C0,I3C_SLAVE_TGTRST_FLAG);
        reg_rst7 = reg_rst7&(~FLD_RST7_I3C1);
        reg_rst7 |= FLD_RST7_I3C1;
        target_reset =1;
    }
}
PLIC_ISR_REGISTER(i3c0_irq_handler, IRQ_I3C0)
#endif
#endif












