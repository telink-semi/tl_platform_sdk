/*
 * @FilePath: \epm_driver\third_party\usb_driver\class\audio\usbd_audio.h
 * @Version: V1.0.0
 * @Date: 2025-05-23 12:11:44
 * @Author: driver group
 * @Description: Header for usbd_audio.c file.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USBD_AUDIO_H__
#define __USBD_AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/**************************** include header *********************************/
#include "usbd_core.h"
#include "usb_audio.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/

/**************************** type definition ********************************/
typedef struct {
    uint8_t bDescriptorSubtype;
    uint8_t bEntityId;
    uint8_t ep;
} audio_entity_info_t;

typedef struct {
    void (*set_cur_volume)(uint8_t ep, uint8_t ch, uint32_t volume);
    uint32_t (*get_cur_volume)(uint8_t ep, uint8_t ch);
    uint32_t (*get_min_volume)(uint8_t ep, uint8_t ch);
    uint32_t (*get_max_volume)(uint8_t ep, uint8_t ch);
    uint32_t (*get_res_volume)(uint8_t ep, uint8_t ch);
    void (*set_mute)(uint8_t ep, uint8_t ch, uint8_t mute);
    uint8_t (*get_mute)(uint8_t ep, uint8_t ch);
    void (*set_sample_rate)(uint8_t ep, uint32_t sample_rate);
    uint32_t (*get_sample_rate)(uint8_t ep);
    void (*get_sample_rate_table)(uint8_t ep, uint8_t **sample_rate_table);
} usbd_audio_cb_t;

typedef struct {
    audio_entity_info_t *table;
    const usbd_audio_cb_t *cb;
    uint16_t uac_ver;
    uint8_t table_num;
    usbd_intf_cb_t intf_cb;
} usbd_audio_class_t;

typedef struct {
    uint8_t hp_mute;
    uint8_t hp_alt;
    int32_t hp_vol_cur;
    int32_t hp_vol_max;
    int32_t hp_vol_min;
    int32_t hp_vol_res;
    uint32_t hp_freq;
    uint8_t hp_datawidth;

    uint8_t mic_mute;
    uint8_t mic_alt;
    int32_t mic_vol_cur;
    int32_t mic_vol_max;
    int32_t mic_vol_min;
    int32_t mic_vol_res;
    uint32_t mic_freq;
    uint8_t mic_datawidth;
    uint8_t mic_channel;

    uint8_t ctrl_alt;
    uint8_t hid_alt;
} usbd_audio_control_t;

typedef struct {
    volatile uint32_t alt_setting;
    usbd_audio_control_t control;
    uint32_t hid_vendor_out_buffer[16];
    uint32_t hid_vendor_in_buffer[16];
    uint8_t hid_vendor_idle_timer;
} usbd_audio_handle_t;

/**************************** variable declear *******************************/

/**************************** function declear *******************************/
/**
 * @brief  usb audio callback register
 * @param  cb \ref usbd_audio_class_callback_t
 * @retval None
 */
extern void usbd_audio_cb_register(uint16_t uac_ver, audio_entity_info_t *table, uint8_t table_num, usbd_audio_cb_t *cb);
/**
 * @brief  usb audio callback unregister
 * @param  intf_index: interface index
 * @retval None
 */
extern void usbd_audio_cb_unregister(uint8_t intf_index);
/**
 * @brief  get usb audio class interface callback
 * @param  None
 * @retval None
 */
extern usbd_intf_cb_t *usbd_audio_get_inf_cb(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* USBD_AUDIO_H */
