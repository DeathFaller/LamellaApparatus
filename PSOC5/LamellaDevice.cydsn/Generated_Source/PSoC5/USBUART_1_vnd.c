/*******************************************************************************
* File Name: USBUART_1_vnd.c
* Version 2.80
*
* Description:
*  USB vendor request handler.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBUART_1.h"
#include "USBUART_1_pvt.h"


#if(USBUART_1_EXTERN_VND == USBUART_1_FALSE)


/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USBUART_1_HandleVendorRqst
********************************************************************************
*
* Summary:
*  This routine provide users with a method to implement vendor specific
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USBUART_1_HandleVendorRqst(void) 
{
    uint8 requestHandled = USBUART_1_FALSE;

    if ((CY_GET_REG8(USBUART_1_bmRequestType) & USBUART_1_RQST_DIR_MASK) == USBUART_1_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(USBUART_1_bRequest))
        {
            case USBUART_1_GET_EXTENDED_CONFIG_DESCRIPTOR:
                #if defined(USBUART_1_ENABLE_MSOS_STRING)
                    USBUART_1_currentTD.pData = (volatile uint8 *)&USBUART_1_MSOS_CONFIGURATION_DESCR[0u];
                    USBUART_1_currentTD.count = USBUART_1_MSOS_CONFIGURATION_DESCR[0u];
                    requestHandled  = USBUART_1_InitControlRead();
                #endif /*  USBUART_1_ENABLE_MSOS_STRING */
                break;
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

    #ifdef USBUART_1_HANDLE_VENDOR_RQST_CALLBACK
        USBUART_1_HandleVendorRqst_Callback();
    #endif /* USBUART_1_HANDLE_VENDOR_RQST_CALLBACK */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* USBUART_1_EXTERN_VND */


/* [] END OF FILE */
