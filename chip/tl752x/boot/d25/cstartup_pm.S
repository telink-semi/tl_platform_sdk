/*******************************************************************************************************
 *
 * @file    cstartup_pm.S
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
#if defined(MCU_CORE_TL752X_D25F)

.section .retention_ram_code,"ax"

.balign    4
.type env_save_and_restore,@function
.global env_save_and_restore
env_save_and_restore:
    addi sp,sp,-4
    sw  ra,0(sp)

    jal save_all_s_reg

    addi sp,sp,-28

    sw  gp,0(sp)
    csrr t0,mstatus
    sw t0,4(sp)
    csrr t0,mie
    sw t0,8(sp)

    csrr t0,mtvec
    sw t0,12(sp)

    csrr t0,mmisc_ctl
    sw t0,16(sp)

    lui t1, 0xe4000
    lw  t0,0x0(t1)
    sw  t0,20(sp)

    lui t0,0xA0120
    lui t1,0xa0000
    /* save sp */
    sw sp,0x18(t0)

    /* PM_STATUS_N22_DEEP_SLEEP_READY flag get */
    lw t4,0xb0(t0)
    li t5,0x2
    and t4,t4,t5
    fence.i

    /* wakeup_vector was set by N22 for deep_sleep */
    beq t4,t5,_kick_sleep

    /*
    save d25f pc to reset vector, follow situations will reach here:
    1. sleep_mode is not deepsleep
    2. deepsleep but n22 run in error, flag not set
    3. deepsleep but d25f run faster, flag not set
     */
    la  t2,.wakeup_vector
    sw t2,0x10(t0)
_kick_sleep:
    /* set sleep */
    lui t2,0x00010
    ori t2,t2,0x1
    sw t2,0xc4(t1)
    la a0,0x1
#if 0
LOOP_LABLE:
    j LOOP_LABLE
#endif
.balign    4
.option push
.option norelax
.option norvc

    fence.i
    wfi
.wakeup_vector:
    nop
.option pop

#if 1
    /*set exec.it*/
    la t0, _ITB_BASE_;
    csrw uitb, t0
#endif

    lui t0,0xA0120
    lui t1,0xa0000

    /* restore sp */
    lw sp,0x18(t0)

    lw  gp,0(sp)
    lw  t2,4(sp)
    csrw mstatus,t2
    lw  t2,8(sp)
    csrw mie,t2
    lw  t2,12(sp)
    csrw mtvec,t2

    lw  t2,16(sp)
    csrw mmisc_ctl,t2

    /*vector or preemptive mode enable bit (VECTORED) of the Feature Enable Register */
    lui  t3, 0xe4000
    lw t2,20(sp)
    sw  t2, 0x0(t3)

    addi sp,sp,28

    jal restore_all_s_reg
    lw  ra,0(sp)
    addi sp,sp,4
    jr ra

.type save_all_s_reg,@function
.global save_all_s_reg
save_all_s_reg:
    addi sp,sp,-48
    sw s0,0(sp)
    sw s1,4(sp)
    sw s2,8(sp)
    sw s3,12(sp)
    sw s4,16(sp)
    sw s5,20(sp)
    sw s6,24(sp)
    sw s7,28(sp)
    sw s8,32(sp)
    sw s9,36(sp)
    sw s10,40(sp)
    sw s11,44(sp)
    jr ra

.type restore_all_s_reg,@function
.global restore_all_s_reg
restore_all_s_reg:
    lw s0,0(sp)
    lw s1,4(sp)
    lw s2,8(sp)
    lw s3,12(sp)
    lw s4,16(sp)
    lw s5,20(sp)
    lw s6,24(sp)
    lw s7,28(sp)
    lw s8,32(sp)
    lw s9,36(sp)
    lw s10,40(sp)
    lw s11,44(sp)
    addi sp,sp,48
    jr ra
#endif

