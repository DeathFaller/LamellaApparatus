/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This file provides private function prototypes and constants for the 
*  USBFS component. It is not intended to be used in the user project.
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USBUART_PC_pvt_H)
#define CY_USBFS_USBUART_PC_pvt_H

#include "USBUART_PC.h"
   
#ifdef USBUART_PC_ENABLE_AUDIO_CLASS
    #include "USBUART_PC_audio.h"
#endif /* USBUART_PC_ENABLE_AUDIO_CLASS */

#ifdef USBUART_PC_ENABLE_CDC_CLASS
    #include "USBUART_PC_cdc.h"
#endif /* USBUART_PC_ENABLE_CDC_CLASS */

#if (USBUART_PC_ENABLE_MIDI_CLASS)
    #include "USBUART_PC_midi.h"
#endif /* (USBUART_PC_ENABLE_MIDI_CLASS) */

#if (USBUART_PC_ENABLE_MSC_CLASS)
    #include "USBUART_PC_msc.h"
#endif /* (USBUART_PC_ENABLE_MSC_CLASS) */

#if (USBUART_PC_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        #include <CyDMA.h>
    #else
        #include <CyDmac.h>
        #if ((USBUART_PC_EP_MANAGEMENT_DMA_AUTO) && (USBUART_PC_EP_DMA_AUTO_OPT == 0u))
            #include "USBUART_PC_EP_DMA_Done_isr.h"
            #include "USBUART_PC_EP8_DMA_Done_SR.h"
            #include "USBUART_PC_EP17_DMA_Done_SR.h"
        #endif /* ((USBUART_PC_EP_MANAGEMENT_DMA_AUTO) && (USBUART_PC_EP_DMA_AUTO_OPT == 0u)) */
    #endif /* (CY_PSOC4) */
#endif /* (USBUART_PC_EP_MANAGEMENT_DMA) */

#if (USBUART_PC_DMA1_ACTIVE)
    #include "USBUART_PC_ep1_dma.h"
    #define USBUART_PC_EP1_DMA_CH     (USBUART_PC_ep1_dma_CHANNEL)
#endif /* (USBUART_PC_DMA1_ACTIVE) */

#if (USBUART_PC_DMA2_ACTIVE)
    #include "USBUART_PC_ep2_dma.h"
    #define USBUART_PC_EP2_DMA_CH     (USBUART_PC_ep2_dma_CHANNEL)
#endif /* (USBUART_PC_DMA2_ACTIVE) */

#if (USBUART_PC_DMA3_ACTIVE)
    #include "USBUART_PC_ep3_dma.h"
    #define USBUART_PC_EP3_DMA_CH     (USBUART_PC_ep3_dma_CHANNEL)
#endif /* (USBUART_PC_DMA3_ACTIVE) */

#if (USBUART_PC_DMA4_ACTIVE)
    #include "USBUART_PC_ep4_dma.h"
    #define USBUART_PC_EP4_DMA_CH     (USBUART_PC_ep4_dma_CHANNEL)
#endif /* (USBUART_PC_DMA4_ACTIVE) */

#if (USBUART_PC_DMA5_ACTIVE)
    #include "USBUART_PC_ep5_dma.h"
    #define USBUART_PC_EP5_DMA_CH     (USBUART_PC_ep5_dma_CHANNEL)
#endif /* (USBUART_PC_DMA5_ACTIVE) */

#if (USBUART_PC_DMA6_ACTIVE)
    #include "USBUART_PC_ep6_dma.h"
    #define USBUART_PC_EP6_DMA_CH     (USBUART_PC_ep6_dma_CHANNEL)
#endif /* (USBUART_PC_DMA6_ACTIVE) */

#if (USBUART_PC_DMA7_ACTIVE)
    #include "USBUART_PC_ep7_dma.h"
    #define USBUART_PC_EP7_DMA_CH     (USBUART_PC_ep7_dma_CHANNEL)
#endif /* (USBUART_PC_DMA7_ACTIVE) */

#if (USBUART_PC_DMA8_ACTIVE)
    #include "USBUART_PC_ep8_dma.h"
    #define USBUART_PC_EP8_DMA_CH     (USBUART_PC_ep8_dma_CHANNEL)
#endif /* (USBUART_PC_DMA8_ACTIVE) */


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors. */
extern const uint8 CYCODE USBUART_PC_DEVICE0_DESCR[18u];
extern const uint8 CYCODE USBUART_PC_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_USBUART_PC_EP_SETTINGS_BLOCK CYCODE USBUART_PC_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE USBUART_PC_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_USBUART_PC_LUT CYCODE USBUART_PC_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_USBUART_PC_LUT CYCODE USBUART_PC_DEVICE0_TABLE[3u];
extern const T_USBUART_PC_LUT CYCODE USBUART_PC_TABLE[1u];
extern const uint8 CYCODE USBUART_PC_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE USBUART_PC_STRING_DESCRIPTORS[159u];


extern const uint8 CYCODE USBUART_PC_MSOS_DESCRIPTOR[USBUART_PC_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE USBUART_PC_MSOS_CONFIGURATION_DESCR[USBUART_PC_MSOS_CONF_DESCR_LENGTH];
#if defined(USBUART_PC_ENABLE_IDSN_STRING)
    extern uint8 USBUART_PC_idSerialNumberStringDescriptor[USBUART_PC_IDSN_DESCR_LENGTH];
#endif /* (USBUART_PC_ENABLE_IDSN_STRING) */

extern volatile uint8 USBUART_PC_interfaceNumber;
extern volatile uint8 USBUART_PC_interfaceSetting[USBUART_PC_MAX_INTERFACES_NUMBER];
extern volatile uint8 USBUART_PC_interfaceSettingLast[USBUART_PC_MAX_INTERFACES_NUMBER];
extern volatile uint8 USBUART_PC_deviceAddress;
extern volatile uint8 USBUART_PC_interfaceStatus[USBUART_PC_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *USBUART_PC_interfaceClass;

extern volatile T_USBUART_PC_EP_CTL_BLOCK USBUART_PC_EP[USBUART_PC_MAX_EP];
extern volatile T_USBUART_PC_TD USBUART_PC_currentTD;

#if (USBUART_PC_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        extern const uint8 USBUART_PC_DmaChan[USBUART_PC_MAX_EP];
    #else
        extern uint8 USBUART_PC_DmaChan[USBUART_PC_MAX_EP];
        extern uint8 USBUART_PC_DmaTd  [USBUART_PC_MAX_EP];
    #endif /* (CY_PSOC4) */
#endif /* (USBUART_PC_EP_MANAGEMENT_DMA) */

#if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    extern uint8  USBUART_PC_DmaEpBurstCnt   [USBUART_PC_MAX_EP];
    extern uint8  USBUART_PC_DmaEpLastBurstEl[USBUART_PC_MAX_EP];

    extern uint8  USBUART_PC_DmaEpBurstCntBackup  [USBUART_PC_MAX_EP];
    extern uint32 USBUART_PC_DmaEpBufferAddrBackup[USBUART_PC_MAX_EP];
    
    extern const uint8 USBUART_PC_DmaReqOut     [USBUART_PC_MAX_EP];    
    extern const uint8 USBUART_PC_DmaBurstEndOut[USBUART_PC_MAX_EP];
#else
    #if (USBUART_PC_EP_DMA_AUTO_OPT == 0u)
        extern uint8 USBUART_PC_DmaNextTd[USBUART_PC_MAX_EP];
        extern volatile uint16 USBUART_PC_inLength [USBUART_PC_MAX_EP];
        extern volatile uint8  USBUART_PC_inBufFull[USBUART_PC_MAX_EP];
        extern const uint8 USBUART_PC_epX_TD_TERMOUT_EN[USBUART_PC_MAX_EP];
        extern const uint8 *USBUART_PC_inDataPointer[USBUART_PC_MAX_EP];
    #endif /* (USBUART_PC_EP_DMA_AUTO_OPT == 0u) */
#endif /* CY_PSOC4 */
#endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */

extern volatile uint8 USBUART_PC_ep0Toggle;
extern volatile uint8 USBUART_PC_lastPacketSize;
extern volatile uint8 USBUART_PC_ep0Mode;
extern volatile uint8 USBUART_PC_ep0Count;
extern volatile uint16 USBUART_PC_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  USBUART_PC_ReInitComponent(void)            ;
void  USBUART_PC_HandleSetup(void)                ;
void  USBUART_PC_HandleIN(void)                   ;
void  USBUART_PC_HandleOUT(void)                  ;
void  USBUART_PC_LoadEP0(void)                    ;
uint8 USBUART_PC_InitControlRead(void)            ;
uint8 USBUART_PC_InitControlWrite(void)           ;
void  USBUART_PC_ControlReadDataStage(void)       ;
void  USBUART_PC_ControlReadStatusStage(void)     ;
void  USBUART_PC_ControlReadPrematureStatus(void) ;
uint8 USBUART_PC_InitControlWrite(void)           ;
uint8 USBUART_PC_InitZeroLengthControlTransfer(void) ;
void  USBUART_PC_ControlWriteDataStage(void)      ;
void  USBUART_PC_ControlWriteStatusStage(void)    ;
void  USBUART_PC_ControlWritePrematureStatus(void);
uint8 USBUART_PC_InitNoDataControlTransfer(void)  ;
void  USBUART_PC_NoDataControlStatusStage(void)   ;
void  USBUART_PC_InitializeStatusBlock(void)      ;
void  USBUART_PC_UpdateStatusBlock(uint8 completionCode) ;
uint8 USBUART_PC_DispatchClassRqst(void)          ;

void USBUART_PC_Config(uint8 clearAltSetting) ;
void USBUART_PC_ConfigAltChanged(void)        ;
void USBUART_PC_ConfigReg(void)               ;
void USBUART_PC_EpStateInit(void)             ;


const T_USBUART_PC_LUT CYCODE *USBUART_PC_GetConfigTablePtr(uint8 confIndex);
const T_USBUART_PC_LUT CYCODE *USBUART_PC_GetDeviceTablePtr(void)           ;
#if (USBUART_PC_BOS_ENABLE)
    const T_USBUART_PC_LUT CYCODE *USBUART_PC_GetBOSPtr(void)               ;
#endif /* (USBUART_PC_BOS_ENABLE) */
const uint8 CYCODE *USBUART_PC_GetInterfaceClassTablePtr(void)                    ;
uint8 USBUART_PC_ClearEndpointHalt(void)                                          ;
uint8 USBUART_PC_SetEndpointHalt(void)                                            ;
uint8 USBUART_PC_ValidateAlternateSetting(void)                                   ;

void USBUART_PC_SaveConfig(void)      ;
void USBUART_PC_RestoreConfig(void)   ;

#if (CY_PSOC3 || CY_PSOC5LP)
    #if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO && (USBUART_PC_EP_DMA_AUTO_OPT == 0u))
        void USBUART_PC_LoadNextInEP(uint8 epNumber, uint8 mode)  ;
    #endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO && (USBUART_PC_EP_DMA_AUTO_OPT == 0u)) */
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if defined(USBUART_PC_ENABLE_IDSN_STRING)
    void USBUART_PC_ReadDieID(uint8 descr[])  ;
#endif /* USBUART_PC_ENABLE_IDSN_STRING */

#if defined(USBUART_PC_ENABLE_HID_CLASS)
    uint8 USBUART_PC_DispatchHIDClassRqst(void) ;
#endif /* (USBUART_PC_ENABLE_HID_CLASS) */

#if defined(USBUART_PC_ENABLE_AUDIO_CLASS)
    uint8 USBUART_PC_DispatchAUDIOClassRqst(void) ;
#endif /* (USBUART_PC_ENABLE_AUDIO_CLASS) */

#if defined(USBUART_PC_ENABLE_CDC_CLASS)
    uint8 USBUART_PC_DispatchCDCClassRqst(void) ;
#endif /* (USBUART_PC_ENABLE_CDC_CLASS) */

#if (USBUART_PC_ENABLE_MSC_CLASS)
    #if (USBUART_PC_HANDLE_MSC_REQUESTS)
        uint8 USBUART_PC_DispatchMSCClassRqst(void) ;
    #endif /* (USBUART_PC_HANDLE_MSC_REQUESTS) */
#endif /* (USBUART_PC_ENABLE_MSC_CLASS */

CY_ISR_PROTO(USBUART_PC_EP_0_ISR);
CY_ISR_PROTO(USBUART_PC_BUS_RESET_ISR);

#if (USBUART_PC_SOF_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_SOF_ISR);
#endif /* (USBUART_PC_SOF_ISR_ACTIVE) */

#if (USBUART_PC_EP1_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_EP_1_ISR);
#endif /* (USBUART_PC_EP1_ISR_ACTIVE) */

#if (USBUART_PC_EP2_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_EP_2_ISR);
#endif /* (USBUART_PC_EP2_ISR_ACTIVE) */

#if (USBUART_PC_EP3_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_EP_3_ISR);
#endif /* (USBUART_PC_EP3_ISR_ACTIVE) */

#if (USBUART_PC_EP4_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_EP_4_ISR);
#endif /* (USBUART_PC_EP4_ISR_ACTIVE) */

#if (USBUART_PC_EP5_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_EP_5_ISR);
#endif /* (USBUART_PC_EP5_ISR_ACTIVE) */

#if (USBUART_PC_EP6_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_EP_6_ISR);
#endif /* (USBUART_PC_EP6_ISR_ACTIVE) */

#if (USBUART_PC_EP7_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_EP_7_ISR);
#endif /* (USBUART_PC_EP7_ISR_ACTIVE) */

#if (USBUART_PC_EP8_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_EP_8_ISR);
#endif /* (USBUART_PC_EP8_ISR_ACTIVE) */

#if (USBUART_PC_EP_MANAGEMENT_DMA)
    CY_ISR_PROTO(USBUART_PC_ARB_ISR);
#endif /* (USBUART_PC_EP_MANAGEMENT_DMA) */

#if (USBUART_PC_DP_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_PC_DP_ISR);
#endif /* (USBUART_PC_DP_ISR_ACTIVE) */

#if (CY_PSOC4)
    CY_ISR_PROTO(USBUART_PC_INTR_HI_ISR);
    CY_ISR_PROTO(USBUART_PC_INTR_MED_ISR);
    CY_ISR_PROTO(USBUART_PC_INTR_LO_ISR);
    #if (USBUART_PC_LPM_ACTIVE)
        CY_ISR_PROTO(USBUART_PC_LPM_ISR);
    #endif /* (USBUART_PC_LPM_ACTIVE) */
#endif /* (CY_PSOC4) */

#if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    #if (USBUART_PC_DMA1_ACTIVE)
        void USBUART_PC_EP1_DMA_DONE_ISR(void);
    #endif /* (USBUART_PC_DMA1_ACTIVE) */

    #if (USBUART_PC_DMA2_ACTIVE)
        void USBUART_PC_EP2_DMA_DONE_ISR(void);
    #endif /* (USBUART_PC_DMA2_ACTIVE) */

    #if (USBUART_PC_DMA3_ACTIVE)
        void USBUART_PC_EP3_DMA_DONE_ISR(void);
    #endif /* (USBUART_PC_DMA3_ACTIVE) */

    #if (USBUART_PC_DMA4_ACTIVE)
        void USBUART_PC_EP4_DMA_DONE_ISR(void);
    #endif /* (USBUART_PC_DMA4_ACTIVE) */

    #if (USBUART_PC_DMA5_ACTIVE)
        void USBUART_PC_EP5_DMA_DONE_ISR(void);
    #endif /* (USBUART_PC_DMA5_ACTIVE) */

    #if (USBUART_PC_DMA6_ACTIVE)
        void USBUART_PC_EP6_DMA_DONE_ISR(void);
    #endif /* (USBUART_PC_DMA6_ACTIVE) */

    #if (USBUART_PC_DMA7_ACTIVE)
        void USBUART_PC_EP7_DMA_DONE_ISR(void);
    #endif /* (USBUART_PC_DMA7_ACTIVE) */

    #if (USBUART_PC_DMA8_ACTIVE)
        void USBUART_PC_EP8_DMA_DONE_ISR(void);
    #endif /* (USBUART_PC_DMA8_ACTIVE) */

#else
    #if (USBUART_PC_EP_DMA_AUTO_OPT == 0u)
        CY_ISR_PROTO(USBUART_PC_EP_DMA_DONE_ISR);
    #endif /* (USBUART_PC_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */


/***************************************
*         Request Handlers
***************************************/

uint8 USBUART_PC_HandleStandardRqst(void) ;
uint8 USBUART_PC_DispatchClassRqst(void)  ;
uint8 USBUART_PC_HandleVendorRqst(void)   ;


/***************************************
*    HID Internal references
***************************************/

#if defined(USBUART_PC_ENABLE_HID_CLASS)
    void USBUART_PC_FindReport(void)            ;
    void USBUART_PC_FindReportDescriptor(void)  ;
    void USBUART_PC_FindHidClassDecriptor(void) ;
#endif /* USBUART_PC_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(USBUART_PC_ENABLE_MIDI_STREAMING)
    void USBUART_PC_MIDI_IN_EP_Service(void)  ;
#endif /* (USBUART_PC_ENABLE_MIDI_STREAMING) */


/***************************************
*    CDC Internal references
***************************************/

#if defined(USBUART_PC_ENABLE_CDC_CLASS)

    typedef struct
    {
        uint8  bRequestType;
        uint8  bNotification;
        uint8  wValue;
        uint8  wValueMSB;
        uint8  wIndex;
        uint8  wIndexMSB;
        uint8  wLength;
        uint8  wLengthMSB;
        uint8  wSerialState;
        uint8  wSerialStateMSB;
    } t_USBUART_PC_cdc_notification;

    uint8 USBUART_PC_GetInterfaceComPort(uint8 interface) ;
    uint8 USBUART_PC_Cdc_EpInit( const T_USBUART_PC_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) ;

    extern volatile uint8  USBUART_PC_cdc_dataInEpList[USBUART_PC_MAX_MULTI_COM_NUM];
    extern volatile uint8  USBUART_PC_cdc_dataOutEpList[USBUART_PC_MAX_MULTI_COM_NUM];
    extern volatile uint8  USBUART_PC_cdc_commInEpList[USBUART_PC_MAX_MULTI_COM_NUM];
#endif /* (USBUART_PC_ENABLE_CDC_CLASS) */


#endif /* CY_USBFS_USBUART_PC_pvt_H */


/* [] END OF FILE */
