/*
 * @FilePath: \epm_driver\third_party\usb_driver\port\usb_regs.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:54
 * @Author: driver group
 * @Description: Header file for usb.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USB_REGS_H__
#define __USB_REGS_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "usb_conf.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/
#define USB_GLOBAL_REGS_BASE       0x000UL
#define USB_DEVICE_REGS_BASE       0x800UL
#define USB_IN_ENDPOINT_REGS_BASE  0x900UL
#define USB_OUT_ENDPOINT_REGS_BASE 0xB00UL
#define USB_EP_REGS_SIZE           0x20UL
#define USB_HOST_REGS_BASE         0x400UL
#define USB_HOST_PORT_REGS_BASE    0x440UL
#define USB_HOST_CHANNEL_REGS_BASE 0x500UL
#define USB_HOST_CHANNEL_REGS_SIZE 0x20UL
#define USB_PCGCCTL_REGS_BASE      0xE00UL
#define USB_FIFO_REGS_BASE         0x1000UL
#define USB_FIFO_REGS_SIZE         0x1000UL

#define USB_MAX_TX_FIFOS 15

/******************************************************************************/
/*                               USB Bit definition                           */
/******************************************************************************/

/********************  Bit definition for USB_GOTGCTL register  ***********/
#define USB_GOTGCTL_SRQSCS_Pos    (0U)
#define USB_GOTGCTL_SRQSCS_Msk    (0x1UL << USB_GOTGCTL_SRQSCS_Pos) /*!< Session request success */
#define USB_GOTGCTL_SRQ_Pos       (1U)
#define USB_GOTGCTL_SRQ_Msk       (0x1UL << USB_GOTGCTL_SRQ_Pos) /*!<  Session request */
#define USB_GOTGCTL_VBVALOEN_Pos  (2U)
#define USB_GOTGCTL_VBVALOEN_Msk  (0x1UL << USB_GOTGCTL_VBVALOEN_Pos) /*!< VBUS valid override enable */
#define USB_GOTGCTL_VBVALOVAL_Pos (3U)
#define USB_GOTGCTL_VBVALOVAL_Msk (0x1UL << USB_GOTGCTL_VBVALOVAL_Pos) /*!< VBUS valid override value */
#define USB_GOTGCTL_AVALOEN_Pos   (4U)
#define USB_GOTGCTL_AVALOEN_Msk   (0x1UL << USB_GOTGCTL_AVALOEN_Pos) /*!< A-peripheral session valid override enable */
#define USB_GOTGCTL_AVALOVAL_Pos  (5U)
#define USB_GOTGCTL_AVALOVAL_Msk  (0x1UL << USB_GOTGCTL_AVALOVAL_Pos) /*!< A-peripheral session valid override value */
#define USB_GOTGCTL_BVALOEN_Pos   (6U)
#define USB_GOTGCTL_BVALOEN_Msk   (0x1UL << USB_GOTGCTL_BVALOEN_Pos) /*!< B-peripheral session valid override enable */
#define USB_GOTGCTL_BVALOVAL_Pos  (7U)
#define USB_GOTGCTL_BVALOVAL_Msk  (0x1UL << USB_GOTGCTL_BVALOVAL_Pos) /*!< B-peripheral session valid override value  */
#define USB_GOTGCTL_HNGSCS_Pos    (8U)
#define USB_GOTGCTL_HNGSCS_Msk    (0x1UL << USB_GOTGCTL_HNGSCS_Pos) /*!< Host set HNP enable */
#define USB_GOTGCTL_HNPRQ_Pos     (9U)
#define USB_GOTGCTL_HNPRQ_Msk     (0x1UL << USB_GOTGCTL_HNPRQ_Pos) /*!< HNP request */
#define USB_GOTGCTL_HSHNPEN_Pos   (10U)
#define USB_GOTGCTL_HSHNPEN_Msk   (0x1UL << USB_GOTGCTL_HSHNPEN_Pos) /*!< Host set HNP enable */
#define USB_GOTGCTL_DHNPEN_Pos    (11U)
#define USB_GOTGCTL_DHNPEN_Msk    (0x1UL << USB_GOTGCTL_DHNPEN_Pos) /*!< Device HNP enabled */
#define USB_GOTGCTL_EHEN_Pos      (12U)
#define USB_GOTGCTL_EHEN_Msk      (0x1UL << USB_GOTGCTL_EHEN_Pos) /*!< Embedded host enable */
#define USB_GOTGCTL_CIDSTS_Pos    (16U)
#define USB_GOTGCTL_CIDSTS_Msk    (0x1UL << USB_GOTGCTL_CIDSTS_Pos) /*!< Connector ID status */
#define USB_GOTGCTL_DBCT_Pos      (17U)
#define USB_GOTGCTL_DBCT_Msk      (0x1UL << USB_GOTGCTL_DBCT_Pos) /*!< Long/short debounce time */
#define USB_GOTGCTL_ASVLD_Pos     (18U)
#define USB_GOTGCTL_ASVLD_Msk     (0x1UL << USB_GOTGCTL_ASVLD_Pos) /*!< A-session valid  */
#define USB_GOTGCTL_BSVLD_Pos     (19U)
#define USB_GOTGCTL_BSVLD_Msk     (0x1UL << USB_GOTGCTL_BSVLD_Pos) /*!< B-session valid */
#define USB_GOTGCTL_OTGVER_Pos    (20U)
#define USB_GOTGCTL_OTGVER_Msk    (0x1UL << USB_GOTGCTL_OTGVER_Pos) /*!< OTG version  */

/********************  Bit definition for USB_HCFG register  ********************/
#define USB_HCFG_FSLSPCS_Pos (0U)
#define USB_HCFG_FSLSPCS_Msk (0x3UL << USB_HCFG_FSLSPCS_Pos) /*!< FS/LS PHY clock select  */
#define USB_HCFG_FSLSPCS_0   (0x1UL << USB_HCFG_FSLSPCS_Pos) /*!< 0x00000001 */
#define USB_HCFG_FSLSPCS_1   (0x2UL << USB_HCFG_FSLSPCS_Pos) /*!< 0x00000002 */
#define USB_HCFG_FSLSS_Pos   (2U)
#define USB_HCFG_FSLSS_Msk   (0x1UL << USB_HCFG_FSLSS_Pos) /*!< FS- and LS-only support */

/********************  Bit definition for USB_DCFG register  ********************/
#define USB_DCFG_DSPD_Pos     (0U)
#define USB_DCFG_DSPD_Msk     (0x3UL << USB_DCFG_DSPD_Pos) /*!< Device speed */
#define USB_DCFG_DSPD_0       (0x1UL << USB_DCFG_DSPD_Pos) /*!< 0x00000001 */
#define USB_DCFG_DSPD_1       (0x2UL << USB_DCFG_DSPD_Pos) /*!< 0x00000002 */
#define USB_DCFG_NZLSOHSK_Pos (2U)
#define USB_DCFG_NZLSOHSK_Msk (0x1UL << USB_DCFG_NZLSOHSK_Pos) /*!< Nonzero-length status OUT handshake */

#define USB_DCFG_DAD_Pos (4U)
#define USB_DCFG_DAD_Msk (0x7FUL << USB_DCFG_DAD_Pos) /*!< Device address */
#define USB_DCFG_DAD_0   (0x01UL << USB_DCFG_DAD_Pos) /*!< 0x00000010 */
#define USB_DCFG_DAD_1   (0x02UL << USB_DCFG_DAD_Pos) /*!< 0x00000020 */
#define USB_DCFG_DAD_2   (0x04UL << USB_DCFG_DAD_Pos) /*!< 0x00000040 */
#define USB_DCFG_DAD_3   (0x08UL << USB_DCFG_DAD_Pos) /*!< 0x00000080 */
#define USB_DCFG_DAD_4   (0x10UL << USB_DCFG_DAD_Pos) /*!< 0x00000100 */
#define USB_DCFG_DAD_5   (0x20UL << USB_DCFG_DAD_Pos) /*!< 0x00000200 */
#define USB_DCFG_DAD_6   (0x40UL << USB_DCFG_DAD_Pos) /*!< 0x00000400 */

#define USB_DCFG_PFIVL_Pos (11U)
#define USB_DCFG_PFIVL_Msk (0x3UL << USB_DCFG_PFIVL_Pos) /*!< Periodic (micro)frame interval */
#define USB_DCFG_PFIVL_0   (0x1UL << USB_DCFG_PFIVL_Pos) /*!< 0x00000800 */
#define USB_DCFG_PFIVL_1   (0x2UL << USB_DCFG_PFIVL_Pos) /*!< 0x00001000 */

#define USB_DCFG_XCVRDLY_Pos (14U)
#define USB_DCFG_XCVRDLY_Msk (0x1UL << USB_DCFG_XCVRDLY_Pos) /*!< Transceiver delay */

#define USB_DCFG_ERRATIM_Pos (15U)
#define USB_DCFG_ERRATIM_Msk (0x1UL << USB_DCFG_ERRATIM_Pos) /*!< Erratic error interrupt mask */

#define USB_DCFG_DESCDMA_Pos (23U)
#define USB_DCFG_DESCDMA_Msk (0x1UL << USB_DCFG_DESCDMA_Pos)

#define USB_DCFG_PERSCHIVL_Pos (24U)
#define USB_DCFG_PERSCHIVL_Msk (0x3UL << USB_DCFG_PERSCHIVL_Pos) /*!< Periodic scheduling interval */
#define USB_DCFG_PERSCHIVL_0   (0x1UL << USB_DCFG_PERSCHIVL_Pos) /*!< 0x01000000 */
#define USB_DCFG_PERSCHIVL_1   (0x2UL << USB_DCFG_PERSCHIVL_Pos) /*!< 0x02000000 */

/********************  Bit definition for USB_PCGCR register  ********************/
#define USB_PCGCR_STPPCLK_Pos  (0U)
#define USB_PCGCR_STPPCLK_Msk  (0x1UL << USB_PCGCR_STPPCLK_Pos) /*!< Stop PHY clock */
#define USB_PCGCR_GATEHCLK_Pos (1U)
#define USB_PCGCR_GATEHCLK_Msk (0x1UL << USB_PCGCR_GATEHCLK_Pos) /*!< Gate HCLK */
#define USB_PCGCR_PHYSUSP_Pos  (4U)
#define USB_PCGCR_PHYSUSP_Msk  (0x1UL << USB_PCGCR_PHYSUSP_Pos) /*!< PHY suspended */

/********************  Bit definition for USB_GOTGINT register  ********************/
#define USB_GOTGINT_SEDET_Pos   (2U)
#define USB_GOTGINT_SEDET_Msk   (0x1UL << USB_GOTGINT_SEDET_Pos) /*!< Session end detected */
#define USB_GOTGINT_SRSSCHG_Pos (8U)
#define USB_GOTGINT_SRSSCHG_Msk (0x1UL << USB_GOTGINT_SRSSCHG_Pos) /*!< Session request success status change  */
#define USB_GOTGINT_HNSSCHG_Pos (9U)
#define USB_GOTGINT_HNSSCHG_Msk (0x1UL << USB_GOTGINT_HNSSCHG_Pos) /*!< Host negotiation success status change */
#define USB_GOTGINT_HNGDET_Pos  (17U)
#define USB_GOTGINT_HNGDET_Msk  (0x1UL << USB_GOTGINT_HNGDET_Pos) /*!< Host negotiation detected */
#define USB_GOTGINT_ADTOCHG_Pos (18U)
#define USB_GOTGINT_ADTOCHG_Msk (0x1UL << USB_GOTGINT_ADTOCHG_Pos) /*!< A-device timeout change */
#define USB_GOTGINT_DBCDNE_Pos  (19U)
#define USB_GOTGINT_DBCDNE_Msk  (0x1UL << USB_GOTGINT_DBCDNE_Pos) /*!< Debounce done */

/********************  Bit definition for USB_DCTL register  ********************/
#define USB_DCTL_RWUSIG_Pos   (0U)
#define USB_DCTL_RWUSIG_Msk   (0x1UL << USB_DCTL_RWUSIG_Pos) /*!< Remote wakeup signaling */
#define USB_DCTL_SDIS_Pos     (1U)
#define USB_DCTL_SDIS_Msk     (0x1UL << USB_DCTL_SDIS_Pos) /*!< Soft disconnect */
#define USB_DCTL_GINSTS_Pos   (2U)
#define USB_DCTL_GINSTS_Msk   (0x1UL << USB_DCTL_GINSTS_Pos) /*!< Global IN NAK status */
#define USB_DCTL_GONSTS_Pos   (3U)
#define USB_DCTL_GONSTS_Msk   (0x1UL << USB_DCTL_GONSTS_Pos) /*!< Global OUT NAK status */
#define USB_DCTL_TCTL_Pos     (4U)
#define USB_DCTL_TCTL_Msk     (0x7UL << USB_DCTL_TCTL_Pos) /*!< Test control */
#define USB_DCTL_TCTL_0       (0x1UL << USB_DCTL_TCTL_Pos) /*!< 0x00000010 */
#define USB_DCTL_TCTL_1       (0x2UL << USB_DCTL_TCTL_Pos) /*!< 0x00000020 */
#define USB_DCTL_TCTL_2       (0x4UL << USB_DCTL_TCTL_Pos) /*!< 0x00000040 */
#define USB_DCTL_SGINAK_Pos   (7U)
#define USB_DCTL_SGINAK_Msk   (0x1UL << USB_DCTL_SGINAK_Pos) /*!< Set global IN NAK */
#define USB_DCTL_CGINAK_Pos   (8U)
#define USB_DCTL_CGINAK_Msk   (0x1UL << USB_DCTL_CGINAK_Pos) /*!< Clear global IN NAK */
#define USB_DCTL_SGONAK_Pos   (9U)
#define USB_DCTL_SGONAK_Msk   (0x1UL << USB_DCTL_SGONAK_Pos) /*!< Set global OUT NAK */
#define USB_DCTL_CGONAK_Pos   (10U)
#define USB_DCTL_CGONAK_Msk   (0x1UL << USB_DCTL_CGONAK_Pos) /*!< Clear global OUT NAK */
#define USB_DCTL_POPRGDNE_Pos (11U)
#define USB_DCTL_POPRGDNE_Msk (0x1UL << USB_DCTL_POPRGDNE_Pos) /*!< Power-on programming done */

/********************  Bit definition for USB_HFIR register  ********************/
#define USB_HFIR_FRIVL_Pos (0U)
#define USB_HFIR_FRIVL_Msk (0xFFFFUL << USB_HFIR_FRIVL_Pos) /*!< Frame interval */

/********************  Bit definition for USB_HFNUM register  ********************/
#define USB_HFNUM_FRNUM_Pos (0U)
#define USB_HFNUM_FRNUM_Msk (0xFFFFUL << USB_HFNUM_FRNUM_Pos) /*!< Frame number */
#define USB_HFNUM_FTREM_Pos (16U)
#define USB_HFNUM_FTREM_Msk (0xFFFFUL << USB_HFNUM_FTREM_Pos) /*!< Frame time remaining */

/********************  Bit definition for USB_DSTS register  ********************/
#define USB_DSTS_SUSPSTS_Pos (0U)
#define USB_DSTS_SUSPSTS_Msk (0x1UL << USB_DSTS_SUSPSTS_Pos) /*!< Suspend status */
#define USB_DSTS_ENUMSPD_Pos (1U)
#define USB_DSTS_ENUMSPD_Msk (0x3UL << USB_DSTS_ENUMSPD_Pos) /*!< Enumerated speed */
#define USB_DSTS_ENUMSPD_0   (0x1UL << USB_DSTS_ENUMSPD_Pos) /*!< 0x00000002 */
#define USB_DSTS_ENUMSPD_1   (0x2UL << USB_DSTS_ENUMSPD_Pos) /*!< 0x00000004 */
#define USB_DSTS_EERR_Pos    (3U)
#define USB_DSTS_EERR_Msk    (0x1UL << USB_DSTS_EERR_Pos) /*!< Erratic error */
#define USB_DSTS_FNSOF_Pos   (8U)
#define USB_DSTS_FNSOF_Msk   (0x3FFFUL << USB_DSTS_FNSOF_Pos) /*!< Frame number of the received sof */

/********************  Bit definition for USB_GAHBCFG register  ********************/
#define USB_GAHBCFG_GINT_Pos     (0U)
#define USB_GAHBCFG_GINT_Msk     (0x1UL << USB_GAHBCFG_GINT_Pos) /*!< Global interrupt mask */
#define USB_GAHBCFG_HBSTLEN_Pos  (1U)
#define USB_GAHBCFG_HBSTLEN_Msk  (0xFUL << USB_GAHBCFG_HBSTLEN_Pos) /*!< Burst length/type */
#define USB_GAHBCFG_HBSTLEN_0    (0x0UL << USB_GAHBCFG_HBSTLEN_Pos) /*!< Single */
#define USB_GAHBCFG_HBSTLEN_1    (0x1UL << USB_GAHBCFG_HBSTLEN_Pos) /*!< INCR */
#define USB_GAHBCFG_HBSTLEN_2    (0x3UL << USB_GAHBCFG_HBSTLEN_Pos) /*!< INCR4 */
#define USB_GAHBCFG_HBSTLEN_3    (0x5UL << USB_GAHBCFG_HBSTLEN_Pos) /*!< INCR8 */
#define USB_GAHBCFG_HBSTLEN_4    (0x7UL << USB_GAHBCFG_HBSTLEN_Pos) /*!< INCR16 */
#define USB_GAHBCFG_DMAEN_Pos    (5U)
#define USB_GAHBCFG_DMAEN_Msk    (0x1UL << USB_GAHBCFG_DMAEN_Pos) /*!< DMA enable */
#define USB_GAHBCFG_TXFELVL_Pos  (7U)
#define USB_GAHBCFG_TXFELVL_Msk  (0x1UL << USB_GAHBCFG_TXFELVL_Pos) /*!< TxFIFO empty level */
#define USB_GAHBCFG_PTXFELVL_Pos (8U)
#define USB_GAHBCFG_PTXFELVL_Msk (0x1UL << USB_GAHBCFG_PTXFELVL_Pos) /*!< Periodic TxFIFO empty level */

/********************  Bit definition for USB_GUSBCFG register  ********************/
#define USB_GUSBCFG_TOCAL_Pos         (0U)
#define USB_GUSBCFG_TOCAL_Msk         (0x7UL << USB_GUSBCFG_TOCAL_Pos) /*!< FS timeout calibration */
#define USB_GUSBCFG_TOCAL_0           (0x1UL << USB_GUSBCFG_TOCAL_Pos) /*!< 0x00000001 */
#define USB_GUSBCFG_TOCAL_1           (0x2UL << USB_GUSBCFG_TOCAL_Pos) /*!< 0x00000002 */
#define USB_GUSBCFG_TOCAL_2           (0x4UL << USB_GUSBCFG_TOCAL_Pos) /*!< 0x00000004 */
#define USB_GUSBCFG_PHYIF_Pos         (3U)
#define USB_GUSBCFG_PHYIF_Msk         (0x1UL << USB_GUSBCFG_PHYIF_Pos)
#define USB_GUSBCFG_ULPI_UTMI_SEL_Pos (4U)
#define USB_GUSBCFG_ULPI_UTMI_SEL_Msk (0x1UL << USB_GUSBCFG_ULPI_UTMI_SEL_Pos)
#define USB_GUSBCFG_PHYINTF_Pos       (5U)
#define USB_GUSBCFG_PHYINTF_Msk       (0x1UL << USB_GUSBCFG_PHYINTF_Pos)
#define USB_GUSBCFG_PHYSEL_Pos        (6U)
#define USB_GUSBCFG_PHYSEL_Msk        (0x1UL << USB_GUSBCFG_PHYSEL_Pos)
/*!< USB 2.0 high-speed ULPI PHY or USB 1.1 full-speed serial transceiver select */
#define USB_GUSBCFG_SRPCAP_Pos     (8U)
#define USB_GUSBCFG_SRPCAP_Msk     (0x1UL << USB_GUSBCFG_SRPCAP_Pos) /*!< SRP-capable */
#define USB_GUSBCFG_HNPCAP_Pos     (9U)
#define USB_GUSBCFG_HNPCAP_Msk     (0x1UL << USB_GUSBCFG_HNPCAP_Pos) /*!< HNP-capable */
#define USB_GUSBCFG_TRDT_Pos       (10U)
#define USB_GUSBCFG_TRDT_Msk       (0xFUL << USB_GUSBCFG_TRDT_Pos) /*!< USB turnaround time */
#define USB_GUSBCFG_TRDT_0         (0x1UL << USB_GUSBCFG_TRDT_Pos) /*!< 0x00000400 */
#define USB_GUSBCFG_TRDT_1         (0x2UL << USB_GUSBCFG_TRDT_Pos) /*!< 0x00000800 */
#define USB_GUSBCFG_TRDT_2         (0x4UL << USB_GUSBCFG_TRDT_Pos) /*!< 0x00001000 */
#define USB_GUSBCFG_TRDT_3         (0x8UL << USB_GUSBCFG_TRDT_Pos) /*!< 0x00002000 */
#define USB_GUSBCFG_PHYLPCS_Pos    (15U)
#define USB_GUSBCFG_PHYLPCS_Msk    (0x1UL << USB_GUSBCFG_PHYLPCS_Pos) /*!< PHY Low-power clock select */
#define USB_GUSBCFG_ULPIFSLS_Pos   (17U)
#define USB_GUSBCFG_ULPIFSLS_Msk   (0x1UL << USB_GUSBCFG_ULPIFSLS_Pos) /*!< ULPI FS/LS select */
#define USB_GUSBCFG_ULPIAR_Pos     (18U)
#define USB_GUSBCFG_ULPIAR_Msk     (0x1UL << USB_GUSBCFG_ULPIAR_Pos) /*!< ULPI Auto-resume */
#define USB_GUSBCFG_ULPICSM_Pos    (19U)
#define USB_GUSBCFG_ULPICSM_Msk    (0x1UL << USB_GUSBCFG_ULPICSM_Pos) /*!< ULPI Clock SuspendM */
#define USB_GUSBCFG_ULPIEVBUSD_Pos (20U)
#define USB_GUSBCFG_ULPIEVBUSD_Msk (0x1UL << USB_GUSBCFG_ULPIEVBUSD_Pos) /*!< ULPI External VBUS Drive */
#define USB_GUSBCFG_ULPIEVBUSI_Pos (21U)
#define USB_GUSBCFG_ULPIEVBUSI_Msk (0x1UL << USB_GUSBCFG_ULPIEVBUSI_Pos) /*!< ULPI external VBUS indicator */
#define USB_GUSBCFG_TSDPS_Pos      (22U)
#define USB_GUSBCFG_TSDPS_Msk      (0x1UL << USB_GUSBCFG_TSDPS_Pos) /*!< TermSel DLine pulsing selection */
#define USB_GUSBCFG_PCCI_Pos       (23U)
#define USB_GUSBCFG_PCCI_Msk       (0x1UL << USB_GUSBCFG_PCCI_Pos) /*!< Indicator complement */
#define USB_GUSBCFG_PTCI_Pos       (24U)
#define USB_GUSBCFG_PTCI_Msk       (0x1UL << USB_GUSBCFG_PTCI_Pos) /*!< Indicator pass through */
#define USB_GUSBCFG_ULPIIPD_Pos    (25U)
#define USB_GUSBCFG_ULPIIPD_Msk    (0x1UL << USB_GUSBCFG_ULPIIPD_Pos) /*!< ULPI interface protect disable  */
#define USB_GUSBCFG_FHMOD_Pos      (29U)
#define USB_GUSBCFG_FHMOD_Msk      (0x1UL << USB_GUSBCFG_FHMOD_Pos) /*!< Forced host mode */
#define USB_GUSBCFG_FDMOD_Pos      (30U)
#define USB_GUSBCFG_FDMOD_Msk      (0x1UL << USB_GUSBCFG_FDMOD_Pos) /*!< Forced peripheral mode */
#define USB_GUSBCFG_CTXPKT_Pos     (31U)
#define USB_GUSBCFG_CTXPKT_Msk     (0x1UL << USB_GUSBCFG_CTXPKT_Pos) /*!< Corrupt Tx packet */

/********************  Bit definition for USB_GRSTCTL register  ********************/
#define USB_GRSTCTL_CSRST_Pos     (0U)
#define USB_GRSTCTL_CSRST_Msk     (0x1UL << USB_GRSTCTL_CSRST_Pos) /*!< Core soft reset */
#define USB_GRSTCTL_HSRST_Pos     (1U)
#define USB_GRSTCTL_HSRST_Msk     (0x1UL << USB_GRSTCTL_HSRST_Pos) /*!< HCLK soft reset */
#define USB_GRSTCTL_FCRST_Pos     (2U)
#define USB_GRSTCTL_FCRST_Msk     (0x1UL << USB_GRSTCTL_FCRST_Pos) /*!< Host frame counter reset */
#define USB_GRSTCTL_RXFFLSH_Pos   (4U)
#define USB_GRSTCTL_RXFFLSH_Msk   (0x1UL << USB_GRSTCTL_RXFFLSH_Pos) /*!< RxFIFO flush */
#define USB_GRSTCTL_TXFFLSH_Pos   (5U)
#define USB_GRSTCTL_TXFFLSH_Msk   (0x1UL << USB_GRSTCTL_TXFFLSH_Pos) /*!< TxFIFO flush */
#define USB_GRSTCTL_CSRSTDONE_Pos (29U)
#define USB_GRSTCTL_CSRSTDONE_Msk (0x1UL << USB_GRSTCTL_CSRSTDONE_Pos) /*!< Core soft reset done */

#define USB_GRSTCTL_TXFNUM_Pos (6U)
#define USB_GRSTCTL_TXFNUM_Msk (0x1FUL << USB_GRSTCTL_TXFNUM_Pos) /*!< TxFIFO number */
#define USB_GRSTCTL_TXFNUM_0   (0x01UL << USB_GRSTCTL_TXFNUM_Pos) /*!< 0x00000040 */
#define USB_GRSTCTL_TXFNUM_1   (0x02UL << USB_GRSTCTL_TXFNUM_Pos) /*!< 0x00000080 */
#define USB_GRSTCTL_TXFNUM_2   (0x04UL << USB_GRSTCTL_TXFNUM_Pos) /*!< 0x00000100 */
#define USB_GRSTCTL_TXFNUM_3   (0x08UL << USB_GRSTCTL_TXFNUM_Pos) /*!< 0x00000200 */
#define USB_GRSTCTL_TXFNUM_4   (0x10UL << USB_GRSTCTL_TXFNUM_Pos) /*!< 0x00000400 */
#define USB_GRSTCTL_DMAREQ_Pos (30U)
#define USB_GRSTCTL_DMAREQ_Msk (0x1UL << USB_GRSTCTL_DMAREQ_Pos) /*!< DMA request signal */
#define USB_GRSTCTL_AHBIDL_Pos (31U)
#define USB_GRSTCTL_AHBIDL_Msk (0x1UL << USB_GRSTCTL_AHBIDL_Pos) /*!< AHB master idle */

/********************  Bit definition for USB_DIEPMSK register  ********************/
#define USB_DIEPMSK_XFRCM_Pos     (0U)
#define USB_DIEPMSK_XFRCM_Msk     (0x1UL << USB_DIEPMSK_XFRCM_Pos) /*!< Transfer completed interrupt mask */
#define USB_DIEPMSK_EPDM_Pos      (1U)
#define USB_DIEPMSK_EPDM_Msk      (0x1UL << USB_DIEPMSK_EPDM_Pos) /*!< Endpoint disabled interrupt mask */
#define USB_DIEPMSK_TOM_Pos       (3U)
#define USB_DIEPMSK_TOM_Msk       (0x1UL << USB_DIEPMSK_TOM_Pos) /*!< Timeout condition mask (nonisochronous endpoints) */
#define USB_DIEPMSK_ITTXFEMSK_Pos (4U)
#define USB_DIEPMSK_ITTXFEMSK_Msk (0x1UL << USB_DIEPMSK_ITTXFEMSK_Pos) /*!< IN token received when TxFIFO empty mask */
#define USB_DIEPMSK_INEPNMM_Pos   (5U)
#define USB_DIEPMSK_INEPNMM_Msk   (0x1UL << USB_DIEPMSK_INEPNMM_Pos) /*!< IN token received with EP mismatch mask */
#define USB_DIEPMSK_INEPNEM_Pos   (6U)
#define USB_DIEPMSK_INEPNEM_Msk   (0x1UL << USB_DIEPMSK_INEPNEM_Pos) /*!< IN endpoint NAK effective mask */
#define USB_DIEPMSK_TXFURM_Pos    (8U)
#define USB_DIEPMSK_TXFURM_Msk    (0x1UL << USB_DIEPMSK_TXFURM_Pos) /*!< FIFO underrun mask */
#define USB_DIEPMSK_BIM_Pos       (9U)
#define USB_DIEPMSK_BIM_Msk       (0x1UL << USB_DIEPMSK_BIM_Pos) /*!< BNA interrupt mask */

/********************  Bit definition for USB_HPTXSTS register  ********************/
#define USB_HPTXSTS_PTXFSAVL_Pos (0U)
#define USB_HPTXSTS_PTXFSAVL_Msk (0xFFFFUL << USB_HPTXSTS_PTXFSAVL_Pos) /*!< Periodic transmit data FIFO space available */
#define USB_HPTXSTS_PTXQSAV_Pos  (16U)
#define USB_HPTXSTS_PTXQSAV_Msk  (0xFFUL << USB_HPTXSTS_PTXQSAV_Pos) /*!< Periodic transmit request queue space available */
#define USB_HPTXSTS_PTXQSAV_0    (0x01UL << USB_HPTXSTS_PTXQSAV_Pos) /*!< 0x00010000 */
#define USB_HPTXSTS_PTXQSAV_1    (0x02UL << USB_HPTXSTS_PTXQSAV_Pos) /*!< 0x00020000 */
#define USB_HPTXSTS_PTXQSAV_2    (0x04UL << USB_HPTXSTS_PTXQSAV_Pos) /*!< 0x00040000 */
#define USB_HPTXSTS_PTXQSAV_3    (0x08UL << USB_HPTXSTS_PTXQSAV_Pos) /*!< 0x00080000 */
#define USB_HPTXSTS_PTXQSAV_4    (0x10UL << USB_HPTXSTS_PTXQSAV_Pos) /*!< 0x00100000 */
#define USB_HPTXSTS_PTXQSAV_5    (0x20UL << USB_HPTXSTS_PTXQSAV_Pos) /*!< 0x00200000 */
#define USB_HPTXSTS_PTXQSAV_6    (0x40UL << USB_HPTXSTS_PTXQSAV_Pos) /*!< 0x00400000 */
#define USB_HPTXSTS_PTXQSAV_7    (0x80UL << USB_HPTXSTS_PTXQSAV_Pos) /*!< 0x00800000 */

#define USB_HPTXSTS_PTXQTOP_Pos (24U)
#define USB_HPTXSTS_PTXQTOP_Msk (0xFFUL << USB_HPTXSTS_PTXQTOP_Pos) /*!< Top of the periodic transmit request queue */
#define USB_HPTXSTS_PTXQTOP_0   (0x01UL << USB_HPTXSTS_PTXQTOP_Pos) /*!< 0x01000000 */
#define USB_HPTXSTS_PTXQTOP_1   (0x02UL << USB_HPTXSTS_PTXQTOP_Pos) /*!< 0x02000000 */
#define USB_HPTXSTS_PTXQTOP_2   (0x04UL << USB_HPTXSTS_PTXQTOP_Pos) /*!< 0x04000000 */
#define USB_HPTXSTS_PTXQTOP_3   (0x08UL << USB_HPTXSTS_PTXQTOP_Pos) /*!< 0x08000000 */
#define USB_HPTXSTS_PTXQTOP_4   (0x10UL << USB_HPTXSTS_PTXQTOP_Pos) /*!< 0x10000000 */
#define USB_HPTXSTS_PTXQTOP_5   (0x20UL << USB_HPTXSTS_PTXQTOP_Pos) /*!< 0x20000000 */
#define USB_HPTXSTS_PTXQTOP_6   (0x40UL << USB_HPTXSTS_PTXQTOP_Pos) /*!< 0x40000000 */
#define USB_HPTXSTS_PTXQTOP_7   (0x80UL << USB_HPTXSTS_PTXQTOP_Pos) /*!< 0x80000000 */

#define USB_HPTXSTS_PTXQTOP_CHNUM_Pos (27U)
#define USB_HPTXSTS_PTXQTOP_CHNUM_Msk (0xFUL << USB_HPTXSTS_PTXQTOP_CHNUM_Pos) /*!< Top of the nonperiodic transmit request queue */

/********************  Bit definition for USB_HAINT register  ********************/
#define USB_HAINT_HAINT_Pos (0U)
#define USB_HAINT_HAINT_Msk (0xFFFFUL << USB_HAINT_HAINT_Pos) /*!< Channel interrupts */

/********************  Bit definition for USB_DOEPMSK register  ********************/
#define USB_DOEPMSK_XFRCM_Pos    (0U)
#define USB_DOEPMSK_XFRCM_Msk    (0x1UL << USB_DOEPMSK_XFRCM_Pos) /*!< Transfer completed interrupt mask */
#define USB_DOEPMSK_EPDM_Pos     (1U)
#define USB_DOEPMSK_EPDM_Msk     (0x1UL << USB_DOEPMSK_EPDM_Pos) /*!< Endpoint disabled interrupt mask */
#define USB_DOEPMSK_AHBERRM_Pos  (2U)
#define USB_DOEPMSK_AHBERRM_Msk  (0x1UL << USB_DOEPMSK_AHBERRM_Pos) /*!< OUT transaction AHB Error interrupt mask */
#define USB_DOEPMSK_STUPM_Pos    (3U)
#define USB_DOEPMSK_STUPM_Msk    (0x1UL << USB_DOEPMSK_STUPM_Pos) /*!< SETUP phase done mask */
#define USB_DOEPMSK_OTEPDM_Pos   (4U)
#define USB_DOEPMSK_OTEPDM_Msk   (0x1UL << USB_DOEPMSK_OTEPDM_Pos) /*!< OUT token received when endpoint disabled mask */
#define USB_DOEPMSK_OTEPSPRM_Pos (5U)
#define USB_DOEPMSK_OTEPSPRM_Msk (0x1UL << USB_DOEPMSK_OTEPSPRM_Pos) /*!< Status Phase Received mask */
#define USB_DOEPMSK_B2BSTUP_Pos  (6U)
#define USB_DOEPMSK_B2BSTUP_Msk  (0x1UL << USB_DOEPMSK_B2BSTUP_Pos) /*!< Back-to-back SETUP packets received mask */
#define USB_DOEPMSK_OPEM_Pos     (8U)
#define USB_DOEPMSK_OPEM_Msk     (0x1UL << USB_DOEPMSK_OPEM_Pos) /*!< OUT packet error mask */
#define USB_DOEPMSK_BOIM_Pos     (9U)
#define USB_DOEPMSK_BOIM_Msk     (0x1UL << USB_DOEPMSK_BOIM_Pos) /*!< BNA interrupt mask */
#define USB_DOEPMSK_BERRM_Pos    (12U)
#define USB_DOEPMSK_BERRM_Msk    (0x1UL << USB_DOEPMSK_BERRM_Pos) /*!< Babble error interrupt mask */
#define USB_DOEPMSK_NAKM_Pos     (13U)
#define USB_DOEPMSK_NAKM_Msk     (0x1UL << USB_DOEPMSK_NAKM_Pos) /*!< OUT Packet NAK interrupt mask */
#define USB_DOEPMSK_NYETM_Pos    (14U)
#define USB_DOEPMSK_NYETM_Msk    (0x1UL << USB_DOEPMSK_NYETM_Pos) /*!< NYET interrupt mask */

/********************  Bit definition for USB_GINTSTS register  ********************/
#define USB_GINTSTS_CMOD_Pos              (0U)
#define USB_GINTSTS_CMOD_Msk              (0x1UL << USB_GINTSTS_CMOD_Pos) /*!< Current mode of operation */
#define USB_GINTSTS_MMIS_Pos              (1U)
#define USB_GINTSTS_MMIS_Msk              (0x1UL << USB_GINTSTS_MMIS_Pos) /*!< Mode mismatch interrupt */
#define USB_GINTSTS_OTGINT_Pos            (2U)
#define USB_GINTSTS_OTGINT_Msk            (0x1UL << USB_GINTSTS_OTGINT_Pos) /*!< OTG interrupt */
#define USB_GINTSTS_SOF_Pos               (3U)
#define USB_GINTSTS_SOF_Msk               (0x1UL << USB_GINTSTS_SOF_Pos) /*!< Start of frame */
#define USB_GINTSTS_RXFLVL_Pos            (4U)
#define USB_GINTSTS_RXFLVL_Msk            (0x1UL << USB_GINTSTS_RXFLVL_Pos) /*!< RxFIFO nonempty */
#define USB_GINTSTS_NPTXFE_Pos            (5U)
#define USB_GINTSTS_NPTXFE_Msk            (0x1UL << USB_GINTSTS_NPTXFE_Pos) /*!< Nonperiodic TxFIFO empty */
#define USB_GINTSTS_GINAKEFF_Pos          (6U)
#define USB_GINTSTS_GINAKEFF_Msk          (0x1UL << USB_GINTSTS_GINAKEFF_Pos) /*!< Global IN nonperiodic NAK effective */
#define USB_GINTSTS_GOUTNAKEFF_Pos        (7U)
#define USB_GINTSTS_GOUTNAKEFF_Msk        (0x1UL << USB_GINTSTS_GOUTNAKEFF_Pos) /*!< Global OUT NAK effective */
#define USB_GINTSTS_ESUSP_Pos             (10U)
#define USB_GINTSTS_ESUSP_Msk             (0x1UL << USB_GINTSTS_ESUSP_Pos) /*!< Early suspend */
#define USB_GINTSTS_USBSUSP_Pos           (11U)
#define USB_GINTSTS_USBSUSP_Msk           (0x1UL << USB_GINTSTS_USBSUSP_Pos) /*!< USB suspend */
#define USB_GINTSTS_USBRST_Pos            (12U)
#define USB_GINTSTS_USBRST_Msk            (0x1UL << USB_GINTSTS_USBRST_Pos) /*!< USB reset */
#define USB_GINTSTS_ENUMDNE_Pos           (13U)
#define USB_GINTSTS_ENUMDNE_Msk           (0x1UL << USB_GINTSTS_ENUMDNE_Pos) /*!< Enumeration done */
#define USB_GINTSTS_ISOODRP_Pos           (14U)
#define USB_GINTSTS_ISOODRP_Msk           (0x1UL << USB_GINTSTS_ISOODRP_Pos) /*!< Isochronous OUT packet dropped interrupt */
#define USB_GINTSTS_EOPF_Pos              (15U)
#define USB_GINTSTS_EOPF_Msk              (0x1UL << USB_GINTSTS_EOPF_Pos) /*!< End of periodic frame interrupt */
#define USB_GINTSTS_IEPINT_Pos            (18U)
#define USB_GINTSTS_IEPINT_Msk            (0x1UL << USB_GINTSTS_IEPINT_Pos) /*!< IN endpoint interrupt */
#define USB_GINTSTS_OEPINT_Pos            (19U)
#define USB_GINTSTS_OEPINT_Msk            (0x1UL << USB_GINTSTS_OEPINT_Pos) /*!< OUT endpoint interrupt */
#define USB_GINTSTS_IISOIXFR_Pos          (20U)
#define USB_GINTSTS_IISOIXFR_Msk          (0x1UL << USB_GINTSTS_IISOIXFR_Pos) /*!< Incomplete isochronous IN transfer */
#define USB_GINTSTS_PXFR_INCOMPISOOUT_Pos (21U)
#define USB_GINTSTS_PXFR_INCOMPISOOUT_Msk (0x1UL << USB_GINTSTS_PXFR_INCOMPISOOUT_Pos) /*!< Incomplete periodic transfer */
#define USB_GINTSTS_DATAFSUSP_Pos         (22U)
#define USB_GINTSTS_DATAFSUSP_Msk         (0x1UL << USB_GINTSTS_DATAFSUSP_Pos) /*!< Data fetch suspended */
#define USB_GINTSTS_RSTDET_Pos            (23U)
#define USB_GINTSTS_RSTDET_Msk            (0x1UL << USB_GINTSTS_RSTDET_Pos) /*!< Reset detected interrupt */
#define USB_GINTSTS_HPRTINT_Pos           (24U)
#define USB_GINTSTS_HPRTINT_Msk           (0x1UL << USB_GINTSTS_HPRTINT_Pos) /*!< Host port interrupt */
#define USB_GINTSTS_HCINT_Pos             (25U)
#define USB_GINTSTS_HCINT_Msk             (0x1UL << USB_GINTSTS_HCINT_Pos) /*!< Host channels interrupt */
#define USB_GINTSTS_PTXFE_Pos             (26U)
#define USB_GINTSTS_PTXFE_Msk             (0x1UL << USB_GINTSTS_PTXFE_Pos) /*!< Periodic TxFIFO empty */
#define USB_GINTSTS_LPMINT_Pos            (27U)
#define USB_GINTSTS_LPMINT_Msk            (0x1UL << USB_GINTSTS_LPMINT_Pos) /*!< LPM interrupt */
#define USB_GINTSTS_CIDSCHG_Pos           (28U)
#define USB_GINTSTS_CIDSCHG_Msk           (0x1UL << USB_GINTSTS_CIDSCHG_Pos) /*!< Connector ID status change */
#define USB_GINTSTS_DISCINT_Pos           (29U)
#define USB_GINTSTS_DISCINT_Msk           (0x1UL << USB_GINTSTS_DISCINT_Pos) /*!< Disconnect detected interrupt */
#define USB_GINTSTS_SRQINT_Pos            (30U)
#define USB_GINTSTS_SRQINT_Msk            (0x1UL << USB_GINTSTS_SRQINT_Pos) /*!< Session request/new session detected interrupt */
#define USB_GINTSTS_WKUINT_Pos            (31U)
#define USB_GINTSTS_WKUINT_Msk            (0x1UL << USB_GINTSTS_WKUINT_Pos) /*!< Resume/remote wakeup detected interrupt */

/********************  Bit definition for USB_GINTMSK register  ********************/
#define USB_GINTMSK_MMISM_Pos           (1U)
#define USB_GINTMSK_MMISM_Msk           (0x1UL << USB_GINTMSK_MMISM_Pos) /*!< Mode mismatch interrupt mask */
#define USB_GINTMSK_OTGINT_Pos          (2U)
#define USB_GINTMSK_OTGINT_Msk          (0x1UL << USB_GINTMSK_OTGINT_Pos) /*!< OTG interrupt mask */
#define USB_GINTMSK_SOFM_Pos            (3U)
#define USB_GINTMSK_SOFM_Msk            (0x1UL << USB_GINTMSK_SOFM_Pos) /*!< Start of frame mask */
#define USB_GINTMSK_RXFLVLM_Pos         (4U)
#define USB_GINTMSK_RXFLVLM_Msk         (0x1UL << USB_GINTMSK_RXFLVLM_Pos) /*!< Receive FIFO nonempty mask */
#define USB_GINTMSK_NPTXFEM_Pos         (5U)
#define USB_GINTMSK_NPTXFEM_Msk         (0x1UL << USB_GINTMSK_NPTXFEM_Pos) /*!< Nonperiodic TxFIFO empty mask */
#define USB_GINTMSK_GINAKEFFM_Pos       (6U)
#define USB_GINTMSK_GINAKEFFM_Msk       (0x1UL << USB_GINTMSK_GINAKEFFM_Pos) /*!< Global nonperiodic IN NAK effective mask */
#define USB_GINTMSK_GONAKEFFM_Pos       (7U)
#define USB_GINTMSK_GONAKEFFM_Msk       (0x1UL << USB_GINTMSK_GONAKEFFM_Pos) /*!< Global OUT NAK effective mask */
#define USB_GINTMSK_ESUSPM_Pos          (10U)
#define USB_GINTMSK_ESUSPM_Msk          (0x1UL << USB_GINTMSK_ESUSPM_Pos) /*!< Early suspend mask */
#define USB_GINTMSK_USBSUSPM_Pos        (11U)
#define USB_GINTMSK_USBSUSPM_Msk        (0x1UL << USB_GINTMSK_USBSUSPM_Pos) /*!< USB suspend mask */
#define USB_GINTMSK_USBRST_Pos          (12U)
#define USB_GINTMSK_USBRST_Msk          (0x1UL << USB_GINTMSK_USBRST_Pos) /*!< USB reset mask */
#define USB_GINTMSK_ENUMDNEM_Pos        (13U)
#define USB_GINTMSK_ENUMDNEM_Msk        (0x1UL << USB_GINTMSK_ENUMDNEM_Pos) /*!< Enumeration done mask */
#define USB_GINTMSK_ISOODRPM_Pos        (14U)
#define USB_GINTMSK_ISOODRPM_Msk        (0x1UL << USB_GINTMSK_ISOODRPM_Pos) /*!< Isochronous OUT packet dropped interrupt mask */
#define USB_GINTMSK_EOPFM_Pos           (15U)
#define USB_GINTMSK_EOPFM_Msk           (0x1UL << USB_GINTMSK_EOPFM_Pos) /*!< End of periodic frame interrupt mask */
#define USB_GINTMSK_EPMISM_Pos          (17U)
#define USB_GINTMSK_EPMISM_Msk          (0x1UL << USB_GINTMSK_EPMISM_Pos) /*!< Endpoint mismatch interrupt mask */
#define USB_GINTMSK_IEPINT_Pos          (18U)
#define USB_GINTMSK_IEPINT_Msk          (0x1UL << USB_GINTMSK_IEPINT_Pos) /*!< IN endpoints interrupt mask */
#define USB_GINTMSK_OEPINT_Pos          (19U)
#define USB_GINTMSK_OEPINT_Msk          (0x1UL << USB_GINTMSK_OEPINT_Pos) /*!< OUT endpoints interrupt mask */
#define USB_GINTMSK_IISOIXFRM_Pos       (20U)
#define USB_GINTMSK_IISOIXFRM_Msk       (0x1UL << USB_GINTMSK_IISOIXFRM_Pos) /*!< Incomplete isochronous IN transfer mask */
#define USB_GINTMSK_PXFRM_IISOOXFRM_Pos (21U)
#define USB_GINTMSK_PXFRM_IISOOXFRM_Msk (0x1UL << USB_GINTMSK_PXFRM_IISOOXFRM_Pos) /*!< Incomplete periodic transfer mask */
#define USB_GINTMSK_FSUSPM_Pos          (22U)
#define USB_GINTMSK_FSUSPM_Msk          (0x1UL << USB_GINTMSK_FSUSPM_Pos) /*!< Data fetch suspended mask */
#define USB_GINTMSK_RSTDEM_Pos          (23U)
#define USB_GINTMSK_RSTDEM_Msk          (0x1UL << USB_GINTMSK_RSTDEM_Pos) /*!< Reset detected interrupt mask */
#define USB_GINTMSK_PRTIM_Pos           (24U)
#define USB_GINTMSK_PRTIM_Msk           (0x1UL << USB_GINTMSK_PRTIM_Pos) /*!< Host port interrupt mask */
#define USB_GINTMSK_HCIM_Pos            (25U)
#define USB_GINTMSK_HCIM_Msk            (0x1UL << USB_GINTMSK_HCIM_Pos) /*!< Host channels interrupt mask */
#define USB_GINTMSK_PTXFEM_Pos          (26U)
#define USB_GINTMSK_PTXFEM_Msk          (0x1UL << USB_GINTMSK_PTXFEM_Pos) /*!< Periodic TxFIFO empty mask */
#define USB_GINTMSK_LPMINTM_Pos         (27U)
#define USB_GINTMSK_LPMINTM_Msk         (0x1UL << USB_GINTMSK_LPMINTM_Pos) /*!< LPM interrupt Mask */
#define USB_GINTMSK_CIDSCHGM_Pos        (28U)
#define USB_GINTMSK_CIDSCHGM_Msk        (0x1UL << USB_GINTMSK_CIDSCHGM_Pos) /*!< Connector ID status change mask */
#define USB_GINTMSK_DISCINT_Pos         (29U)
#define USB_GINTMSK_DISCINT_Msk         (0x1UL << USB_GINTMSK_DISCINT_Pos) /*!< Disconnect detected interrupt mask */
#define USB_GINTMSK_SRQIM_Pos           (30U)
#define USB_GINTMSK_SRQIM_Msk           (0x1UL << USB_GINTMSK_SRQIM_Pos) /*!< Session request/new session detected interrupt mask */
#define USB_GINTMSK_WUIM_Pos            (31U)
#define USB_GINTMSK_WUIM_Msk            (0x1UL << USB_GINTMSK_WUIM_Pos) /*!< Resume/remote wakeup detected interrupt mask */

/********************  Bit definition for USB_DAINT register  ********************/
#define USB_DAINT_IEPINT_Pos (0U)
#define USB_DAINT_IEPINT_Msk (0xFFFFUL << USB_DAINT_IEPINT_Pos) /*!< IN endpoint interrupt bits  */
#define USB_DAINT_OEPINT_Pos (16U)
#define USB_DAINT_OEPINT_Msk (0xFFFFUL << USB_DAINT_OEPINT_Pos) /*!< OUT endpoint interrupt bits */

/********************  Bit definition for USB_HAINTMSK register  ********************/
#define USB_HAINTMSK_HAINTM_Pos (0U)
#define USB_HAINTMSK_HAINTM_Msk (0xFFFFUL << USB_HAINTMSK_HAINTM_Pos) /*!< Channel interrupt mask */

/********************  Bit definition for USB_GRXSTSP register  ********************/
#define USB_GRXSTSP_EPNUM_Pos  (0U)
#define USB_GRXSTSP_EPNUM_Msk  (0xFUL << USB_GRXSTSP_EPNUM_Pos) /*!< IN EP interrupt mask bits  */
#define USB_GRXSTSP_BCNT_Pos   (4U)
#define USB_GRXSTSP_BCNT_Msk   (0x7FFUL << USB_GRXSTSP_BCNT_Pos) /*!< OUT EP interrupt mask bits */
#define USB_GRXSTSP_DPID_Pos   (15U)
#define USB_GRXSTSP_DPID_Msk   (0x3UL << USB_GRXSTSP_DPID_Pos) /*!< OUT EP interrupt mask bits */
#define USB_GRXSTSP_PKTSTS_Pos (17U)
#define USB_GRXSTSP_PKTSTS_Msk (0xFUL << USB_GRXSTSP_PKTSTS_Pos) /*!< OUT EP interrupt mask bits */

/********************  Bit definition for USB_DAINTMSK register  ********************/
#define USB_DAINTMSK_IEPM_Pos (0U)
#define USB_DAINTMSK_IEPM_Msk (0xFFFFUL << USB_DAINTMSK_IEPM_Pos) /*!< IN EP interrupt mask bits */
#define USB_DAINTMSK_OEPM_Pos (16U)
#define USB_DAINTMSK_OEPM_Msk (0xFFFFUL << USB_DAINTMSK_OEPM_Pos) /*!< OUT EP interrupt mask bits */

/********************  Bit definition for USB_GRXFSIZ register  ********************/
#define USB_GRXFSIZ_RXFD_Pos (0U)
#define USB_GRXFSIZ_RXFD_Msk (0xFFFFUL << USB_GRXFSIZ_RXFD_Pos) /*!< RxFIFO depth */

/********************  Bit definition for USB_DVBUSDIS register  ********************/
#define USB_DVBUSDIS_VBUSDT_Pos (0U)
#define USB_DVBUSDIS_VBUSDT_Msk (0xFFFFUL << USB_DVBUSDIS_VBUSDT_Pos) /*!< Device VBUS discharge time */

/********************  Bit definition for OTG register  ********************/
#define USB_NPTXFSA_Pos (0U)
#define USB_NPTXFSA_Msk (0xFFFFUL << USB_NPTXFSA_Pos) /*!< Nonperiodic transmit RAM start address */
#define USB_NPTXFD_Pos  (16U)
#define USB_NPTXFD_Msk  (0xFFFFUL << USB_NPTXFD_Pos) /*!< Nonperiodic TxFIFO depth */
#define USB_TX0FSA_Pos  (0U)
#define USB_TX0FSA_Msk  (0xFFFFUL << USB_TX0FSA_Pos) /*!< Endpoint 0 transmit RAM start address  */
#define USB_TX0FD_Pos   (16U)
#define USB_TX0FD_Msk   (0xFFFFUL << USB_TX0FD_Pos) /*!< Endpoint 0 TxFIFO depth */

/********************  Bit definition forUSB_DVBUSPULSE register  ********************/
#define USB_DVBUSPULSE_DVBUSP_Pos (0U)
#define USB_DVBUSPULSE_DVBUSP_Msk (0xFFFUL << USB_DVBUSPULSE_DVBUSP_Pos) /*!< Device VBUS pulsing time */

/********************  Bit definition for USB_GNPTXSTS register  ********************/
#define USB_GNPTXSTS_NPTXFSAV_Pos (0U)
#define USB_GNPTXSTS_NPTXFSAV_Msk (0xFFFFUL << USB_GNPTXSTS_NPTXFSAV_Pos) /*!< Nonperiodic TxFIFO space available */

#define USB_GNPTXSTS_NPTQXSAV_Pos (16U)
#define USB_GNPTXSTS_NPTQXSAV_Msk (0xFFUL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< Nonperiodic transmit request queue space available */
#define USB_GNPTXSTS_NPTQXSAV_0   (0x01UL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00010000 */
#define USB_GNPTXSTS_NPTQXSAV_1   (0x02UL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00020000 */
#define USB_GNPTXSTS_NPTQXSAV_2   (0x04UL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00040000 */
#define USB_GNPTXSTS_NPTQXSAV_3   (0x08UL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00080000 */
#define USB_GNPTXSTS_NPTQXSAV_4   (0x10UL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00100000 */
#define USB_GNPTXSTS_NPTQXSAV_5   (0x20UL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00200000 */
#define USB_GNPTXSTS_NPTQXSAV_6   (0x40UL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00400000 */
#define USB_GNPTXSTS_NPTQXSAV_7   (0x80UL << USB_GNPTXSTS_NPTQXSAV_Pos) /*!< 0x00800000 */

#define USB_GNPTXSTS_NPTXQTOP_Pos (24U)
#define USB_GNPTXSTS_NPTXQTOP_Msk (0x7FUL << USB_GNPTXSTS_NPTXQTOP_Pos) /*!< Top of the nonperiodic transmit request queue */
#define USB_GNPTXSTS_NPTXQTOP_0   (0x01UL << USB_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x01000000 */
#define USB_GNPTXSTS_NPTXQTOP_1   (0x02UL << USB_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x02000000 */
#define USB_GNPTXSTS_NPTXQTOP_2   (0x04UL << USB_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x04000000 */
#define USB_GNPTXSTS_NPTXQTOP_3   (0x08UL << USB_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x08000000 */
#define USB_GNPTXSTS_NPTXQTOP_4   (0x10UL << USB_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x10000000 */
#define USB_GNPTXSTS_NPTXQTOP_5   (0x20UL << USB_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x20000000 */
#define USB_GNPTXSTS_NPTXQTOP_6   (0x40UL << USB_GNPTXSTS_NPTXQTOP_Pos) /*!< 0x40000000 */

#define USB_GNPTXSTS_NPTXQTOP_CHNUM_Pos (27U)
#define USB_GNPTXSTS_NPTXQTOP_CHNUM_Msk (0xFUL << USB_GNPTXSTS_NPTXQTOP_CHNUM_Pos) /*!< Top of the nonperiodic transmit request queue */

/********************  Bit definition for USB_DTHRCTL register  ********************/
#define USB_DTHRCTL_NONISOTHREN_Pos (0U)
#define USB_DTHRCTL_NONISOTHREN_Msk (0x1UL << USB_DTHRCTL_NONISOTHREN_Pos) /*!< Nonisochronous IN endpoints threshold enable */
#define USB_DTHRCTL_ISOTHREN_Pos    (1U)
#define USB_DTHRCTL_ISOTHREN_Msk    (0x1UL << USB_DTHRCTL_ISOTHREN_Pos) /*!< ISO IN endpoint threshold enable */

#define USB_DTHRCTL_TXTHRLEN_Pos (2U)
#define USB_DTHRCTL_TXTHRLEN_Msk (0x1FFUL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< Transmit threshold length */
#define USB_DTHRCTL_TXTHRLEN_0   (0x001UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000004 */
#define USB_DTHRCTL_TXTHRLEN_1   (0x002UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000008 */
#define USB_DTHRCTL_TXTHRLEN_2   (0x004UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000010 */
#define USB_DTHRCTL_TXTHRLEN_3   (0x008UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000020 */
#define USB_DTHRCTL_TXTHRLEN_4   (0x010UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000040 */
#define USB_DTHRCTL_TXTHRLEN_5   (0x020UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000080 */
#define USB_DTHRCTL_TXTHRLEN_6   (0x040UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000100 */
#define USB_DTHRCTL_TXTHRLEN_7   (0x080UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000200 */
#define USB_DTHRCTL_TXTHRLEN_8   (0x100UL << USB_DTHRCTL_TXTHRLEN_Pos) /*!< 0x00000400 */
#define USB_DTHRCTL_RXTHREN_Pos  (16U)
#define USB_DTHRCTL_RXTHREN_Msk  (0x1UL << USB_DTHRCTL_RXTHREN_Pos) /*!< Receive threshold enable */

#define USB_DTHRCTL_RXTHRLEN_Pos (17U)
#define USB_DTHRCTL_RXTHRLEN_Msk (0x1FFUL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< Receive threshold length */
#define USB_DTHRCTL_RXTHRLEN_0   (0x001UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00020000 */
#define USB_DTHRCTL_RXTHRLEN_1   (0x002UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00040000 */
#define USB_DTHRCTL_RXTHRLEN_2   (0x004UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00080000 */
#define USB_DTHRCTL_RXTHRLEN_3   (0x008UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00100000 */
#define USB_DTHRCTL_RXTHRLEN_4   (0x010UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00200000 */
#define USB_DTHRCTL_RXTHRLEN_5   (0x020UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00400000 */
#define USB_DTHRCTL_RXTHRLEN_6   (0x040UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x00800000 */
#define USB_DTHRCTL_RXTHRLEN_7   (0x080UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x01000000 */
#define USB_DTHRCTL_RXTHRLEN_8   (0x100UL << USB_DTHRCTL_RXTHRLEN_Pos) /*!< 0x02000000 */
#define USB_DTHRCTL_ARPEN_Pos    (27U)
#define USB_DTHRCTL_ARPEN_Msk    (0x1UL << USB_DTHRCTL_ARPEN_Pos) /*!< Arbiter parking enable */

/********************  Bit definition for USB_DIEPEMPMSK register  ********************/
#define USB_DIEPEMPMSK_INEPTXFEM_Pos (0U)
#define USB_DIEPEMPMSK_INEPTXFEM_Msk (0xFFFFUL << USB_DIEPEMPMSK_INEPTXFEM_Pos) /*!< IN EP Tx FIFO empty interrupt mask bits */

/********************  Bit definition for USB_DEACHINT register  ********************/
#define USB_DEACHINT_IEP1INT_Pos (1U)
#define USB_DEACHINT_IEP1INT_Msk (0x1UL << USB_DEACHINT_IEP1INT_Pos) /*!< IN endpoint 1interrupt bit   */
#define USB_DEACHINT_OEP1INT_Pos (17U)
#define USB_DEACHINT_OEP1INT_Msk (0x1UL << USB_DEACHINT_OEP1INT_Pos) /*!< OUT endpoint 1 interrupt bit */

/********************  Bit definition for USB_GCCFG register  ********************/
#define USB_GCCFG_DCDET_Pos  (0U)
#define USB_GCCFG_DCDET_Msk  (0x1UL << USB_GCCFG_DCDET_Pos) /*!< Data contact detection (DCD) status */
#define USB_GCCFG_PDET_Pos   (1U)
#define USB_GCCFG_PDET_Msk   (0x1UL << USB_GCCFG_PDET_Pos) /*!< Primary detection (PD) status */
#define USB_GCCFG_SDET_Pos   (2U)
#define USB_GCCFG_SDET_Msk   (0x1UL << USB_GCCFG_SDET_Pos) /*!< Secondary detection (SD) status */
#define USB_GCCFG_PS2DET_Pos (3U)
#define USB_GCCFG_PS2DET_Msk (0x1UL << USB_GCCFG_PS2DET_Pos) /*!< DM pull-up detection status */
#define USB_GCCFG_PWRDWN_Pos (16U)
#define USB_GCCFG_PWRDWN_Msk (0x1UL << USB_GCCFG_PWRDWN_Pos) /*!< Power down */
#define USB_GCCFG_BCDEN_Pos  (17U)
#define USB_GCCFG_BCDEN_Msk  (0x1UL << USB_GCCFG_BCDEN_Pos) /*!< Battery charging detector (BCD) enable */
#define USB_GCCFG_DCDEN_Pos  (18U)
#define USB_GCCFG_DCDEN_Msk  (0x1UL << USB_GCCFG_DCDEN_Pos) /*!< Data contact detection (DCD) mode enable*/
#define USB_GCCFG_PDEN_Pos   (19U)
#define USB_GCCFG_PDEN_Msk   (0x1UL << USB_GCCFG_PDEN_Pos) /*!< Primary detection (PD) mode enable*/
#define USB_GCCFG_SDEN_Pos   (20U)
#define USB_GCCFG_SDEN_Msk   (0x1UL << USB_GCCFG_SDEN_Pos) /*!< Secondary detection (SD) mode enable */
#define USB_GCCFG_VBDEN_Pos  (21U)
#define USB_GCCFG_VBDEN_Msk  (0x1UL << USB_GCCFG_VBDEN_Pos) /*!< Secondary detection (SD) mode enable */

#define USB_GCCFG_I2CPADEN_Pos   (17U)
#define USB_GCCFG_I2CPADEN_Msk   (0x1UL << USB_GCCFG_I2CPADEN_Pos) /*!< Enable I2C bus connection for the external I2C PHY interface*/
#define USB_GCCFG_VBUSASEN_Pos   (18U)
#define USB_GCCFG_VBUSASEN_Msk   (0x1UL << USB_GCCFG_VBUSASEN_Pos) /*!< Enable the VBUS sensing device */
#define USB_GCCFG_VBUSBSEN_Pos   (19U)
#define USB_GCCFG_VBUSBSEN_Msk   (0x1UL << USB_GCCFG_VBUSBSEN_Pos) /*!< Enable the VBUS sensing device */
#define USB_GCCFG_SOFOUTEN_Pos   (20U)
#define USB_GCCFG_SOFOUTEN_Msk   (0x1UL << USB_GCCFG_SOFOUTEN_Pos) /*!< sof output enable */
#define USB_GCCFG_NOVBUSSENS_Pos (21U)
#define USB_GCCFG_NOVBUSSENS_Msk (0x1UL << USB_GCCFG_NOVBUSSENS_Pos) /*!< VBUS sensing disable option*/

/********************  Bit definition forUSB_GPWRDN) register  ********************/
#define USB_GPWRDN_ADPMEN_Pos (0U)
#define USB_GPWRDN_ADPMEN_Msk (0x1UL << USB_GPWRDN_ADPMEN_Pos) /*!< ADP module enable */
#define USB_GPWRDN_ADPIF_Pos  (23U)
#define USB_GPWRDN_ADPIF_Msk  (0x1UL << USB_GPWRDN_ADPIF_Pos) /*!< ADP Interrupt flag */

/********************  Bit definition forUSB_DEACHINTMSK register  ********************/
#define USB_DEACHINTMSK_IEP1INTM_Pos (1U)
#define USB_DEACHINTMSK_IEP1INTM_Msk (0x1UL << USB_DEACHINTMSK_IEP1INTM_Pos) /*!< IN Endpoint 1 interrupt mask bit  */
#define USB_DEACHINTMSK_OEP1INTM_Pos (17U)
#define USB_DEACHINTMSK_OEP1INTM_Msk (0x1UL << USB_DEACHINTMSK_OEP1INTM_Pos) /*!< OUT Endpoint 1 interrupt mask bit */

/********************  Bit definition for USB_CID register  ********************/
#define USB_CID_PRODUCT_ID_Pos (0U)
#define USB_CID_PRODUCT_ID_Msk (0xFFFFFFFFUL << USB_CID_PRODUCT_ID_Pos) /*!< Product ID field */

/********************  Bit definition for USB_GLPMCFG register  ********************/
#define USB_GLPMCFG_LPMEN_Pos      (0U)
#define USB_GLPMCFG_LPMEN_Msk      (0x1UL << USB_GLPMCFG_LPMEN_Pos) /*!< LPM support enable */
#define USB_GLPMCFG_LPMACK_Pos     (1U)
#define USB_GLPMCFG_LPMACK_Msk     (0x1UL << USB_GLPMCFG_LPMACK_Pos) /*!< LPM Token acknowledge enable */
#define USB_GLPMCFG_BESL_Pos       (2U)
#define USB_GLPMCFG_BESL_Msk       (0xFUL << USB_GLPMCFG_BESL_Pos) /*!< BESL value received with last ACKed LPM Token */
#define USB_GLPMCFG_REMWAKE_Pos    (6U)
#define USB_GLPMCFG_REMWAKE_Msk    (0x1UL << USB_GLPMCFG_REMWAKE_Pos) /*!< bRemoteWake value received with last ACKed LPM Token */
#define USB_GLPMCFG_L1SSEN_Pos     (7U)
#define USB_GLPMCFG_L1SSEN_Msk     (0x1UL << USB_GLPMCFG_L1SSEN_Pos) /*!< L1 shallow sleep enable */
#define USB_GLPMCFG_BESLTHRS_Pos   (8U)
#define USB_GLPMCFG_BESLTHRS_Msk   (0xFUL << USB_GLPMCFG_BESLTHRS_Pos) /*!< BESL threshold */
#define USB_GLPMCFG_L1DSEN_Pos     (12U)
#define USB_GLPMCFG_L1DSEN_Msk     (0x1UL << USB_GLPMCFG_L1DSEN_Pos) /*!< L1 deep sleep enable */
#define USB_GLPMCFG_LPMRSP_Pos     (13U)
#define USB_GLPMCFG_LPMRSP_Msk     (0x3UL << USB_GLPMCFG_LPMRSP_Pos) /*!< LPM response */
#define USB_GLPMCFG_SLPSTS_Pos     (15U)
#define USB_GLPMCFG_SLPSTS_Msk     (0x1UL << USB_GLPMCFG_SLPSTS_Pos) /*!< Port sleep status */
#define USB_GLPMCFG_L1RSMOK_Pos    (16U)
#define USB_GLPMCFG_L1RSMOK_Msk    (0x1UL << USB_GLPMCFG_L1RSMOK_Pos) /*!< Sleep State Resume OK */
#define USB_GLPMCFG_LPMCHIDX_Pos   (17U)
#define USB_GLPMCFG_LPMCHIDX_Msk   (0xFUL << USB_GLPMCFG_LPMCHIDX_Pos) /*!< LPM Channel Index */
#define USB_GLPMCFG_LPMRCNT_Pos    (21U)
#define USB_GLPMCFG_LPMRCNT_Msk    (0x7UL << USB_GLPMCFG_LPMRCNT_Pos) /*!< LPM retry count */
#define USB_GLPMCFG_SNDLPM_Pos     (24U)
#define USB_GLPMCFG_SNDLPM_Msk     (0x1UL << USB_GLPMCFG_SNDLPM_Pos) /*!< Send LPM transaction */
#define USB_GLPMCFG_LPMRCNTSTS_Pos (25U)
#define USB_GLPMCFG_LPMRCNTSTS_Msk (0x7UL << USB_GLPMCFG_LPMRCNTSTS_Pos) /*!< LPM retry count status */
#define USB_GLPMCFG_ENBESL_Pos     (28U)
#define USB_GLPMCFG_ENBESL_Msk     (0x1UL << USB_GLPMCFG_ENBESL_Pos) /*!< Enable best effort service latency */

/********************  Bit definition for USB_DIEPEACHMSK1 register  ********************/
#define USB_DIEPEACHMSK1_XFRCM_Pos     (0U)
#define USB_DIEPEACHMSK1_XFRCM_Msk     (0x1UL << USB_DIEPEACHMSK1_XFRCM_Pos) /*!< Transfer completed interrupt mask */
#define USB_DIEPEACHMSK1_EPDM_Pos      (1U)
#define USB_DIEPEACHMSK1_EPDM_Msk      (0x1UL << USB_DIEPEACHMSK1_EPDM_Pos) /*!< Endpoint disabled interrupt mask */
#define USB_DIEPEACHMSK1_TOM_Pos       (3U)
#define USB_DIEPEACHMSK1_TOM_Msk       (0x1UL << USB_DIEPEACHMSK1_TOM_Pos) /*!< Timeout condition mask (nonisochronous endpoints) */
#define USB_DIEPEACHMSK1_ITTXFEMSK_Pos (4U)
#define USB_DIEPEACHMSK1_ITTXFEMSK_Msk (0x1UL << USB_DIEPEACHMSK1_ITTXFEMSK_Pos) /*!< IN token received when TxFIFO empty mask */
#define USB_DIEPEACHMSK1_INEPNMM_Pos   (5U)
#define USB_DIEPEACHMSK1_INEPNMM_Msk   (0x1UL << USB_DIEPEACHMSK1_INEPNMM_Pos) /*!< IN token received with EP mismatch mask */
#define USB_DIEPEACHMSK1_INEPNEM_Pos   (6U)
#define USB_DIEPEACHMSK1_INEPNEM_Msk   (0x1UL << USB_DIEPEACHMSK1_INEPNEM_Pos) /*!< IN endpoint NAK effective mask */
#define USB_DIEPEACHMSK1_TXFURM_Pos    (8U)
#define USB_DIEPEACHMSK1_TXFURM_Msk    (0x1UL << USB_DIEPEACHMSK1_TXFURM_Pos) /*!< FIFO underrun mask */
#define USB_DIEPEACHMSK1_BIM_Pos       (9U)
#define USB_DIEPEACHMSK1_BIM_Msk       (0x1UL << USB_DIEPEACHMSK1_BIM_Pos) /*!< BNA interrupt mask */
#define USB_DIEPEACHMSK1_NAKM_Pos      (13U)
#define USB_DIEPEACHMSK1_NAKM_Msk      (0x1UL << USB_DIEPEACHMSK1_NAKM_Pos) /*!< NAK interrupt mask */

/********************  Bit definition for USB_HPRT register  ********************/
#define USB_HPRT_PCSTS_Pos   (0U)
#define USB_HPRT_PCSTS_Msk   (0x1UL << USB_HPRT_PCSTS_Pos) /*!< Port connect status */
#define USB_HPRT_PCDET_Pos   (1U)
#define USB_HPRT_PCDET_Msk   (0x1UL << USB_HPRT_PCDET_Pos) /*!< Port connect detected */
#define USB_HPRT_PENA_Pos    (2U)
#define USB_HPRT_PENA_Msk    (0x1UL << USB_HPRT_PENA_Pos) /*!< Port enable */
#define USB_HPRT_PENCHNG_Pos (3U)
#define USB_HPRT_PENCHNG_Msk (0x1UL << USB_HPRT_PENCHNG_Pos) /*!< Port enable/disable change */
#define USB_HPRT_POCA_Pos    (4U)
#define USB_HPRT_POCA_Msk    (0x1UL << USB_HPRT_POCA_Pos) /*!< Port overcurrent active */
#define USB_HPRT_POCCHNG_Pos (5U)
#define USB_HPRT_POCCHNG_Msk (0x1UL << USB_HPRT_POCCHNG_Pos) /*!< Port overcurrent change */
#define USB_HPRT_PRES_Pos    (6U)
#define USB_HPRT_PRES_Msk    (0x1UL << USB_HPRT_PRES_Pos) /*!< Port resume */
#define USB_HPRT_PSUSP_Pos   (7U)
#define USB_HPRT_PSUSP_Msk   (0x1UL << USB_HPRT_PSUSP_Pos) /*!< Port suspend */
#define USB_HPRT_PRST_Pos    (8U)
#define USB_HPRT_PRST_Msk    (0x1UL << USB_HPRT_PRST_Pos) /*!< Port reset */

#define USB_HPRT_PLSTS_Pos (10U)
#define USB_HPRT_PLSTS_Msk (0x3UL << USB_HPRT_PLSTS_Pos) /*!< Port line status */
#define USB_HPRT_PLSTS_0   (0x1UL << USB_HPRT_PLSTS_Pos) /*!< 0x00000400 */
#define USB_HPRT_PLSTS_1   (0x2UL << USB_HPRT_PLSTS_Pos) /*!< 0x00000800 */
#define USB_HPRT_PPWR_Pos  (12U)
#define USB_HPRT_PPWR_Msk  (0x1UL << USB_HPRT_PPWR_Pos) /*!< Port power */
#define USB_HPRT_PTCTL_Pos (13U)
#define USB_HPRT_PTCTL_Msk (0xFUL << USB_HPRT_PTCTL_Pos) /*!< Port test control */
#define USB_HPRT_PTCTL_0   (0x1UL << USB_HPRT_PTCTL_Pos) /*!< 0x00002000 */
#define USB_HPRT_PTCTL_1   (0x2UL << USB_HPRT_PTCTL_Pos) /*!< 0x00004000 */
#define USB_HPRT_PTCTL_2   (0x4UL << USB_HPRT_PTCTL_Pos) /*!< 0x00008000 */
#define USB_HPRT_PTCTL_3   (0x8UL << USB_HPRT_PTCTL_Pos) /*!< 0x00010000 */

#define USB_HPRT_PSPD_Pos (17U)
#define USB_HPRT_PSPD_Msk (0x3UL << USB_HPRT_PSPD_Pos) /*!< Port speed */
#define USB_HPRT_PSPD_0   (0x1UL << USB_HPRT_PSPD_Pos) /*!< 0x00020000 */
#define USB_HPRT_PSPD_1   (0x2UL << USB_HPRT_PSPD_Pos) /*!< 0x00040000 */

/********************  Bit definition for USB_DOEPEACHMSK1 register  ********************/
#define USB_DOEPEACHMSK1_XFRCM_Pos     (0U)
#define USB_DOEPEACHMSK1_XFRCM_Msk     (0x1UL << USB_DOEPEACHMSK1_XFRCM_Pos) /*!< Transfer completed interrupt mask */
#define USB_DOEPEACHMSK1_EPDM_Pos      (1U)
#define USB_DOEPEACHMSK1_EPDM_Msk      (0x1UL << USB_DOEPEACHMSK1_EPDM_Pos) /*!< Endpoint disabled interrupt mask */
#define USB_DOEPEACHMSK1_TOM_Pos       (3U)
#define USB_DOEPEACHMSK1_TOM_Msk       (0x1UL << USB_DOEPEACHMSK1_TOM_Pos) /*!< Timeout condition mask */
#define USB_DOEPEACHMSK1_ITTXFEMSK_Pos (4U)
#define USB_DOEPEACHMSK1_ITTXFEMSK_Msk (0x1UL << USB_DOEPEACHMSK1_ITTXFEMSK_Pos) /*!< IN token received when TxFIFO empty mask  */
#define USB_DOEPEACHMSK1_INEPNMM_Pos   (5U)
#define USB_DOEPEACHMSK1_INEPNMM_Msk   (0x1UL << USB_DOEPEACHMSK1_INEPNMM_Pos) /*!< IN token received with EP mismatch mask */
#define USB_DOEPEACHMSK1_INEPNEM_Pos   (6U)
#define USB_DOEPEACHMSK1_INEPNEM_Msk   (0x1UL << USB_DOEPEACHMSK1_INEPNEM_Pos) /*!< IN endpoint NAK effective mask */
#define USB_DOEPEACHMSK1_TXFURM_Pos    (8U)
#define USB_DOEPEACHMSK1_TXFURM_Msk    (0x1UL << USB_DOEPEACHMSK1_TXFURM_Pos) /*!< OUT packet error mask */
#define USB_DOEPEACHMSK1_BIM_Pos       (9U)
#define USB_DOEPEACHMSK1_BIM_Msk       (0x1UL << USB_DOEPEACHMSK1_BIM_Pos) /*!< BNA interrupt mask */
#define USB_DOEPEACHMSK1_BERRM_Pos     (12U)
#define USB_DOEPEACHMSK1_BERRM_Msk     (0x1UL << USB_DOEPEACHMSK1_BERRM_Pos) /*!< Bubble error interrupt mask */
#define USB_DOEPEACHMSK1_NAKM_Pos      (13U)
#define USB_DOEPEACHMSK1_NAKM_Msk      (0x1UL << USB_DOEPEACHMSK1_NAKM_Pos) /*!< NAK interrupt mask */
#define USB_DOEPEACHMSK1_NYETM_Pos     (14U)
#define USB_DOEPEACHMSK1_NYETM_Msk     (0x1UL << USB_DOEPEACHMSK1_NYETM_Pos) /*!< NYET interrupt mask */

/********************  Bit definition for USB_HPTXFSIZ register  ********************/
#define USB_HPTXFSIZ_PTXSA_Pos (0U)
#define USB_HPTXFSIZ_PTXSA_Msk (0xFFFFUL << USB_HPTXFSIZ_PTXSA_Pos) /*!< Host periodic TxFIFO start address */
#define USB_HPTXFSIZ_PTXFD_Pos (16U)
#define USB_HPTXFSIZ_PTXFD_Msk (0xFFFFUL << USB_HPTXFSIZ_PTXFD_Pos) /*!< Host periodic TxFIFO depth */

/********************  Bit definition for USB_DIEPCTL register  ********************/
#define USB_DIEPCTL_MPSIZ_Pos          (0U)
#define USB_DIEPCTL_MPSIZ_Msk          (0x7FFUL << USB_DIEPCTL_MPSIZ_Pos) /*!< Maximum packet size */
#define USB_DIEPCTL_USBAEP_Pos         (15U)
#define USB_DIEPCTL_USBAEP_Msk         (0x1UL << USB_DIEPCTL_USBAEP_Pos) /*!< USB active endpoint */
#define USB_DIEPCTL_EONUM_DPID_Pos     (16U)
#define USB_DIEPCTL_EONUM_DPID_Msk     (0x1UL << USB_DIEPCTL_EONUM_DPID_Pos) /*!< Even/odd frame */
#define USB_DIEPCTL_NAKSTS_Pos         (17U)
#define USB_DIEPCTL_NAKSTS_Msk         (0x1UL << USB_DIEPCTL_NAKSTS_Pos) /*!< NAK status */
#define USB_DIEPCTL_EPTYP_Pos          (18U)
#define USB_DIEPCTL_EPTYP_Msk          (0x3UL << USB_DIEPCTL_EPTYP_Pos) /*!< Endpoint type */
#define USB_DIEPCTL_EPTYP_0            (0x1UL << USB_DIEPCTL_EPTYP_Pos) /*!< 0x00040000 */
#define USB_DIEPCTL_EPTYP_1            (0x2UL << USB_DIEPCTL_EPTYP_Pos) /*!< 0x00080000 */
#define USB_DIEPCTL_STALL_Pos          (21U)
#define USB_DIEPCTL_STALL_Msk          (0x1UL << USB_DIEPCTL_STALL_Pos) /*!< STALL handshake */
#define USB_DIEPCTL_TXFNUM_Pos         (22U)
#define USB_DIEPCTL_TXFNUM_Msk         (0xFUL << USB_DIEPCTL_TXFNUM_Pos) /*!< TxFIFO number */
#define USB_DIEPCTL_TXFNUM_0           (0x1UL << USB_DIEPCTL_TXFNUM_Pos) /*!< 0x00400000 */
#define USB_DIEPCTL_TXFNUM_1           (0x2UL << USB_DIEPCTL_TXFNUM_Pos) /*!< 0x00800000 */
#define USB_DIEPCTL_TXFNUM_2           (0x4UL << USB_DIEPCTL_TXFNUM_Pos) /*!< 0x01000000 */
#define USB_DIEPCTL_TXFNUM_3           (0x8UL << USB_DIEPCTL_TXFNUM_Pos) /*!< 0x02000000 */
#define USB_DIEPCTL_CNAK_Pos           (26U)
#define USB_DIEPCTL_CNAK_Msk           (0x1UL << USB_DIEPCTL_CNAK_Pos) /*!< Clear NAK */
#define USB_DIEPCTL_SNAK_Pos           (27U)
#define USB_DIEPCTL_SNAK_Msk           (0x1UL << USB_DIEPCTL_SNAK_Pos) /*!< Set NAK */
#define USB_DIEPCTL_SD0PID_SEVNFRM_Pos (28U)
#define USB_DIEPCTL_SD0PID_SEVNFRM_Msk (0x1UL << USB_DIEPCTL_SD0PID_SEVNFRM_Pos) /*!< Set DATA0 PID */
#define USB_DIEPCTL_SODDFRM_Pos        (29U)
#define USB_DIEPCTL_SODDFRM_Msk        (0x1UL << USB_DIEPCTL_SODDFRM_Pos) /*!< Set odd frame */
#define USB_DIEPCTL_EPDIS_Pos          (30U)
#define USB_DIEPCTL_EPDIS_Msk          (0x1UL << USB_DIEPCTL_EPDIS_Pos) /*!< Endpoint disable */
#define USB_DIEPCTL_EPENA_Pos          (31U)
#define USB_DIEPCTL_EPENA_Msk          (0x1UL << USB_DIEPCTL_EPENA_Pos) /*!< Endpoint enable */

/********************  Bit definition for USB_HCCHAR register  ********************/
#define USB_HCCHAR_MPSIZ_Pos (0U)
#define USB_HCCHAR_MPSIZ_Msk (0x7FFUL << USB_HCCHAR_MPSIZ_Pos) /*!< Maximum packet size */

#define USB_HCCHAR_EPNUM_Pos (11U)
#define USB_HCCHAR_EPNUM_Msk (0xFUL << USB_HCCHAR_EPNUM_Pos) /*!< Endpoint number */
#define USB_HCCHAR_EPNUM_0   (0x1UL << USB_HCCHAR_EPNUM_Pos) /*!< 0x00000800 */
#define USB_HCCHAR_EPNUM_1   (0x2UL << USB_HCCHAR_EPNUM_Pos) /*!< 0x00001000 */
#define USB_HCCHAR_EPNUM_2   (0x4UL << USB_HCCHAR_EPNUM_Pos) /*!< 0x00002000 */
#define USB_HCCHAR_EPNUM_3   (0x8UL << USB_HCCHAR_EPNUM_Pos) /*!< 0x00004000 */
#define USB_HCCHAR_EPDIR_Pos (15U)
#define USB_HCCHAR_EPDIR_Msk (0x1UL << USB_HCCHAR_EPDIR_Pos) /*!< Endpoint direction */
#define USB_HCCHAR_LSDEV_Pos (17U)
#define USB_HCCHAR_LSDEV_Msk (0x1UL << USB_HCCHAR_LSDEV_Pos) /*!< Low-speed device */
#define USB_HCCHAR_EPTYP_Pos (18U)
#define USB_HCCHAR_EPTYP_Msk (0x3UL << USB_HCCHAR_EPTYP_Pos) /*!< Endpoint type */
#define USB_HCCHAR_EPTYP_0   (0x1UL << USB_HCCHAR_EPTYP_Pos) /*!< 0x00040000 */
#define USB_HCCHAR_EPTYP_1   (0x2UL << USB_HCCHAR_EPTYP_Pos) /*!< 0x00080000 */

#define USB_HCCHAR_MC_Pos (20U)
#define USB_HCCHAR_MC_Msk (0x3UL << USB_HCCHAR_MC_Pos) /*!< Multi Count (MC) / Error Count (EC) */
#define USB_HCCHAR_MC_0   (0x1UL << USB_HCCHAR_MC_Pos) /*!< 0x00100000 */
#define USB_HCCHAR_MC_1   (0x1UL << USB_HCCHAR_MC_Pos) /*!< 0x00100000 */
#define USB_HCCHAR_MC_2   (0x2UL << USB_HCCHAR_MC_Pos) /*!< 0x00200000 */
#define USB_HCCHAR_MC_3   (0x3UL << USB_HCCHAR_MC_Pos) /*!< 0x00300000 */

#define USB_HCCHAR_DAD_Pos    (22U)
#define USB_HCCHAR_DAD_Msk    (0x7FUL << USB_HCCHAR_DAD_Pos) /*!< Device address */
#define USB_HCCHAR_DAD_0      (0x01UL << USB_HCCHAR_DAD_Pos) /*!< 0x00400000 */
#define USB_HCCHAR_DAD_1      (0x02UL << USB_HCCHAR_DAD_Pos) /*!< 0x00800000 */
#define USB_HCCHAR_DAD_2      (0x04UL << USB_HCCHAR_DAD_Pos) /*!< 0x01000000 */
#define USB_HCCHAR_DAD_3      (0x08UL << USB_HCCHAR_DAD_Pos) /*!< 0x02000000 */
#define USB_HCCHAR_DAD_4      (0x10UL << USB_HCCHAR_DAD_Pos) /*!< 0x04000000 */
#define USB_HCCHAR_DAD_5      (0x20UL << USB_HCCHAR_DAD_Pos) /*!< 0x08000000 */
#define USB_HCCHAR_DAD_6      (0x40UL << USB_HCCHAR_DAD_Pos) /*!< 0x10000000 */
#define USB_HCCHAR_ODDFRM_Pos (29U)
#define USB_HCCHAR_ODDFRM_Msk (0x1UL << USB_HCCHAR_ODDFRM_Pos) /*!< Odd frame */
#define USB_HCCHAR_CHDIS_Pos  (30U)
#define USB_HCCHAR_CHDIS_Msk  (0x1UL << USB_HCCHAR_CHDIS_Pos) /*!< Channel disable */
#define USB_HCCHAR_CHENA_Pos  (31U)
#define USB_HCCHAR_CHENA_Msk  (0x1UL << USB_HCCHAR_CHENA_Pos) /*!< Channel enable */

/********************  Bit definition for USB_HCSPLT register  ********************/
#define USB_HCSPLT_PRTADDR_Pos (0U)
#define USB_HCSPLT_PRTADDR_Msk (0x7FUL << USB_HCSPLT_PRTADDR_Pos) /*!< Port address */
#define USB_HCSPLT_PRTADDR_0   (0x01UL << USB_HCSPLT_PRTADDR_Pos) /*!< 0x00000001 */
#define USB_HCSPLT_PRTADDR_1   (0x02UL << USB_HCSPLT_PRTADDR_Pos) /*!< 0x00000002 */
#define USB_HCSPLT_PRTADDR_2   (0x04UL << USB_HCSPLT_PRTADDR_Pos) /*!< 0x00000004 */
#define USB_HCSPLT_PRTADDR_3   (0x08UL << USB_HCSPLT_PRTADDR_Pos) /*!< 0x00000008 */
#define USB_HCSPLT_PRTADDR_4   (0x10UL << USB_HCSPLT_PRTADDR_Pos) /*!< 0x00000010 */
#define USB_HCSPLT_PRTADDR_5   (0x20UL << USB_HCSPLT_PRTADDR_Pos) /*!< 0x00000020 */
#define USB_HCSPLT_PRTADDR_6   (0x40UL << USB_HCSPLT_PRTADDR_Pos) /*!< 0x00000040 */

#define USB_HCSPLT_HUBADDR_Pos (7U)
#define USB_HCSPLT_HUBADDR_Msk (0x7FUL << USB_HCSPLT_HUBADDR_Pos) /*!< Hub address */
#define USB_HCSPLT_HUBADDR_0   (0x01UL << USB_HCSPLT_HUBADDR_Pos) /*!< 0x00000080 */
#define USB_HCSPLT_HUBADDR_1   (0x02UL << USB_HCSPLT_HUBADDR_Pos) /*!< 0x00000100 */
#define USB_HCSPLT_HUBADDR_2   (0x04UL << USB_HCSPLT_HUBADDR_Pos) /*!< 0x00000200 */
#define USB_HCSPLT_HUBADDR_3   (0x08UL << USB_HCSPLT_HUBADDR_Pos) /*!< 0x00000400 */
#define USB_HCSPLT_HUBADDR_4   (0x10UL << USB_HCSPLT_HUBADDR_Pos) /*!< 0x00000800 */
#define USB_HCSPLT_HUBADDR_5   (0x20UL << USB_HCSPLT_HUBADDR_Pos) /*!< 0x00001000 */
#define USB_HCSPLT_HUBADDR_6   (0x40UL << USB_HCSPLT_HUBADDR_Pos) /*!< 0x00002000 */

#define USB_HCSPLT_XACTPOS_Pos   (14U)
#define USB_HCSPLT_XACTPOS_Msk   (0x3UL << USB_HCSPLT_XACTPOS_Pos) /*!< XACTPOS */
#define USB_HCSPLT_XACTPOS_0     (0x1UL << USB_HCSPLT_XACTPOS_Pos) /*!< 0x00004000 */
#define USB_HCSPLT_XACTPOS_1     (0x2UL << USB_HCSPLT_XACTPOS_Pos) /*!< 0x00008000 */
#define USB_HCSPLT_COMPLSPLT_Pos (16U)
#define USB_HCSPLT_COMPLSPLT_Msk (0x1UL << USB_HCSPLT_COMPLSPLT_Pos) /*!< Do complete split */
#define USB_HCSPLT_SPLITEN_Pos   (31U)
#define USB_HCSPLT_SPLITEN_Msk   (0x1UL << USB_HCSPLT_SPLITEN_Pos) /*!< Split enable */

/********************  Bit definition for USB_HCINT register  ********************/
#define USB_HCINT_XFRC_Pos   (0U)
#define USB_HCINT_XFRC_Msk   (0x1UL << USB_HCINT_XFRC_Pos) /*!< Transfer completed */
#define USB_HCINT_CHH_Pos    (1U)
#define USB_HCINT_CHH_Msk    (0x1UL << USB_HCINT_CHH_Pos) /*!< Channel halted */
#define USB_HCINT_AHBERR_Pos (2U)
#define USB_HCINT_AHBERR_Msk (0x1UL << USB_HCINT_AHBERR_Pos) /*!< AHB error */
#define USB_HCINT_STALL_Pos  (3U)
#define USB_HCINT_STALL_Msk  (0x1UL << USB_HCINT_STALL_Pos) /*!< STALL response received interrupt */
#define USB_HCINT_NAK_Pos    (4U)
#define USB_HCINT_NAK_Msk    (0x1UL << USB_HCINT_NAK_Pos) /*!< NAK response received interrupt */
#define USB_HCINT_ACK_Pos    (5U)
#define USB_HCINT_ACK_Msk    (0x1UL << USB_HCINT_ACK_Pos) /*!< ACK response received/transmitted interrupt */
#define USB_HCINT_NYET_Pos   (6U)
#define USB_HCINT_NYET_Msk   (0x1UL << USB_HCINT_NYET_Pos) /*!< Response received interrupt */
#define USB_HCINT_TXERR_Pos  (7U)
#define USB_HCINT_TXERR_Msk  (0x1UL << USB_HCINT_TXERR_Pos) /*!< Transaction error */
#define USB_HCINT_BBERR_Pos  (8U)
#define USB_HCINT_BBERR_Msk  (0x1UL << USB_HCINT_BBERR_Pos) /*!< Babble error */
#define USB_HCINT_FRMOR_Pos  (9U)
#define USB_HCINT_FRMOR_Msk  (0x1UL << USB_HCINT_FRMOR_Pos) /*!< Frame overrun */
#define USB_HCINT_DTERR_Pos  (10U)
#define USB_HCINT_DTERR_Msk  (0x1UL << USB_HCINT_DTERR_Pos) /*!< Data toggle error */

/********************  Bit definition for USB_DIEPINT register  ********************/
#define USB_DIEPINT_XFRC_Pos       (0U)
#define USB_DIEPINT_XFRC_Msk       (0x1UL << USB_DIEPINT_XFRC_Pos) /*!< Transfer completed interrupt */
#define USB_DIEPINT_EPDISD_Pos     (1U)
#define USB_DIEPINT_EPDISD_Msk     (0x1UL << USB_DIEPINT_EPDISD_Pos) /*!< Endpoint disabled interrupt */
#define USB_DIEPINT_AHBERR_Pos     (2U)
#define USB_DIEPINT_AHBERR_Msk     (0x1UL << USB_DIEPINT_AHBERR_Pos) /*!< AHB Error (AHBErr) during an IN transaction */
#define USB_DIEPINT_TOC_Pos        (3U)
#define USB_DIEPINT_TOC_Msk        (0x1UL << USB_DIEPINT_TOC_Pos) /*!< Timeout condition */
#define USB_DIEPINT_ITTXFE_Pos     (4U)
#define USB_DIEPINT_ITTXFE_Msk     (0x1UL << USB_DIEPINT_ITTXFE_Pos) /*!< IN token received when TxFIFO is empty */
#define USB_DIEPINT_INEPNM_Pos     (5U)
#define USB_DIEPINT_INEPNM_Msk     (0x1UL << USB_DIEPINT_INEPNM_Pos) /*!< IN token received with EP mismatch */
#define USB_DIEPINT_INEPNE_Pos     (6U)
#define USB_DIEPINT_INEPNE_Msk     (0x1UL << USB_DIEPINT_INEPNE_Pos) /*!< IN endpoint NAK effective */
#define USB_DIEPINT_TXFE_Pos       (7U)
#define USB_DIEPINT_TXFE_Msk       (0x1UL << USB_DIEPINT_TXFE_Pos) /*!< Transmit FIFO empty */
#define USB_DIEPINT_TXFIFOUDRN_Pos (8U)
#define USB_DIEPINT_TXFIFOUDRN_Msk (0x1UL << USB_DIEPINT_TXFIFOUDRN_Pos) /*!< Transmit Fifo Underrun */
#define USB_DIEPINT_BNA_Pos        (9U)
#define USB_DIEPINT_BNA_Msk        (0x1UL << USB_DIEPINT_BNA_Pos) /*!< Buffer not available interrupt */
#define USB_DIEPINT_PKTDRPSTS_Pos  (11U)
#define USB_DIEPINT_PKTDRPSTS_Msk  (0x1UL << USB_DIEPINT_PKTDRPSTS_Pos) /*!< Packet dropped status */
#define USB_DIEPINT_BERR_Pos       (12U)
#define USB_DIEPINT_BERR_Msk       (0x1UL << USB_DIEPINT_BERR_Pos) /*!< Babble error interrupt */
#define USB_DIEPINT_NAK_Pos        (13U)
#define USB_DIEPINT_NAK_Msk        (0x1UL << USB_DIEPINT_NAK_Pos) /*!< NAK interrupt */

/********************  Bit definition forUSB_HCINTMSK register  ********************/
#define USB_HCINTMSK_XFRCM_Pos  (0U)
#define USB_HCINTMSK_XFRCM_Msk  (0x1UL << USB_HCINTMSK_XFRCM_Pos) /*!< Transfer completed mask */
#define USB_HCINTMSK_CHHM_Pos   (1U)
#define USB_HCINTMSK_CHHM_Msk   (0x1UL << USB_HCINTMSK_CHHM_Pos) /*!< Channel halted mask */
#define USB_HCINTMSK_AHBERR_Pos (2U)
#define USB_HCINTMSK_AHBERR_Msk (0x1UL << USB_HCINTMSK_AHBERR_Pos) /*!< AHB error */
#define USB_HCINTMSK_STALLM_Pos (3U)
#define USB_HCINTMSK_STALLM_Msk (0x1UL << USB_HCINTMSK_STALLM_Pos) /*!< STALL response received interrupt mask */
#define USB_HCINTMSK_NAKM_Pos   (4U)
#define USB_HCINTMSK_NAKM_Msk   (0x1UL << USB_HCINTMSK_NAKM_Pos) /*!< NAK response received interrupt mask */
#define USB_HCINTMSK_ACKM_Pos   (5U)
#define USB_HCINTMSK_ACKM_Msk   (0x1UL << USB_HCINTMSK_ACKM_Pos) /*!< ACK response received/transmitted interrupt mask */
#define USB_HCINTMSK_NYET_Pos   (6U)
#define USB_HCINTMSK_NYET_Msk   (0x1UL << USB_HCINTMSK_NYET_Pos) /*!< response received interrupt mask */
#define USB_HCINTMSK_TXERRM_Pos (7U)
#define USB_HCINTMSK_TXERRM_Msk (0x1UL << USB_HCINTMSK_TXERRM_Pos) /*!< Transaction error mask */
#define USB_HCINTMSK_BBERRM_Pos (8U)
#define USB_HCINTMSK_BBERRM_Msk (0x1UL << USB_HCINTMSK_BBERRM_Pos) /*!< Babble error mask */
#define USB_HCINTMSK_FRMORM_Pos (9U)
#define USB_HCINTMSK_FRMORM_Msk (0x1UL << USB_HCINTMSK_FRMORM_Pos) /*!< Frame overrun mask */
#define USB_HCINTMSK_DTERRM_Pos (10U)
#define USB_HCINTMSK_DTERRM_Msk (0x1UL << USB_HCINTMSK_DTERRM_Pos) /*!< Data toggle error mask */

/********************  Bit definition for USB_DIEPTSIZ register  ********************/
#define USB_DIEPTSIZ_XFRSIZ_Pos (0U)
#define USB_DIEPTSIZ_XFRSIZ_Msk (0x7FFFFUL << USB_DIEPTSIZ_XFRSIZ_Pos) /*!< Transfer size */
#define USB_DIEPTSIZ_PKTCNT_Pos (19U)
#define USB_DIEPTSIZ_PKTCNT_Msk (0x3FFUL << USB_DIEPTSIZ_PKTCNT_Pos) /*!< Packet count */
#define USB_DIEPTSIZ_MULCNT_Pos (29U)
#define USB_DIEPTSIZ_MULCNT_Msk (0x3UL << USB_DIEPTSIZ_MULCNT_Pos) /*!< Packet count */

/********************  Bit definition for USB_HCTSIZ register  ********************/
#define USB_HCTSIZ_XFRSIZ_Pos (0U)
#define USB_HCTSIZ_XFRSIZ_Msk (0x7FFFFUL << USB_HCTSIZ_XFRSIZ_Pos) /*!< Transfer size */
#define USB_HCTSIZ_PKTCNT_Pos (19U)
#define USB_HCTSIZ_PKTCNT_Msk (0x3FFUL << USB_HCTSIZ_PKTCNT_Pos) /*!< Packet count */
#define USB_HCTSIZ_DOPING_Pos (31U)
#define USB_HCTSIZ_DOPING_Msk (0x1UL << USB_HCTSIZ_DOPING_Pos) /*!< Do PING */
#define USB_HCTSIZ_DPID_Pos   (29U)
#define USB_HCTSIZ_DPID_Msk   (0x3UL << USB_HCTSIZ_DPID_Pos) /*!< Data PID */
#define USB_HCTSIZ_DPID_0     (0x1UL << USB_HCTSIZ_DPID_Pos) /*!< 0x20000000 */
#define USB_HCTSIZ_DPID_1     (0x2UL << USB_HCTSIZ_DPID_Pos) /*!< 0x40000000 */

/********************  Bit definition for USB_DIEPDMA register  ********************/
#define USB_DIEPDMA_DMAADDR_Pos (0U)
#define USB_DIEPDMA_DMAADDR_Msk (0xFFFFFFFFUL << USB_DIEPDMA_DMAADDR_Pos) /*!< DMA address */

/********************  Bit definition for USB_HCDMA register  ********************/
#define USB_HCDMA_DMAADDR_Pos (0U)
#define USB_HCDMA_DMAADDR_Msk (0xFFFFFFFFUL << USB_HCDMA_DMAADDR_Pos) /*!< DMA address */

/********************  Bit definition for USB_DTXFSTS register  ********************/
#define USB_DTXFSTS_INEPTFSAV_Pos (0U)
#define USB_DTXFSTS_INEPTFSAV_Msk (0xFFFFUL << USB_DTXFSTS_INEPTFSAV_Pos) /*!< IN endpoint TxFIFO space available */

/********************  Bit definition for USB_DIEPTXF register  ********************/
#define USB_DIEPTXF_INEPTXSA_Pos (0U)
#define USB_DIEPTXF_INEPTXSA_Msk (0xFFFFUL << USB_DIEPTXF_INEPTXSA_Pos) /*!< IN endpoint FIFOx transmit RAM start address */
#define USB_DIEPTXF_INEPTXFD_Pos (16U)
#define USB_DIEPTXF_INEPTXFD_Msk (0xFFFFUL << USB_DIEPTXF_INEPTXFD_Pos) /*!< IN endpoint TxFIFO depth */

/********************  Bit definition for USB_DOEPCTL register  ********************/
#define USB_DOEPCTL_MPSIZ_Pos          (0U)
#define USB_DOEPCTL_MPSIZ_Msk          (0x7FFUL << USB_DOEPCTL_MPSIZ_Pos) /*!< Maximum packet size */
#define USB_DOEPCTL_USBAEP_Pos         (15U)
#define USB_DOEPCTL_USBAEP_Msk         (0x1UL << USB_DOEPCTL_USBAEP_Pos) /*!< USB active endpoint */
#define USB_DOEPCTL_NAKSTS_Pos         (17U)
#define USB_DOEPCTL_NAKSTS_Msk         (0x1UL << USB_DOEPCTL_NAKSTS_Pos) /*!< NAK status */
#define USB_DOEPCTL_SD0PID_SEVNFRM_Pos (28U)
#define USB_DOEPCTL_SD0PID_SEVNFRM_Msk (0x1UL << USB_DOEPCTL_SD0PID_SEVNFRM_Pos) /*!< Set DATA0 PID */
#define USB_DOEPCTL_SODDFRM_Pos        (29U)
#define USB_DOEPCTL_SODDFRM_Msk        (0x1UL << USB_DOEPCTL_SODDFRM_Pos) /*!< Set odd frame */
#define USB_DOEPCTL_EPTYP_Pos          (18U)
#define USB_DOEPCTL_EPTYP_Msk          (0x3UL << USB_DOEPCTL_EPTYP_Pos) /*!< Endpoint type */
#define USB_DOEPCTL_EPTYP_0            (0x1UL << USB_DOEPCTL_EPTYP_Pos) /*!< 0x00040000 */
#define USB_DOEPCTL_EPTYP_1            (0x2UL << USB_DOEPCTL_EPTYP_Pos) /*!< 0x00080000 */
#define USB_DOEPCTL_SNPM_Pos           (20U)
#define USB_DOEPCTL_SNPM_Msk           (0x1UL << USB_DOEPCTL_SNPM_Pos) /*!< Snoop mode */
#define USB_DOEPCTL_STALL_Pos          (21U)
#define USB_DOEPCTL_STALL_Msk          (0x1UL << USB_DOEPCTL_STALL_Pos) /*!< STALL handshake */
#define USB_DOEPCTL_CNAK_Pos           (26U)
#define USB_DOEPCTL_CNAK_Msk           (0x1UL << USB_DOEPCTL_CNAK_Pos) /*!< Clear NAK */
#define USB_DOEPCTL_SNAK_Pos           (27U)
#define USB_DOEPCTL_SNAK_Msk           (0x1UL << USB_DOEPCTL_SNAK_Pos) /*!< Set NAK */
#define USB_DOEPCTL_EPDIS_Pos          (30U)
#define USB_DOEPCTL_EPDIS_Msk          (0x1UL << USB_DOEPCTL_EPDIS_Pos) /*!< Endpoint disable */
#define USB_DOEPCTL_EPENA_Pos          (31U)
#define USB_DOEPCTL_EPENA_Msk          (0x1UL << USB_DOEPCTL_EPENA_Pos) /*!< Endpoint enable */

/********************  Bit definition for USB_DOEPINT register  ********************/
#define USB_DOEPINT_XFRC_Pos      (0U)
#define USB_DOEPINT_XFRC_Msk      (0x1UL << USB_DOEPINT_XFRC_Pos) /*!< Transfer completed interrupt */
#define USB_DOEPINT_EPDISD_Pos    (1U)
#define USB_DOEPINT_EPDISD_Msk    (0x1UL << USB_DOEPINT_EPDISD_Pos) /*!< Endpoint disabled interrupt */
#define USB_DOEPINT_AHBERR_Pos    (2U)
#define USB_DOEPINT_AHBERR_Msk    (0x1UL << USB_DOEPINT_AHBERR_Pos) /*!< AHB Error (AHBErr) during an OUT transaction */
#define USB_DOEPINT_STUP_Pos      (3U)
#define USB_DOEPINT_STUP_Msk      (0x1UL << USB_DOEPINT_STUP_Pos) /*!< SETUP phase done */
#define USB_DOEPINT_OTEPDIS_Pos   (4U)
#define USB_DOEPINT_OTEPDIS_Msk   (0x1UL << USB_DOEPINT_OTEPDIS_Pos) /*!< OUT token received when endpoint disabled */
#define USB_DOEPINT_OTEPSPR_Pos   (5U)
#define USB_DOEPINT_OTEPSPR_Msk   (0x1UL << USB_DOEPINT_OTEPSPR_Pos) /*!< Status Phase Received For Control Write */
#define USB_DOEPINT_B2BSTUP_Pos   (6U)
#define USB_DOEPINT_B2BSTUP_Msk   (0x1UL << USB_DOEPINT_B2BSTUP_Pos) /*!< Back-to-back SETUP packets received */
#define USB_DOEPINT_OUTPKTERR_Pos (8U)
#define USB_DOEPINT_OUTPKTERR_Msk (0x1UL << USB_DOEPINT_OUTPKTERR_Pos) /*!< OUT packet error */
#define USB_DOEPINT_BERR_Pos      (12U)
#define USB_DOEPINT_BERR_Msk      (0x1UL << USB_DOEPINT_BERR_Pos) /*!< Babble error interrupt */
#define USB_DOEPINT_NAK_Pos       (13U)
#define USB_DOEPINT_NAK_Msk       (0x1UL << USB_DOEPINT_NAK_Pos) /*!< NAK Packet is transmitted by the device */
#define USB_DOEPINT_NYET_Pos      (14U)
#define USB_DOEPINT_NYET_Msk      (0x1UL << USB_DOEPINT_NYET_Pos) /*!< NYET interrupt */
#define USB_DOEPINT_STPKTRX_Pos   (15U)
#define USB_DOEPINT_STPKTRX_Msk   (0x1UL << USB_DOEPINT_STPKTRX_Pos) /*!< Setup Packet Received */

/********************  Bit definition for USB_DOEPTSIZ register  ********************/
#define USB_DOEPTSIZ_XFRSIZ_Pos (0U)
#define USB_DOEPTSIZ_XFRSIZ_Msk (0x7FFFFUL << USB_DOEPTSIZ_XFRSIZ_Pos) /*!< Transfer size */
#define USB_DOEPTSIZ_PKTCNT_Pos (19U)
#define USB_DOEPTSIZ_PKTCNT_Msk (0x3FFUL << USB_DOEPTSIZ_PKTCNT_Pos) /*!< Packet count */

#define USB_DOEPTSIZ_STUPCNT_Pos (29U)
#define USB_DOEPTSIZ_STUPCNT_Msk (0x3UL << USB_DOEPTSIZ_STUPCNT_Pos) /*!< SETUP packet count */
#define USB_DOEPTSIZ_STUPCNT_0   (0x1UL << USB_DOEPTSIZ_STUPCNT_Pos) /*!< 0x20000000 */
#define USB_DOEPTSIZ_STUPCNT_1   (0x2UL << USB_DOEPTSIZ_STUPCNT_Pos) /*!< 0x40000000 */

/********************  Bit definition for PCGCCTL register  ********************/
#define USB_PCGCCTL_STOPCLK_Pos (0U)
#define USB_PCGCCTL_STOPCLK_Msk (0x1UL << USB_PCGCCTL_STOPCLK_Pos) /*!< SETUP packet count */
#define USB_PCGCCTL_GATECLK_Pos (1U)
#define USB_PCGCCTL_GATECLK_Msk (0x1UL << USB_PCGCCTL_GATECLK_Pos) /*!<Bit 0 */
#define USB_PCGCCTL_PHYSUSP_Pos (4U)
#define USB_PCGCCTL_PHYSUSP_Msk (0x1UL << USB_PCGCCTL_PHYSUSP_Pos) /*!<Bit 1 */

/********************  Bit definition for OTG register  ********************/
#define USB_CHNUM_Pos (0U)
#define USB_CHNUM_Msk (0xFUL << USB_CHNUM_Pos) /*!< Channel number */
#define USB_CHNUM_0   (0x1UL << USB_CHNUM_Pos) /*!< 0x00000001 */
#define USB_CHNUM_1   (0x2UL << USB_CHNUM_Pos) /*!< 0x00000002 */
#define USB_CHNUM_2   (0x4UL << USB_CHNUM_Pos) /*!< 0x00000004 */
#define USB_CHNUM_3   (0x8UL << USB_CHNUM_Pos) /*!< 0x00000008 */
#define USB_BCNT_Pos  (4U)
#define USB_BCNT_Msk  (0x7FFUL << USB_BCNT_Pos) /*!< Byte count */

#define USB_DPID_Pos (15U)
#define USB_DPID_Msk (0x3UL << USB_DPID_Pos) /*!< Data PID */
#define USB_DPID_0   (0x1UL << USB_DPID_Pos) /*!< 0x00008000 */
#define USB_DPID_1   (0x2UL << USB_DPID_Pos) /*!< 0x00010000 */

#define USB_PKTSTS_Pos (17U)
#define USB_PKTSTS_Msk (0xFUL << USB_PKTSTS_Pos) /*!< Packet status */
#define USB_PKTSTS_0   (0x1UL << USB_PKTSTS_Pos) /*!< 0x00020000 */
#define USB_PKTSTS_1   (0x2UL << USB_PKTSTS_Pos) /*!< 0x00040000 */
#define USB_PKTSTS_2   (0x4UL << USB_PKTSTS_Pos) /*!< 0x00080000 */
#define USB_PKTSTS_3   (0x8UL << USB_PKTSTS_Pos) /*!< 0x00100000 */

#define USB_EPNUM_Pos (0U)
#define USB_EPNUM_Msk (0xFUL << USB_EPNUM_Pos) /*!< Endpoint number */
#define USB_EPNUM_0   (0x1UL << USB_EPNUM_Pos) /*!< 0x00000001 */
#define USB_EPNUM_1   (0x2UL << USB_EPNUM_Pos) /*!< 0x00000002 */
#define USB_EPNUM_2   (0x4UL << USB_EPNUM_Pos) /*!< 0x00000004 */
#define USB_EPNUM_3   (0x8UL << USB_EPNUM_Pos) /*!< 0x00000008 */

#define USB_FRMNUM_Pos (21U)
#define USB_FRMNUM_Msk (0xFUL << USB_FRMNUM_Pos) /*!< Frame number */
#define USB_FRMNUM_0   (0x1UL << USB_FRMNUM_Pos) /*!< 0x00200000 */
#define USB_FRMNUM_1   (0x2UL << USB_FRMNUM_Pos) /*!< 0x00400000 */
#define USB_FRMNUM_2   (0x4UL << USB_FRMNUM_Pos) /*!< 0x00800000 */
#define USB_FRMNUM_3   (0x8UL << USB_FRMNUM_Pos) /*!< 0x01000000 */

/**************************** type definition ********************************/
/**
  * @brief USB_Core_Registers
  */
typedef struct /* 000h */
{
    volatile uint32_t GOTGCTL;     /* USB_OTG Control and Status Register 000h */
    volatile uint32_t GOTGINT;     /* USB_OTG Interrupt Register          004h */
    volatile uint32_t GAHBCFG;     /* Core AHB Configuration Register     008h */
    volatile uint32_t GUSBCFG;     /* Core USB Configuration Register     00Ch */
    volatile uint32_t GRSTCTL;     /* Core Reset Register                 010h */
    volatile uint32_t GINTSTS;     /* Core Interrupt Register             014h */
    volatile uint32_t GINTMSK;     /* Core Interrupt Mask Register        018h */
    volatile uint32_t GRXSTSR;     /* Receive Sts Q Read Register         01Ch */
    volatile uint32_t GRXSTSP;     /* Receive Sts Q Read & POP Register   020h */
    volatile uint32_t GRXFSIZ;     /* Receive FIFO Size Register          024h */
    volatile uint32_t GNPTXFSIZ;   /* Non Periodic Tx FIFO Size Register  028h */
    volatile uint32_t GNPTXSTS;    /* Non Periodic Tx FIFO/Queue Sts reg  02Ch */
    volatile uint32_t GI2CCTL;     /* NOT USE                             030h */
    volatile uint32_t GPVNDCTL;    /* NOT USE                             034h */
    volatile uint32_t GGPIO;       /* General Purpose IO Register         038h */
    volatile uint32_t GUID;        /* User ID Register                    03Ch */
    volatile uint32_t GSNPSID;     /* synopsys id, read only              040h */
    volatile uint32_t GHWCFG1;     /* hardware config1                    044h */
    volatile uint32_t GHWCFG2;     /* hardware config2                    048h */
    volatile uint32_t GHWCFG3;     /* hardware config3                    04Ch */
    volatile uint32_t GHWCFG4;     /* hardware config4                    050h */
    volatile uint32_t GLPMCFG;     /* LPM Config Register                 054h */
    volatile uint32_t GPWRDN;      /* Global Power Down register          058h */
    volatile uint32_t GDFIFOCFG;   /* Global DFIFO config                 05Ch */
    uint32_t Reserved60[40];       /* Reserved                            060h-0FFh */
    volatile uint32_t HPTXFSIZ;    /* Host Periodic Tx FIFO Size Reg      100h */
    volatile uint32_t DIEPTXF[16]; /* dev Periodic Transmit FIFO */
} usb_otg_gregs_t;

/**
  * @brief USB_device_Registers
  */
typedef struct /* 800h */
{
    volatile uint32_t DCFG;       /* dev Configuration Register   800h */
    volatile uint32_t DCTL;       /* dev Control Register         804h */
    volatile uint32_t DSTS;       /* dev Status Register (RO)     808h */
    uint32_t Reserved0C;          /* Reserved                     80Ch */
    volatile uint32_t DIEPMSK;    /* dev IN Endpoint Mask         810h */
    volatile uint32_t DOEPMSK;    /* dev OUT Endpoint Mask        814h */
    volatile uint32_t DAINT;      /* dev All Endpoints Itr Reg    818h */
    volatile uint32_t DAINTMSK;   /* dev All Endpoints Itr Mask   81Ch */
    uint32_t Reserved20;          /* Reserved                     820h */
    uint32_t Reserved24;          /* Reserved                     824h */
    volatile uint32_t DVBUSDIS;   /* dev VBUS discharge Register  828h */
    volatile uint32_t DVBUSPULSE; /* dev VBUS Pulse Register      82Ch */
    volatile uint32_t DTHRCTL;    /* dev thr                      830h */
    volatile uint32_t DIEPEMPMSK; /* dev empty msk                834h */
    volatile uint32_t DEACHINT;   /* dedicated EP interrupt       838h */
    volatile uint32_t DEACHMSK;   /* dedicated EP msk             83Ch */
    volatile uint32_t DINEP0MSK;  /* dedicated EP mask            840h */
    uint32_t Reserved44[15];      /* Reserved                     844-87Ch */
    volatile uint32_t DOUTEP0MSK; /* dedicated EP msk             880h */
} usb_otg_dregs_t;

/**
  * @brief USB_IN_Endpoint-Specific_Register
  */
typedef struct {
    volatile uint32_t DIEPCTL;  /* dev IN Endpoint Control Reg    900h + (ep_num * 20h) + 00h */
    uint32_t Reserved04;        /* Reserved                       900h + (ep_num * 20h) + 04h */
    volatile uint32_t DIEPINT;  /* dev IN Endpoint Itr Reg        900h + (ep_num * 20h) + 08h */
    uint32_t Reserved0C;        /* Reserved                       900h + (ep_num * 20h) + 0Ch */
    volatile uint32_t DIEPTSIZ; /* IN Endpoint Txfer Size         900h + (ep_num * 20h) + 10h */
    volatile uint32_t DIEPDMA;  /* IN Endpoint DMA Address Reg    900h + (ep_num * 20h) + 14h */
    volatile uint32_t DTXFSTS;  /* IN Endpoint Tx FIFO Status Reg 900h + (ep_num * 20h) + 18h */
    uint32_t Reserved18;        /* Reserved                       900h+(ep_num*20h)+1Ch-900h+(ep_num*20h)+1Ch */
} usb_otg_inepregs_t;

/**
  * @brief USB_OUT_Endpoint-Specific_Registers
  */
typedef struct {
    volatile uint32_t DOEPCTL;  /* dev OUT Endpoint Control Reg   B00h + (ep_num * 20h) + 00h */
    uint32_t Reserved04;        /* Reserved                       B00h + (ep_num * 20h) + 04h */
    volatile uint32_t DOEPINT;  /* dev OUT Endpoint Itr Reg       B00h + (ep_num * 20h) + 08h */
    uint32_t Reserved0C;        /* Reserved                       B00h + (ep_num * 20h) + 0Ch */
    volatile uint32_t DOEPTSIZ; /* dev OUT Endpoint Txfer Size    B00h + (ep_num * 20h) + 10h */
    volatile uint32_t DOEPDMA;  /* dev OUT Endpoint DMA Address   B00h + (ep_num * 20h) + 14h */
    uint32_t Reserved18[2];     /* Reserved B00h + (ep_num * 20h) + 18h - B00h + (ep_num * 20h) + 1Ch */
} usb_otg_outepregs_t;

/**
  * @brief USB_Host_Mode_Register_Structures
  */
typedef struct {
    volatile uint32_t HCFG;     /* Host Configuration Register          400h */
    volatile uint32_t HFIR;     /* Host Frame Interval Register         404h */
    volatile uint32_t HFNUM;    /* Host Frame Nbr/Frame Remaining       408h */
    uint32_t Reserved40C;       /* Reserved                             40Ch */
    volatile uint32_t HPTXSTS;  /* Host Periodic Tx FIFO/ Queue Status  410h */
    volatile uint32_t HAINT;    /* Host All Channels Interrupt Register 414h */
    volatile uint32_t HAINTMSK; /* Host All Channels Interrupt Mask     418h */
    volatile uint32_t HFLBADDR; /* Host frame list base address register 41Ch */
    uint32_t Reserved420[8];    /* Reserved                              420h */
    volatile uint32_t HPRT;     /* Host port control and status register 440h */
} usb_otg_hregs_t;

/**
  * @brief USB_Host_Channel_Specific_Registers
  */
typedef struct {
    volatile uint32_t HCCHAR;   /* Host Channel Characteristics Register    500h */
    volatile uint32_t HCSPLT;   /* Host Channel Split Control Register      504h */
    volatile uint32_t HCINT;    /* Host Channel Interrupt Register          508h */
    volatile uint32_t HCINTMSK; /* Host Channel Interrupt Mask Register     50Ch */
    volatile uint32_t HCTSIZ;   /* Host Channel Transfer Size Register      510h */
    volatile uint32_t HCDMA;    /* Host Channel DMA Address Register        514h */
    uint32_t Reserved0;         /* Reserved                                 518h */
    volatile uint32_t HCDMAB;   /* Host Channel DMA Address Buffer Register 51Ch */
    uint32_t Reserved[2];       /* Reserved                                      */
} usb_otg_hc_regs_t;

#ifdef USB_CFG_DEBUG_ENABLE

typedef struct usb_otg_core_regs {
    usb_otg_gregs_t *GREGS;
    usb_otg_dregs_t *DREGS;
    usb_otg_hregs_t *HREGS;
    usb_otg_inepregs_t *INEP_REGS[USB_MAX_TX_FIFOS];
    usb_otg_outepregs_t *OUTEP_REGS[USB_MAX_TX_FIFOS];
    usb_otg_hc_regs_t *HC_REGS[USB_MAX_TX_FIFOS];
    volatile uint32_t *HPRT0;
    volatile uint32_t *DFIFO[USB_MAX_TX_FIFOS];
    volatile uint32_t *PCGCCTL;
} usb_core_regs_t;
#endif

#define USB_GREGS         ((usb_otg_gregs_t *)(USB_BASE))                                                             /* 000h */
#define USB_DREGS         ((usb_otg_dregs_t *)(USB_BASE + USB_DEVICE_REGS_BASE))                                      /* 800h */
#define USB_INEP_REGS(i)  ((usb_otg_inepregs_t *)(USB_BASE + USB_IN_ENDPOINT_REGS_BASE + ((i) * USB_EP_REGS_SIZE)))   /* 900h */
#define USB_OUTEP_REGS(i) ((usb_otg_outepregs_t *)(USB_BASE + USB_OUT_ENDPOINT_REGS_BASE + ((i) * USB_EP_REGS_SIZE))) /* B00h */
#define USB_PCGCCTL       *(volatile uint32_t *)((uint32_t)USB_BASE + USB_PCGCCTL_REGS_BASE)                          /* E00h */
#define USB_DFIFO(i)      *(volatile uint32_t *)(USB_BASE + USB_FIFO_REGS_BASE + ((i) * USB_FIFO_REGS_SIZE))          /* 1000h */

#define USB_HREGS      ((usb_otg_hregs_t *)(USB_BASE + USB_HOST_REGS_BASE))                                                /* 400h */
#define USB_HPRT0      *(volatile uint32_t *)(USB_BASE + USB_HOST_PORT_REGS_BASE)                                          /* 440h */
#define USB_HC_REGS(i) ((usb_otg_hc_regs_t *)(USB_BASE + USB_HOST_CHANNEL_REGS_BASE + ((i) * USB_HOST_CHANNEL_REGS_SIZE))) /* 500h */

/**************************** variable declear *******************************/

/**************************** function declear *******************************/

#endif

#ifdef __cplusplus
}
#endif

#endif
