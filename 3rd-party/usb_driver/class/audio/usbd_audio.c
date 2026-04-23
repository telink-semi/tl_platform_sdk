/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * This driver is based on the 1.4.1 version of class/audio/usbd_audio.c
 * but has been rewritten to be easier to read and use.
 */

/**************************** include header *********************************/
#include "usbd_audio.h"

#if USB_CFG_USE_USB

#if defined(USB_CFG_USE_OTG_MODE) || defined(USB_CFG_USE_DEVICE_MODE)

/*************************** macro definition ********************************/

/**************************** type definition ********************************/

/**************************** function declear *******************************/
static usb_status_t usbd_audio_class_intf_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len);
static usb_status_t usbd_audio_class_ep_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len);

/************************* variable definition *******************************/
static usbd_audio_class_t usbd_audio_handle = {
    .table = NULL,
    .cb = NULL,
    .uac_ver = 0,
    .table_num = 0,
    .intf_cb = {
        usbd_audio_class_intf_req_handler,
        usbd_audio_class_ep_req_handler,
        NULL,
    },
};

/********************** function implementation ******************************/
/**
 * @brief  usbd_audio_class_intf_req_handler
 *         Handles the Audio control request parsing.
 * @param  req: usb requests
 * @param  data: data
 * @param  len: data Length
 * @retval status
 */
static usb_status_t usbd_audio_class_intf_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    uint8_t entity_id = 0;
    uint8_t endpoint = 0;
    uint8_t subtype = 0x01;
    uint8_t ctl_selector = 0;
    uint8_t ch = 0;
    uint8_t mute = 0;
    uint16_t volume_16bit = 0;
    uint32_t volume_32bit = 0;
    uint32_t sample_rate = 0;

    entity_id = USB_HIBYTE(req->wIndex);
    ctl_selector = USB_HIBYTE(req->wValue);
    ch = USB_LOBYTE(req->wValue);

    for (uint8_t i = 0; i < usbd_audio_handle.table_num; i++) {
        if (usbd_audio_handle.table[i].bEntityId == entity_id) {
            subtype = usbd_audio_handle.table[i].bDescriptorSubtype;
            endpoint = usbd_audio_handle.table[i].ep;
            break;
        }
    }

    if (subtype == 0x01) {
        USB_LOG_ERR("Do not find subtype for 0x%02x\r\n", entity_id);
        return USB_ERROR;
    }

    switch (subtype) {
    case AUDIO_CONTROL_INPUT_TERMINAL:
    case AUDIO_CONTROL_OUTPUT_TERMINAL:
        if (req->bmRequestType & USB_REQ_DIR_MASK) {
            if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_cur_volume) {
                volume_32bit = usbd_audio_handle.cb->get_cur_volume(endpoint, ch);
            }
            memcpy(*data, &volume_32bit, 4);
            (*data)[4] = 0;
            (*data)[5] = 0;
            *len = 6;
        } else {
            memcpy(&volume_32bit, *data, *len);
            if (usbd_audio_handle.cb && usbd_audio_handle.cb->set_cur_volume) {
                usbd_audio_handle.cb->set_cur_volume(endpoint, ch, volume_32bit);
            }
        }
        break;

    case AUDIO_CONTROL_MIXER_UNIT:
        switch (req->bRequest) {
        case AUDIO_REQUEST_CUR:
            if (req->bmRequestType & USB_REQ_DIR_MASK) {
                if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_mute) {
                    (*data)[0] = usbd_audio_handle.cb->get_mute(endpoint, ch);
                    (*data)[1] = 0;
                }
                *len = 2;
            } else {
                mute = (*data)[0];
                if (usbd_audio_handle.cb && usbd_audio_handle.cb->set_mute) {
                    usbd_audio_handle.cb->set_mute(endpoint, ch, mute);
                }
            }
            break;

        default:
            USB_LOG_ERR("Audio Class bRequest error: 0x%02x in cs 0x%02x\r\n", req->bRequest, ctl_selector);
            return USB_ERROR;
        }
        break;

    case AUDIO_CONTROL_FEATURE_UNIT:
        switch (ctl_selector) {
        case AUDIO_FU_CONTROL_MUTE:
            if (usbd_audio_handle.uac_ver < 0x0200) {
                switch (req->bRequest) {
                case AUDIO_REQUEST_SET_CUR:
                    mute = (*data)[0];
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->set_mute) {
                        usbd_audio_handle.cb->set_mute(endpoint, ch, mute);
                    }
                    break;

                case AUDIO_REQUEST_GET_CUR:
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_mute) {
                        (*data)[0] = usbd_audio_handle.cb->get_mute(endpoint, ch);
                    }
                    *len = 1;
                    break;

                default:
                    USB_LOG_ERR("Audio Class bRequest error: 0x%02x in cs 0x%02x\r\n", req->bRequest, ctl_selector);
                    return USB_ERROR;
                }
            } else {
                switch (req->bRequest) {
                case AUDIO_REQUEST_CUR:
                    if (req->bmRequestType & USB_REQ_DIR_MASK) {
                        if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_mute) {
                            (*data)[0] = usbd_audio_handle.cb->get_mute(endpoint, ch);
                        }
                        *len = 1;
                    } else {
                        mute = (*data)[0];
                        if (usbd_audio_handle.cb && usbd_audio_handle.cb->set_mute) {
                            usbd_audio_handle.cb->set_mute(endpoint, ch, mute);
                        }
                    }
                    break;

                default:
                    USB_LOG_ERR("Audio Class bRequest error: 0x%02x in cs 0x%02x\r\n", req->bRequest, ctl_selector);
                    return USB_ERROR;
                }
            }
            break;

        case AUDIO_FU_CONTROL_VOLUME:
            if (usbd_audio_handle.uac_ver < 0x0200) {
                switch (req->bRequest) {
                case AUDIO_REQUEST_SET_CUR:
                    memcpy(&volume_16bit, *data, *len);
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->set_cur_volume) {
                        usbd_audio_handle.cb->set_cur_volume(endpoint, ch, (uint32_t)volume_16bit);
                    }
                    break;

                case AUDIO_REQUEST_GET_CUR:
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_cur_volume) {
                        volume_32bit = usbd_audio_handle.cb->get_cur_volume(endpoint, ch);
                    }
                    volume_16bit = (uint16_t)volume_32bit;
                    memcpy(*data, &volume_16bit, 2);
                    *len = 2;
                    break;

                case AUDIO_REQUEST_GET_MIN:
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_min_volume) {
                        volume_32bit = usbd_audio_handle.cb->get_min_volume(endpoint, ch);
                    }
                    volume_16bit = (uint16_t)volume_32bit;
                    memcpy(*data, &volume_16bit, 2);
                    *len = 2;
                    break;

                case AUDIO_REQUEST_GET_MAX:
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_max_volume) {
                        volume_32bit = usbd_audio_handle.cb->get_max_volume(endpoint, ch);
                    }
                    volume_16bit = (uint16_t)volume_32bit;
                    memcpy(*data, &volume_16bit, 2);
                    *len = 2;
                    break;

                case AUDIO_REQUEST_GET_RES:
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_res_volume) {
                        volume_32bit = usbd_audio_handle.cb->get_res_volume(endpoint, ch);
                    }
                    volume_16bit = (uint16_t)volume_32bit;
                    memcpy(*data, &volume_16bit, 2);
                    *len = 2;
                    break;

                default:
                    USB_LOG_ERR("Audio Class bRequest error: 0x%02x in cs 0x%02x\r\n", req->bRequest, ctl_selector);
                    return USB_ERROR;
                }
            } else {
                switch (req->bRequest) {
                case AUDIO_REQUEST_CUR:
                    if (req->bmRequestType & USB_REQ_DIR_MASK) {
                        if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_cur_volume) {
                            volume_32bit = usbd_audio_handle.cb->get_cur_volume(endpoint, ch);
                        }
                        volume_16bit = (uint16_t)volume_32bit;
                        memcpy(*data, &volume_16bit, 2);
                        *len = 2;
                    } else {
                        memcpy(&volume_16bit, *data, *len);
                        if (usbd_audio_handle.cb && usbd_audio_handle.cb->set_cur_volume) {
                            usbd_audio_handle.cb->set_cur_volume(endpoint, ch, volume_16bit);
                        }
                    }
                    break;

                case AUDIO_REQUEST_RANGE:
                    if (req->bmRequestType & USB_REQ_DIR_MASK) {
                        *((uint16_t *)(*data + 0)) = 1;
                        *((uint16_t *)(*data + 2)) = 0;
                        *((uint16_t *)(*data + 4)) = 100;
                        *((uint16_t *)(*data + 6)) = 1;
                        *len = 8;
                    } else {
                    }
                    break;

                default:
                    //USB_LOG_ERR("Unhandled Audio Class bRequest 0x%02x in cs 0x%02x\r\n", req->bRequest, ctl_selector);
                    return USB_ERROR;
                }
            }
            break;

        default:
            USB_LOG_ERR("Audio Class cs error: 0x%02x \r\n", ctl_selector);
            return USB_ERROR;
        }
        break;

    case AUDIO_CONTROL_CLOCK_SOURCE:
        switch (ctl_selector) {
        case AUDIO_CS_CONTROL_SAM_FREQ:
            switch (req->bRequest) {
            case AUDIO_REQUEST_CUR:
                if (req->bmRequestType & USB_REQ_DIR_MASK) {
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_sample_rate) {
                        sample_rate = usbd_audio_handle.cb->get_sample_rate(endpoint);
                    }
                    memcpy(*data, &sample_rate, 4);
                    *len = 4;
                } else {
                    memcpy(&sample_rate, *data, req->wLength);
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->set_sample_rate) {
                        usbd_audio_handle.cb->set_sample_rate(endpoint, sample_rate);
                    }
                }
                break;

            case AUDIO_REQUEST_RANGE:
                if (req->bmRequestType & USB_REQ_DIR_MASK) {
                    uint8_t *sample_rate_table = NULL;
                    uint16_t num = 0;
                    if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_sample_rate_table) {
                        usbd_audio_handle.cb->get_sample_rate_table(endpoint, &sample_rate_table);
                    }
                    num = (uint16_t)((uint16_t)(sample_rate_table[1] << 8) | ((uint16_t)sample_rate_table[0]));
                    memcpy(*data, sample_rate_table, (12 * num + 2));
                    *len = (12 * num + 2);
                } else {
                }
                break;

            default:
                return USB_ERROR;
            }
            break;

        case AUDIO_CS_CONTROL_CLOCK_VALID:
            if (req->bmRequestType & USB_REQ_DIR_MASK) {
                (*data)[0] = 1;
                *len = 1;
            } else {
                return USB_ERROR;
            }
            break;

        default:
            return USB_ERROR;
        }
        break;
    }
    return USB_OK;
}

static usb_status_t usbd_audio_class_ep_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    uint8_t ctl_selector = 0;
    uint32_t sample_rate = 0;
    uint8_t endpoint = 0;

    ctl_selector = USB_HIBYTE(req->wValue);
    endpoint = USB_LOBYTE(req->wIndex);

    switch (ctl_selector) {
    case AUDIO_EP_CONTROL_SAMPLING_FEQ:
        switch (req->bRequest) {
        case AUDIO_REQUEST_GET_CUR:
        case AUDIO_REQUEST_GET_MIN:
        case AUDIO_REQUEST_GET_MAX:
        case AUDIO_REQUEST_GET_RES:
            if (usbd_audio_handle.cb && usbd_audio_handle.cb->get_sample_rate) {
                sample_rate = usbd_audio_handle.cb->get_sample_rate(endpoint);
            }
            memcpy(*data, &sample_rate, 3);
            *len = 3;
            break;

        case AUDIO_REQUEST_SET_CUR:
            memcpy((uint8_t *)&sample_rate, *data, *len);
            if (usbd_audio_handle.cb && usbd_audio_handle.cb->set_sample_rate) {
                usbd_audio_handle.cb->set_sample_rate(endpoint, sample_rate);
            }
            break;
        }
        break;

    default:
        USB_LOG_ERR("Audio Class control selector error: 0x%02x\r\n", ctl_selector);
        return USB_ERROR;
    }
    return USB_OK;
}

/**
 * @brief  usb audio callback register
 * @param  cb \ref usbd_audio_class_callback_t
 * @retval None
 */
void usbd_audio_cb_register(uint16_t uac_ver, audio_entity_info_t *table, uint8_t table_num, usbd_audio_cb_t *cb)
{
    usbd_audio_handle.uac_ver = uac_ver;
    usbd_audio_handle.table = table;
    usbd_audio_handle.table_num = table_num;
    usbd_audio_handle.cb = cb;
}

/**
 * @brief  usb audio callback unregister
 * @param  intf_index: interface index
 * @retval None
 */
void usbd_audio_cb_unregister(uint8_t intf_index)
{
    (void)intf_index;
    usbd_audio_handle.uac_ver = 0;
    usbd_audio_handle.table = NULL;
    usbd_audio_handle.table_num = 0;
    usbd_audio_handle.cb = NULL;
}

/**
 * @brief  get usb audio class interface callback
 * @param  None
 * @retval None
 */
usbd_intf_cb_t *usbd_audio_get_inf_cb(void)
{
    return &(usbd_audio_handle.intf_cb);
}

#endif
#endif
