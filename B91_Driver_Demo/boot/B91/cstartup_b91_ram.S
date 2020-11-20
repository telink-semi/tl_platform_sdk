/********************************************************************************************************
 * @file	cstartup_b91_ram.S
 *
 * @brief	This is the boot file for B91
 *
 * @author	Driver Group
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
#ifdef MCU_STARTUP_RAM_B91
#define __LOAD_DUT 	64


.section .ram_boot, "ax"
    .option push
	.option norelax
    .global _RAM_RESET_ENTRY
 	.type _RAM_RESET_ENTRY,@function
    .align 2
_RAM_RESET_ENTRY:
	/* Decide whether this is an NMI or cold reset */
	j 		_RAM_START
	/* Limit the the size of ram code  in DUT_Test_Demo */
	.org 0x14
	.word(0x01000000+__LOAD_DUT<<16)
	.org 0x22

_RAM_START:

	/* Initialize global pointer */
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
	fscsr zero
#endif

    /* Initial machine trap-vector Base */
    la     t0, __vectors
    csrw   mtvec, t0

    /* Enable vectored external plic interrupt */
    csrsi  mmisc_ctl, 2

	/*vector mode enable bit (VECTORED) of the Feature Enable Register */
    lui		t0, 0xe4000
	li		t1, 0x02
	sw		t1, 0x0(t0)		 //(*(volatile unsigned long*)(0xe4000000))= 0x02

    /* Enable I/D-Cache */
    csrr   t0,  mcache_ctl
    ori    t0,  t0,  1  #/I-Cache
    ori    t0,  t0,  2  #/D-Cache
    csrw   mcache_ctl,  t0
    fence.i

	/* Zero .bss section in sram */
_RAM_ZERO_BSS:
    lui    t0, 0
    la     t2, _BSS_VMA_START
    la     t3, _BSS_VMA_END
_RAM_ZERO_BSS_BEGIN:
    bleu   t3, t2, _RAM_ZERO_AES
    sw     t0, 0(t2)
    addi   t2, t2, 4
    j      _RAM_ZERO_BSS_BEGIN

	/* Zero .aes section in sram */
_RAM_ZERO_AES:
    lui    t0, 0
    la     t2, _AES_VMA_START
    la     t3, _AES_VMA_END
_RAM_ZERO_AES_BEGIN:
    bleu   t3, t2, _RAM_FILL_STK
    sw     t0, 0(t2)
    addi   t2, t2, 4
    j      _RAM_ZERO_AES_BEGIN


	/* Fill the remaining section in sram */
_RAM_FILL_STK:
#if 0
    lui    t0, 0x55555
    addi   t0, t0, 0x555
    la     t2, _BSS_VMA_END
    la     t3, _STACK_TOP
_RAM_FILL_STK_BEGIN:
    bleu   t3, t2, _RAM_MAIN_FUNC
    sw     t0, 0(t2)
    addi   t2, t2, 4
    j      _RAM_FILL_STK_BEGIN
#endif
	/* Jump to the main function */
_RAM_MAIN_FUNC:
    nop

    la     t0, main
    jalr   t0

    nop
    nop
    nop
    nop
    nop

_RAM_END:
    j    _RAM_END





.text
	.global default_irq_entry
	.align 2

default_irq_entry:
1:	j 1b

       .weak trap_handler

 trap_handler:
1:	j 1b

	.macro INTERRUPT num
	.weak entry_irq\num
	.set entry_irq\num, default_irq_entry
	.long entry_irq\num
	.endm

#define VECTOR_NUMINTRS         63

   	.section .ram_code, "ax"

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
