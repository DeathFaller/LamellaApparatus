/***************************************************************************//**
* \file USBUART_PC_cls.c
* \version 3.20
*
* \brief
*  This file contains the USB Class request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBUART_PC_pvt.h"


#if(USBUART_PC_EXTERN_CLS == USBUART_PC_FALSE)

/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USBUART_PC_DispatchClassRqst
****************************************************************************//**
*  This routine dispatches class specific requests depend on interface class.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_DispatchClassRqst(void) 
{
    uint8 interfaceNumber;
    uint8 requestHandled = USBUART_PC_FALSE;

    /* Get interface to which request is intended. */
    switch (USBUART_PC_bmRequestTypeReg & USBUART_PC_RQST_RCPT_MASK)
    {
        case USBUART_PC_RQST_RCPT_IFC:
            /* Class-specific request directed to interface: wIndexLoReg 
            * contains interface number.
            */
            interfaceNumber = (uint8) USBUART_PC_wIndexLoReg;
            break;
        
        case USBUART_PC_RQST_RCPT_EP:
            /* Class-specific request directed to endpoint: wIndexLoReg contains 
            * endpoint number. Find interface related to endpoint. 
            */
            interfaceNumber = USBUART_PC_EP[USBUART_PC_wIndexLoReg & USBUART_PC_DIR_UNUSED].interface;
            break;
            
        default:
            /* Default interface is zero. */
            interfaceNumber = 0u;
            break;
    }
    
    /* Check that interface is within acceptable range */
    if (interfaceNumber <= USBUART_PC_MAX_INTERFACES_NUMBER)
    {
    #if (defined(USBUART_PC_ENABLE_HID_CLASS)   || \
         defined(USBUART_PC_ENABLE_AUDIO_CLASS) || \
         defined(USBUART_PC_ENABLE_CDC_CLASS)   || \
         USBUART_PC_ENABLE_MSC_CLASS)

        /* Handle class request depends on interface type. */
        switch (USBUART_PC_interfaceClass[interfaceNumber])
        {
        #if defined(USBUART_PC_ENABLE_HID_CLASS)
            case USBUART_PC_CLASS_HID:
                requestHandled = USBUART_PC_DispatchHIDClassRqst();
                break;
        #endif /* (USBUART_PC_ENABLE_HID_CLASS) */
                
        #if defined(USBUART_PC_ENABLE_AUDIO_CLASS)
            case USBUART_PC_CLASS_AUDIO:
                requestHandled = USBUART_PC_DispatchAUDIOClassRqst();
                break;
        #endif /* (USBUART_PC_CLASS_AUDIO) */
                
        #if defined(USBUART_PC_ENABLE_CDC_CLASS)
            case USBUART_PC_CLASS_CDC:
                requestHandled = USBUART_PC_DispatchCDCClassRqst();
                break;
        #endif /* (USBUART_PC_ENABLE_CDC_CLASS) */
            
        #if (USBUART_PC_ENABLE_MSC_CLASS)
            case USBUART_PC_CLASS_MSD:
            #if (USBUART_PC_HANDLE_MSC_REQUESTS)
                /* MSC requests are handled by the component. */
                requestHandled = USBUART_PC_DispatchMSCClassRqst();
            #elif defined(USBUART_PC_DISPATCH_MSC_CLASS_RQST_CALLBACK)
                /* MSC requests are handled by user defined callbcak. */
                requestHandled = USBUART_PC_DispatchMSCClassRqst_Callback();
            #else
                /* MSC requests are not handled. */
                requestHandled = USBUART_PC_FALSE;
            #endif /* (USBUART_PC_HANDLE_MSC_REQUESTS) */
                break;
        #endif /* (USBUART_PC_ENABLE_MSC_CLASS) */
            
            default:
                /* Request is not handled: unknown class request type. */
                requestHandled = USBUART_PC_FALSE;
                break;
        }
    #endif /* Class support is enabled */
    }
    
    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

#ifdef USBUART_PC_DISPATCH_CLASS_RQST_CALLBACK
    if (USBUART_PC_FALSE == requestHandled)
    {
        requestHandled = USBUART_PC_DispatchClassRqst_Callback(interfaceNumber);
    }
#endif /* (USBUART_PC_DISPATCH_CLASS_RQST_CALLBACK) */

    return (requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* USBUART_PC_EXTERN_CLS */


/* [] END OF FILE */
