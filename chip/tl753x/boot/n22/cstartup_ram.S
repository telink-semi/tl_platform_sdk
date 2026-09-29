/********************************************************************************************************
 * @file    cstartup_ram.S
 *
 * @brief   This is the boot file for tl753x
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
#ifdef N22_MCU_STARTUP_RAM

/* If using Andes toolchain, this Macro is defined in it's toolchain */
/* If using std gcc toolchain, this core register(not standard risc-v core register)
    should be defined here. */
#ifdef STD_GCC
#define mmisc_ctl  0x7D0
#endif

//RAM0 128 (KB/Bank) * 6  (Bank) = 768KB
//RAM1 32  (KB/Bank) * 16 (Bank) = 512KB
//RAM2 64  (KB/Bank) * 12 (Bank) = 768KB
//Note: d25f/cstartup_flash.S, d25f/cstartup_ram.S, n22/cstartup_flash.S, n22/cstartup_ram.S configurations are consistent and need to be modified together.
//RAM0
    .equ RAM0_SIZE,              6
    .equ RAM0_DSP_SIZE,          6
    .equ RAM0_N22_SIZE,          0
    .equ RAM0_D25_DLM_SIZE,      0
    .equ RAM0_N22_DLM_SIZE,      0
    .equ RAM0_DSP_DLM_SIZE,      4
//RAM1
    .equ RAM1_SIZE,              16
    .equ RAM1_DSP_SIZE,          0
    .equ RAM1_N22_SIZE,          16
    .equ RAM1_D25_DLM_SIZE,      0
    .equ RAM1_N22_DLM_SIZE,      4
    .equ RAM1_DSP_DLM_SIZE,      0
//RAM2
    .equ RAM2_SIZE,              12
    .equ RAM2_DSP_SIZE,          0
    .equ RAM2_N22_SIZE,          0
    .equ RAM2_D25_DLM_SIZE,      6
    .equ RAM2_N22_DLM_SIZE,      0
    .equ RAM2_DSP_DLM_SIZE,      0

    .equ __D25F_IRAM_SIZE,       ((RAM0_SIZE - RAM0_DSP_SIZE - RAM0_N22_SIZE) - RAM0_D25_DLM_SIZE) * 128 * 1024 + \
                                 ((RAM1_SIZE - RAM1_DSP_SIZE - RAM1_N22_SIZE) - RAM1_D25_DLM_SIZE) * 32  * 1024 + \
                                 ((RAM2_SIZE - RAM2_DSP_SIZE - RAM2_N22_SIZE) - RAM2_D25_DLM_SIZE) * 64  * 1024

    .equ __D25F_DRAM_SIZE,       (RAM0_D25_DLM_SIZE * 128 * 1024 + RAM1_D25_DLM_SIZE * 32 * 1024 + RAM2_D25_DLM_SIZE * 64 * 1024)

    .equ __N22_IRAM_SIZE,        (RAM0_N22_SIZE - RAM0_N22_DLM_SIZE) * 128 * 1024 + \
                                 (RAM1_N22_SIZE - RAM1_N22_DLM_SIZE) * 32  * 1024 + \
                                 (RAM2_N22_SIZE - RAM2_N22_DLM_SIZE) * 64  * 1024

    .equ __N22_DRAM_SIZE,        (RAM0_N22_DLM_SIZE * 128 * 1024 + RAM1_N22_DLM_SIZE * 32  * 1024 + RAM2_N22_DLM_SIZE * 64  * 1024)

    .section .vectors, "ax"

    .global     __D25F_IRAM_SIZE
    .global     __D25F_DRAM_SIZE
    .global     __N22_IRAM_SIZE
    .global     __N22_DRAM_SIZE

    .option push
    .option norelax
        .org 0x0


        .global _RESET_ENTRY
    .type _RESET_ENTRY,@function

        .align 2
_RESET_ENTRY:
    j        _START
    //free the 6th ~ 7th byte to store the crc type of the bin file
     .org 0x08
     .word (_ILM_SIZE)//0x20080008
     .org 0x0c
     .word (_DLM_SIZE)//0x2008000c
     .org 0x10
     .word (_DATA_LMA_START_OFFSET)//20080010
     .org 0x18
     .word (BIN_SIZE)
     .org 0x20
     .word ('T'<<24 | 'L'<<16 | 'N'<<8 | 'K')
     .org 0x24
    .word (0x030027a8)               //READ:    cmd:1x, addr:1x, data:1x, dummy:8
    //.word (0x3B0097A9)             //DREAD:   cmd:1x, addr:1x, data:2x, dummy:8
    //.word (0xBB0093B9)             //X2READ:  cmd:1x, addr:2x, data:2x, dummy:4
    //.word (0x6B0097AA)             //QREAD:   cmd:1x, addr:1x, data:4x, dummy:8
    //.word (0xEB0095BA)               //X4READ:  cmd:1x, addr:4x, data:4x, dummy:6

        .option pop
        .align 2

_START:
    /* Initialize global pointer */
        .option push
        .option norelax
        la     gp, __global_pointer$
        .option pop

    /* Initialize stack pointer */
        la     t0, _STACK_TOP
        mv     sp, t0

#ifdef __nds_execit
    /* Initialize EXEC.IT table */
    la t0, _ITB_BASE_
    csrw uitb, t0
#endif

#ifdef __riscv_flen
    /* Enable FPU */
    li t0, 0x00006000
    csrrs t0, mstatus, t0
    /* Initialize FCSR */
    //fscsr zero
#endif

    /* Initial machine trap vector base Base */
    la  t0, trap_entry
    ori t0, t0, 3
    csrw    mtvec, t0
    /* Initial machine interrupt-vector table Base */
    la  t0, __vectors
    csrw    mtvt, t0
#if 0
    /* Enable vectored external plic interrupt */
        csrsi  mmisc_ctl, 2

    /*vector mode enable bit (VECTORED) of the Feature Enable Register */
        lui     t0, 0xe4000
    li      t1, 0x02
    sw      t1, 0x0(t0)      //(*(volatile unsigned long*)(0xe4000000))= 0x02
#endif

    /* Zero .bss section in sram */
_ZERO_BSS:
        lui    t0, 0
        la     t2, _BSS_VMA_START
        la     t3, _BSS_VMA_END
_ZERO_BSS_BEGIN:
        bleu   t3, t2, _FILL_STK
        sw     t0, 0(t2)
        addi   t2, t2, 4
        j      _ZERO_BSS_BEGIN

    /* Fill the remaining section in sram */
_FILL_STK:
#if 0
        lui    t0, 0x55555
        addi   t0, t0, 0x555
        la     t2, _BSS_VMA_END   //_BSS_VMA_END  must be 4-byte aligned
        la     t3, _STACK_TOP     //_STACK_TOP    must be 4-byte aligned
_FILL_STK_BEGIN:
        bleu   t3, t2, _MAIN_FUNC
        sw     t0, 0(t2)
        addi   t2, t2, 4
        j      _FILL_STK_BEGIN
#endif
    /* Jump to the main function */
_MAIN_FUNC:
    nop

    la     t0, main
    jalr   t0

    nop
    nop
    nop
    nop
    nop
_END:
    j    _END


    .global default_irq_entry
    .align 2

default_irq_entry:
1:  j 1b

        .weak trap_handler
    .weak g_pm_multi_addr

 trap_handler:
1:  j 1b

    .macro INTERRUPT num
    .weak entry_irq\num
    .set entry_irq\num, default_irq_entry
    .long entry_irq\num
    .endm

#define VECTOR_NUMINTRS         81/* 63+18  1~18 reserved */

    .global __vectors
    .balign 512                 /*2^(ceiling（log2(N)+2),N=82*/


__vectors:
    /* CLIC interrupt vector */
    .altmacro
    .set irqno, 0
    .rept VECTOR_NUMINTRS/*  .rept  .endr  */
    INTERRUPT %irqno
    .set irqno, irqno+1
    .endr
#endif
