/********************************************************************************************************
 * @file    rsa_test.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include <stdio.h>
#include "../app_config.h"

void print_U32_buf(unsigned int *buf, unsigned int wordLen, char *name);



#if 1

unsigned int rsa_modexp_1024_test(void)
{
    //n is the conversion of the stored data u32 small end to u8 large end form, i.e., annotated to the actual large value.
    unsigned int n[]=
    {
        0xFEA18675,0x1538B245,0x84E8E165,0x91BEB0D8,0x9D0B6997,0x1D7B833A,0xEFA2C3F6,0x7DF45F14,
        0x55565D78,0x69230B98,0x591F158B,0xE106BDD8,0x26AF59F0,0xE430C55E,0xB9EE5D48,0xC74A11EF,
        0x16D22D06,0xC453225E,0xEF660075,0x7119E5DB,0x57111778,0x66DAC542,0x0E2A4D2E,0xA6A47646,
        0x04D816F2,0xB5704D41,0x282C21EE,0x9D950126,0xA69A2B1C,0xEADB452B,0x0CF439F0,0xBEC7A940,
    };
    unsigned int e[]= {0x00010001};
    unsigned int d[]=
    {
        0x39CD7DE1,0x765A9FBE,0x28A3F778,0x9C0BBB36,0x92F2B6D6,0xA7B0D6E6,0x4AC3AC9D,0x495F0629,
        0x2B15D590,0x1DEA94F0,0x09655DB7,0x4A2A74BE,0xA830AEE4,0xA5C64770,0x36013850,0xF0667BA8,
        0xF32A533E,0x882FD8F7,0x045FBEC6,0x132E91D0,0xC83A5CE5,0xEBCEC702,0xE2698BC8,0xA8CE2AE4,
        0xB91FAE10,0xA06B202B,0xD8013303,0x1E06979A,0xC5FAE3E4,0xDAD7E244,0xD8366EDA,0xBC5D2053,
    };
    unsigned int p[]=
    {
        0x0C3B82FD,0x563A7F00,0x4C43666F,0xBC274F20,0x30247539,0x071A594D,0x0E069034,0x184B665F,
        0x8421D20C,0xBD3B7A16,0x0F45B041,0x6B1BA853,0xEC556813,0x3B21167E,0x2D08AE4A,0xE5324D00,
    };
    unsigned int q[]=
    {
        0x7A70D6D9,0xD91EB87C,0xA610AF00,0x2664B357,0x250F0450,0x963FBF1F,0xC423CD7D,0xE12EA919,
        0x1B0EB235,0x7F77F947,0x4A17C833,0x84715F7A,0xF264953B,0xC0695F17,0x75796707,0xD5173E2C,
    };
    unsigned int dp[]=
    {
        0x8AF1926D,0xE6B3D129,0x2BCEE822,0x8F142AB6,0xA9A1922B,0x36FB2DD9,0x50BA4D2D,0x43D30545,
        0xF4A72E1B,0xFB17B678,0x117F6668,0x3E3DB8E1,0x49818B30,0x26BB5E12,0x949AB54F,0x14B89077,
    };
    unsigned int dq[]=
    {
        0x69E1C5B1,0x12B84DA8,0x823396C5,0xF1EB5D37,0x8E8FF40D,0x9260C390,0x48E1B1D6,0xFCA4FE82,
        0x2F02230F,0x38A57BF4,0x99B73F12,0xCA14A8FF,0xCB3D116D,0xDCAA4637,0x7C7AA349,0x4A1674B5,
    };
    unsigned int u[]=
    {
        0xA2964E5B,0xF37FB26D,0x8B15254C,0xCAFAAD33,0xE3B1270B,0xCD27513C,0x7385C488,0x48899F5B,
        0x2234D1AA,0x893B7E4D,0xB343300B,0xEDA155DE,0x53C472E3,0x1602F8E0,0xBFE44F44,0x3FB0D177,
    };
    unsigned int std_out[]=
    {
        0x6918BEE1,0x5A78A5AE,0x537C93F8,0xBADE3C88,0x906FD649,0x082DA994,0x10BC7D78,0xE02469F7,
        0x20F71F91,0x9D56188D,0xA1933733,0x3A0FE3FD,0xFA551EC2,0x0F7BD1AC,0xDA221E31,0x60DA6F4F,
        0xC424F841,0xDB256AAD,0xB3C3B259,0x5480DDC6,0xBCF51563,0x9A245963,0x3106369F,0xDAD4C504,
        0x9C960A3B,0x357044F9,0x95F5521A,0x9F6D9285,0xC13468B2,0x8CD09D47,0x45A4B220,0x5351A82E,
    };


    unsigned int in[128], out[128], out2[128];
    unsigned int eBitLen = 17;
    unsigned int nBitLen = 1024;
    unsigned int  wordLen=(nBitLen+31)/32;
    unsigned int ret;
    //get_H(n, out, wordLen);print_BN_buf_U32(n, wordLen, "n");print_BN_buf_U32(out, wordLen, "out");
    //set input
    memset_(in, 0x5a, wordLen<<2);

    //sign(non-CRT mode)
    ret = RSA_ModExp(in, d, n, out, get_valid_bits(d, wordLen), nBitLen);
    if(RSA_SUCCESS != ret || uint32_BigNumCmp(out, wordLen, std_out, wordLen))
    {
        printf("\r\n RSA MOD EXP 1024 test failure, ret=%d", ret);
        print_BN_buf_U32(in, wordLen, "in");
        print_BN_buf_U32(out, wordLen, "out");
        return 1;
    }
    else
    {
        printf("\r\n RSA MOD EXP 1024 test success");
    }

    //sign(CRT mode)
    memset_(out, 0, wordLen<<2);
    ret = RSA_CRTModExp(in, p, q, dp, dq, u, out, nBitLen);
    if(RSA_SUCCESS != ret || uint32_BigNumCmp(out, wordLen, std_out, wordLen))
    {
        printf("\r\n RSA CRT MOD EXP 1024 test failure, ret=%d", ret);
        print_BN_buf_U32(p, wordLen/2, "p");
        print_BN_buf_U32(q, wordLen/2, "q");
        print_BN_buf_U32(dp, wordLen/2, "dp");
        print_BN_buf_U32(dq, wordLen/2, "dq");
        print_BN_buf_U32(u, wordLen/2, "u");
        print_BN_buf_U32(in, wordLen, "in");
        print_BN_buf_U32(out, wordLen, "out");
        return 1;
    }
    else
    {
        printf("\r\n RSA CRT MOD EXP 1024 test success");
    }

    //verify
    ret = RSA_ModExp(out, e, n, out2, eBitLen, nBitLen);
    if(RSA_SUCCESS != ret || uint32_BigNumCmp(out2, wordLen, in, wordLen))
    {
        printf("\r\n RSA MOD EXP 1024 test failure, ret=%d", ret);
        print_BN_buf_U32(out, wordLen, "out");
        print_BN_buf_U32(out2, wordLen, "out2");
        return 1;
    }
    else
    {
        printf("\r\n RSA MOD EXP 1024 test success");
    }

    return 0;
}



unsigned int rsa_modexp_2048_test(void)
{
    //n is 0xA7C5D82068EC9949...3958A753BB5248B9
    unsigned int n[]=
    {
        0xBB5248B9,0x3958A753,0x8374E33D,0x361B77F2,0xCB85F949,0xCA8E668C,0x66EDE655,0x3DDEE69E,
        0x8AACE682,0x99F46E90,0x4492985F,0x29F0F9C0,0xEBF0722B,0xE0179832,0xCF18AE20,0xE665C7C1,
        0x0CBE0F3A,0x40B1FD85,0x55F30FEC,0x667DD0CF,0x0445664A,0x324C8E9A,0x86ACD519,0xBB6B6E72,
        0xF2B5D9FE,0x147B9465,0xD1A21022,0xCBA4B564,0xFD868F9A,0x5FBDFE51,0x66635C00,0xD477C1B2,
        0xD154302A,0x60BD6712,0x40451294,0xBD3D93D6,0xB99E7133,0x42BF8DF8,0x481A2235,0x4F4290A2,
        0xFE90B45E,0x892B8244,0x0A33F5FA,0x381E10F9,0xA2B41B34,0xFCD8D1E4,0x865B96DA,0xF46D1760,
        0xCC5085D7,0x88EA540B,0xED35377E,0x07160284,0xFA1C1603,0xFB6CC61F,0x0C76B0BE,0x56353B18,
        0x3ED0F658,0x4C9FA8B4,0x59CC2863,0xC2128C81,0x371A8B13,0x6C807C1E,0x68EC9949,0xA7C5D820,
    };
    unsigned int e[]= {0x00010001};
    unsigned int d[]=
    {
        0xBFBF5039,0xE52AE46D,0x52610295,0x72AAF83F,0x28D40FA1,0x270A858B,0x8DEAB989,0x78ED0FB3,
        0x29946A0E,0xC56355E4,0x3F186B53,0xD486B4B3,0x63F56868,0xE450D0AE,0x1722616A,0x77199EFC,
        0x02FAEA03,0xBE0DA0CA,0xB94C869D,0xA9A94DD5,0x17082AB9,0xE71BEE19,0xDDF45A1D,0x7D1BE624,
        0x65397435,0x40B8B56E,0x4B591AA6,0x13FC9A6D,0x0FD48ABF,0xD7B78EDB,0x71C18BCF,0x073EA51C,
        0x6583789F,0xFA407806,0xEDC5285D,0x6DEE416C,0x5A2C7BF6,0x71BBAFF4,0xEEB3A6B3,0xA9ABFDBC,
        0x8391DB1F,0x667ACF54,0x1687748F,0x50ECE2F3,0xF7E9B284,0x9B0EDECC,0x3D4EE14C,0x5C7EE93B,
        0x0B048AC1,0x2DCE686A,0xE03B91A2,0xECBB1EF3,0xD88E255B,0xEE2863B5,0x8C9D97F5,0x062BC46F,
        0x8BE63E86,0x37A59DA4,0x126551A2,0x3B462FDE,0xEDB1B18C,0x5E487B35,0x92D2FDE8,0x7FBA29CE,
    };
    unsigned int p[]=
    {
        0xD2C5399F,0xF3EF5110,0x04970D25,0xE64CAEC5,0x5D5A068D,0xA7CE6463,0x80E71F9D,0x69331C79,
        0x45871E7C,0xA0B6B1D0,0xB5B27E5B,0x538F84A9,0x8DB003F7,0x68356ACE,0x42252C1D,0xDD889308,
        0x9D55A1E2,0xB51B0532,0x6D605FBA,0xEDAE1122,0xB5F34AF5,0xB552403E,0x7CC23ED4,0xA10075A3,
        0xB88DD8E3,0xDA3A1A7C,0x46942D7E,0x718EBCF2,0x339F1881,0xFF79A8CA,0x394262E7,0xD38DFA8E,
    };
    unsigned int q[]=
    {
        0xC39D0EA7,0x7C85F825,0x479D951E,0x65D3CC95,0xB544E463,0x5D704D69,0x7D3B641D,0xE5D7637B,
        0x3BB96DE8,0x3CF3EAFE,0x6E36C52E,0xB8148229,0xBB82F49E,0xE6A13EFE,0x5BA6BCA1,0xD0C9CCF0,
        0xE3B07AE5,0x67EEF090,0x6B9D44C0,0x6AF163AC,0x53749666,0xB90FAA34,0x770B3AB0,0x727A2482,
        0x0633A781,0x767780EA,0x1A0CBC6A,0xEB01038D,0x1E1FD9C1,0xA2D9284B,0xDED4E7A4,0xCB052788,
    };
    unsigned int dp[]=
    {
        0xDB507F89,0x23B7FCFD,0x5C1C714E,0xC6D07B7A,0x9357ABA1,0x6739F404,0x929A6045,0xCD381F53,
        0x14E8EB0D,0x0EA5CD18,0xBFCF414E,0x0067D48B,0xF19AC916,0x5A536CA3,0xD45FA412,0x47C0DF86,
        0x0B4A9B2E,0xB9644313,0xB1C99B7B,0xFA188B68,0x59063167,0x9DF56E18,0xF133AC96,0x0A299C90,
        0x61CE43C5,0x2F6C834A,0x8A572FDF,0x8EE58583,0xE8151555,0x4AE7E982,0xC79D7147,0x4CD6F8F6,
    };
    unsigned int dq[]=
    {
        0x10101715,0x0F98249C,0xBB96FB4E,0xE5BFD64A,0x6BA46F1C,0x9940C563,0x8F40084E,0xA37A7032,
        0xEDA54D31,0xAE6AC537,0x7DC043DF,0xCA9EA769,0x8E982024,0xBD410FA8,0x971F310C,0xA5EA69CF,
        0x95F7FDDA,0x7783167C,0xABA3CECF,0x0F3B41FD,0xA45AFA22,0x89F0CCF2,0xE173F472,0xB7283956,
        0x257EE399,0xDE489159,0xD8C9E2D1,0x1E7364EB,0x22564A75,0x7EBD126C,0x8041927F,0x847AF297,
    };
    unsigned int u[]=
    {
        0x273134B8,0x811F3B02,0x61385B16,0x4940D62E,0xAC11E62E,0x90657139,0xE0BA820D,0x3517F5E3,
        0xA0152677,0xFC65FE57,0xCF28A8AF,0x65E9080E,0xD88F479E,0xF9775F4D,0x60BF9490,0xB2BAEE6E,
        0x5A68CD17,0xB549B32F,0xF86E8A0F,0x0376A3B5,0xB34A8B3D,0x93B8C51A,0xE4A04408,0x2250EA7A,
        0xD905105E,0x2367E8BE,0x8C6F6643,0x0123C7C4,0xE9C2A57D,0xE3939FE8,0xFF8A801C,0xC99AC5E1,
    };
    unsigned int std_out[]=
    {
        0x65DE5107,0xEC26699D,0x0D76CE00,0x397AD40D,0x0DBD4F97,0xF30D4311,0x48CA76D0,0x5F2723C7,
        0xE3A21752,0xCB6F36A3,0xDA1204DB,0x66DF3D61,0x0334BACC,0xEC127801,0x90AD6D35,0x9307AE25,
        0x4B6F3716,0x74B04B2C,0x61E072D6,0x9DA1A085,0x4E685D85,0x640EC696,0x6AAF6343,0x87351877,
        0x70C97CE5,0x7B035CED,0xCB2C2C9F,0x17620FA2,0x724EBFBE,0x9F61B6F8,0xD58F829B,0x2F299CC5,
        0xCA5D6B61,0x2095905B,0xB3C8958A,0x36DA96E2,0x0DD9993C,0x8C8A76EC,0x91B75607,0xB25A39A3,
        0x8EDB1559,0xE5D2A164,0x3053F1B2,0x4AB1E95E,0x1EEB0CAB,0xD6EF57D0,0x5913D85F,0x64EEC60E,
        0xCFF42207,0x1F8065E2,0x6ED6A7AB,0x705F2F9E,0xD67FFDE5,0x03DAAFED,0x3372EFF6,0x4F58C1A8,
        0x3A1B21D6,0x1AD49793,0x3589FF12,0xA222521F,0x8A78096C,0x749AC189,0x411577B9,0x7FD2D10E,
    };

    unsigned int in[256], out[256], out2[256];
    unsigned int eBitLen = 17;
    unsigned int nBitLen = 2048;
    unsigned int wordLen=(nBitLen+31)/32;
    unsigned int ret;

    //get_H(n, out, wordLen);print_BN_buf_U32(n, wordLen, "n");print_BN_buf_U32(out, wordLen, "out");
    //set input
    memset_(in, 0x5a, wordLen<<2);

    //sign(non-CRT mode with pub)
//xil_printf("\r\n begin     "); fflush(stdout);
//for(int j=0;j<28;j++){
    ret = RSA_ModExp(in, d, n, out, nBitLen, nBitLen);
//}xil_printf("\r\n end     ");fflush(stdout);
    if(RSA_SUCCESS != ret || uint32_BigNumCmp(out, wordLen, std_out, wordLen))
    {
//      printf("\r\n RSA MOD EXP 2048 test 1 failure, ret=%d", ret);
//      print_BN_buf_U32(in, wordLen, "in");
//      print_BN_buf_U32(e, 1, "e");
//      print_BN_buf_U32(d, wordLen, "d");
//      print_BN_buf_U32(n, wordLen, "n");
//      print_BN_buf_U32(out, wordLen, "out");
        return 1;
    }
    else
    {
        printf("\r\n RSA MOD EXP 2048 test 1 success");
    }

    //sign(CRT mode with pub)
    memset_(out, 0, wordLen<<2);
//xil_printf("\r\n begin     "); fflush(stdout);
//for(int j=0;j<28;j++){
    ret = RSA_CRTModExp(in, p, q, dp, dq, u, out, nBitLen);
//}xil_printf("\r\n end     ");fflush(stdout);
    if(RSA_SUCCESS != ret || uint32_BigNumCmp(out, wordLen, std_out, wordLen))
    {
//      printf("\r\n RSA CRT MOD EXP 2048 test 1 failure, ret=%d", ret);
//      print_BN_buf_U32(p, wordLen/2, "p");
//      print_BN_buf_U32(q, wordLen/2, "q");
//      print_BN_buf_U32(dp, wordLen/2, "dp");
//      print_BN_buf_U32(dq, wordLen/2, "dq");
//      print_BN_buf_U32(u, wordLen/2, "u");
//      print_BN_buf_U32(in, wordLen, "in");
//      print_BN_buf_U32(out, wordLen, "out");
        return 1;
    }
    else
    {
        printf("\r\n RSA CRT MOD EXP 2048 test 1 success");
    }

    //verify
//xil_printf("\r\n begin     "); fflush(stdout);
//for(int j=0;j<800;j++){
    ret = RSA_ModExp(out, e, n, out2, eBitLen, nBitLen);
//}xil_printf("\r\n end     ");fflush(stdout);
    if(RSA_SUCCESS != ret || uint32_BigNumCmp(out2, wordLen, in, wordLen))
    {
//      printf("\r\n RSA MOD EXP 2048 test 2 failure, ret=%d", ret);
//      print_BN_buf_U32(out, wordLen, "out");
//      print_BN_buf_U32(out2, wordLen, "out2");
        return 1;
    }
    else
    {
        printf("\r\n RSA MOD EXP 2048 test 2 success");
    }

    return 0;
}








unsigned int rsa_test(void)
{

    unsigned int e[128]={0};
    unsigned int d[128];
    unsigned int n[128];
    unsigned int p[128];
    unsigned int q[128];
    unsigned int dp[128];
    unsigned int dq[128];
    unsigned int u[128];
    unsigned int in[128];
    unsigned int out[128];
    unsigned int out2[128];
    unsigned int eBitLen=17;
    unsigned int nBitLen=1024;
    unsigned int eWordLen=(eBitLen+0x1F)>>5;
    unsigned int nWordLen=(nBitLen+0x1F)>>5;
//  unsigned int pWordLen=(nBitLen/2+0x1F)>>5;
    unsigned int ret;
    unsigned int i;


#if 0
/**/    for(nBitLen=1024; nBitLen<=4096; nBitLen+=1024)//for(nBitLen=1024; nBitLen<=2048; nBitLen+=2)
    {
        ret = RSA_GetKey(e, d, n, eBitLen, nBitLen);
        if(ret)
        {
            xil_printf("\r\n RSA_GetKey failure, ret = %d", ret);
            return 1;
        }
        xil_printf("\r\n RSA_GetKey nBitLen = %d", nBitLen);fflush(stdout);
    }

    for(nBitLen=1024; nBitLen<=4096; nBitLen+=1024)
    {
        ret =RSA_GetCRTKey(e, p, q, dp, dq, u, n, eBitLen, nBitLen);
        if(ret)
        {
            xil_printf("\r\n RSA_GetCRTKey failure, ret = %d", ret);
            return 1;
        }
        xil_printf("\r\n RSA_GetCRTKey nBitLen = %d", nBitLen);
    }
#endif


#if 1
    //RSA NON-CRT
    eBitLen=17;
    nBitLen=1024;//2048;//4096;//
    eWordLen=(eBitLen+0x1F)>>5;
    nWordLen=(nBitLen+0x1F)>>5;
//  pWordLen=(nBitLen/2+0x1F)>>5;
    for(i=0;i<10;i++)
    {
        ret = RSA_GetKey(e, d, n, eBitLen, nBitLen);
        if(ret)
        {
            printf("\r\n RSA_GetKey failure, ret = %d", ret);
            return 1;
        }
#if 1
        //test encrypt & decrypt
        uint32_set(in, 0x1, nWordLen);
//xil_printf("\r\n begin     "); fflush(stdout);
//for(int j=0;j<8;j++){
        ret = RSA_ModExp(in, d, n, out, get_valid_bits(d, nWordLen), nBitLen);
//}xil_printf("\r\n end     ");fflush(stdout);
        if(ret)
        {
            printf("\r\n RSA_ModExp error, ret = %d", ret);
            return 1;
        }

        ret = RSA_ModExp(out, e, n, out2, eBitLen, nBitLen);
        if(ret)
        {
            printf("\r\n RSA_ModExp error, ret = %d", ret);
            return 1;
        }

        if(uint32_BigNumCmp(out2, nWordLen, in, nWordLen))
        {
            printf("\r\n RSA encrypt & decrypt error");
            print_BN_buf_U32(in, nWordLen, "in");
            print_BN_buf_U32(out, nWordLen, "out");
            print_BN_buf_U32(out2, nWordLen, "out2");
            print_BN_buf_U32(e, eWordLen, "e");
            print_BN_buf_U32(d, nWordLen, "d");
            print_BN_buf_U32(n, nWordLen, "n");
            return 1;
        }
        else
        {
            printf("\r\n RSA encrypt & decrypt success");
        }

        //corner case: 0^0 mod n
        uint32_clear(in, nWordLen);
        ret = RSA_ModExp(in, in, n, out, 0, nBitLen);
        if(RSA_SUCCESS == ret)
        {
            printf("\r\n RSA_ModExp corner test 1 error, ret = %d", ret);
            return 1;
        }

        //corner case: base is n
        ret = RSA_ModExp(n, e, n, out, eBitLen, nBitLen);
        if(RSA_SUCCESS == ret)
        {
            printf("\r\n RSA_ModExp corner test 2 error, ret = %d", ret);
            return 1;
        }

#endif
        //if((i+1)%5 == 0)
            printf("\r\n %d", i+1);
    }
#endif



#if 1
    //RSA CRT
    eBitLen=17;
    nBitLen=2048;//4096;//1024;//
    eWordLen=(eBitLen+0x1F)>>5;
    nWordLen=(nBitLen+0x1F)>>5;
//  pWordLen=(nBitLen/2+0x1F)>>5;
    for(i=0;i<10;i++)
    {
        ret = RSA_GetCRTKey(e, p, q, dp, dq, u, n, eBitLen, nBitLen);
        if(ret)
        {
            printf("\r\n RSA_GetCRTKey failure, ret = %d", ret);
            return 1;
        }
#if 0
        //test encrypt & decrypt
        uint32_set(in, 0x1, nWordLen);
//xil_printf("\r\n begin     "); fflush(stdout);
//for(int j=0;j<25000;j++){
        ret = RSA_ModExp(in, e, n, out, eBitLen, nBitLen);
//}
//xil_printf("\r\n end     ");fflush(stdout);
        if(ret)
        {
            xil_printf("\r\n RSA_ModExp error, ret = %d", ret);
            return 1;
        }

//xil_printf("\r\n begin     "); fflush(stdout);
//for(int j=0;j<2500;j++){
        ret = RSA_CRTModExp(out, p, q, dp, dq, u, out2, nBitLen);
//}
//xil_printf("\r\n end     ");fflush(stdout);
        if(ret)
        {
            xil_printf("\r\n RSA_CRTModExp error, ret = %d", ret);
            return 1;
        }

        if(uint32_BigNumCmp(out2, nWordLen, in, nWordLen))
        {
            xil_printf("\r\n RSA CRT encrypt & decrypt error");
            print_BN_buf_U32(in, nWordLen, "in");
            print_BN_buf_U32(out, nWordLen, "out");
            print_BN_buf_U32(out2, nWordLen, "out2");
            print_BN_buf_U32(e, eWordLen, "e");
            print_BN_buf_U32(p, nWordLen, "p");
            print_BN_buf_U32(q, nWordLen, "q");
            print_BN_buf_U32(dp, nWordLen, "dp");
            print_BN_buf_U32(dq, nWordLen, "dq");
            print_BN_buf_U32(u, nWordLen, "u");
            print_BN_buf_U32(n, nWordLen, "n");
            return 1;
        }
        else
        {
            xil_printf("\r\n RSA CRT encrypt & decrypt success");
        }

        //corner case: base is 0
        uint32_clear(in, nWordLen);
        ret = RSA_CRTModExp(in, p, q, dp, dq, u, out, nBitLen);
        if(RSA_SUCCESS != ret || (1 != uint32_BigNum_Check_Zero(out, nWordLen)))
        {
            xil_printf("\r\n RSA_CRTModExp corner test 1 error, ret = %d", ret);
            return 1;
        }

        //corner case: base is 1
        uint32_clear(in, nWordLen);
        in[0]=1;
        ret = RSA_CRTModExp(in, p, q, dp, dq, u, out, nBitLen);
        if(RSA_SUCCESS != ret || (0 != uint32_BigNumCmp(out, nWordLen, in, nWordLen)))
        {
            xil_printf("\r\n RSA_CRTModExp corner test 2 error, ret = %d", ret);
            print_BN_buf_U32(out, (nBitLen+0x1F)>>5, "n");
            return 1;
        }

        //corner case: base is 2
        uint32_clear(in, nWordLen);
        in[0]=2;
        ret = RSA_CRTModExp(in, p, q, dp, dq, u, out, nBitLen);
        ret |= RSA_ModExp(out, e, n, out2, eBitLen, nBitLen);
        if(RSA_SUCCESS != ret || (0 != uint32_BigNumCmp(out2, nWordLen, in, nWordLen)))
        {
            xil_printf("\r\n RSA_CRTModExp corner test 3 error, ret = %d", ret);
            return 1;
        }

        //corner case: base is n-2
        uint32_copy(in, n, nWordLen);
        in[0]-=2;
        ret = RSA_CRTModExp(in, p, q, dp, dq, u, out, nBitLen);
        ret |= RSA_ModExp(out, e, n, out2, eBitLen, nBitLen);
        if(RSA_SUCCESS != ret || (0 != uint32_BigNumCmp(out2, nWordLen, in, nWordLen)))
        {
            xil_printf("\r\n RSA_CRTModExp corner test 4 error, ret = %d", ret);
            return 1;
        }

        //corner case: base is n-1
        uint32_copy(in, n, nWordLen);
        in[0]-=1;
        ret = RSA_CRTModExp(in, p, q, dp, dq, u, out, nBitLen);
        if(RSA_SUCCESS != ret || (0 != uint32_BigNumCmp(out, nWordLen, in, nWordLen)))
        {
            xil_printf("\r\n RSA_CRTModExp corner test 5 error, ret = %d", ret);
            return 1;
        }

        //corner case: base is n
        ret = RSA_CRTModExp(n, p, q, dp, dq, u, out, nBitLen);
        if(RSA_SUCCESS == ret)
        {
            xil_printf("\r\n RSA_CRTModExp corner test 6 error, ret = %d", ret);
            return 1;
        }
#endif
        //if((i+1)%5 == 0)
            printf("\r\n %d", i+1);fflush(stdout);
    }
#endif

    return 0;
}


unsigned char RSA_all_test(void)
{
    if(rsa_modexp_1024_test())
        return 1;

    if(rsa_modexp_2048_test())
        return 1;

    if(rsa_test())
        return 1;

    return 0;
}
#endif



