/********************************************************************************************************
 * @file	bqb.c
 *
 * @brief	This is the source file for B91
 *
 * @author	X.P.C
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *          
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *          
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *          
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions 
 *              in binary form must reproduce the above copyright notice, this list of 
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *          
 *              3. Neither the name of TELINK, nor the names of its contributors may be 
 *              used to endorse or promote products derived from this software without 
 *              specific prior written permission.
 *          
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or 
 *              relating to such deletion(s), modification(s) or alteration(s).
 *         
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *         
 *******************************************************************************************************/
#include "bqb.h"
#include "../app_config.h"

#if(TEST_DEMO==BQB_DEMO)


static unsigned short pkt_cnt =0,cmd_pkt,l, h;
static unsigned char chn, pkt_type,freq,uart_tx_index,uart_rx_index,para, ctrl;
static unsigned char bb_mode;
static unsigned int pkt_interval;
static unsigned int tick_rx = 0;
volatile unsigned int t0,tick_tx;
Test_Status_t test_state;


unsigned char	bqbtest_buffer[272] __attribute__ ((aligned (4)));
u8 __attribute__ ((aligned (4))) bqbtest_pkt [264] = {
	37, 0, 0, 0,
	0, 37,
	0, 1, 2, 3, 4, 5, 6, 7
};

static union pkt_length_u
{
	unsigned char len;
	struct len_t
	{
		unsigned char low:6;
		unsigned char upper:2;
	}l;
}pkt_length;

/**
 * @brief   This function serves to get ble channel index
 * @param   chn: input channel
 * @return  ble channel index
 */
unsigned char bqbtest_channel (unsigned char chn)
{
	if (chn == 0)
	{
		return 37;
	}
	else if (chn < 12)
	{
		return chn - 1;
	}
	else if (chn == 12)
	{
		return 38;
	}
	else if (chn < 39)
	{
		return chn - 2;
	}
	else
	{
		return 39;
	}
}

/**
 * @brief   This function serves to obtain the pkt interval in different payload lengths and different modes
 * @param   payload_len: payload length
 * @param   mode: tx mode
 * 				1:BLE1M
 * 				2:BLE2M
 * 				3:BLE125K
 * 				4:BLE500K
 * @return  the pkt interval
 */
//unsigned char preamble_len;
unsigned int get_pkt_interval(unsigned char payload_len, unsigned char mode)
{
	unsigned int total_len,byte_time=8;
	unsigned char preamble_len;
	unsigned int total_time;

	if(mode==1)//1m
	{
		preamble_len = read_reg8(0x140802) & 0x1f ;
		total_len = preamble_len + 4 + 2 + payload_len +3; // preamble + access_code + header + payload + crc
		byte_time = 8;
		return (((byte_time * total_len + 249  + 624)/625)*625);
	}
	else if(mode==2)//2m
	{
		preamble_len = read_reg8(0x140802) & 0x1f ;
		total_len = preamble_len + 4 + 2 + payload_len +3; // preamble + access_code + header + payload + crc
		byte_time = 4;
		return (((byte_time * total_len + 249  + 624)/625)*625);
	}
	else if(mode==4) // s=2
	{
		byte_time = 2;	//2us/bit
		total_time = (80 + 256 + 16 + 24) + (16 + payload_len*8 + 24 +3)*byte_time; // preamble + access_code + coding indicator + TERM1 + header + payload + crc + TERM2
		return (((total_time + 249  + 624)/625)*625);
	}
	else if(mode==3)//s=8
	{
		byte_time = 8;	//8us/bit
		total_time = (80 + 256 + 16 + 24) + (16 + payload_len*8 + 24 +3)*byte_time; // preamble + access_code + coding indicator + TERM1 + header + payload + crc + TERM2
		return (((total_time + 249  + 624)/625)*625);
	}
	return 0;
}

extern uart_num_redef uart_using;
/**
 * @brief   This function serves to read the usrt data and execute BQB program
 * @param   Pointer to uart data
 * @return  1:  2 bytes data is received.
 * 			0:  no data is received.
 */
unsigned short uart_bqbtest_get(unsigned short* cmd)
{
	if (!tick_rx && ((reg_uart_buf_cnt(uart_using)&FLD_UART_RX_BUF_CNT) == 1))
	{
		tick_rx = reg_system_tick;
	}
	else if ((reg_uart_buf_cnt(uart_using)&FLD_UART_RX_BUF_CNT) == 2)
	{
		h = reg_uart_data_buf(uart_using, uart_rx_index)&0xff;
		uart_rx_index++;
		uart_rx_index &= 0x03;
		l = reg_uart_data_buf(uart_using, uart_rx_index)&0xff;
		uart_rx_index++;
		uart_rx_index &= 0x03;

		*cmd = (l | (h<<8));

		tick_rx = 0;
		return 1;
	}
	else if (tick_rx && clock_time_exceed(tick_rx, 5000))
	{
		tick_rx = 0;
		reg_uart_data_buf(uart_using, uart_rx_index);
		uart_rx_index++;
		uart_rx_index &= 0x03;
	}
	else if((reg_uart_buf_cnt(uart_using)&FLD_UART_RX_BUF_CNT)>2)
	{
		unsigned char i;

		unsigned char l = REG_ADDR8(0x9c)&0x0f;
		for(i=0; i<l; i++)
		{
			reg_uart_data_buf(uart_using, uart_rx_index);
			uart_rx_index++;
			uart_rx_index &= 0x03;
		}
	}
	return 0;
}

void bqb_serviceloop (void)
{
	if (uart_bqbtest_get (&cmd_pkt))
	{
		unsigned short rsp=0;
		unsigned char cmd = cmd_pkt >> 14;
		unsigned char k;
		unsigned int transLen = 0;
		tick_tx =  reg_system_tick;
		switch(cmd)
		{
			case CMD_SETUP:
			{
				ctrl = (cmd_pkt >> 8)&0x3f;
				para = (cmd_pkt >> 2)&0x3f;
				if(ctrl==0)
				{
					if(para==0)
					{
						pkt_length.l.upper =0;
						rsp = 0;
					}
					else
					{
						rsp = BIT(0);//Error
					}
					rf_set_tx_rx_off_auto_mode();
					rf_set_ble_1M_NO_PN_mode();
				}
				else if(ctrl== 1)
				{
					if((para>=0) && (para<=3))
					{
						pkt_length.l.upper = para &0x03;
					}
					else
					{
						rsp = BIT(0); //Error
					}
				}
				else if(ctrl==2)
				{
					rf_set_tx_rx_off_auto_mode();
					if(para==1)//BLE 1M
					{
						rf_set_ble_1M_NO_PN_mode();
						rsp = 0;
					}
					else if(para==2)//BLE 2M
					{
						rf_set_ble_2M_NO_PN_mode();
						rsp = 0;
					}
					else if(para==3)//s=8
					{
						rf_set_ble_125K_mode();
						rsp = 0;
					}
					else if(para==4)//s=2
					{
						rf_set_ble_500K_mode();
						rsp = 0;
					}
					else
					{
						rsp = BIT(0);
					}
					rf_pn_disable();
					bb_mode = para;
				}
				else if(ctrl==3)
				{
					rsp = 0;
				}
				else if(ctrl==4)
				{
					rsp |= BIT(1) | BIT(2);
					rsp = (rsp <<1);
				}
				else if(ctrl==5)
				{
					if(para==0)
					{
						rsp = (251<<1)&0x7ffe;
					}
					else if(para==1)
					{
						rsp = (17040 << 1)&0x7ffe;
					}
					else if(para==2)
					{
						rsp = (251<<1)&0x7ffe;
					}
					else if(para==3)
					{
						rsp = (17040 << 1)&0x7ffe;
					}
					else
					{
						rsp = BIT(0);//status EVENT Error
					}
				}
				bqb_uart_send_byte((rsp>>8)&0x7f);
				bqb_uart_send_byte(rsp&0xff);
				test_state = SETUP_STATE;
				pkt_cnt = 0;
				break;
			}
			case CMD_RX_TEST:
			{
				chn = (cmd_pkt >> 8) & 0x3f;	//frequency
				pkt_length.l.low  = (cmd_pkt >> 2) & 0x3f;
				pkt_type = cmd_pkt & 0x03;
				freq = bqbtest_channel(chn);//set channel
				rf_set_tx_rx_off_auto_mode();
				rf_set_ble_chn(freq);
				rf_set_rx_dma(bqbtest_buffer,3,8);
				rf_start_srx(reg_system_tick);
				bqb_uart_send_byte((rsp>>8)&0xff);
				bqb_uart_send_byte(rsp&0xff);
				test_state = RX_STATE;
				pkt_cnt = 0;
				break;
			}
			case CMD_TX_TEST:
			{
				chn = (cmd_pkt >> 8) & 0x3f;	//frequency
				pkt_length.l.low  = (cmd_pkt >> 2) & 0x3f;
				pkt_type = cmd_pkt & 0x03;
				transLen = pkt_length.len+2;
				transLen = rf_tx_packet_dma_len(transLen);
				bqbtest_pkt[3] = (transLen >> 24)&0xff;
				bqbtest_pkt[2] = (transLen >> 16)&0xff;
				bqbtest_pkt[1] = (transLen >> 8)&0xff;
				bqbtest_pkt[0] = transLen & 0xff;
				bqbtest_pkt[5] = pkt_length.len;
				if(pkt_type==0)
				{
					rf_phy_test_prbs9 (bqbtest_pkt + 6, pkt_length.len);
				}
				else if(pkt_type==1)
				{

					for(k=0;k<(pkt_length.len);k++)
					{
						bqbtest_pkt[k+6] = 0x0f;
					}


				}
				else if(pkt_type==2)
				{

					for(k=0;k<(pkt_length.len);k++)
					{
						bqbtest_pkt[k+6] = 0x55;
					}

				}
				else if(pkt_type==3)
				{
					pkt_type = 4;

					//todo if not LE Coded
					for(k=0;k<(pkt_length.len);k++)
					{
						bqbtest_pkt[k+6] = 0xff;
					}
				}
				else
				{
					rsp = BIT(0);
				}
				bqbtest_pkt[4] = pkt_type;
				pkt_interval = get_pkt_interval(pkt_length.len, bb_mode);//TODO
				freq = bqbtest_channel(chn);//set channel
				rf_set_tx_rx_off_auto_mode();
				rf_set_ble_chn(freq);
				rf_set_power_level_index(BQB_TX_POWER);
				rf_set_tx_dma(2,8);
				bqb_uart_send_byte((rsp>>8)&0xff);
				bqb_uart_send_byte(rsp&0xff);
				test_state = TX_STATE;
				pkt_cnt = 0;
				break;
			}
			case CMD_END:
			{
				ctrl = (cmd_pkt >> 8)&0x3f;
				para = (cmd_pkt >> 2)&0x3f;

#if (!RETURN_TX_LEN_EN)
				if(test_state==TX_STATE)//The tx quantity does not need to be reported
					pkt_cnt = 0;
#endif
				test_state = END_STATE;
				if((ctrl==0) && (para==0))
				{
					pkt_length.len =0;
					bqb_uart_send_byte((BIT(7))|((pkt_cnt>>8)&0x7f));
					bqb_uart_send_byte(pkt_cnt&0xff);
				}

				break;
			}
			default:
				break;
		}
	}
	if(test_state==RX_STATE)
	{
		if (rf_get_irq_status(FLD_RF_IRQ_RX))
		{
			if((REG_ADDR8(0x140840)&0xf0)==0)
			{
					pkt_cnt++;
			}
			rf_clr_irq_status(FLD_RF_IRQ_RX);
			rf_set_tx_rx_off_auto_mode();
			rf_start_srx(reg_system_tick);
		}
	}
	else if(test_state==TX_STATE)
	{
		if (clock_time_exceed(tick_tx, pkt_interval) || (pkt_cnt == 0))//pkt_interval
		{
			tick_tx =  reg_system_tick;
			rf_set_tx_rx_off_auto_mode();
			rf_start_stx(bqbtest_pkt,reg_system_tick);
			pkt_cnt++;
		}
	}


}


/**
 * @brief   This function serves to initialize  BQB
 * @param   none.
 * @return  none.
 */
void  bqbtest_init(void)
{
	unsigned char chnidx=0;
	t0 = reg_system_tick;
	rf_phy_test_prbs9 (bqbtest_pkt + 6, 37);
	write_reg8(0x140a03,0x1c); //disable first timeout
	rf_mode_init();
	rf_set_ble_1M_NO_PN_mode();
	rf_access_code_comm(ACCESS_CODE);
	uart_tx_index=0;
	uart_rx_index=0;
	flash_read_page(0x77000,1,&chnidx);
	if(chnidx!=0xff)
	{
		chnidx&=0x3f;
		analog_write_reg8(0x8a,(analog_read_reg8(0x8a)&0xc0)|chnidx);//close internal cap
	}
}

/**
 * @brief     uart send data function with not DMA method.
 *            variable uart_TxIndex,it must cycle the four registers 0x90 0x91 0x92 0x93 for the design of SOC.
 *            so we need variable to remember the index.
 * @param[in] uartData - the data to be send.
 * @return    none
 */
void bqb_uart_send_byte(unsigned char uartData)
{
	int t;
//	static unsigned char uart_TxIndex = 0;

	t = 0;
	while((!(reg_uart_status2(uart_using)&FLD_UART_TX_DONE)) && (t<0xfffff))
	{
		t++;
	}
	if(t >= 0xfffff)
		return;

	reg_uart_data_buf(uart_using, uart_tx_index) = uartData;

	uart_tx_index++;
	uart_tx_index &= 0x03;// cycle the four register 0x90 0x91 0x92 0x93.
}



#endif
