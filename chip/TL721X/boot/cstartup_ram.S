/********************************************************************************************************
 * @file    cstartup_ram.S
 *
 * @brief   This is the boot file for TL721X
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
#ifdef MCU_STARTUP_RAM
#define __LOAD_DUT  64
/**
 * @brief   Set "DP_THROUGH_SWIRE_DIS" as "1" to disable the "dp_through_swire" function. Set "DP_THROUGH_SWIRE_DIS" as "0" to enable the "dp_through_swire" function.
 *          Risk description:
 *          The "dp_through_swire" function is enabled by default.When DP and DM pin are used as GPIO function and trigger "dp_through_swire" timing,
 *          there may be a problem of miswriting the chip through swire to cause the chip to crash. Therefore, disable the "dp_through_swire" function in this startup file.(set "DP_THROUGH_SWIRE_DIS" as "1").
 *          If the chip has only dp pin but no sws pin, using the above scheme (set "DP_THROUGH_SWIRE_DIS" as "1") will cause the following problems.
 *          1. During fixture production, burning a firmware program that disables the "dp_through_swire"function into unprogrammed chip will cause the problem that chip can not be burned again due to swire communication failure.
 *          2. Burning a firmware program that disables the "dp_through_swire" function with BDT tool may result in failure of debugging due to swire communication failure.
 *          If developers evaluate that the above scheme (set "DP_THROUGH_SWIRE_DIS" as "1") cannot be used, they can only set "DP_THROUGH_SWIRE_DIS" to "0" to enable the "dp_through_swire" function. However, be careful not to make DP and DM pin trigger "dp_through_swire" timing.
 *          In USB applications, 1. calling the usb_set_pin(1) interface (equivalent to usb_set_pin_en) will re-enable the dp_through_swire function 2. calling the usb_set_pin(0) interface will disable the dp_through_swire function.
 */
#ifndef DP_THROUGH_SWIRE_DIS
#define DP_THROUGH_SWIRE_DIS      1
#endif

/* If using Andes toolchain, these two Macro are defined in it's toolchain */
/* If using std gcc toolchain, these two core registers(not standard risc-v core registers)
    should be defined here. */
#ifdef STD_GCC
#define mmisc_ctl  0x7D0
#define mcache_ctl 0x7CA
#endif

.extern gpio_shutdown_ramcode_for_asm
.extern adc_anti_aging_mode_ramcode_for_asm

//The default driver configuration is 128K to ensure that the default driver configuration can work properly on all models.
//In actual use, please configure the sram size according to your own model, otherwise the efficiency will be affected.
//the most efficient use is:
//IRAM is used to store code, DRAM is used to store data, if the data-related segments are stored in IRAM, the efficiency will be affected.
//(add by weihua.zhang, confirmed by kaixin.chen and shujuan.chu 20230725)
#define SRAM_128K      1    //128KSRAM, 128KB-IRAM(128KB-Retention)/0KB-DRAM
#define SRAM_256K      2    //256KSRAM, 256KB-IRAM(256KB-Retention)/0KB-DRAM
#define SRAM_384K      3    //384KSRAM, 256KB-IRAM(256KB-Retention)/128KB-DRAM
#define SRAM_512K      4    //512KSRAM, 256KB-IRAM(256KB-Retention)/256KB-DRAM
#define SRAM_SIZE      SRAM_128K

#if (SRAM_SIZE == SRAM_256K)
    .equ __IRAM_2_EN,   1
    .equ __DRAM_1_EN,   0
    .equ __DRAM_2_EN,   0
    .equ __DRAM_DIS,    1
#elif (SRAM_SIZE == SRAM_384K)
    .equ __IRAM_2_EN,   1
    .equ __DRAM_1_EN,   1
    .equ __DRAM_2_EN,   0
    .equ __DRAM_DIS,    0
#elif (SRAM_SIZE == SRAM_512K)
    .equ __IRAM_2_EN,   1
    .equ __DRAM_1_EN,   1
    .equ __DRAM_2_EN,   1
    .equ __DRAM_DIS,    0
#elif (SRAM_SIZE == SRAM_128K)
    .equ __IRAM_2_EN,   0
    .equ __DRAM_1_EN,   0
    .equ __DRAM_2_EN,   0
    .equ __DRAM_DIS,    1
#endif

    .section .ram_boot, "ax"
    .global     __IRAM_2_EN
    .global     __DRAM_1_EN
    .global     __DRAM_2_EN
    .global     __DRAM_DIS

    .option push
    .option norelax
    .global _RAM_RESET_ENTRY
    .type _RAM_RESET_ENTRY,@function
    .align 2
_RAM_RESET_ENTRY:
    /* Decide whether this is an NMI or cold reset */
    j       _RAM_START
    .org 0x02
    .word(0x0004)//version
    /* This configuration is specifically for RF_Certification and does not need to be enabled for other scenarios */
#ifdef RF_CERTIFICATION_CGF_EN
    .org 0x10
    .word(_RF_CERTIFICATION_CFG_ADDR_OFFSET)
#endif
    /* Limit the the size of ram code  in DUT_Test_Demo */
    .org 0x14
    .word(0x01000000+__LOAD_DUT<<16)
    .org 0x20

_RAM_START:

    /* Initialize global pointer */
    la     gp, __global_pointer$
    .option pop

#if DP_THROUGH_SWIRE_DIS
    lui     t0, 0x80100
    addi    t0 , t0 , 0x700
    li      t1, 0x00
    sb      t1, 0x501(t0)  //0x80100c01 -> 0x00  <7>: 0 swire_usb_dis 
#endif

    /* Initialize stack pointer */
    la     t0, _STACK_TOP
    mv     sp, t0

#ifndef DUT_TEST
    /* gpio shutdown to decrease current. for retention this function was in ram segment which can be called early. */
    la     t0, gpio_shutdown_ramcode_for_asm
    jalr   t0
#endif

#ifdef __nds_execit
    /* Initialize EXEC.IT table */
    la t0, _ITB_BASE_
    csrw uitb, t0
#endif

#if 1
    /*
    * Since the adc reference voltage decreases over time, resulting in inaccurate sampling, invoking this interface can avoid this problem.
    * Since the chip experiences aging as soon as it is powered on, it is recommended to place the anti-aging logic as early as possible to prevent such issues.
    * The A0/A1/A2 versions have aging issues and need to be modified as necessary. the A3 versions, once confirmed to be problem free, should have the logic removed.
    * (updated by bolong.zhang, confirmed by haitao.gu shiyi.wu at 20250219)
    */
    la     t0, adc_anti_aging_mode_ramcode_for_asm
    jalr   t0
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
    lui     t0, 0xc4000
    li      t1, 0x02
    sw      t1, 0x0(t0)      //(*(volatile unsigned long*)(0xc4000000))= 0x02

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
    bleu   t3, t2, _RAM_FILL_STK
    sw     t0, 0(t2)
    addi   t2, t2, 4
    j      _RAM_ZERO_BSS_BEGIN

    /* Fill the remaining section in sram */
_RAM_FILL_STK:
#if 0
    lui    t0, 0x55555
    addi   t0, t0, 0x555
    la     t2, _BSS_VMA_END    //_BSS_VMA_END  must be 4-byte aligned
    la     t3, _STACK_TOP      //_STACK_TOP    must be 4-byte aligned
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
