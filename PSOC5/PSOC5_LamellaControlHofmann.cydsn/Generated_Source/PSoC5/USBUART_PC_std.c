/***************************************************************************//**
* \file USBUART_PC_std.c
* \version 3.20
*
* \brief
*  This file contains the USB Standard request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBUART_PC_pvt.h"

/***************************************
*   Static data allocation
***************************************/

#if defined(USBUART_PC_ENABLE_FWSN_STRING)
    static volatile uint8* USBUART_PC_fwSerialNumberStringDescriptor;
    static volatile uint8  USBUART_PC_snStringConfirm = USBUART_PC_FALSE;
#endif  /* (USBUART_PC_ENABLE_FWSN_STRING) */

#if defined(USBUART_PC_ENABLE_FWSN_STRING)
    /***************************************************************************
    * Function Name: USBUART_PC_SerialNumString
    ************************************************************************//**
    *
    *  This function is available only when the User Call Back option in the 
    *  Serial Number String descriptor properties is selected. Application 
    *  firmware can provide the source of the USB device serial number string 
    *  descriptor during run time. The default string is used if the application 
    *  firmware does not use this function or sets the wrong string descriptor.
    *
    *  \param snString:  Pointer to the user-defined string descriptor. The 
    *  string descriptor should meet the Universal Serial Bus Specification 
    *  revision 2.0 chapter 9.6.7
    *  Offset|Size|Value|Description
    *  ------|----|------|---------------------------------
    *  0     |1   |N     |Size of this descriptor in bytes
    *  1     |1   |0x03  |STRING Descriptor Type
    *  2     |N-2 |Number|UNICODE encoded string
    *  
    * *For example:* uint8 snString[16]={0x0E,0x03,'F',0,'W',0,'S',0,'N',0,'0',0,'1',0};
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void  USBUART_PC_SerialNumString(uint8 snString[]) 
    {
        USBUART_PC_snStringConfirm = USBUART_PC_FALSE;
        
        if (snString != NULL)
        {
            /* Check descriptor validation */
            if ((snString[0u] > 1u) && (snString[1u] == USBUART_PC_DESCR_STRING))
            {
                USBUART_PC_fwSerialNumberStringDescriptor = snString;
                USBUART_PC_snStringConfirm = USBUART_PC_TRUE;
            }
        }
    }
#endif  /* USBUART_PC_ENABLE_FWSN_STRING */


/*******************************************************************************
* Function Name: USBUART_PC_HandleStandardRqst
****************************************************************************//**
*
*  This Routine dispatches standard requests
*
*
* \return
*  TRUE if request handled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_HandleStandardRqst(void) 
{
    uint8 requestHandled = USBUART_PC_FALSE;
    uint8 interfaceNumber;
    uint8 configurationN;
    uint8 bmRequestType = USBUART_PC_bmRequestTypeReg;

#if defined(USBUART_PC_ENABLE_STRINGS)
    volatile uint8 *pStr = 0u;
    #if defined(USBUART_PC_ENABLE_DESCRIPTOR_STRINGS)
        uint8 nStr;
        uint8 descrLength;
    #endif /* (USBUART_PC_ENABLE_DESCRIPTOR_STRINGS) */
#endif /* (USBUART_PC_ENABLE_STRINGS) */
    
    static volatile uint8 USBUART_PC_tBuffer[USBUART_PC_STATUS_LENGTH_MAX];
    const T_USBUART_PC_LUT CYCODE *pTmp;

    USBUART_PC_currentTD.count = 0u;

    if (USBUART_PC_RQST_DIR_D2H == (bmRequestType & USBUART_PC_RQST_DIR_MASK))
    {
        /* Control Read */
        switch (USBUART_PC_bRequestReg)
        {
            case USBUART_PC_GET_DESCRIPTOR:
                if (USBUART_PC_DESCR_DEVICE ==USBUART_PC_wValueHiReg)
                {
                    pTmp = USBUART_PC_GetDeviceTablePtr();
                    USBUART_PC_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                    USBUART_PC_currentTD.count = USBUART_PC_DEVICE_DESCR_LENGTH;
                    
                    requestHandled  = USBUART_PC_InitControlRead();
                }
                else if (USBUART_PC_DESCR_CONFIG == USBUART_PC_wValueHiReg)
                {
                    pTmp = USBUART_PC_GetConfigTablePtr((uint8) USBUART_PC_wValueLoReg);
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        USBUART_PC_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                        USBUART_PC_currentTD.count = (uint16)((uint16)(USBUART_PC_currentTD.pData)[USBUART_PC_CONFIG_DESCR_TOTAL_LENGTH_HI] << 8u) | \
                                                                            (USBUART_PC_currentTD.pData)[USBUART_PC_CONFIG_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = USBUART_PC_InitControlRead();
                    }
                }
                
            #if(USBUART_PC_BOS_ENABLE)
                else if (USBUART_PC_DESCR_BOS == USBUART_PC_wValueHiReg)
                {
                    pTmp = USBUART_PC_GetBOSPtr();
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        USBUART_PC_currentTD.pData = (volatile uint8 *)pTmp;
                        USBUART_PC_currentTD.count = ((uint16)((uint16)(USBUART_PC_currentTD.pData)[USBUART_PC_BOS_DESCR_TOTAL_LENGTH_HI] << 8u)) | \
                                                                             (USBUART_PC_currentTD.pData)[USBUART_PC_BOS_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = USBUART_PC_InitControlRead();
                    }
                }
            #endif /*(USBUART_PC_BOS_ENABLE)*/
            
            #if defined(USBUART_PC_ENABLE_STRINGS)
                else if (USBUART_PC_DESCR_STRING == USBUART_PC_wValueHiReg)
                {
                /* Descriptor Strings */
                #if defined(USBUART_PC_ENABLE_DESCRIPTOR_STRINGS)
                    nStr = 0u;
                    pStr = (volatile uint8 *) &USBUART_PC_STRING_DESCRIPTORS[0u];
                    
                    while ((USBUART_PC_wValueLoReg > nStr) && (*pStr != 0u))
                    {
                        /* Read descriptor length from 1st byte */
                        descrLength = *pStr;
                        /* Move to next string descriptor */
                        pStr = &pStr[descrLength];
                        nStr++;
                    }
                #endif /* (USBUART_PC_ENABLE_DESCRIPTOR_STRINGS) */
                
                /* Microsoft OS String */
                #if defined(USBUART_PC_ENABLE_MSOS_STRING)
                    if (USBUART_PC_STRING_MSOS == USBUART_PC_wValueLoReg)
                    {
                        pStr = (volatile uint8 *)& USBUART_PC_MSOS_DESCRIPTOR[0u];
                    }
                #endif /* (USBUART_PC_ENABLE_MSOS_STRING) */
                
                /* SN string */
                #if defined(USBUART_PC_ENABLE_SN_STRING)
                    if ((USBUART_PC_wValueLoReg != 0u) && 
                        (USBUART_PC_wValueLoReg == USBUART_PC_DEVICE0_DESCR[USBUART_PC_DEVICE_DESCR_SN_SHIFT]))
                    {
                    #if defined(USBUART_PC_ENABLE_IDSN_STRING)
                        /* Read DIE ID and generate string descriptor in RAM */
                        USBUART_PC_ReadDieID(USBUART_PC_idSerialNumberStringDescriptor);
                        pStr = USBUART_PC_idSerialNumberStringDescriptor;
                    #elif defined(USBUART_PC_ENABLE_FWSN_STRING)
                        
                        if(USBUART_PC_snStringConfirm != USBUART_PC_FALSE)
                        {
                            pStr = USBUART_PC_fwSerialNumberStringDescriptor;
                        }
                        else
                        {
                            pStr = (volatile uint8 *)&USBUART_PC_SN_STRING_DESCRIPTOR[0u];
                        }
                    #else
                        pStr = (volatile uint8 *)&USBUART_PC_SN_STRING_DESCRIPTOR[0u];
                    #endif  /* (USBUART_PC_ENABLE_IDSN_STRING) */
                    }
                #endif /* (USBUART_PC_ENABLE_SN_STRING) */
                
                    if (*pStr != 0u)
                    {
                        USBUART_PC_currentTD.count = *pStr;
                        USBUART_PC_currentTD.pData = pStr;
                        requestHandled  = USBUART_PC_InitControlRead();
                    }
                }
            #endif /*  USBUART_PC_ENABLE_STRINGS */
                else
                {
                    requestHandled = USBUART_PC_DispatchClassRqst();
                }
                break;
                
            case USBUART_PC_GET_STATUS:
                switch (bmRequestType & USBUART_PC_RQST_RCPT_MASK)
                {
                    case USBUART_PC_RQST_RCPT_EP:
                        USBUART_PC_currentTD.count = USBUART_PC_EP_STATUS_LENGTH;
                        USBUART_PC_tBuffer[0u]     = USBUART_PC_EP[USBUART_PC_wIndexLoReg & USBUART_PC_DIR_UNUSED].hwEpState;
                        USBUART_PC_tBuffer[1u]     = 0u;
                        USBUART_PC_currentTD.pData = &USBUART_PC_tBuffer[0u];
                        
                        requestHandled  = USBUART_PC_InitControlRead();
                        break;
                    case USBUART_PC_RQST_RCPT_DEV:
                        USBUART_PC_currentTD.count = USBUART_PC_DEVICE_STATUS_LENGTH;
                        USBUART_PC_tBuffer[0u]     = USBUART_PC_deviceStatus;
                        USBUART_PC_tBuffer[1u]     = 0u;
                        USBUART_PC_currentTD.pData = &USBUART_PC_tBuffer[0u];
                        
                        requestHandled  = USBUART_PC_InitControlRead();
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case USBUART_PC_GET_CONFIGURATION:
                USBUART_PC_currentTD.count = 1u;
                USBUART_PC_currentTD.pData = (volatile uint8 *) &USBUART_PC_configuration;
                requestHandled  = USBUART_PC_InitControlRead();
                break;
                
            case USBUART_PC_GET_INTERFACE:
                USBUART_PC_currentTD.count = 1u;
                USBUART_PC_currentTD.pData = (volatile uint8 *) &USBUART_PC_interfaceSetting[USBUART_PC_wIndexLoReg];
                requestHandled  = USBUART_PC_InitControlRead();
                break;
                
            default: /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {
        /* Control Write */
        switch (USBUART_PC_bRequestReg)
        {
            case USBUART_PC_SET_ADDRESS:
                /* Store address to be set in USBUART_PC_NoDataControlStatusStage(). */
                USBUART_PC_deviceAddress = (uint8) USBUART_PC_wValueLoReg;
                requestHandled = USBUART_PC_InitNoDataControlTransfer();
                break;
                
            case USBUART_PC_SET_CONFIGURATION:
                configurationN = USBUART_PC_wValueLoReg;
                
                /* Verify that configuration descriptor exists */
                if(configurationN > 0u)
                {
                    pTmp = USBUART_PC_GetConfigTablePtr((uint8) configurationN - 1u);
                }
                
                /* Responds with a Request Error when configuration number is invalid */
                if (((configurationN > 0u) && (pTmp != NULL)) || (configurationN == 0u))
                {
                    /* Set new configuration if it has been changed */
                    if(configurationN != USBUART_PC_configuration)
                    {
                        USBUART_PC_configuration = (uint8) configurationN;
                        USBUART_PC_configurationChanged = USBUART_PC_TRUE;
                        USBUART_PC_Config(USBUART_PC_TRUE);
                    }
                    requestHandled = USBUART_PC_InitNoDataControlTransfer();
                }
                break;
                
            case USBUART_PC_SET_INTERFACE:
                if (0u != USBUART_PC_ValidateAlternateSetting())
                {
                    /* Get interface number from the request. */
                    interfaceNumber = USBUART_PC_wIndexLoReg;
                    USBUART_PC_interfaceNumber = (uint8) USBUART_PC_wIndexLoReg;
                     
                    /* Check if alternate settings is changed for interface. */
                    if (USBUART_PC_interfaceSettingLast[interfaceNumber] != USBUART_PC_interfaceSetting[interfaceNumber])
                    {
                        USBUART_PC_configurationChanged = USBUART_PC_TRUE;
                    
                        /* Change alternate setting for the endpoints. */
                    #if (USBUART_PC_EP_MANAGEMENT_MANUAL && USBUART_PC_EP_ALLOC_DYNAMIC)
                        USBUART_PC_Config(USBUART_PC_FALSE);
                    #else
                        USBUART_PC_ConfigAltChanged();
                    #endif /* (USBUART_PC_EP_MANAGEMENT_MANUAL && USBUART_PC_EP_ALLOC_DYNAMIC) */
                    }
                    
                    requestHandled = USBUART_PC_InitNoDataControlTransfer();
                }
                break;
                
            case USBUART_PC_CLEAR_FEATURE:
                switch (bmRequestType & USBUART_PC_RQST_RCPT_MASK)
                {
                    case USBUART_PC_RQST_RCPT_EP:
                        if (USBUART_PC_wValueLoReg == USBUART_PC_ENDPOINT_HALT)
                        {
                            requestHandled = USBUART_PC_ClearEndpointHalt();
                        }
                        break;
                    case USBUART_PC_RQST_RCPT_DEV:
                        /* Clear device REMOTE_WAKEUP */
                        if (USBUART_PC_wValueLoReg == USBUART_PC_DEVICE_REMOTE_WAKEUP)
                        {
                            USBUART_PC_deviceStatus &= (uint8)~USBUART_PC_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = USBUART_PC_InitNoDataControlTransfer();
                        }
                        break;
                    case USBUART_PC_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (USBUART_PC_wIndexLoReg < USBUART_PC_MAX_INTERFACES_NUMBER)
                        {
                            USBUART_PC_interfaceStatus[USBUART_PC_wIndexLoReg] &= (uint8) ~USBUART_PC_wValueLoReg;
                            requestHandled = USBUART_PC_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case USBUART_PC_SET_FEATURE:
                switch (bmRequestType & USBUART_PC_RQST_RCPT_MASK)
                {
                    case USBUART_PC_RQST_RCPT_EP:
                        if (USBUART_PC_wValueLoReg == USBUART_PC_ENDPOINT_HALT)
                        {
                            requestHandled = USBUART_PC_SetEndpointHalt();
                        }
                        break;
                        
                    case USBUART_PC_RQST_RCPT_DEV:
                        /* Set device REMOTE_WAKEUP */
                        if (USBUART_PC_wValueLoReg == USBUART_PC_DEVICE_REMOTE_WAKEUP)
                        {
                            USBUART_PC_deviceStatus |= USBUART_PC_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = USBUART_PC_InitNoDataControlTransfer();
                        }
                        break;
                        
                    case USBUART_PC_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (USBUART_PC_wIndexLoReg < USBUART_PC_MAX_INTERFACES_NUMBER)
                        {
                            USBUART_PC_interfaceStatus[USBUART_PC_wIndexLoReg] &= (uint8) ~USBUART_PC_wValueLoReg;
                            requestHandled = USBUART_PC_InitNoDataControlTransfer();
                        }
                        break;
                    
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    
    return (requestHandled);
}


#if defined(USBUART_PC_ENABLE_IDSN_STRING)
    /***************************************************************************
    * Function Name: USBUART_PC_ReadDieID
    ************************************************************************//**
    *
    *  This routine read Die ID and generate Serial Number string descriptor.
    *
    *  \param descr:  pointer on string descriptor. This string size has to be equal or
    *          greater than USBUART_PC_IDSN_DESCR_LENGTH.
    *
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void USBUART_PC_ReadDieID(uint8 descr[]) 
    {
        const char8 CYCODE hex[] = "0123456789ABCDEF";
        uint8 i;
        uint8 j = 0u;
        uint8 uniqueId[8u];

        if (NULL != descr)
        {
            /* Initialize descriptor header. */
            descr[0u] = USBUART_PC_IDSN_DESCR_LENGTH;
            descr[1u] = USBUART_PC_DESCR_STRING;
            
            /* Unique ID size is 8 bytes. */
            CyGetUniqueId((uint32 *) uniqueId);

            /* Fill descriptor with unique device ID. */
            for (i = 2u; i < USBUART_PC_IDSN_DESCR_LENGTH; i += 4u)
            {
                descr[i]      = (uint8) hex[(uniqueId[j] >> 4u)];
                descr[i + 1u] = 0u;
                descr[i + 2u] = (uint8) hex[(uniqueId[j] & 0x0Fu)];
                descr[i + 3u] = 0u;
                ++j;
            }
        }
    }
#endif /* (USBUART_PC_ENABLE_IDSN_STRING) */


/*******************************************************************************
* Function Name: USBUART_PC_ConfigReg
****************************************************************************//**
*
*  This routine configures hardware registers from the variables.
*  It is called from USBUART_PC_Config() function and from RestoreConfig
*  after Wakeup.
*
*******************************************************************************/
void USBUART_PC_ConfigReg(void) 
{
    uint8 ep;

#if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
    uint8 epType = 0u;
#endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */

    /* Go thought all endpoints and set hardware configuration */
    for (ep = USBUART_PC_EP1; ep < USBUART_PC_MAX_EP; ++ep)
    {
        USBUART_PC_ARB_EP_BASE.arbEp[ep].epCfg = USBUART_PC_ARB_EPX_CFG_DEFAULT;
        
    #if (USBUART_PC_EP_MANAGEMENT_DMA)
        /* Enable arbiter endpoint interrupt sources */
        USBUART_PC_ARB_EP_BASE.arbEp[ep].epIntEn = USBUART_PC_ARB_EPX_INT_MASK;
    #endif /* (USBUART_PC_EP_MANAGEMENT_DMA) */
    
        if (USBUART_PC_EP[ep].epMode != USBUART_PC_MODE_DISABLE)
        {
            if (0u != (USBUART_PC_EP[ep].addr & USBUART_PC_DIR_IN))
            {
                USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = USBUART_PC_MODE_NAK_IN;
                
            #if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4)
                /* Clear DMA_TERMIN for IN endpoint. */
                USBUART_PC_ARB_EP_BASE.arbEp[ep].epIntEn &= (uint32) ~USBUART_PC_ARB_EPX_INT_DMA_TERMIN;
            #endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4) */
            }
            else
            {
                USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = USBUART_PC_MODE_NAK_OUT;

            #if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
                /* (CY_PSOC4): DMA_TERMIN for OUT endpoint is set above. */
                
                /* Prepare endpoint type mask. */
                epType |= (uint8) (0x01u << (ep - USBUART_PC_EP1));
            #endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */
            }
        }
        else
        {
            USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = USBUART_PC_MODE_STALL_DATA_EP;
        }
        
    #if (!USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
        #if (CY_PSOC4)
            USBUART_PC_ARB_EP16_BASE.arbEp[ep].rwRa16  = (uint32) USBUART_PC_EP[ep].buffOffset;
            USBUART_PC_ARB_EP16_BASE.arbEp[ep].rwWa16  = (uint32) USBUART_PC_EP[ep].buffOffset;
        #else
            USBUART_PC_ARB_EP_BASE.arbEp[ep].rwRa    = LO8(USBUART_PC_EP[ep].buffOffset);
            USBUART_PC_ARB_EP_BASE.arbEp[ep].rwRaMsb = HI8(USBUART_PC_EP[ep].buffOffset);
            USBUART_PC_ARB_EP_BASE.arbEp[ep].rwWa    = LO8(USBUART_PC_EP[ep].buffOffset);
            USBUART_PC_ARB_EP_BASE.arbEp[ep].rwWaMsb = HI8(USBUART_PC_EP[ep].buffOffset);
        #endif /* (CY_PSOC4) */
    #endif /* (!USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */
    }

#if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
     /* BUF_SIZE depend on DMA_THRESS value:0x55-32 bytes  0x44-16 bytes 0x33-8 bytes 0x22-4 bytes 0x11-2 bytes */
    USBUART_PC_BUF_SIZE_REG = USBUART_PC_DMA_BUF_SIZE;

    /* Configure DMA burst threshold */
#if (CY_PSOC4)
    USBUART_PC_DMA_THRES16_REG   = USBUART_PC_DMA_BYTES_PER_BURST;
#else
    USBUART_PC_DMA_THRES_REG     = USBUART_PC_DMA_BYTES_PER_BURST;
    USBUART_PC_DMA_THRES_MSB_REG = 0u;
#endif /* (CY_PSOC4) */
    USBUART_PC_EP_ACTIVE_REG = USBUART_PC_DEFAULT_ARB_INT_EN;
    USBUART_PC_EP_TYPE_REG   = epType;
    
    /* Cfg_cmp bit set to 1 once configuration is complete. */
    /* Lock arbiter configtuation */
    USBUART_PC_ARB_CFG_REG |= (uint8)  USBUART_PC_ARB_CFG_CFG_CMP;
    /* Cfg_cmp bit set to 0 during configuration of PFSUSB Registers. */
    USBUART_PC_ARB_CFG_REG &= (uint8) ~USBUART_PC_ARB_CFG_CFG_CMP;

#endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */

    /* Enable interrupt SIE interurpt source from EP0-EP1 */
    USBUART_PC_SIE_EP_INT_EN_REG = (uint8) USBUART_PC_DEFAULT_SIE_EP_INT_EN;
}


/*******************************************************************************
* Function Name: USBUART_PC_EpStateInit
****************************************************************************//**
*
*  This routine initialize state of Data end points based of its type: 
*   IN  - USBUART_PC_IN_BUFFER_EMPTY (USBUART_PC_EVENT_PENDING)
*   OUT - USBUART_PC_OUT_BUFFER_EMPTY (USBUART_PC_NO_EVENT_PENDING)
*
*******************************************************************************/
void USBUART_PC_EpStateInit(void) 
{
    uint8 i;

    for (i = USBUART_PC_EP1; i < USBUART_PC_MAX_EP; i++)
    { 
        if (0u != (USBUART_PC_EP[i].addr & USBUART_PC_DIR_IN))
        {
            /* IN Endpoint */
            USBUART_PC_EP[i].apiEpState = USBUART_PC_EVENT_PENDING;
        }
        else
        {
            /* OUT Endpoint */
            USBUART_PC_EP[i].apiEpState = USBUART_PC_NO_EVENT_PENDING;
        }
    }
                    
}


/*******************************************************************************
* Function Name: USBUART_PC_Config
****************************************************************************//**
*
*  This routine configures endpoints for the entire configuration by scanning
*  the configuration descriptor.
*
*  \param clearAltSetting: It configures the bAlternateSetting 0 for each interface.
*
* USBUART_PC_interfaceClass - Initialized class array for each interface.
*   It is used for handling Class specific requests depend on interface class.
*   Different classes in multiple Alternate settings does not supported.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBUART_PC_Config(uint8 clearAltSetting) 
{
    uint8 ep;
    uint8 curEp;
    uint8 i;
    uint8 epType;
    const uint8 *pDescr;
    
    #if (!USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
        uint16 buffCount = 0u;
    #endif /* (!USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */

    const T_USBUART_PC_LUT CYCODE *pTmp;
    const T_USBUART_PC_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Clear endpoints settings */
    for (ep = 0u; ep < USBUART_PC_MAX_EP; ++ep)
    {
        USBUART_PC_EP[ep].attrib     = 0u;
        USBUART_PC_EP[ep].hwEpState  = 0u;
        USBUART_PC_EP[ep].epToggle   = 0u;
        USBUART_PC_EP[ep].bufferSize = 0u;
        USBUART_PC_EP[ep].interface  = 0u;
        USBUART_PC_EP[ep].apiEpState = USBUART_PC_NO_EVENT_PENDING;
        USBUART_PC_EP[ep].epMode     = USBUART_PC_MODE_DISABLE;   
    }

    /* Clear Alternate settings for all interfaces. */
    if (0u != clearAltSetting)
    {
        for (i = 0u; i < USBUART_PC_MAX_INTERFACES_NUMBER; ++i)
        {
            USBUART_PC_interfaceSetting[i]     = 0u;
            USBUART_PC_interfaceSettingLast[i] = 0u;
        }
    }

    /* Init Endpoints and Device Status if configured */
    if (USBUART_PC_configuration > 0u)
    {
        #if defined(USBUART_PC_ENABLE_CDC_CLASS)
            uint8 cdcComNums = 0u;
        #endif  /* (USBUART_PC_ENABLE_CDC_CLASS) */  

        pTmp = USBUART_PC_GetConfigTablePtr(USBUART_PC_configuration - 1u);
        
        /* Set Power status for current configuration */
        pDescr = (const uint8 *)pTmp->p_list;
        if ((pDescr[USBUART_PC_CONFIG_DESCR_ATTRIB] & USBUART_PC_CONFIG_DESCR_ATTRIB_SELF_POWERED) != 0u)
        {
            USBUART_PC_deviceStatus |= (uint8)  USBUART_PC_DEVICE_STATUS_SELF_POWERED;
        }
        else
        {
            USBUART_PC_deviceStatus &= (uint8) ~USBUART_PC_DEVICE_STATUS_SELF_POWERED;
        }
        
        /* Move to next element */
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        #if (USBUART_PC_EP_MANAGEMENT_MANUAL && USBUART_PC_EP_ALLOC_DYNAMIC)
            /* Configure for dynamic EP memory allocation */
            /* p_list points the endpoint setting table. */
            pEP = (T_USBUART_PC_EP_SETTINGS_BLOCK *) pTmp->p_list;
            
            for (i = 0u; i < ep; i++)
            {     
                /* Compare current Alternate setting with EP Alt */
                if (USBUART_PC_interfaceSetting[pEP->interface] == pEP->altSetting)
                {                                                          
                    curEp  = pEP->addr & USBUART_PC_DIR_UNUSED;
                    epType = pEP->attributes & USBUART_PC_EP_TYPE_MASK;
                    
                    USBUART_PC_EP[curEp].addr       = pEP->addr;
                    USBUART_PC_EP[curEp].attrib     = pEP->attributes;
                    USBUART_PC_EP[curEp].bufferSize = pEP->bufferSize;

                    if (0u != (pEP->addr & USBUART_PC_DIR_IN))
                    {
                        /* IN Endpoint */
                        USBUART_PC_EP[curEp].epMode     = USBUART_PC_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                        USBUART_PC_EP[curEp].apiEpState = USBUART_PC_EVENT_PENDING;
                    
                    #if (defined(USBUART_PC_ENABLE_MIDI_STREAMING) && (USBUART_PC_MIDI_IN_BUFF_SIZE > 0))
                        if ((pEP->bMisc == USBUART_PC_CLASS_AUDIO) && (epType == USBUART_PC_EP_TYPE_BULK))
                        {
                            USBUART_PC_midi_in_ep = curEp;
                        }
                    #endif  /* (USBUART_PC_ENABLE_MIDI_STREAMING) */
                    }
                    else
                    {
                        /* OUT Endpoint */
                        USBUART_PC_EP[curEp].epMode     = USBUART_PC_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                        USBUART_PC_EP[curEp].apiEpState = USBUART_PC_NO_EVENT_PENDING;
                        
                    #if (defined(USBUART_PC_ENABLE_MIDI_STREAMING) && (USBUART_PC_MIDI_OUT_BUFF_SIZE > 0))
                        if ((pEP->bMisc == USBUART_PC_CLASS_AUDIO) && (epType == USBUART_PC_EP_TYPE_BULK))
                        {
                            USBUART_PC_midi_out_ep = curEp;
                        }
                    #endif  /* (USBUART_PC_ENABLE_MIDI_STREAMING) */
                    }

                #if(defined (USBUART_PC_ENABLE_CDC_CLASS))
                    if((pEP->bMisc == USBUART_PC_CLASS_CDC_DATA) ||(pEP->bMisc == USBUART_PC_CLASS_CDC))
                    {
                        cdcComNums = USBUART_PC_Cdc_EpInit(pEP, curEp, cdcComNums);
                    }
                #endif  /* (USBUART_PC_ENABLE_CDC_CLASS) */
                }
                
                pEP = &pEP[1u];
            }
            
        #else
            for (i = USBUART_PC_EP1; i < USBUART_PC_MAX_EP; ++i)
            {
                /* p_list points the endpoint setting table. */
                pEP = (const T_USBUART_PC_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
                /* Find max length for each EP and select it (length could be different in different Alt settings) */
                /* but other settings should be correct with regards to Interface alt Setting */
                
                for (curEp = 0u; curEp < ep; ++curEp)
                {
                    if (i == (pEP->addr & USBUART_PC_DIR_UNUSED))
                    {
                        /* Compare endpoint buffers size with current size to find greater. */
                        if (USBUART_PC_EP[i].bufferSize < pEP->bufferSize)
                        {
                            USBUART_PC_EP[i].bufferSize = pEP->bufferSize;
                        }
                        
                        /* Compare current Alternate setting with EP Alt */
                        if (USBUART_PC_interfaceSetting[pEP->interface] == pEP->altSetting)
                        {                            
                            USBUART_PC_EP[i].addr = pEP->addr;
                            USBUART_PC_EP[i].attrib = pEP->attributes;
                            
                            epType = pEP->attributes & USBUART_PC_EP_TYPE_MASK;
                            
                            if (0u != (pEP->addr & USBUART_PC_DIR_IN))
                            {
                                /* IN Endpoint */
                                USBUART_PC_EP[i].epMode     = USBUART_PC_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                                USBUART_PC_EP[i].apiEpState = USBUART_PC_EVENT_PENDING;
                                
                            #if (defined(USBUART_PC_ENABLE_MIDI_STREAMING) && (USBUART_PC_MIDI_IN_BUFF_SIZE > 0))
                                if ((pEP->bMisc == USBUART_PC_CLASS_AUDIO) && (epType == USBUART_PC_EP_TYPE_BULK))
                                {
                                    USBUART_PC_midi_in_ep = i;
                                }
                            #endif  /* (USBUART_PC_ENABLE_MIDI_STREAMING) */
                            }
                            else
                            {
                                /* OUT Endpoint */
                                USBUART_PC_EP[i].epMode     = USBUART_PC_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                                USBUART_PC_EP[i].apiEpState = USBUART_PC_NO_EVENT_PENDING;
                                
                            #if (defined(USBUART_PC_ENABLE_MIDI_STREAMING) && (USBUART_PC_MIDI_OUT_BUFF_SIZE > 0))
                                if ((pEP->bMisc == USBUART_PC_CLASS_AUDIO) && (epType == USBUART_PC_EP_TYPE_BULK))
                                {
                                    USBUART_PC_midi_out_ep = i;
                                }
                            #endif  /* (USBUART_PC_ENABLE_MIDI_STREAMING) */
                            }

                        #if (defined(USBUART_PC_ENABLE_CDC_CLASS))
                            if((pEP->bMisc == USBUART_PC_CLASS_CDC_DATA) ||(pEP->bMisc == USBUART_PC_CLASS_CDC))
                            {
                                cdcComNums = USBUART_PC_Cdc_EpInit(pEP, i, cdcComNums);
                            }
                        #endif  /* (USBUART_PC_ENABLE_CDC_CLASS) */

                            #if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
                                break;  /* Use first EP setting in Auto memory management */
                            #endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */
                        }
                    }
                    
                    pEP = &pEP[1u];
                }
            }
        #endif /*  (USBUART_PC_EP_MANAGEMENT_MANUAL && USBUART_PC_EP_ALLOC_DYNAMIC) */

        /* Init class array for each interface and interface number for each EP.
        *  It is used for handling Class specific requests directed to either an
        *  interface or the endpoint.
        */
        /* p_list points the endpoint setting table. */
        pEP = (const T_USBUART_PC_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /* Configure interface number for each EP */
            USBUART_PC_EP[pEP->addr & USBUART_PC_DIR_UNUSED].interface = pEP->interface;
            pEP = &pEP[1u];
        }
        
        /* Init pointer on interface class table */
        USBUART_PC_interfaceClass = USBUART_PC_GetInterfaceClassTablePtr();
        
    /* Set the endpoint buffer addresses */
    #if (!USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
        buffCount = 0u;
        for (ep = USBUART_PC_EP1; ep < USBUART_PC_MAX_EP; ++ep)
        {
            USBUART_PC_EP[ep].buffOffset = buffCount;        
            buffCount += USBUART_PC_EP[ep].bufferSize;
            
        #if (USBUART_PC_GEN_16BITS_EP_ACCESS)
            /* Align EP buffers to be event size to access 16-bits DR register. */
            buffCount += (0u != (buffCount & 0x01u)) ? 1u : 0u;
        #endif /* (USBUART_PC_GEN_16BITS_EP_ACCESS) */            
        }
    #endif /* (!USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */

        /* Configure hardware registers */
        USBUART_PC_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: USBUART_PC_ConfigAltChanged
****************************************************************************//**
*
*  This routine update configuration for the required endpoints only.
*  It is called after SET_INTERFACE request when Static memory allocation used.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBUART_PC_ConfigAltChanged(void) 
{
    uint8 ep;
    uint8 curEp;
    uint8 epType;
    uint8 i;
    uint8 interfaceNum;

    const T_USBUART_PC_LUT CYCODE *pTmp;
    const T_USBUART_PC_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Init Endpoints and Device Status if configured */
    if (USBUART_PC_configuration > 0u)
    {
        /* Get number of endpoints configurations (ep). */
        pTmp = USBUART_PC_GetConfigTablePtr(USBUART_PC_configuration - 1u);
        pTmp = &pTmp[1u];
        ep = pTmp->c;

        /* Get pointer to endpoints setting table (pEP). */
        pEP = (const T_USBUART_PC_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        
        /* Look through all possible endpoint configurations. Find endpoints 
        * which belong to current interface and alternate settings for 
        * re-configuration.
        */
        interfaceNum = USBUART_PC_interfaceNumber;
        for (i = 0u; i < ep; i++)
        {
            /* Find endpoints which belong to current interface and alternate settings. */
            if ((interfaceNum == pEP->interface) && 
                (USBUART_PC_interfaceSetting[interfaceNum] == pEP->altSetting))
            {
                curEp  = ((uint8) pEP->addr & USBUART_PC_DIR_UNUSED);
                epType = ((uint8) pEP->attributes & USBUART_PC_EP_TYPE_MASK);
                
                /* Change the SIE mode for the selected EP to NAK ALL */
                USBUART_PC_EP[curEp].epToggle   = 0u;
                USBUART_PC_EP[curEp].addr       = pEP->addr;
                USBUART_PC_EP[curEp].attrib     = pEP->attributes;
                USBUART_PC_EP[curEp].bufferSize = pEP->bufferSize;

                if (0u != (pEP->addr & USBUART_PC_DIR_IN))
                {
                    /* IN Endpoint */
                    USBUART_PC_EP[curEp].epMode     = USBUART_PC_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                    USBUART_PC_EP[curEp].apiEpState = USBUART_PC_EVENT_PENDING;
                }
                else
                {
                    /* OUT Endpoint */
                    USBUART_PC_EP[curEp].epMode     = USBUART_PC_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                    USBUART_PC_EP[curEp].apiEpState = USBUART_PC_NO_EVENT_PENDING;
                }
                
                /* Make SIE to NAK any endpoint requests */
                USBUART_PC_SIE_EP_BASE.sieEp[curEp].epCr0 = USBUART_PC_MODE_NAK_IN_OUT;

            #if (USBUART_PC_EP_MANAGEMENT_DMA_AUTO)
                /* Clear IN data ready. */
                USBUART_PC_ARB_EP_BASE.arbEp[curEp].epCfg &= (uint8) ~USBUART_PC_ARB_EPX_CFG_IN_DATA_RDY;

                /* Select endpoint number of reconfiguration */
                USBUART_PC_DYN_RECONFIG_REG = (uint8) ((curEp - 1u) << USBUART_PC_DYN_RECONFIG_EP_SHIFT);
                
                /* Request for dynamic re-configuration of endpoint. */
                USBUART_PC_DYN_RECONFIG_REG |= USBUART_PC_DYN_RECONFIG_ENABLE;
                
                /* Wait until block is ready for re-configuration */
                while (0u == (USBUART_PC_DYN_RECONFIG_REG & USBUART_PC_DYN_RECONFIG_RDY_STS))
                {
                }
                
                /* Once DYN_RECONFIG_RDY_STS bit is set, FW can change the EP configuration. */
                /* Change EP Type with new direction */
                if (0u != (pEP->addr & USBUART_PC_DIR_IN))
                {
                    /* Set endpoint type: 0 - IN and 1 - OUT. */
                    USBUART_PC_EP_TYPE_REG &= (uint8) ~(uint8)((uint8) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Clear DMA_TERMIN for IN endpoint */
                    USBUART_PC_ARB_EP_BASE.arbEp[curEp].epIntEn &= (uint32) ~USBUART_PC_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                else
                {
                    /* Set endpoint type: 0 - IN and 1- OUT. */
                    USBUART_PC_EP_TYPE_REG |= (uint8) ((uint8) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Set DMA_TERMIN for OUT endpoint */
                    USBUART_PC_ARB_EP_BASE.arbEp[curEp].epIntEn |= (uint32) USBUART_PC_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                
                /* Complete dynamic re-configuration: all endpoint related status and signals 
                * are set into the default state.
                */
                USBUART_PC_DYN_RECONFIG_REG &= (uint8) ~USBUART_PC_DYN_RECONFIG_ENABLE;

            #else
                USBUART_PC_SIE_EP_BASE.sieEp[curEp].epCnt0 = HI8(USBUART_PC_EP[curEp].bufferSize);
                USBUART_PC_SIE_EP_BASE.sieEp[curEp].epCnt1 = LO8(USBUART_PC_EP[curEp].bufferSize);
                
                #if (CY_PSOC4)
                    USBUART_PC_ARB_EP16_BASE.arbEp[curEp].rwRa16  = (uint32) USBUART_PC_EP[curEp].buffOffset;
                    USBUART_PC_ARB_EP16_BASE.arbEp[curEp].rwWa16  = (uint32) USBUART_PC_EP[curEp].buffOffset;
                #else
                    USBUART_PC_ARB_EP_BASE.arbEp[curEp].rwRa    = LO8(USBUART_PC_EP[curEp].buffOffset);
                    USBUART_PC_ARB_EP_BASE.arbEp[curEp].rwRaMsb = HI8(USBUART_PC_EP[curEp].buffOffset);
                    USBUART_PC_ARB_EP_BASE.arbEp[curEp].rwWa    = LO8(USBUART_PC_EP[curEp].buffOffset);
                    USBUART_PC_ARB_EP_BASE.arbEp[curEp].rwWaMsb = HI8(USBUART_PC_EP[curEp].buffOffset);
                #endif /* (CY_PSOC4) */                
            #endif /* (USBUART_PC_EP_MANAGEMENT_DMA_AUTO) */
            }
            
            pEP = &pEP[1u]; /* Get next EP element */
        }
        
        /* The main loop has to re-enable DMA and OUT endpoint */
    }
}


/*******************************************************************************
* Function Name: USBUART_PC_GetConfigTablePtr
****************************************************************************//**
*
*  This routine returns a pointer a configuration table entry
*
*  \param confIndex:  Configuration Index
*
* \return
*  Device Descriptor pointer or NULL when descriptor does not exist.
*
*******************************************************************************/
const T_USBUART_PC_LUT CYCODE *USBUART_PC_GetConfigTablePtr(uint8 confIndex)
                                                        
{
    /* Device Table */
    const T_USBUART_PC_LUT CYCODE *pTmp;

    pTmp = (const T_USBUART_PC_LUT CYCODE *) USBUART_PC_TABLE[USBUART_PC_device].p_list;

    /* The first entry points to the Device Descriptor,
    *  the second entry point to the BOS Descriptor
    *  the rest configuration entries.
    *  Set pointer to the first Configuration Descriptor
    */
    pTmp = &pTmp[2u];
    /* For this table, c is the number of configuration descriptors  */
    if(confIndex >= pTmp->c)   /* Verify that required configuration descriptor exists */
    {
        pTmp = (const T_USBUART_PC_LUT CYCODE *) NULL;
    }
    else
    {
        pTmp = (const T_USBUART_PC_LUT CYCODE *) pTmp[confIndex].p_list;
    }

    return (pTmp);
}


#if (USBUART_PC_BOS_ENABLE)
    /*******************************************************************************
    * Function Name: USBUART_PC_GetBOSPtr
    ****************************************************************************//**
    *
    *  This routine returns a pointer a BOS table entry
    *
    *  
    *
    * \return
    *  BOS Descriptor pointer or NULL when descriptor does not exist.
    *
    *******************************************************************************/
    const T_USBUART_PC_LUT CYCODE *USBUART_PC_GetBOSPtr(void)
                                                            
    {
        /* Device Table */
        const T_USBUART_PC_LUT CYCODE *pTmp;

        pTmp = (const T_USBUART_PC_LUT CYCODE *) USBUART_PC_TABLE[USBUART_PC_device].p_list;

        /* The first entry points to the Device Descriptor,
        *  the second entry points to the BOS Descriptor
        */
        pTmp = &pTmp[1u];
        pTmp = (const T_USBUART_PC_LUT CYCODE *) pTmp->p_list;
        return (pTmp);
    }
#endif /* (USBUART_PC_BOS_ENABLE) */


/*******************************************************************************
* Function Name: USBUART_PC_GetDeviceTablePtr
****************************************************************************//**
*
*  This routine returns a pointer to the Device table
*
* \return
*  Device Table pointer
*
*******************************************************************************/
const T_USBUART_PC_LUT CYCODE *USBUART_PC_GetDeviceTablePtr(void)
                                                            
{
    /* Device Table */
    return( (const T_USBUART_PC_LUT CYCODE *) USBUART_PC_TABLE[USBUART_PC_device].p_list );
}


/*******************************************************************************
* Function Name: USB_GetInterfaceClassTablePtr
****************************************************************************//**
*
*  This routine returns Interface Class table pointer, which contains
*  the relation between interface number and interface class.
*
* \return
*  Interface Class table pointer.
*
*******************************************************************************/
const uint8 CYCODE *USBUART_PC_GetInterfaceClassTablePtr(void)
                                                        
{
    const T_USBUART_PC_LUT CYCODE *pTmp;
    const uint8 CYCODE *pInterfaceClass;
    uint8 currentInterfacesNum;

    pTmp = USBUART_PC_GetConfigTablePtr(USBUART_PC_configuration - 1u);
    if (pTmp != NULL)
    {
        currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[USBUART_PC_CONFIG_DESCR_NUM_INTERFACES];
        /* Third entry in the LUT starts the Interface Table pointers */
        /* The INTERFACE_CLASS table is located after all interfaces */
        pTmp = &pTmp[currentInterfacesNum + 2u];
        pInterfaceClass = (const uint8 CYCODE *) pTmp->p_list;
    }
    else
    {
        pInterfaceClass = (const uint8 CYCODE *) NULL;
    }

    return (pInterfaceClass);
}


/*******************************************************************************
* Function Name: USBUART_PC_TerminateEP
****************************************************************************//**
*
*  This function terminates the specified USBFS endpoint.
*  This function should be used before endpoint reconfiguration.
*
*  \param ep Contains the data endpoint number.
*
*  \reentrant
*  No.
*
* \sideeffect
* 
* The device responds with a NAK for any transactions on the selected endpoint.
*   
*******************************************************************************/
void USBUART_PC_TerminateEP(uint8 epNumber) 
{
    /* Get endpoint number */
    epNumber &= USBUART_PC_DIR_UNUSED;

    if ((epNumber > USBUART_PC_EP0) && (epNumber < USBUART_PC_MAX_EP))
    {
        /* Set the endpoint Halt */
        USBUART_PC_EP[epNumber].hwEpState |= USBUART_PC_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        USBUART_PC_EP[epNumber].epToggle = 0u;
        USBUART_PC_EP[epNumber].apiEpState = USBUART_PC_NO_EVENT_ALLOWED;

        if ((USBUART_PC_EP[epNumber].addr & USBUART_PC_DIR_IN) != 0u)
        {   
            /* IN Endpoint */
            USBUART_PC_SIE_EP_BASE.sieEp[epNumber].epCr0 = USBUART_PC_MODE_NAK_IN;
        }
        else
        {
            /* OUT Endpoint */
            USBUART_PC_SIE_EP_BASE.sieEp[epNumber].epCr0 = USBUART_PC_MODE_NAK_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: USBUART_PC_SetEndpointHalt
****************************************************************************//**
*
*  This routine handles set endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_SetEndpointHalt(void) 
{
    uint8 requestHandled = USBUART_PC_FALSE;
    uint8 ep;
    
    /* Set endpoint halt */
    ep = USBUART_PC_wIndexLoReg & USBUART_PC_DIR_UNUSED;

    if ((ep > USBUART_PC_EP0) && (ep < USBUART_PC_MAX_EP))
    {
        /* Set the endpoint Halt */
        USBUART_PC_EP[ep].hwEpState |= (USBUART_PC_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        USBUART_PC_EP[ep].epToggle = 0u;
        USBUART_PC_EP[ep].apiEpState |= USBUART_PC_NO_EVENT_ALLOWED;

        if ((USBUART_PC_EP[ep].addr & USBUART_PC_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = (USBUART_PC_MODE_STALL_DATA_EP | 
                                                            USBUART_PC_MODE_ACK_IN);
        }
        else
        {
            /* OUT Endpoint */
            USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = (USBUART_PC_MODE_STALL_DATA_EP | 
                                                            USBUART_PC_MODE_ACK_OUT);
        }
        requestHandled = USBUART_PC_InitNoDataControlTransfer();
    }

    return (requestHandled);
}


/*******************************************************************************
* Function Name: USBUART_PC_ClearEndpointHalt
****************************************************************************//**
*
*  This routine handles clear endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_ClearEndpointHalt(void) 
{
    uint8 requestHandled = USBUART_PC_FALSE;
    uint8 ep;

    /* Clear endpoint halt */
    ep = USBUART_PC_wIndexLoReg & USBUART_PC_DIR_UNUSED;

    if ((ep > USBUART_PC_EP0) && (ep < USBUART_PC_MAX_EP))
    {
        /* Clear the endpoint Halt */
        USBUART_PC_EP[ep].hwEpState &= (uint8) ~USBUART_PC_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        USBUART_PC_EP[ep].epToggle = 0u;
        
        /* Clear toggle bit for already armed packet */
        USBUART_PC_SIE_EP_BASE.sieEp[ep].epCnt0 &= (uint8) ~(uint8)USBUART_PC_EPX_CNT_DATA_TOGGLE;
        
        /* Return API State as it was defined before */
        USBUART_PC_EP[ep].apiEpState &= (uint8) ~USBUART_PC_NO_EVENT_ALLOWED;

        if ((USBUART_PC_EP[ep].addr & USBUART_PC_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            if(USBUART_PC_EP[ep].apiEpState == USBUART_PC_IN_BUFFER_EMPTY)
            {       
                /* Wait for next packet from application */
                USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = USBUART_PC_MODE_NAK_IN;
            }
            else    /* Continue armed transfer */
            {
                USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = USBUART_PC_MODE_ACK_IN;
            }
        }
        else
        {
            /* OUT Endpoint */
            if (USBUART_PC_EP[ep].apiEpState == USBUART_PC_OUT_BUFFER_FULL)
            {       
                /* Allow application to read full buffer */
                USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = USBUART_PC_MODE_NAK_OUT;
            }
            else    /* Mark endpoint as empty, so it will be reloaded */
            {
                USBUART_PC_SIE_EP_BASE.sieEp[ep].epCr0 = USBUART_PC_MODE_ACK_OUT;
            }
        }
        
        requestHandled = USBUART_PC_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: USBUART_PC_ValidateAlternateSetting
****************************************************************************//**
*
*  Validates (and records) a SET INTERFACE request.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_PC_ValidateAlternateSetting(void) 
{
    uint8 requestHandled = USBUART_PC_FALSE;
    
    uint8 interfaceNum;
    uint8 curInterfacesNum;
    const T_USBUART_PC_LUT CYCODE *pTmp;
    
    /* Get interface number from the request. */
    interfaceNum = (uint8) USBUART_PC_wIndexLoReg;
    
    /* Get number of interfaces for current configuration. */
    pTmp = USBUART_PC_GetConfigTablePtr(USBUART_PC_configuration - 1u);
    curInterfacesNum  = ((const uint8 *) pTmp->p_list)[USBUART_PC_CONFIG_DESCR_NUM_INTERFACES];

    /* Validate that interface number is within range. */
    if ((interfaceNum <= curInterfacesNum) || (interfaceNum <= USBUART_PC_MAX_INTERFACES_NUMBER))
    {
        /* Save current and new alternate settings (come with request) to make 
        * desicion about following endpoint re-configuration.
        */
        USBUART_PC_interfaceSettingLast[interfaceNum] = USBUART_PC_interfaceSetting[interfaceNum];
        USBUART_PC_interfaceSetting[interfaceNum]     = (uint8) USBUART_PC_wValueLoReg;
        
        requestHandled = USBUART_PC_TRUE;
    }

    return (requestHandled);
}


/* [] END OF FILE */
