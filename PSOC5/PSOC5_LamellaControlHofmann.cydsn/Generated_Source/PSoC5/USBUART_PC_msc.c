/***************************************************************************//**
* \file USBUART_PC_cdc.c
* \version 3.20
*
* \brief
*  This file contains the USB MSC Class request handler and global API for MSC 
*  class.
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

#include "USBUART_PC_msc.h"
#include "USBUART_PC_pvt.h"


#if (USBUART_PC_HANDLE_MSC_REQUESTS)

/***************************************
*          Internal variables
***************************************/

static uint8 USBUART_PC_lunCount = USBUART_PC_MSC_LUN_NUMBER;


/*******************************************************************************
* Function Name: USBUART_PC_DispatchMSCClassRqst
****************************************************************************//**
*   
*  \internal 
*  This routine dispatches MSC class requests.
*
* \return
*  Status of request processing: handled or not handled.
*
* \globalvars
*  USBUART_PC_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_DispatchMSCClassRqst(void) 
{
    uint8 requestHandled = USBUART_PC_FALSE;
    
    /* Get request data. */
    uint16 value  = USBUART_PC_GET_UINT16(USBUART_PC_wValueHiReg,  USBUART_PC_wValueLoReg);
    uint16 dataLength = USBUART_PC_GET_UINT16(USBUART_PC_wLengthHiReg, USBUART_PC_wLengthLoReg);
       
    /* Check request direction: D2H or H2D. */
    if (0u != (USBUART_PC_bmRequestTypeReg & USBUART_PC_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (USBUART_PC_MSC_GET_MAX_LUN == USBUART_PC_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == USBUART_PC_MSC_GET_MAX_LUN_WVALUE) &&
                (dataLength == USBUART_PC_MSC_GET_MAX_LUN_WLENGTH))
            {
                /* Reply to Get Max LUN request: setup control read. */
                USBUART_PC_currentTD.pData = &USBUART_PC_lunCount;
                USBUART_PC_currentTD.count =  USBUART_PC_MSC_GET_MAX_LUN_WLENGTH;
                
                requestHandled  = USBUART_PC_InitControlRead();
            }
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (USBUART_PC_MSC_RESET == USBUART_PC_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == USBUART_PC_MSC_RESET_WVALUE) &&
                (dataLength == USBUART_PC_MSC_RESET_WLENGTH))
            {
                /* Handle to Bulk-Only Reset request: no data control transfer. */
                USBUART_PC_currentTD.count = USBUART_PC_MSC_RESET_WLENGTH;
                
            #ifdef USBUART_PC_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK
                USBUART_PC_DispatchMSCClass_MSC_RESET_RQST_Callback();
            #endif /* (USBUART_PC_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK) */
                
                requestHandled = USBUART_PC_InitNoDataControlTransfer();
            }
        }
    }
    
    return (requestHandled);
}


/*******************************************************************************
* Function Name: USBUART_PC_MSC_SetLunCount
****************************************************************************//**
*
*  This function sets the number of logical units supported in the application. 
*  The default number of logical units is set in the component customizer.
*
*  \param lunCount: Count of the logical units. Valid range is between 1 and 16.
*
*
* \globalvars
*  USBUART_PC_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBUART_PC_MSC_SetLunCount(uint8 lunCount) 
{
    USBUART_PC_lunCount = (lunCount - 1u);
}


/*******************************************************************************
* Function Name: USBUART_PC_MSC_GetLunCount
****************************************************************************//**
*
*  This function returns the number of logical units.
*
* \return
*   Number of the logical units.
*
* \globalvars
*  USBUART_PC_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_MSC_GetLunCount(void) 
{
    return (USBUART_PC_lunCount + 1u);
}   

#endif /* (USBUART_PC_HANDLE_MSC_REQUESTS) */


/* [] END OF FILE */
