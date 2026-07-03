/********************************************************************************************************
 * @file    pmp.c
 *
 * @brief   This is the source file for B91m
 *
 * @author  Driver Group
 * @date    2023
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
#include "pmp_config.h"

#if (defined(MCU_CORE_B92))
#include "lib/include/pmp.h"
#endif

/**
 * @brief The value of the mtval register when the exception is entered.
 */
static volatile long exception_mtval;

/**
 * @brief The value of the mepc register when the exception is entered.
 */
static volatile long exception_mepc;

/**
 * @brief The value of the mstatus register when the exception is entered.
 */
static volatile long exception_mstatus;

/**
 * @brief The value of the mcause register when the exception is entered.
 */
static volatile long exception_mcause;

/**
 * @brief The value of the mdcause register when the exception is entered.
 */
static volatile long exception_mdcause;

/**
 * @brief This array is used for PMP testing.
 */
unsigned char RO_Array[1*KB] __attribute__ ((aligned(2*KB)));

/**
 * @brief      This function serves to switch from machine mode to user mode and jump to a user-defined function.
 * @param[in]  fun_ptr  Pointer to the user-defined function to jump to in user mode.
 * @return     None
 */
void __attribute__((naked)) switch_to_user_mode(user_fun fun_ptr)
{
    /* switch to user mode and go to fun_ptr */
    MC_SWITCH_USER_MODE(NDS_MSTATUS, NDS_MEPC, (unsigned long)fun_ptr);

    /**
       Jump to user executive function and user mode is enabled.
       NOTE:
           The PC value is equal to MEPC and privilege mode is equal to MSTATUS.MPP,
           when 'mret' is executed.
     */
    if (fun_ptr)
    {
        __asm__("mret\n\t");
    }
    /* Use naked attribute since no pop stack after mret */
}


/**
 * @brief      This function serves to switch to machine mode and jump to a user-defined function.
 * @param[in]  fun_ptr  Pointer to the user-defined function to jump to in user mode.
 * @return     None
 */
void __attribute__((naked)) switch_to_machine_mode(user_fun fun_ptr)
{
    /* switch to machine mode and go to fun_ptr */
    USER_SWITCH_MC_MODE(NDS_MSTATUS, NDS_MEPC, (unsigned long)fun_ptr);

    /**
       Jump to user executive function and user mode is enabled.
       NOTE:
           The PC value is equal to MEPC and privilege mode is equal to MSTATUS.MPP,
           when 'mret' is executed.
     */
    if (fun_ptr)
    {
        __asm__("mret\n\t");
    }
    /* Use naked attribute since no pop stack after mret */
}

#if(!defined(MCU_CORE_B92))
/**
 * @brief      This function serves to configure a PMP entry using the TOR (Top of Region) scheme.
 * @param[in]  entry    PMP entry number (0-15) to configure.
 * @param[in]  va       Virtual address representing the start of the address range.
 * @param[in]  pmpcfg   Configuration value for the PMP entry.
 * @return     None
 */
void pmp_tor_config(char entry, void* va, char pmpcfg)
{
    switch (entry) {
    case 0:
        write_csr(NDS_PMPADDR0, TOR(va));
        break;
    case 1:
        write_csr(NDS_PMPADDR1, TOR(va));
        break;
    case 2:
        write_csr(NDS_PMPADDR2, TOR(va));
        break;
    case 3:
        write_csr(NDS_PMPADDR3, TOR(va));
        break;
#if !(defined(MCU_CORE_TL323X) || defined(MCU_CORE_TL521X))
    case 4:
        write_csr(NDS_PMPADDR4, TOR(va));
        break;
    case 5:
        write_csr(NDS_PMPADDR5, TOR(va));
        break;
    case 6:
        write_csr(NDS_PMPADDR6, TOR(va));
        break;
    case 7:
        write_csr(NDS_PMPADDR7, TOR(va));
        break;
#endif
    }
#if __riscv_xlen == 64  /*64bit-MCU*/
    switch (entry >> 3){
    case 0:
        write_csr(NDS_PMPCFG0, ((read_csr(NDS_PMPCFG0) & (~(0xFFLL << ((long)(entry%8) << 3)))) | (((long)pmpcfg) << ((long)(entry%8) << 3))));
        break;
    case 1:
        write_csr(NDS_PMPCFG2, ((read_csr(NDS_PMPCFG2) & (~(0xFFLL << ((long)(entry%8) << 3)))) | (((long)pmpcfg) << ((long)(entry%8) << 3))));
        break;
    }
#else                  /*32bit-MCU*/
    switch (entry >> 2) {
    case 0:
        write_csr(NDS_PMPCFG0, ((read_csr(NDS_PMPCFG0) & (~((0xFF) << ((entry%4) << 3)))) | (((long)pmpcfg) << ((entry%4) << 3))));
        break;
    case 1:
        write_csr(NDS_PMPCFG1, ((read_csr(NDS_PMPCFG1) & (~((0xFF) << ((entry%4) << 3)))) | (((long)pmpcfg) << ((entry%4) << 3))));
        break;
    case 2:
        write_csr(NDS_PMPCFG2, ((read_csr(NDS_PMPCFG2) & (~((0xFF) << ((entry%4) << 3)))) | (((long)pmpcfg) << ((entry%4) << 3))));
        break;
    case 3:
        write_csr(NDS_PMPCFG3, ((read_csr(NDS_PMPCFG3) & (~((0xFF) << ((entry%4) << 3)))) | (((long)pmpcfg) << ((entry%4) << 3))));
        break;
    }
#endif
}

/**
 * @brief      This function serves to configure a PMP entry using the NAPOT (Not A Power Of Two) scheme.
 * @param[in]  entry    PMP entry number (0-15) to configure.
 * @param[in]  va       Virtual address representing the start of the address range.
 * @param[in]  size     Size of the address range.
 * @param[in]  pmpcfg   Configuration value for the PMP entry.
 * @return     None
 */
void pmp_napot_config(char entry, void* va, unsigned long size, char pmpcfg)
{
    switch (entry) {
    case 0:
        write_csr(NDS_PMPADDR0, NAPOT(va, size));
        break;
    case 1:
        write_csr(NDS_PMPADDR1, NAPOT(va, size));
        break;
    case 2:
        write_csr(NDS_PMPADDR2, NAPOT(va, size));
        break;
    case 3:
        write_csr(NDS_PMPADDR3, NAPOT(va, size));
        break;
#if !(defined(MCU_CORE_TL323X) || defined(MCU_CORE_TL521X))
    case 4:
        write_csr(NDS_PMPADDR4, NAPOT(va, size));
        break;
    case 5:
        write_csr(NDS_PMPADDR5, NAPOT(va, size));
        break;
    case 6:
        write_csr(NDS_PMPADDR6, NAPOT(va, size));
        break;
    case 7:
        write_csr(NDS_PMPADDR7, NAPOT(va, size));
        break;
#endif
    }
#if __riscv_xlen == 64   /*64bit-MCU*/
    switch (entry >> 3){
    case 0:
        write_csr(NDS_PMPCFG0, ((read_csr(NDS_PMPCFG0) & (~(0xFFLL << ((long)(entry%8) << 3)))) | (((long)pmpcfg) << ((long)(entry%8) << 3))));
        break;
    case 1:
        write_csr(NDS_PMPCFG2, ((read_csr(NDS_PMPCFG2) & (~(0xFFLL << ((long)(entry%8) << 3)))) | (((long)pmpcfg) << ((long)(entry%8) << 3))));
        break;
    }
#else                   /*32bit-MCU*/
    switch (entry >> 2) {
    case 0:
        write_csr(NDS_PMPCFG0, ((read_csr(NDS_PMPCFG0) & (~((0xFF) << ((entry%4) << 3)))) | (((long)pmpcfg) << ((entry%4) << 3))));
        break;
    case 1:
        write_csr(NDS_PMPCFG1, ((read_csr(NDS_PMPCFG1) & (~((0xFF) << ((entry%4) << 3)))) | (((long)pmpcfg) << ((entry%4) << 3))));
        break;
    case 2:
        write_csr(NDS_PMPCFG2, ((read_csr(NDS_PMPCFG2) & (~((0xFF) << ((entry%4) << 3)))) | (((long)pmpcfg) << ((entry%4) << 3))));
        break;
    case 3:
        write_csr(NDS_PMPCFG3, ((read_csr(NDS_PMPCFG3) & (~((0xFF) << ((entry%4) << 3)))) | (((long)pmpcfg) << ((entry%4) << 3))));
        break;
    }
#endif
}
#endif

/**
 * @brief   This function serves to initialize PMP (Physical Memory Protection) configuration.
 * @return  None
 */
void init_pmp_config(void)
{
    extern char _DATA_VMA_START;
    /**
       Check whether the CPU configured with PMP feature.
       Write 0x3 to the pmpcfg0 register, and read it back
       to check the number of PMP entries.
     */
    write_csr(NDS_PMPCFG0, 0x3);
    if (!read_csr(NDS_PMPCFG0)) {
        printf("PMP entries is 0, CPU does NOT support PMP.\n");
        while(1);
    }
    else
    {
        printf("CPU support PMP.\r\n");
    }

    printf("\r\n*******************************************************\r\n");
    printf("DATA_VMA_START:          %p\r\n", (void *)&_DATA_VMA_START);
    printf("RO_Array[0]:             %p\r\n", (void *)&RO_Array[0]);
    printf("End of RO_Array:         %p\r\n", (void *)(&RO_Array[0] + sizeof(RO_Array)));
    printf("user_app_test addr :     %p\r\n", (void *)user_app);
    printf("user_test_function addr: %p\r\n", (void *)user_test_function);
    printf("*******************************************************\r\n\r\n");

    /* Disable global interrupt but allow exception */
    clear_csr(NDS_MSTATUS, FLD_MSTATUS_MIE);

    /* RISCV-SPA PMP Priority and Matching Logic: support overlapped PMP entry setting
     The lowest-numbered PMP entry that matches any byte of an access determines whether that access succeeds or fails */
#if(MCU_MODE==U_MODE)

#if (ADDR_MATCH_MODE==USE_NAPOT)
    /* PMP entry 0 : 0~0x80000*/
    pmp_napot_config(0, (void*)0, (unsigned long)(&_DATA_VMA_START), PMPCFG_LAXWR(PMP_L_OFF, PMP_A_NAPOT, PMP_W_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 1 : RO_Array ~ (RO_Array + sizeof(RO_Array))*/
    pmp_napot_config(1, (void*)&RO_Array[0],sizeof(RO_Array), PMPCFG_LAXWR(PMP_L_OFF, PMP_A_NAPOT, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /*PMP entry 2 :_DATA_VMA_START~_STACK_TOP  0x80000~0xa0000 */
    pmp_napot_config(2, (void*)&_DATA_VMA_START, EDLM_SIZE, PMPCFG_LAXWR(PMP_L_OFF, PMP_A_NAPOT, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 3 : 0x20000000 ~ 0x40000000*/
    pmp_napot_config(3, (void*)0x20000000, 0x20000000, PMPCFG_LAXWR(PMP_L_OFF, PMP_A_NAPOT, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 3 : 0x00000000 ~ 0xFFFFFFFF*/
    pmp_napot_config(4, (void*)0x00000000, 0xFFFFFFFF, PMPCFG_LAXWR(PMP_L_OFF, PMP_A_NAPOT, PMP_X_ON, PMP_W_ON, PMP_R_ON));

#else    /* USE_TOR */

    printf("\r\n*************PMP uses TOR scheme!.*********************\r\n");
    printf("PMP entry 0 :       0  ~  %8p\r\n",(void *)&_DATA_VMA_START);
    printf("PMP entry 1 :%8p  ~  %8p\r\n",(void *)&_DATA_VMA_START, (void *)&RO_Array[0]);
    printf("PMP entry 2 :%8p  ~  %8p\r\n",(void *)&RO_Array[0],(void *)(&RO_Array[0] + sizeof(RO_Array)));
    printf("PMP entry 3 :%8p  ~  FFFFFFFF\r\n",(void *)(&RO_Array[0] + sizeof(RO_Array)));
    printf("*******************************************************\r\n\r\n");

    /* PMP entry 0 : 0~_DATA_VMA_START*/
    pmp_tor_config(0, (void*)(&_DATA_VMA_START), PMPCFG_LAXWR(PMP_L_OFF, PMP_A_TOR, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 1 : _DATA_VMA_START ~RO_Array[0]*/
    pmp_tor_config(1, (void*)&RO_Array[0], PMPCFG_LAXWR(PMP_L_OFF, PMP_A_TOR, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 2 : RO_Array ~ (RO_Array[0] + sizeof(RO_Array))*/
    pmp_tor_config(2, (void*)(&RO_Array[0] + sizeof(RO_Array)), PMPCFG_LAXWR(PMP_L_OFF, PMP_A_TOR, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 3 : (RO_Array + sizeof(RO_Array)) ~ 0xFFFFFFFF */
    pmp_tor_config(3, (void*)0xFFFFFFFF, PMPCFG_LAXWR(PMP_L_OFF, PMP_A_TOR, PMP_X_ON, PMP_W_ON, PMP_R_ON));
#endif

#else    /* M_Mode */

#if (ADDR_MATCH_MODE==USE_NAPOT)
    /* PMP entry 0 : 0~0x80000*/
    pmp_napot_config(0, (void*)0, (unsigned long)(&_DATA_VMA_START), PMPCFG_LAXWR(PMP_L_ON, PMP_A_NAPOT, PMP_W_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 1 : RO_Array ~ (RO_Array + sizeof(RO_Array))*/
    pmp_napot_config(1, (void*)&RO_Array[0],sizeof(RO_Array), PMPCFG_LAXWR(PMP_L_ON, PMP_A_NAPOT, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /*PMP entry 2 :_DATA_VMA_START~_STACK_TOP  0x80000~0xa0000 */
    pmp_napot_config(2, (void*)&_DATA_VMA_START, EDLM_SIZE, PMPCFG_LAXWR(PMP_L_ON, PMP_A_NAPOT, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 3 : 0x20000000 ~ 0x40000000*/
    pmp_napot_config(3, (void*)0x20000000, 0x20000000, PMPCFG_LAXWR(PMP_L_ON, PMP_A_NAPOT, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 3 : 0x00000000 ~ 0xFFFFFFFF*/
    pmp_napot_config(4, (void*)0x00000000, 0xFFFFFFFF, PMPCFG_LAXWR(PMP_L_ON, PMP_A_NAPOT, PMP_X_ON, PMP_W_ON, PMP_R_ON));

#else    /* USE_TOR */
    printf("\r\n*************PMP uses TOR scheme!.*********************\r\n");
    printf("PMP entry 0 :       0  ~  %8p\r\n",(void *)&_DATA_VMA_START);
    printf("PMP entry 1 :%8p  ~  %8p\r\n",(void *)&_DATA_VMA_START, (void *)&RO_Array[0]);
    printf("PMP entry 2 :%8p  ~  %8p\r\n",(void *)&RO_Array[0],(void *)(&RO_Array[0] + sizeof(RO_Array)));
    printf("PMP entry 3 :%8p  ~  FFFFFFFF\r\n",(void *)(&RO_Array[0] + sizeof(RO_Array)));
    printf("*******************************************************\r\n");

    /* PMP entry 0 : 0~_DATA_VMA_START*/
    pmp_tor_config(0, (void*)(&_DATA_VMA_START), PMPCFG_LAXWR(PMP_L_ON, PMP_A_TOR, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 1 : _DATA_VMA_START ~RO_Array[0]*/
    pmp_tor_config(1, (void*)&RO_Array[0], PMPCFG_LAXWR(PMP_L_ON, PMP_A_TOR, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 2 : RO_Array ~ (RO_Array[0] + sizeof(RO_Array))*/
    pmp_tor_config(2, (void*)(&RO_Array[0] + sizeof(RO_Array)), PMPCFG_LAXWR(PMP_L_ON, PMP_A_TOR, PMP_X_ON, PMP_W_ON, PMP_R_ON));
    /* PMP entry 3 : (RO_Array + sizeof(RO_Array)) ~ 0xFFFFFFFF */
    pmp_tor_config(3, (void*)0xFFFFFFFF, PMPCFG_LAXWR(PMP_L_ON, PMP_A_TOR, PMP_X_ON, PMP_W_ON, PMP_R_ON));
#endif

#endif
}

/**
 * @brief     PMP Demo exception irq handler.
 * @return    None
 */
void except_handler(void)
{
    long mpp;

    /* unhandled trap */
    exception_mtval   = read_csr(NDS_MTVAL);
    exception_mepc    = read_csr(NDS_MEPC);
    exception_mstatus = read_csr(NDS_MSTATUS);
    exception_mcause  = read_csr(NDS_MCAUSE);
    exception_mdcause = read_csr(NDS_MDCAUSE);

    printf("\r\n========== Exception Occurred ==========\r\n");

    /* Print current mode (User or Machine mode) */
    mpp = (exception_mstatus & MSTATUS_MPP_MSK) >> 11;
    if (mpp == HART_USER) {
        printf("Current Mode: USER Mode\r\n");
    } else if (mpp == HART_USER) {
        printf("Current Mode: MACHINE Mode\r\n");
    }

    /* Print exception cause */
    printf("Exception Cause (mcause): 0x%lx\r\n", exception_mcause);
    if ((exception_mcause & (1LL << 63)) == 0) {
        switch (exception_mcause) {
            case 2:
                printf("Reason: Illegal Instruction\r\n");
                break;
            case 5:
                printf("Reason: Load Access Fault (PMP Read Violation)\r\n");
                break;
            case 7:
                printf("Reason: Store/AMO Access Fault (PMP Write Violation)\r\n");
                break;
            case 13:
                printf("Reason: Instruction Page Fault (PMP Execute Violation)\r\n");
                break;
            default:
                printf("Reason: Other Exception (%ld)\r\n", exception_mcause);
                break;
        }
    } else {
        printf("Reason: Interrupt\r\n");
    }

    /* Print detailed debug info */
    printf("Fault Address (mtval): 0x%lx\r\n", exception_mtval);
    printf("Fault PC (mepc):       0x%lx\r\n", exception_mepc);
    printf("Debug Cause (mdcause): 0x%lx\r\n", exception_mdcause);
    printf("========================================\r\n");

    while (1) {
        _ASM_NOP_;
    }
}

/**
 * @brief   This function serves to test function call.
 * @return  None
 */
void user_test_function(void)
{
    printf("The entry address of the user_test_function is %p, and the execution was successful.!\r\n",(void *)user_test_function);
}

/**
 * @brief   This function serves to launch application code.
 * @return  None
 * @note    Attention: This function must not return.
 */
void user_app(void)
{
    printf("The entry address of the user_test_function is %p, and the execution was successful.\r\n",(void *)user_app);

    // write test
    (*((unsigned long*)((long)&RO_Array[0]))) = 0x5555AAAA;
    printf("The address of the RO_Array[0] array is %p, and the write test was successful.\r\n",&RO_Array[0]);

    // read test
    write_reg32(0x140420,RO_Array[0]|(RO_Array[1]<<8)|(RO_Array[2]<<16)|(RO_Array[3]<<24));
    printf("The address of the RO_Array[0] array is %p, and the read test was successful.\r\n",&RO_Array[0]);

    // execute test
    user_test_function();
    while(1)
    {
        //Not allowed to return
        gpio_toggle(LED1);
        delay_ms(500);
    }
}
