/********************************************************************************************************
 * @file    hal_rf_tahdt.h
 *
 * @brief   This is the header file for tl752x
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

#ifndef __HAL_RF_TAHDT_H__
#define __HAL_RF_TAHDT_H__

#include "hal/hal_systimer.h"

#define TAHDT_US_TO_TICK(value)    ((value) * 16)
#define TAHDT_TICK_TO_US(value)    ((value) / 16)

#ifndef clock_time
#define clock_time drv_systimer_get_tick
#endif

typedef enum{
    HAL_TAHDT_FRAME_TYPE_1    = 0x00, //Radio frame type 1.
    HAL_TAHDT_FRAME_TYPE_2    = 0x01, //Radio frame type 2.
    HAL_TAHDT_FRAME_TYPE_3    = 0x02,
    HAL_TAHDT_FRAME_TYPE_4    = 0x03,
    HAL_TAHDT_FRAME_TYPE_3_M0 = 0x02, //Radio frame type 3 and m sequence 0.
    HAL_TAHDT_FRAME_TYPE_3_M1 = 0x03, //Radio frame type 3 and m sequence 1.
    HAL_TAHDT_FRAME_TYPE_3_M2 = 0x04, //Radio frame type 3 and m sequence 2.
    HAL_TAHDT_FRAME_TYPE_3_M3 = 0x05, //Radio frame type 3 and m sequence 3.
    HAL_TAHDT_FRAME_TYPE_3_M4 = 0x06, //Radio frame type 3 and m sequence 4.
    HAL_TAHDT_FRAME_TYPE_3_M5 = 0x07, //Radio frame type 3 and m sequence 5.
    HAL_TAHDT_FRAME_TYPE_4_M0 = 0x08, //Radio frame type 4 and m sequence 0.
    HAL_TAHDT_FRAME_TYPE_4_M1 = 0x09, //Radio frame type 4 and m sequence 1.
    HAL_TAHDT_FRAME_TYPE_4_M2 = 0x0A, //Radio frame type 4 and m sequence 2.
    HAL_TAHDT_FRAME_TYPE_4_M3 = 0x0B, //Radio frame type 4 and m sequence 3.
    HAL_TAHDT_FRAME_TYPE_4_M4 = 0x0C, //Radio frame type 4 and m sequence 4.
    HAL_TAHDT_FRAME_TYPE_4_M5 = 0x0D, //Radio frame type 4 and m sequence 5.
}HAL_TAHDT_FRAME_TYPE_ENUM;

typedef enum {
    HAL_TAHDT_PHY_TYPE_1M = 0,
    HAL_TAHDT_PHY_TYPE_2M = 1,
    HAL_TAHDT_PHY_TYPE_4M = 2,
}HAL_TAHDT_PHY_TYPE_ENUM;

typedef enum{
    HAL_TAHDT_PILOT_TYPE_4_TO_1  = 0, //The pilot density is 4:1.
    HAL_TAHDT_PILOT_TYPE_8_TO_1  = 1, //The pilot density is 8:1.
    HAL_TAHDT_PILOT_TYPE_16_TO_1 = 2, //The pilot density is 16:1.
    HAL_TAHDT_PILOT_TYPE_NONE    = 3, //No pilot density
}HAL_TAHDT_PILOT_TYPE_ENUM;

typedef enum {
    HAL_TAHDT_MCS_TYPE_BPSK_2D8 = 0,
    HAL_TAHDT_MCS_TYPE_BPSK_3D8 = 1,
    HAL_TAHDT_MCS_TYPE_QPSK_2D8 = 2,
    HAL_TAHDT_MCS_TYPE_QPSK_3D8 = 3,
    HAL_TAHDT_MCS_TYPE_QPSK_4D8 = 4,
    HAL_TAHDT_MCS_TYPE_QPSK_5D8 = 5,
    HAL_TAHDT_MCS_TYPE_QPSK_6D8 = 6,
    HAL_TAHDT_MCS_TYPE_QPSK_7D8 = 7,
    HAL_TAHDT_MCS_TYPE_QPSK_8D8 = 8,
    HAL_TAHDT_MCS_TYPE_8PSK_5D8 = 9,
    HAL_TAHDT_MCS_TYPE_8PSK_6D8 = 10,
    HAL_TAHDT_MCS_TYPE_8PSK_7D8 = 11,
    HAL_TAHDT_MCS_TYPE_8PSK_8D8 = 12,
}HAL_TAHDT_MCS_TYPE_ENUM;

typedef enum {
    HAL_TAHDT_SEQ_TYPE_M0 = 0,
    HAL_TAHDT_SEQ_TYPE_M1 = 1,
    HAL_TAHDT_SEQ_TYPE_M2 = 2,
    HAL_TAHDT_SEQ_TYPE_M3 = 3,
    HAL_TAHDT_SEQ_TYPE_M4 = 4,
    HAL_TAHDT_SEQ_TYPE_M5 = 5,
}HAL_TAHDT_SEQ_TYPE_ENUM;

typedef enum {
    HAL_TAHDT_CRC_TYPE_24BIT = 0,
    HAL_TAHDT_CRC_TYPE_32BIT = 1,
    HAL_TAHDT_CRC_TYPE_NONE  = 0xFF,
}HAL_TAHDT_CRC_TYPE_ENUM;

typedef enum{
    HAL_TAHDT_CTRL_TYPE_A1 = 0x01,
    HAL_TAHDT_CTRL_TYPE_A2 = 0x02,
    HAL_TAHDT_CTRL_TYPE_A3 = 0x03,
    HAL_TAHDT_CTRL_TYPE_A4 = 0x04,
    HAL_TAHDT_CTRL_TYPE_A5 = 0x05,
    HAL_TAHDT_CTRL_TYPE_A6 = 0x06,
    HAL_TAHDT_CTRL_TYPE_A7 = 0x07,
    HAL_TAHDT_CTRL_TYPE_B1 = 0x11,
    HAL_TAHDT_CTRL_TYPE_B2 = 0x12,
    HAL_TAHDT_CTRL_TYPE_B3 = 0x13,
    HAL_TAHDT_CTRL_TYPE_B4 = 0x14,
    HAL_TAHDT_CTRL_TYPE_B5 = 0x15,
}HAL_TAHDT_CTRL_TYPE_ENUM;

#define HAL_RF_TAHDT_SETTLE_MIN_TIME      47

#define HAL_RF_TAHDT_RX_RF_INFO_LEN       15 //DmaLen(4)+RxSyncTimestamp(4Bytes)+RxDoneTimestamp(4Bytes)+Error(1Bytes)+Gain(1Bytes)+RSSI(1Bytes)
#define HAL_RF_TAHDT_TX_RF_INFO_LEN       4  //DmaLen(4)

//#define HAL_TAHDT_FRAME_TYPE_3      0x02 //Radio frame type 3.
//#define HAL_TAHDT_FRAME_TYPE_4      0x03 //Radio frame type 4.

#define HAL_TAHDT_F1A1_HEAD_LEN                       3 //3Bytes
#define HAL_TAHDT_F2A1_HEAD_LEN                       4 //4Bytes
#define HAL_TAHDT_F1A2_HEAD_LEN                       3
#define HAL_TAHDT_F2A2_HEAD_LEN                       4

typedef struct{
    /*base config*/
    unsigned char frame_type;
    unsigned char phy_type;
    unsigned char pilot_type;

    /*sync word*/
    unsigned char is_sync_man;
    unsigned int syncword_l;
    unsigned int syncword_h;
    unsigned int LLID;
    unsigned char mseq_type;

    /*crc*/
    unsigned char crc_type;
    unsigned int crc_seed;
    unsigned int seg_crc_seed;
} tahdt_mode_st;

typedef struct{
    HAL_TAHDT_FRAME_TYPE_ENUM frame_type;
    HAL_TAHDT_CTRL_TYPE_ENUM ctrl_type;
    HAL_TAHDT_MCS_TYPE_ENUM mcs_type;
    
    /*whiten*/
    unsigned char is_whiten;
    unsigned char whiten_seed;

    /*rf channel*/
    unsigned char rf_channel;

    /*rf rx and tx wait time in us*/
    unsigned short tx_wait;
    unsigned short rx_wait;

    /*sync timeout in us*/
    unsigned int first_sync_timeout;
    unsigned int sync_timeout;

    /*schedule time*/
    unsigned int schedule_time;

    unsigned char buffer[512];
    unsigned short buffer_len;
    unsigned short pdu_len;
} tahdt_frame_st;

typedef struct{
    unsigned char mcs;
    union{
        unsigned int raw;
        struct{
            unsigned int adv_type:3;
            unsigned int packet_type:3;
            unsigned int res1:6;
            unsigned int len:8;
            unsigned int res2:12;
        };
    };
} tahdt_ctrl_a1_st;

typedef struct{
    unsigned char mcs;
    union{
        unsigned int raw;
        struct{
            unsigned int packet_type:2;
            unsigned int is_empty:1;
            unsigned int sn:1;
            unsigned int nesn:1;
            unsigned int flow_ctrl:1;
            unsigned int is_mf:1;
            unsigned int res1:2;
            unsigned int len:11;
            unsigned int res2:12;
        };
    };
} tahdt_ctrl_a2_st;

typedef struct{
    unsigned char mcs;
    union{
        unsigned int raw;
        struct{
            unsigned int packet_type:2;
            unsigned int is_empty:1;
            unsigned int sn:5;
            unsigned int nesn:5;
            unsigned int flow_ctrl:1;
            unsigned int acl_sch:1;
            unsigned int res1:2;
            unsigned int len:11;
            unsigned int res2:4;
        };
    };
} tahdt_ctrl_a3_st;

typedef struct{
    unsigned char mcs;
    union{
        unsigned int raw;
        struct{
            unsigned int packet_type:2;
            unsigned int is_empty:1;
            unsigned int sn:1;
            unsigned int nesn:8;
            unsigned int flow_ctrl:1;
            unsigned int acl_sch:1;
            unsigned int res1:3;
            unsigned int len:11;
            unsigned int res2:4;
        };
    };
} tahdt_ctrl_a4_st;

typedef struct{
    unsigned char mcs;
    union{
        unsigned int raw;
        struct{
            unsigned int packet_type:2;
            unsigned int is_empty:1;
            unsigned int sn:1;
            unsigned int nesn:1;
            unsigned int flow_ctrl:1;
            unsigned int acl_sch:1;
            unsigned int res1:2;
            unsigned int len:11;
            unsigned int res2:12;
        };
    };
} tahdt_ctrl_a5_st;

typedef struct{
    unsigned char mcs;
    union{
        unsigned int raw;
        struct{
            unsigned int packet_type:2;
            unsigned int packet_sn:5;
            unsigned int packet_group:3;
            unsigned int end:1;
            unsigned int is_mf:1;
            unsigned int res1:5;
            unsigned int len:11;
            unsigned int res2:4;
        };
    };
} tahdt_ctrl_a6_st;

typedef struct{
    unsigned char mcs;
    union{
        unsigned int raw;
        struct{
            unsigned int packet_sn:5;
            unsigned int packet_group:3;
            unsigned int res1:9;
            unsigned int len:11;
            unsigned int res2:4;
        };
    };
} tahdt_ctrl_a7_st;

typedef struct{
    union{
        unsigned int raw;
        struct{
            unsigned int frame_ind:1;
            unsigned int harq:8;
            unsigned int packet_sn:1;
            unsigned int mcs:4;
            unsigned int len:11;
            unsigned int flow_ctrl:1;
            unsigned int uplink_signal:1;
            unsigned int res1:5;
        };
    };
} tahdt_ctrl_b1_st;

typedef struct{
    union{
        unsigned int raw;
        struct{
            unsigned int harq:25;
            unsigned int flow_ctrl:1;
            unsigned int uplink_signal:1;
            unsigned int res1:5;
        };
    };
} tahdt_ctrl_b2_st;

typedef struct{
    union{
        unsigned int raw;
        struct{
            unsigned int packet_group:5;
            unsigned int packet_sn:5;
            unsigned int mcs:4;
            unsigned int len:11;
            unsigned int flow_ctrl:1;
            unsigned int max_packet_sn:1;
            unsigned int res1:5;
        };
    };
} tahdt_ctrl_b3_st;

typedef struct{
    union{
        unsigned int raw;
        struct{
            unsigned int adv_set:5;
            unsigned int adv_set_update:1;
            unsigned int packet_sn:4;
            unsigned int mcs:4;
            unsigned int len:11;
            unsigned int flow_ctrl:1;
            unsigned int max_packet_sn:1;
            unsigned int res1:5;
        };
    };
} tahdt_ctrl_b4_st;

typedef struct{
    union{
        unsigned int raw;
        struct{
            unsigned int res1:7;
            unsigned int msg_type:3;
            unsigned int is_connect:1;
            unsigned int is_query:1;
            unsigned int is_direct:1;
            unsigned int is_undirect:1;
            unsigned int data_update:1;
            unsigned int mcs:4;
            unsigned int len:8;
            unsigned int res2:5;
        };
    };
} tahdt_ctrl_b5_st;

typedef struct{
    union{
        tahdt_ctrl_a1_st a1;
        tahdt_ctrl_a2_st a2;
        tahdt_ctrl_a3_st a3;
        tahdt_ctrl_a4_st a4;
        tahdt_ctrl_a5_st a5;
        tahdt_ctrl_a6_st a6;
        tahdt_ctrl_a7_st a7;
        tahdt_ctrl_b1_st b1;
        tahdt_ctrl_b2_st b2;
        tahdt_ctrl_b3_st b3;
        tahdt_ctrl_b4_st b4;
        tahdt_ctrl_b5_st b5;
    };
    unsigned short pdu_len;
    unsigned char *pdu;
} tahdt_packet_st;

void tahdt_set_mode(tahdt_mode_st *config);
int tahdt_send_frame(tahdt_frame_st *frame);
int tahdt_recv_frame(tahdt_frame_st *frame);
int tahdt_send_and_recv_frame(tahdt_frame_st *frame);
int tahdt_recv_and_send_frame(tahdt_frame_st *frame);

int tahdt_build_packet(tahdt_frame_st *frame, tahdt_packet_st *packet);

void tahdt_tx_cplt_cb(void);
void tahdt_rx_cplt_cb(unsigned char *data, unsigned int data_len);
void tahdt_error_cb(unsigned short irq, unsigned error_code);
void tahdt_timeout_cb(unsigned short irq);
void tahdt_irq_handler(void);

void rf_set_pa_power(unsigned char level);

/**
 * @brief       This function serves to set the which irq enable.
 * @param[in]   mask    - Options that need to be enabled.
 * @return      Yes: 1, NO: 0.
 */
static inline void rf_set_spl_irq_mask(rf_tahdt_irq_e mask)
{
    BM_SET(reg_tahdt_ll_irq_mask, mask);
}

/**
 * @brief       This function serves to clear the TX/RX irq mask.
 * @param[in]   mask    - RX/TX irq value.
 * @return      none.
 */
static inline void rf_clr_spl_irq_mask(rf_tahdt_irq_e mask)
{
    BM_CLR(reg_tahdt_ll_irq_mask, mask);
}

/**
 *  @brief      This function serves to judge whether it is in a certain state.
 *  @param[in]  mask      - RX/TX irq status.
 * @retval      non-zero      -  the interrupt occurred.
 * @retval      zero  -  the interrupt did not occur.
 */
static inline unsigned int rf_get_spl_irq_status(rf_tahdt_irq_e status)
{
    return ((unsigned int)(BM_IS_SET(reg_tahdt_ll_irq_status, status)));
}

/**
 *@brief    This function serves to clear the Tx/Rx finish flag bit.
 *          After all packet data are sent, corresponding Tx finish flag bit
 *          will be set as 1.By reading this flag bit, it can check whether
 *          packet transmission is finished. After the check, it is needed to
 *          manually clear this flag bit so as to avoid misjudgment.
 *@return   none.
 */
static inline void rf_clr_spl_irq_status(rf_tahdt_irq_e status)
{
    reg_tahdt_ll_irq_status    = status;
}

#endif /*HAL_RF_TAHDT_H_*/
