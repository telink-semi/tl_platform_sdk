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

#if (DEMO_MODE == TEST_MODE)

volatile tl_test_cmd_pkt_t_another *g_test_cmd_ptr = (tl_test_cmd_pkt_t_another *)0xc0000004;

    #define TASK_MAX 2
struct DUT_CMD_FUNC dut_task_cmd_func[TASK_MAX] = {
    {PEM_STIMER, pem_task_stimer_init, pem_task_stimer_mainloop},
    {PEM_PWM_0,  pem_task_pwm_0_init,  pem_task_pwm_0_mainloop },
};
    #define EVENT_MAX 2
struct DUT_CMD_FUNC dut_event_cmd_func[EVENT_MAX] = {
    {PEM_STIMER, pem_event_stimer_init, pem_event_stimer_start},
    {PEM_PWM_0,  pem_event_pwm_0_init,  pem_event_pwm_0_start },
};

unsigned char task_id;
unsigned char event_id;

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);

    pem_init();
}

void main_loop(void)
{
    unsigned int  i;
    unsigned char rr = 0;

    while (1) {
        if (g_test_cmd_ptr->cmd_state_t.state == 0x01) {
            task_id                 = PEM_NONE;
            event_id                = PEM_NONE;
            g_test_cmd_ptr->resp[0] = 0;
            g_test_cmd_ptr->resp[1] = 0;
            g_test_cmd_ptr->resp[2] = 0;
            for (i = 0; i < TASK_MAX; i++) {
                if (dut_task_cmd_func[i].cmd_name == (unsigned char)(g_test_cmd_ptr->cmd_state_t.cmd)) {
                    task_id = i;
                    break;
                }
            }
            for (i = 0; i < EVENT_MAX; i++) {
                if (dut_event_cmd_func[i].cmd_name == (unsigned char)(g_test_cmd_ptr->param[0])) {
                    event_id = i;
                    break;
                }
            }
            if ((task_id != PEM_NONE) && (event_id != PEM_NONE)) {
                dut_task_cmd_func[i].func1(PEM_ID, (g_test_cmd_ptr->param[1] >> 4));
                dut_event_cmd_func[i].func1(PEM_ID, (g_test_cmd_ptr->param[1] & 0x0f));

                //start
                pem_chn_en(PEM_ID);

                dut_event_cmd_func[i].func2((g_test_cmd_ptr->param[1] & 0x0f));
                rr = dut_task_cmd_func[i].func2((g_test_cmd_ptr->param[1] >> 4));

                if (rr == TL_TEST_RESP_OK) {
                    g_test_cmd_ptr->resp[2] = (unsigned char)g_test_cmd_ptr->cmd_state_t.cmd;
                } else {
                    g_test_cmd_ptr->resp[2] = ~((unsigned char)g_test_cmd_ptr->cmd_state_t.cmd);
                }
                break;
                g_test_cmd_ptr->cmd_state_t.state = 0;
            }
        }
    }
}

#endif
