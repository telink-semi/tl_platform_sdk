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
#if defined(MCU_CORE_TL752X_N22)

.section .retention_ram_code,"ax"

.balign    4
.type env_save_and_restore,@function
.global env_save_and_restore
env_save_and_restore:
    addi sp,sp,-4
    sw  ra,0(sp)

    jal save_all_s_reg

    addi sp,sp,-32

    sw  gp,0(sp)
    csrr t0,mstatus
    sw t0,4(sp)
    csrr t0,mie
    sw t0,8(sp)

    csrr t0,mtvec
    sw t0,12(sp)

    csrr t0,mtvt
    sw t0,16(sp)

    csrr t0,mirq_entry
    sw t0,20(sp)

    lui t0,0xA0120
    lui t1,0xa0000

    /* save sp */
    sw sp,0x1c(t0)

    /* save pc */
    beqc a0,1,_deep_mode
    la  t2,.wakeup_vector
    j _save_pc
_deep_mode:
    li t2,0

    /* PM_STATUS_N22_DEEP_SLEEP_READY flag prepare */
    lw t4,0xb0(t0)
    ori t4,t4,0x2

    /* d25f reset vector and flag set */
    lui t3,0x20000
    sw t3,0x10(t0)
    sw t4,0xb0(t0)
    fence

_save_pc:
    sw t2,0x14(t0)

    /* set sleep */
    lui t2,0x00010
    ori t2,t2,0x1
    sw t2,0xc0(t1)
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

    lui t2,0xa000a
    sw  t2,0x3c(t1)

    /* restore sp */
    lw sp,0x1c(t0)

    /* set clic mode, base addr for interrupt and exception, low 6bit is 000011 */
#    la t2, trap_entry
#    ori t2,t2,0x03
#    csrw   mtvec, t2

    /* set base addr of trap vector table in clic mode */
#    la     t2, _vector_base
#    csrw   mtvt, t2

    /* default SHV is Non-vector mode */

    /* use interrupt fast entry */
#    la t2,fast_irq_enter
#    ori t2,t2,0x01
#    csrw mirq_entry,t2

    lw  gp,0(sp)
    lw  t2,4(sp)
    csrw mstatus,t2
    lw  t2,8(sp)
    csrw mie,t2

    lw  t2,12(sp)
    csrw mtvec,t2

    lw  t2,16(sp)
    csrw mtvt,t2

    lw  t2,20(sp)
    csrw mirq_entry,t2


    addi sp,sp,32

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

