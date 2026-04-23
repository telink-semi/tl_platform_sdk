/*******************************************************************************************************
 *
 * @file    cstartup_ram_start.S
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
#if (defined(MCU_CORE_TL752X_D25F) && defined(MCU_STARTUP_RAM))
.section .init

.globl _reset_entry
.type _reset_entry,@function
_reset_entry:
    j _usr_start
    .balign 4
    /* may define user data,eg bin_size, crc, cmd and so on */

.balign    4
.type _usr_start,@function
_usr_start:
    /* Initialize global pointer */
    .option push
    .option norelax
    la     gp, __global_pointer$
    .option pop

    /* Initialize stack pointer */
    la     t0, __stack_top
    mv     sp, t0

#ifdef __nds_execit
    /* Initialize EXEC.IT table */
    la t0, _ITB_BASE_
    csrw uitb, t0
#endif

    /* Initial machine trap-vector Base */
    la     t0, __vectors
    csrw   mtvec, t0

    /* Enable vectored external plic interrupt */
    csrsi  mmisc_ctl, 2

    /*vector or preemptive mode enable bit (VECTORED) of the Feature Enable Register */
    lui     t0, 0xe4000
    li      t1, 0x02
    sw      t1, 0x0(t0)      /* (*(volatile unsigned word*)(0xe4000000))= 0x02 */

    /* Enable FPU */
    li t0, 0x00006000
    csrs mstatus, t0
    /* Initialize FCSR */
    fscsr zero

    /* move lma data to vma data */
    la a0, _lmadata
    la a1, _vmadata
    la a2, _edata
    bgeu a1, a2, 2f
1:
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b

    /* zero .bss section in sram */
2:
    la a0, __bss_start
    la a1, __bss_end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 1b
2:
  //  call SystemInit
    call main

    .global default_irq_entry
    .align 2

default_irq_entry:
1:  j 1b

       .weak trap_handler

 trap_handler:
1:  j 1b

    .macro INTERRUPT num
    .weak entry_irq\num
    .set entry_irq\num, default_irq_entry
    .long entry_irq\num
    .endm

#define VECTOR_NUMINTRS         63

    .section .init, "ax"

    .global __vectors
    .balign 256

__vectors:
    /* Trap vector */
    .long trap_entry

    /* PLIC interrupt vector */
    .altmacro
    .set irqno, 1
    .rept VECTOR_NUMINTRS/*  .rept  .endr  */
    INTERRUPT %irqno
    .set irqno, irqno+1
    .endr

#endif
