/********************************************************************************************************
 * @file    app_autotest.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#define read_sram8(addr)                        (*(volatile unsigned char *)((addr)))
#define write_sram8(addr, v)                    (*(volatile unsigned char *)((addr)) = (unsigned char)(v))

#if defined(MCU_CORE_TL521X)
    #define SRAM_BASE_ADDR                      0x11000100
#endif

#define CLOCK_INDEX_ADDR                        (SRAM_BASE_ADDR + 0x04)
#define TEST_COMMAND_ADDR                       (SRAM_BASE_ADDR + 0x06)
#define VOLTAGE_ADDR                            (SRAM_BASE_ADDR + 0x10)

#define CMD_RUN_DHRYSTONE                       0x01
#define CMD_SET_VOLTAGE                         0x07
#define CMD_RUN_DHRYSTONE_SCORE                 0x08

#if (DHRYSTONE_TEST_MODE == AUTO_MODE)

/* ==========================================================================
 *  TL521X Clock Macro Table - all public macros from clock.h (excluding internal)
 * ========================================================================== */
#if defined(MCU_CORE_TL521X)
#define TL521X_CLOCK_MACRO_COUNT                16

typedef enum
{
    TL521X_CLOCK_PLL_144M_CCLK_72M_HCLK_36M_PCLK_36M_MSPI_48M = 0,
    TL521X_CLOCK_PLL_144M_CCLK_72M_HCLK_36M_PCLK_18M_MSPI_48M,
    TL521X_CLOCK_PLL_120M_CCLK_60M_HCLK_30M_PCLK_30M_MSPI_40M,
    TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_48M_PCLK_24M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_48M_PCLK_12M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_24M_PCLK_24M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_24M_PCLK_12M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_36M_HCLK_36M_PCLK_18M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_24M_PCLK_12M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_24M_PCLK_6M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_12M_PCLK_12M_MSPI_48M,
    TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_12M_PCLK_6M_MSPI_48M,
    TL521X_CLOCK_XTAL_24M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_24M,
    TL521X_CLOCK_RC_24M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_24M,
} tl521x_clock_index_e;
#endif

/**
 * @brief   Execute clock initialization based on the selected macro index
 * @param   clock_index - index of the clock macro to execute
 * @return  none
 */
#if defined(MCU_CORE_TL521X)
void dhrystone_clock_init(unsigned char clock_index)
{
    switch (clock_index) {
        case TL521X_CLOCK_PLL_144M_CCLK_72M_HCLK_36M_PCLK_36M_MSPI_48M:
            PLL_144M_CCLK_72M_HCLK_36M_PCLK_36M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_72M_HCLK_36M_PCLK_18M_MSPI_48M:
            PLL_144M_CCLK_72M_HCLK_36M_PCLK_18M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_120M_CCLK_60M_HCLK_30M_PCLK_30M_MSPI_40M:
            PLL_120M_CCLK_60M_HCLK_30M_PCLK_30M_MSPI_40M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M:
            PLL_144M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_48M_PCLK_24M_MSPI_48M:
            PLL_144M_CCLK_48M_HCLK_48M_PCLK_24M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_48M_PCLK_12M_MSPI_48M:
            PLL_144M_CCLK_48M_HCLK_48M_PCLK_12M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_24M_PCLK_24M_MSPI_48M:
            PLL_144M_CCLK_48M_HCLK_24M_PCLK_24M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_48M_HCLK_24M_PCLK_12M_MSPI_48M:
            PLL_144M_CCLK_48M_HCLK_24M_PCLK_12M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_36M_HCLK_36M_PCLK_18M_MSPI_48M:
            PLL_144M_CCLK_36M_HCLK_36M_PCLK_18M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M:
            PLL_144M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_24M_PCLK_12M_MSPI_48M:
            PLL_144M_CCLK_24M_HCLK_24M_PCLK_12M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_24M_PCLK_6M_MSPI_48M:
            PLL_144M_CCLK_24M_HCLK_24M_PCLK_6M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_12M_PCLK_12M_MSPI_48M:
            PLL_144M_CCLK_24M_HCLK_12M_PCLK_12M_MSPI_48M;
            break;
        case TL521X_CLOCK_PLL_144M_CCLK_24M_HCLK_12M_PCLK_6M_MSPI_48M:
            PLL_144M_CCLK_24M_HCLK_12M_PCLK_6M_MSPI_48M;
            break;
        case TL521X_CLOCK_XTAL_24M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_24M:
            XTAL_24M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_24M;
            break;
        case TL521X_CLOCK_RC_24M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_24M:
            RC_24M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_24M;
            break;
        default:
            PLL_144M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M;
            break;
    }
}
#endif

/**
 * @brief   Run Dhrystone benchmark
 * @return  none
 * @note    Follows the same pattern as app.c CURRENT_PER_MHZ_TEST
 */
void dhrystone_run_test(void)
{
    gpio_shutdown(GPIO_ALL);
#if defined(MCU_CORE_TL521X)
    reg_rst      = 0x96b88080;
    reg_clk_en   = 0x1e30a080;
    reg_rst_1    = 0x00800004;
    reg_clk_en_1 = 0x00800044;

    for (int i = 0; i < 10; i++) {
        dhry_main();
    }

    reg_rst      = 0xffffffff;
    reg_clk_en   = 0xffffffff;
    reg_rst_1    = 0xffffffff;
    reg_clk_en_1 = 0xffffffff;
#endif
}

/**
 * @brief   Run Dhrystone benchmark score test (single run, prints score)
 * @return  none
 */
void dhrystone_run_score(void)
{
    gpio_shutdown(GPIO_ALL);

    reg_rst      = 0x92390fd4;
    reg_clk_en   = 0x1a312fd4;
    reg_rst_1    = 0x00000204;
    reg_clk_en_1 = 0x00000244;
    
    dhry_main();
    printf("\r\n[dhrystone] : %d\r\n", Dhrystone_DMIPS_Per_MHz);
}

/**
 * @brief   Set core voltage via analog register 0x27
 * @param   voltage_val - voltage trim value to write
 * @return  none
 */
#if defined(MCU_CORE_TL521X)
void dhrystone_set_voltage(unsigned char voltage_val)
{
    analog_write_reg8(0x27, voltage_val);
}
#endif

/**
 * @brief   Dhrystone autotest service loop
 * @return  none
 * @note    Polls SRAM command and executes dhrystone test when triggered
 */
void dhrystone_serviceloop(void)
{
    unsigned char cmd_now = 0;
    unsigned char last_cmd = 0;
    unsigned char clock_index = 0;

    write_sram8(TEST_COMMAND_ADDR, 0);

    while (1) {
        cmd_now = read_sram8(TEST_COMMAND_ADDR);
        if (cmd_now == 0 || cmd_now == last_cmd) continue;
        last_cmd = cmd_now;

        if (cmd_now == CMD_RUN_DHRYSTONE) {
            clock_index = read_sram8(CLOCK_INDEX_ADDR);

            /* Initialize clock with selected macro */
            dhrystone_clock_init(clock_index);

            /* Run dhrystone benchmark */
            dhrystone_run_test();
        }
#if defined(MCU_CORE_TL521X)
        else if (cmd_now == CMD_SET_VOLTAGE) {
            unsigned char voltage_val = read_sram8(VOLTAGE_ADDR);
            dhrystone_set_voltage(voltage_val);
            write_sram8(VOLTAGE_ADDR, 0);
        }
        else if (cmd_now == CMD_RUN_DHRYSTONE_SCORE) {
            dhrystone_run_score();
        }
#endif

        write_sram8(TEST_COMMAND_ADDR, 0);
        last_cmd = 0;
    }
}

/**
 * @brief       This function serves to User Init
 * @return      none
 */
void user_init(void)
{
    gpio_shutdown(GPIO_ALL);
}

/**
 * @brief       This function serves to main loop
 * @return      none
 */
void main_loop(void)
{
    dhrystone_serviceloop();
}
#endif

#if 0
#if defined(MCU_CORE_TL321X) && (GPIO_TEST_MODE == AUTO_TEST_MODE)
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
#endif