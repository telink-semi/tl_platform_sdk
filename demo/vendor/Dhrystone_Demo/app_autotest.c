/********************************************************************************************************
 * @file    app_autotest.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2023, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "app_config.h"
#if defined(MCU_CORE_TL321X) && (DEMO_MODE == TEST_MODE)
// set parament cmd

    #define CMD_CLOCK            0x04

    #define CMD_WRITE_CORE_REG   0x10 // This function is not implemented in the next machine and is used as a placeholder
    #define CMD_WRITE_ANALOG_REG 0x20

void dhrystone_determine_run_interface(void);
void dhrystone_set_parameter(void);

struct PC_CMD_FUNC
{
    unsigned short cmd_name;
    void (*func)(void);
};

struct PC_CMD_FUNC pc_cmd_func[] = {

    {DUTCMD_DHRYSTONE_DETERMINE_RUN_TEST, dhrystone_determine_run_interface},

    {DUTCMD_DHRYSTONE_SET_PARAMETER_TEST, dhrystone_set_parameter          }
};

void dhrystone_set_parameter(void)
{
    autotest_package_t_ptr para  = (autotest_package_t_ptr)para_buff;
    unsigned char          cmd   = para->payload[2];
    unsigned char          value = para->payload[3];
    unsigned char          send_data[4];
    char                   execute_flag = 0x66;

    if (CMD_WRITE_ANALOG_REG == cmd) {
        unsigned char addr = para->payload[4];
        analog_write_reg8(addr, value);
    } else if (CMD_CLOCK == cmd) {
        switch (value) {
        case CCLK_24M_HCLK_12M_PCLK_12M /* constant-expression */:
            /* code */
            PLL_192M_CCLK_24M_HCLK_12M_PCLK_12M_MSPI_48M;
            break;
        case CCLK_24M_HCLK_24M_PCLK_12M /* constant-expression */:
            /* code */
            PLL_192M_CCLK_24M_HCLK_24M_PCLK_12M_MSPI_48M;
            break;
        case CCLK_24M_HCLK_24M_PCLK_24M /* constant-expression */:
            /* code */
            PLL_192M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M;
            break;
        case CCLK_48M_HCLK_24M_PCLK_24M /* constant-expression */:
            /* code */
            PLL_192M_CCLK_48M_HCLK_24M_PCLK_24M_MSPI_48M;
            break;
        case CCLK_48M_HCLK_48M_PCLK_24M /* constant-expression */:
            /* code */
            PLL_192M_CCLK_48M_HCLK_48M_PCLK_24M_MSPI_48M;
            break;
        case CCLK_96M_HCLK_48M_PCLK_24M /* constant-expression */:
            /* code */
            PLL_192M_CCLK_96M_HCLK_48M_PCLK_24M_MSPI_48M;
            break;
        case CCLK_48M_HCLK_48M_PCLK_48M /* constant-expression */:
            /* code */
            PLL_192M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M;
            break;
        case CCLK_96M_HCLK_48M_PCLK_48M /* constant-expression */:
            /* code */
            PLL_192M_CCLK_96M_HCLK_48M_PCLK_48M_MSPI_48M;
            break;

        default:
            break;
        }
    }
    send_data[0] = para->payload[2] + 0xa5;
    send_data[1] = para->payload[3] + 0xa5;
    send_data[2] = 4;
    send_data[3] = execute_flag;
    result_buff_write(send_data, send_data[2]);
}

void dhrystone_determine_run_interface(void)
{
    autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;

    unsigned char send_data[4];
    char          execute_flag = 0x66;

    send_data[0] = para->payload[2] + 0xa5;
    send_data[1] = para->payload[3] + 0xa5;
    send_data[2] = 4;
    send_data[3] = execute_flag;
    result_buff_write(send_data, send_data[2]);

    gpio_shutdown(GPIO_ALL);
    for (int i = 0; i < 100; i++) {
        dhry_main();
    }
}

void user_init(void)
{
    // intiate parameter buffer to receive CMD and parameter
    para_buff_init();
    // initiate result buffer to send the result
    result_buff_init();
}

volatile unsigned int correct_cmd_count = 0;
volatile unsigned int cmd_count         = 0;

void pc_data_handle(void)
{
    unsigned char i;
    int           crc_flag;
    if (para_buff_have_data() != 0) {
        cmd_count++;
        crc_flag                        = para_buff_read(para_buff, COMMAND_BUFF_SIZE); // 1:CRC correct  -1:CRC error  0:buffer size overflow
        autotest_package_t_ptr para     = (autotest_package_t_ptr)para_buff;
        unsigned int           test_cmd = (para->payload[1] << 8 | para->payload[0]);
        if (crc_flag == 1) {
            for (i = 0; i < sizeof(pc_cmd_func) / sizeof(struct PC_CMD_FUNC); i++) {
                if (pc_cmd_func[i].cmd_name == test_cmd) {
                    correct_cmd_count++;
                    pc_cmd_func[i].func();
                    break;
                }
            }
        }
    }
}

/*********************************************************************************************************
 *                                                main loop
 *********************************************************************************************************/
void main_loop(void)
{
    while (1) {
        pc_data_handle();
    }
}

#endif
