/***************************************************************************//**
* \file USBUART_PC_cdc.h
* \version 3.20
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  CDC class.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USBUART_PC_cdc_H)
#define CY_USBFS_USBUART_PC_cdc_H

#include "USBUART_PC.h"


/*******************************************************************************
* Prototypes of the USBUART_PC_cdc API.
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
#if (USBUART_PC_ENABLE_CDC_CLASS_API != 0u)
    uint8 USBUART_PC_CDC_Init(void)            ;
    void USBUART_PC_PutData(const uint8* pData, uint16 length) ;
    void USBUART_PC_PutString(const char8 string[])            ;
    void USBUART_PC_PutChar(char8 txDataByte) ;
    void USBUART_PC_PutCRLF(void)             ;
    uint16 USBUART_PC_GetCount(void)          ;
    uint8  USBUART_PC_CDCIsReady(void)        ;
    uint8  USBUART_PC_DataIsReady(void)       ;
    uint16 USBUART_PC_GetData(uint8* pData, uint16 length)     ;
    uint16 USBUART_PC_GetAll(uint8* pData)    ;
    uint8  USBUART_PC_GetChar(void)           ;
    uint8  USBUART_PC_IsLineChanged(void)     ;
    uint32 USBUART_PC_GetDTERate(void)        ;
    uint8  USBUART_PC_GetCharFormat(void)     ;
    uint8  USBUART_PC_GetParityType(void)     ;
    uint8  USBUART_PC_GetDataBits(void)       ;
    uint16 USBUART_PC_GetLineControl(void)    ;
    void USBUART_PC_SendSerialState (uint16 serialState) ;
    uint16 USBUART_PC_GetSerialState (void)   ;
    void USBUART_PC_SetComPort (uint8 comNumber) ;
    uint8 USBUART_PC_GetComPort (void)        ;
    uint8 USBUART_PC_NotificationIsReady(void) ;

#endif  /* (USBUART_PC_ENABLE_CDC_CLASS_API) */
/** @} cdc */

/*******************************************************************************
*  Constants for USBUART_PC_cdc API.
*******************************************************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define USBUART_PC_CDC_SET_LINE_CODING        (0x20u)
#define USBUART_PC_CDC_GET_LINE_CODING        (0x21u)
#define USBUART_PC_CDC_SET_CONTROL_LINE_STATE (0x22u)

/*PSTN Subclass Specific Notifications (CDC ver 1.2 Table 30)*/
#define USBUART_PC_SERIAL_STATE               (0x20u)

#define USBUART_PC_LINE_CODING_CHANGED        (0x01u)
#define USBUART_PC_LINE_CONTROL_CHANGED       (0x02u)

#define USBUART_PC_1_STOPBIT                  (0x00u)
#define USBUART_PC_1_5_STOPBITS               (0x01u)
#define USBUART_PC_2_STOPBITS                 (0x02u)

#define USBUART_PC_PARITY_NONE                (0x00u)
#define USBUART_PC_PARITY_ODD                 (0x01u)
#define USBUART_PC_PARITY_EVEN                (0x02u)
#define USBUART_PC_PARITY_MARK                (0x03u)
#define USBUART_PC_PARITY_SPACE               (0x04u)

#define USBUART_PC_LINE_CODING_SIZE           (0x07u)
#define USBUART_PC_LINE_CODING_RATE           (0x00u)
#define USBUART_PC_LINE_CODING_STOP_BITS      (0x04u)
#define USBUART_PC_LINE_CODING_PARITY         (0x05u)
#define USBUART_PC_LINE_CODING_DATA_BITS      (0x06u)

#define USBUART_PC_LINE_CONTROL_DTR           (0x01u)
#define USBUART_PC_LINE_CONTROL_RTS           (0x02u)

#define USBUART_PC_MAX_MULTI_COM_NUM          (2u) 

#define USBUART_PC_COM_PORT1                  (0u) 
#define USBUART_PC_COM_PORT2                  (1u) 

#define USBUART_PC_SUCCESS                    (0u)
#define USBUART_PC_FAILURE                    (1u)

#define USBUART_PC_SERIAL_STATE_SIZE          (10u)

/* SerialState constants*/
#define USBUART_PC_SERIAL_STATE_REQUEST_TYPE  (0xA1u)
#define USBUART_PC_SERIAL_STATE_LENGTH        (0x2u)

/*******************************************************************************
* External data references
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
extern volatile uint8  USBUART_PC_linesCoding[USBUART_PC_MAX_MULTI_COM_NUM][USBUART_PC_LINE_CODING_SIZE];
extern volatile uint8  USBUART_PC_linesChanged[USBUART_PC_MAX_MULTI_COM_NUM];
extern volatile uint16 USBUART_PC_linesControlBitmap[USBUART_PC_MAX_MULTI_COM_NUM];
extern volatile uint16 USBUART_PC_serialStateBitmap[USBUART_PC_MAX_MULTI_COM_NUM];
extern volatile uint8  USBUART_PC_cdcDataInEp[USBUART_PC_MAX_MULTI_COM_NUM];
extern volatile uint8  USBUART_PC_cdcDataOutEp[USBUART_PC_MAX_MULTI_COM_NUM];
extern volatile uint8  USBUART_PC_cdcCommInInterruptEp[USBUART_PC_MAX_MULTI_COM_NUM];
/** @} cdc */

/*******************************************************************************
* The following code is DEPRECATED and
* must not be used.
*******************************************************************************/


#define USBUART_PC_lineCoding             USBUART_PC_linesCoding[0]
#define USBUART_PC_lineChanged            USBUART_PC_linesChanged[0]
#define USBUART_PC_lineControlBitmap      USBUART_PC_linesControlBitmap[0]
#define USBUART_PC_cdc_data_in_ep         USBUART_PC_cdcDataInEp[0]
#define USBUART_PC_cdc_data_out_ep        USBUART_PC_cdcDataOutEp[0]

#endif /* (CY_USBFS_USBUART_PC_cdc_H) */


/* [] END OF FILE */
