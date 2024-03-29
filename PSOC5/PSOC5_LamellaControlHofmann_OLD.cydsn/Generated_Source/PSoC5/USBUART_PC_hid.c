/***************************************************************************//**
* \file USBUART_PC_hid.c
* \version 3.20
*
* \brief
*  This file contains the USB HID Class request handler. 
*
* Related Document:
*  Device Class Definition for Human Interface Devices (HID) Version 1.11
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBUART_PC_hid.h"
#include "USBUART_PC_pvt.h"



#if defined(USBUART_PC_ENABLE_HID_CLASS)

/***************************************
*    HID Variables
***************************************/
/** This variable is initialized in the USBFS_InitComponent() API to the 
 * PROTOCOL_REPORT value. It is controlled by the host using the 
 * HID_SET_PROTOCOL request. The value is returned to the user code by the 
 * USBFS_GetProtocol() API.*/
volatile uint8 USBUART_PC_hidProtocol[USBUART_PC_MAX_INTERFACES_NUMBER];

/** This variable controls the HID report rate. It is controlled by the host 
 * using the HID_SET_IDLE request and used by the USBFS_UpdateHIDTimer() API to 
 * reload timer.*/
volatile uint8 USBUART_PC_hidIdleRate[USBUART_PC_MAX_INTERFACES_NUMBER];

/** This variable contains the timer counter, which is decremented and reloaded 
 * by the USBFS_UpdateHIDTimer() API.*/
volatile uint8 USBUART_PC_hidIdleTimer[USBUART_PC_MAX_INTERFACES_NUMBER]; /* HID device idle rate value */


/***************************************
* Custom Declarations
***************************************/

/* `#START HID_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USBUART_PC_UpdateHIDTimer
****************************************************************************//**
*
*  This function updates the HID Report idle timer and returns the status and 
*  reloads the timer if it expires.
*
*  \param interface Contains the interface number.
*
* \return
*  Returns the state of the HID timer. Symbolic names and their associated values are given here:
*  Return Value               |Notes
*  ---------------------------|------------------------------------------------
*  USBFS_IDLE_TIMER_EXPIRED   | The timer expired.
*  USBFS_IDLE_TIMER_RUNNING   | The timer is running.
*  USBFS_IDLE_TIMER_IDEFINITE | The report is sent when data or state changes.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_UpdateHIDTimer(uint8 interface) 
{
    uint8 stat = USBUART_PC_IDLE_TIMER_INDEFINITE;

    if(USBUART_PC_hidIdleRate[interface] != 0u)
    {
        if(USBUART_PC_hidIdleTimer[interface] > 0u)
        {
            USBUART_PC_hidIdleTimer[interface]--;
            stat = USBUART_PC_IDLE_TIMER_RUNNING;
        }
        else
        {
            USBUART_PC_hidIdleTimer[interface] = USBUART_PC_hidIdleRate[interface];
            stat = USBUART_PC_IDLE_TIMER_EXPIRED;
        }
    }

    return((uint8)stat);
}


/*******************************************************************************
* Function Name: USBUART_PC_GetProtocol
****************************************************************************//**
*
*  This function returns the HID protocol value for the selected interface.
*
*  \param interface:  Contains the interface number.
*
*  \return
*  Returns the protocol value. 
*
*******************************************************************************/
uint8 USBUART_PC_GetProtocol(uint8 interface) 
{
    return(USBUART_PC_hidProtocol[interface]);
}


/*******************************************************************************
* Function Name: USBUART_PC_DispatchHIDClassRqst
****************************************************************************//**
*
*  This routine dispatches class requests
*
* \return
*  Results of HID Class request handling: 
*  - USBUART_PC_TRUE  - request was handled without errors
*  - USBUART_PC_FALSE - error occurs during handling of request  
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_DispatchHIDClassRqst(void) 
{
    uint8 requestHandled = USBUART_PC_FALSE;

    uint8 interfaceNumber = (uint8) USBUART_PC_wIndexLoReg;
    
    /* Check request direction: D2H or H2D. */
    if (0u != (USBUART_PC_bmRequestTypeReg & USBUART_PC_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        switch (USBUART_PC_bRequestReg)
        {
            case USBUART_PC_GET_DESCRIPTOR:
                if (USBUART_PC_wValueHiReg == USBUART_PC_DESCR_HID_CLASS)
                {
                    USBUART_PC_FindHidClassDecriptor();
                    if (USBUART_PC_currentTD.count != 0u)
                    {
                        requestHandled = USBUART_PC_InitControlRead();
                    }
                }
                else if (USBUART_PC_wValueHiReg == USBUART_PC_DESCR_HID_REPORT)
                {
                    USBUART_PC_FindReportDescriptor();
                    if (USBUART_PC_currentTD.count != 0u)
                    {
                        requestHandled = USBUART_PC_InitControlRead();
                    }
                }
                else
                {   
                    /* Do not handle this request. */
                }
                break;
                
            case USBUART_PC_HID_GET_REPORT:
                USBUART_PC_FindReport();
                if (USBUART_PC_currentTD.count != 0u)
                {
                    requestHandled = USBUART_PC_InitControlRead();
                }
                break;

            case USBUART_PC_HID_GET_IDLE:
                /* This function does not support multiple reports per interface*/
                /* Validate interfaceNumber and Report ID (should be 0): Do not support Idle per Report ID */
                if ((interfaceNumber < USBUART_PC_MAX_INTERFACES_NUMBER) && (USBUART_PC_wValueLoReg == 0u)) 
                {
                    USBUART_PC_currentTD.count = 1u;
                    USBUART_PC_currentTD.pData = &USBUART_PC_hidIdleRate[interfaceNumber];
                    requestHandled  = USBUART_PC_InitControlRead();
                }
                break;
                
            case USBUART_PC_HID_GET_PROTOCOL:
                /* Validate interfaceNumber */
                if( interfaceNumber < USBUART_PC_MAX_INTERFACES_NUMBER)
                {
                    USBUART_PC_currentTD.count = 1u;
                    USBUART_PC_currentTD.pData = &USBUART_PC_hidProtocol[interfaceNumber];
                    requestHandled  = USBUART_PC_InitControlRead();
                }
                break;
                
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {   
        /* Handle direction from host to device. */
        
        switch (USBUART_PC_bRequestReg)
        {
            case USBUART_PC_HID_SET_REPORT:
                USBUART_PC_FindReport();
                if (USBUART_PC_currentTD.count != 0u)
                {
                    requestHandled = USBUART_PC_InitControlWrite();
                }
                break;
                
            case USBUART_PC_HID_SET_IDLE:
                /* This function does not support multiple reports per interface */
                /* Validate interfaceNumber and Report ID (should be 0): Do not support Idle per Report ID */
                if ((interfaceNumber < USBUART_PC_MAX_INTERFACES_NUMBER) && (USBUART_PC_wValueLoReg == 0u))
                {
                    USBUART_PC_hidIdleRate[interfaceNumber] = (uint8)USBUART_PC_wValueHiReg;
                    /* With regards to HID spec: "7.2.4 Set_Idle Request"
                    *  Latency. If the current period has gone past the
                    *  newly proscribed time duration, then a report
                    *  will be generated immediately.
                    */
                    if(USBUART_PC_hidIdleRate[interfaceNumber] <
                       USBUART_PC_hidIdleTimer[interfaceNumber])
                    {
                        /* Set the timer to zero and let the UpdateHIDTimer() API return IDLE_TIMER_EXPIRED status*/
                        USBUART_PC_hidIdleTimer[interfaceNumber] = 0u;
                    }
                    /* If the new request is received within 4 milliseconds
                    *  (1 count) of the end of the current period, then the
                    *  new request will have no effect until after the report.
                    */
                    else if(USBUART_PC_hidIdleTimer[interfaceNumber] <= 1u)
                    {
                        /* Do nothing.
                        *  Let the UpdateHIDTimer() API continue to work and
                        *  return IDLE_TIMER_EXPIRED status
                        */
                    }
                    else
                    {   /* Reload the timer*/
                        USBUART_PC_hidIdleTimer[interfaceNumber] =
                        USBUART_PC_hidIdleRate[interfaceNumber];
                    }
                    requestHandled = USBUART_PC_InitNoDataControlTransfer();
                }
                break;

            case USBUART_PC_HID_SET_PROTOCOL:
                /* Validate interfaceNumber and protocol (must be 0 or 1) */
                if ((interfaceNumber < USBUART_PC_MAX_INTERFACES_NUMBER) && (USBUART_PC_wValueLoReg <= 1u))
                {
                    USBUART_PC_hidProtocol[interfaceNumber] = (uint8)USBUART_PC_wValueLoReg;
                    requestHandled = USBUART_PC_InitNoDataControlTransfer();
                }
                break;
            
            default:    
                /* Unknown class request is not handled. */
                break;
        }
    }

    return (requestHandled);
}


/*******************************************************************************
* Function Name: USB_FindHidClassDescriptor
****************************************************************************//**
*
*  This routine find Hid Class Descriptor pointer based on the Interface number
*  and Alternate setting then loads the currentTD structure with the address of
*  the buffer and the size.
*  The HID Class Descriptor resides inside the config descriptor.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBUART_PC_FindHidClassDecriptor(void) 
{
    const T_USBUART_PC_LUT CYCODE *pTmp;
    volatile uint8 *pDescr;
    uint8 interfaceN;

    pTmp = USBUART_PC_GetConfigTablePtr(USBUART_PC_configuration - 1u);
    
    interfaceN = (uint8) USBUART_PC_wIndexLoReg;
    /* Third entry in the LUT starts the Interface Table pointers */
    /* Now use the request interface number*/
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_USBUART_PC_LUT CYCODE *) pTmp->p_list;
    
    /* Now use Alternate setting number */
    pTmp = &pTmp[USBUART_PC_interfaceSetting[interfaceN]];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
    pTmp = (const T_USBUART_PC_LUT CYCODE *) pTmp->p_list;
    
    /* Fifth entry in the LUT points to Hid Class Descriptor in Configuration Descriptor */
    pTmp = &pTmp[4u];
    pDescr = (volatile uint8 *)pTmp->p_list;
    
    /* The first byte contains the descriptor length */
    USBUART_PC_currentTD.count = *pDescr;
    USBUART_PC_currentTD.pData = pDescr;
}


/*******************************************************************************
* Function Name: USB_FindReportDescriptor
****************************************************************************//**
*
*  This routine find Hid Report Descriptor pointer based on the Interface
*  number, then loads the currentTD structure with the address of the buffer
*  and the size.
*  Hid Report Descriptor is located after IN/OUT/FEATURE reports.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBUART_PC_FindReportDescriptor(void) 
{
    const T_USBUART_PC_LUT CYCODE *pTmp;
    volatile uint8 *pDescr;
    uint8 interfaceN;

    pTmp = USBUART_PC_GetConfigTablePtr(USBUART_PC_configuration - 1u);
    interfaceN = (uint8) USBUART_PC_wIndexLoReg;
    
    /* Third entry in the LUT starts the Interface Table pointers */
    /* Now use the request interface number */
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_USBUART_PC_LUT CYCODE *) pTmp->p_list;
    
    /* Now use Alternate setting number */
    pTmp = &pTmp[USBUART_PC_interfaceSetting[interfaceN]];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
    pTmp = (const T_USBUART_PC_LUT CYCODE *) pTmp->p_list;
    
    /* Fourth entry in the LUT starts the Hid Report Descriptor */
    pTmp = &pTmp[3u];
    pDescr = (volatile uint8 *)pTmp->p_list;
    
    /* The 1st and 2nd bytes of descriptor contain its length. LSB is 1st. */
    USBUART_PC_currentTD.count =  ((uint16)((uint16) pDescr[1u] << 8u) | pDescr[0u]);
    USBUART_PC_currentTD.pData = &pDescr[2u];
}


/*******************************************************************************
* Function Name: USBUART_PC_FindReport
****************************************************************************//**
*
*  This routine sets up a transfer based on the Interface number, Report Type
*  and Report ID, then loads the currentTD structure with the address of the
*  buffer and the size.  The caller has to decide if it is a control read or
*  control write.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBUART_PC_FindReport(void) 
{
    const T_USBUART_PC_LUT CYCODE *pTmp;
    T_USBUART_PC_TD *pTD;
    uint8 reportType;
    uint8 interfaceN;
 
    /* `#START HID_FINDREPORT` Place custom handling here */

    /* `#END` */
    
#ifdef USBUART_PC_FIND_REPORT_CALLBACK
    USBUART_PC_FindReport_Callback();
#endif /* (USBUART_PC_FIND_REPORT_CALLBACK) */
    
    USBUART_PC_currentTD.count = 0u;   /* Init not supported condition */
    pTmp = USBUART_PC_GetConfigTablePtr(USBUART_PC_configuration - 1u);
    reportType = (uint8) USBUART_PC_wValueHiReg;
    interfaceN = (uint8) USBUART_PC_wIndexLoReg;
    
    /* Third entry in the LUT Configuration Table starts the Interface Table pointers */
    /* Now use the request interface number */
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_USBUART_PC_LUT CYCODE *) pTmp->p_list;
    if (interfaceN < USBUART_PC_MAX_INTERFACES_NUMBER)
    {
        /* Now use Alternate setting number */
        pTmp = &pTmp[USBUART_PC_interfaceSetting[interfaceN]];
        
        /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
        pTmp = (const T_USBUART_PC_LUT CYCODE *) pTmp->p_list;
        
        /* Validate reportType to comply with "7.2.1 Get_Report Request" */
        if ((reportType >= USBUART_PC_HID_GET_REPORT_INPUT) &&
            (reportType <= USBUART_PC_HID_GET_REPORT_FEATURE))
        {
            /* Get the entry proper TD (IN, OUT or Feature Report Table)*/
            pTmp = &pTmp[reportType - 1u];
            
            /* Get reportID */
            reportType = (uint8) USBUART_PC_wValueLoReg;
            
            /* Validate table support by the HID descriptor, compare table count with reportID */
            if (pTmp->c >= reportType)
            {
                pTD = (T_USBUART_PC_TD *) pTmp->p_list;
                pTD = &pTD[reportType];                          /* select entry depend on report ID*/
                USBUART_PC_currentTD.pData = pTD->pData;   /* Buffer pointer */
                USBUART_PC_currentTD.count = pTD->count;   /* Buffer Size */
                USBUART_PC_currentTD.pStatusBlock = pTD->pStatusBlock;
            }
        }
    }
}


/*******************************************************************************
* Additional user functions supporting HID Requests
********************************************************************************/

/* `#START HID_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  USBUART_PC_ENABLE_HID_CLASS */


/* [] END OF FILE */
