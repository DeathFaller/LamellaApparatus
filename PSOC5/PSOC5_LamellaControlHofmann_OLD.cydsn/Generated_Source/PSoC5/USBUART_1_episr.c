/*******************************************************************************
* File Name: USBUART_1_episr.c
* Version 2.80
*
* Description:
*  Data endpoint Interrupt Service Routines
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

#if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && (USBUART_1_ENABLE_MIDI_API != 0u))
    #include "USBUART_1_midi.h"
#endif /* (defined(USBUART_1_ENABLE_MIDI_STREAMING) && (USBUART_1_ENABLE_MIDI_API != 0u)) */
#if ((USBUART_1_EP_MM == USBUART_1__EP_DMAAUTO) && (USBUART_1_EP_DMA_AUTO_OPT == 0u))
    #include "USBUART_1_EP8_DMA_Done_SR.h"
    #include "USBUART_1_EP17_DMA_Done_SR.h"
#endif /* (USBUART_1_EP_MM == USBUART_1__EP_DMAAUTO) && (USBUART_1_EP_DMA_AUTO_OPT == 0u) */


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if(USBUART_1_EP1_ISR_REMOVE == 0u)


    /******************************************************************************
    * Function Name: USBUART_1_EP_1_ISR
    *******************************************************************************
    *
    * Summary:
    *  Endpoint 1 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    ******************************************************************************/
    CY_ISR(USBUART_1_EP_1_ISR)
    {
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT)  && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        #ifdef USBUART_1_EP_1_ISR_ENTRY_CALLBACK
            USBUART_1_EP_1_ISR_EntryCallback();
        #endif /* USBUART_1_EP_1_ISR_ENTRY_CALLBACK */

        /* `#START EP1_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        CY_GET_REG8(USBUART_1_SIE_EP1_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USBUART_1_EP[USBUART_1_EP1].attrib & USBUART_1_EP_TYPE_MASK) !=
                                                                                    USBUART_1_EP_TYPE_ISOC)
        {
            USBUART_1_EP[USBUART_1_EP1].epToggle ^= USBUART_1_EPX_CNT_DATA_TOGGLE;
        }
        USBUART_1_EP[USBUART_1_EP1].apiEpState = USBUART_1_EVENT_PENDING;
        CY_SET_REG8(USBUART_1_SIE_EP_INT_SR_PTR, CY_GET_REG8(USBUART_1_SIE_EP_INT_SR_PTR) &
                                                                    (uint8)~USBUART_1_SIE_EP_INT_EP1_MASK);

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT)
            if(USBUART_1_midi_out_ep == USBUART_1_EP1)
            {
                USBUART_1_MIDI_OUT_EP_Service();
            }
        #endif /*  USBUART_1_ISR_SERVICE_MIDI_OUT */

        /* `#START EP1_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_1_ISR_EXIT_CALLBACK
            USBUART_1_EP_1_ISR_ExitCallback();
        #endif /* USBUART_1_EP_1_ISR_EXIT_CALLBACK */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */
    }

#endif   /*  USBUART_1_EP1_ISR_REMOVE */


#if(USBUART_1_EP2_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USBUART_1_EP_2_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 2 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USBUART_1_EP_2_ISR)
    {
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        #ifdef USBUART_1_EP_2_ISR_ENTRY_CALLBACK
            USBUART_1_EP_2_ISR_EntryCallback();
        #endif /* USBUART_1_EP_2_ISR_ENTRY_CALLBACK */

        /* `#START EP2_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        CY_GET_REG8(USBUART_1_SIE_EP2_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USBUART_1_EP[USBUART_1_EP2].attrib & USBUART_1_EP_TYPE_MASK) !=
                                                                                    USBUART_1_EP_TYPE_ISOC)
        {
            USBUART_1_EP[USBUART_1_EP2].epToggle ^= USBUART_1_EPX_CNT_DATA_TOGGLE;
        }
        USBUART_1_EP[USBUART_1_EP2].apiEpState = USBUART_1_EVENT_PENDING;
        CY_SET_REG8(USBUART_1_SIE_EP_INT_SR_PTR, CY_GET_REG8(USBUART_1_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~USBUART_1_SIE_EP_INT_EP2_MASK);

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT)
            if(USBUART_1_midi_out_ep == USBUART_1_EP2)
            {
                USBUART_1_MIDI_OUT_EP_Service();
            }
        #endif /*  USBUART_1_ISR_SERVICE_MIDI_OUT */

        /* `#START EP2_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_2_ISR_EXIT_CALLBACK
            USBUART_1_EP_2_ISR_ExitCallback();
        #endif /* USBUART_1_EP_2_ISR_EXIT_CALLBACK */
        
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */
    }

#endif   /*  USBUART_1_EP2_ISR_REMOVE */


#if(USBUART_1_EP3_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USBUART_1_EP_3_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 3 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USBUART_1_EP_3_ISR)
    {
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        #ifdef USBUART_1_EP_3_ISR_ENTRY_CALLBACK
            USBUART_1_EP_3_ISR_EntryCallback();
        #endif /* USBUART_1_EP_3_ISR_ENTRY_CALLBACK */

        /* `#START EP3_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(USBUART_1_SIE_EP3_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USBUART_1_EP[USBUART_1_EP3].attrib & USBUART_1_EP_TYPE_MASK) !=
                                                                                    USBUART_1_EP_TYPE_ISOC)
        {
            USBUART_1_EP[USBUART_1_EP3].epToggle ^= USBUART_1_EPX_CNT_DATA_TOGGLE;
        }
        USBUART_1_EP[USBUART_1_EP3].apiEpState = USBUART_1_EVENT_PENDING;
        CY_SET_REG8(USBUART_1_SIE_EP_INT_SR_PTR, CY_GET_REG8(USBUART_1_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~USBUART_1_SIE_EP_INT_EP3_MASK);

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT)
            if(USBUART_1_midi_out_ep == USBUART_1_EP3)
            {
                USBUART_1_MIDI_OUT_EP_Service();
            }
        #endif /*  USBUART_1_ISR_SERVICE_MIDI_OUT */

        /* `#START EP3_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_3_ISR_EXIT_CALLBACK
            USBUART_1_EP_3_ISR_ExitCallback();
        #endif /* USBUART_1_EP_3_ISR_EXIT_CALLBACK */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  USBUART_1_EP3_ISR_REMOVE */


#if(USBUART_1_EP4_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USBUART_1_EP_4_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 4 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USBUART_1_EP_4_ISR)
    {
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        #ifdef USBUART_1_EP_4_ISR_ENTRY_CALLBACK
            USBUART_1_EP_4_ISR_EntryCallback();
        #endif /* USBUART_1_EP_4_ISR_ENTRY_CALLBACK */

        /* `#START EP4_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(USBUART_1_SIE_EP4_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USBUART_1_EP[USBUART_1_EP4].attrib & USBUART_1_EP_TYPE_MASK) !=
                                                                                    USBUART_1_EP_TYPE_ISOC)
        {
            USBUART_1_EP[USBUART_1_EP4].epToggle ^= USBUART_1_EPX_CNT_DATA_TOGGLE;
        }
        USBUART_1_EP[USBUART_1_EP4].apiEpState = USBUART_1_EVENT_PENDING;
        CY_SET_REG8(USBUART_1_SIE_EP_INT_SR_PTR, CY_GET_REG8(USBUART_1_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~USBUART_1_SIE_EP_INT_EP4_MASK);

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT)
            if(USBUART_1_midi_out_ep == USBUART_1_EP4)
            {
                USBUART_1_MIDI_OUT_EP_Service();
            }
        #endif /*  USBUART_1_ISR_SERVICE_MIDI_OUT */

        /* `#START EP4_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_4_ISR_EXIT_CALLBACK
            USBUART_1_EP_4_ISR_ExitCallback();
        #endif /* USBUART_1_EP_4_ISR_EXIT_CALLBACK */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  USBUART_1_EP4_ISR_REMOVE */


#if(USBUART_1_EP5_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USBUART_1_EP_5_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 5 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USBUART_1_EP_5_ISR)
    {
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        #ifdef USBUART_1_EP_5_ISR_ENTRY_CALLBACK
            USBUART_1_EP_5_ISR_EntryCallback();
        #endif /* USBUART_1_EP_5_ISR_ENTRY_CALLBACK */

        /* `#START EP5_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(USBUART_1_SIE_EP5_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USBUART_1_EP[USBUART_1_EP5].attrib & USBUART_1_EP_TYPE_MASK) !=
                                                                                    USBUART_1_EP_TYPE_ISOC)
        {
            USBUART_1_EP[USBUART_1_EP5].epToggle ^= USBUART_1_EPX_CNT_DATA_TOGGLE;
        }
        USBUART_1_EP[USBUART_1_EP5].apiEpState = USBUART_1_EVENT_PENDING;
        CY_SET_REG8(USBUART_1_SIE_EP_INT_SR_PTR, CY_GET_REG8(USBUART_1_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~USBUART_1_SIE_EP_INT_EP5_MASK);

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT)
            if(USBUART_1_midi_out_ep == USBUART_1_EP5)
            {
                USBUART_1_MIDI_OUT_EP_Service();
            }
        #endif /*  USBUART_1_ISR_SERVICE_MIDI_OUT */

        /* `#START EP5_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_5_ISR_EXIT_CALLBACK
            USBUART_1_EP_5_ISR_ExitCallback();
        #endif /* USBUART_1_EP_5_ISR_EXIT_CALLBACK */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */
    }
#endif   /*  USBUART_1_EP5_ISR_REMOVE */


#if(USBUART_1_EP6_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USBUART_1_EP_6_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 6 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USBUART_1_EP_6_ISR)
    {
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        #ifdef USBUART_1_EP_6_ISR_ENTRY_CALLBACK
            USBUART_1_EP_6_ISR_EntryCallback();
        #endif /* USBUART_1_EP_6_ISR_ENTRY_CALLBACK */

        /* `#START EP6_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(USBUART_1_SIE_EP6_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USBUART_1_EP[USBUART_1_EP6].attrib & USBUART_1_EP_TYPE_MASK) !=
                                                                                    USBUART_1_EP_TYPE_ISOC)
        {
            USBUART_1_EP[USBUART_1_EP6].epToggle ^= USBUART_1_EPX_CNT_DATA_TOGGLE;
        }
        USBUART_1_EP[USBUART_1_EP6].apiEpState = USBUART_1_EVENT_PENDING;
        CY_SET_REG8(USBUART_1_SIE_EP_INT_SR_PTR, CY_GET_REG8(USBUART_1_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~USBUART_1_SIE_EP_INT_EP6_MASK);

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT)
            if(USBUART_1_midi_out_ep == USBUART_1_EP6)
            {
                USBUART_1_MIDI_OUT_EP_Service();
            }
        #endif /*  USBUART_1_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP6_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_6_ISR_EXIT_CALLBACK
            USBUART_1_EP_6_ISR_ExitCallback();
        #endif /* USBUART_1_EP_6_ISR_EXIT_CALLBACK */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  USBUART_1_EP6_ISR_REMOVE */


#if(USBUART_1_EP7_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USBUART_1_EP_7_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 7 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USBUART_1_EP_7_ISR)
    {
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        #ifdef USBUART_1_EP_7_ISR_ENTRY_CALLBACK
            USBUART_1_EP_7_ISR_EntryCallback();
        #endif /* USBUART_1_EP_7_ISR_ENTRY_CALLBACK */

        /* `#START EP7_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(USBUART_1_SIE_EP7_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USBUART_1_EP[USBUART_1_EP7].attrib & USBUART_1_EP_TYPE_MASK) !=
                                                                                    USBUART_1_EP_TYPE_ISOC)
        {
            USBUART_1_EP[USBUART_1_EP7].epToggle ^= USBUART_1_EPX_CNT_DATA_TOGGLE;
        }
        USBUART_1_EP[USBUART_1_EP7].apiEpState = USBUART_1_EVENT_PENDING;
        CY_SET_REG8(USBUART_1_SIE_EP_INT_SR_PTR, CY_GET_REG8(USBUART_1_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~USBUART_1_SIE_EP_INT_EP7_MASK);

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT)
            if(USBUART_1_midi_out_ep == USBUART_1_EP7)
            {
                USBUART_1_MIDI_OUT_EP_Service();
            }
        #endif /*  USBUART_1_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP7_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_7_ISR_EXIT_CALLBACK
            USBUART_1_EP_7_ISR_ExitCallback();
        #endif /* USBUART_1_EP_7_ISR_EXIT_CALLBACK */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  USBUART_1_EP7_ISR_REMOVE */


#if(USBUART_1_EP8_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USBUART_1_EP_8_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 8 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USBUART_1_EP_8_ISR)
    {
        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        #ifdef USBUART_1_EP_8_ISR_ENTRY_CALLBACK
            USBUART_1_EP_8_ISR_EntryCallback();
        #endif /* USBUART_1_EP_8_ISR_ENTRY_CALLBACK */

        /* `#START EP8_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(USBUART_1_SIE_EP8_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USBUART_1_EP[USBUART_1_EP8].attrib & USBUART_1_EP_TYPE_MASK) !=
                                                                                    USBUART_1_EP_TYPE_ISOC)
        {
            USBUART_1_EP[USBUART_1_EP8].epToggle ^= USBUART_1_EPX_CNT_DATA_TOGGLE;
        }
        USBUART_1_EP[USBUART_1_EP8].apiEpState = USBUART_1_EVENT_PENDING;
        CY_SET_REG8(USBUART_1_SIE_EP_INT_SR_PTR, CY_GET_REG8(USBUART_1_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~USBUART_1_SIE_EP_INT_EP8_MASK);

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT)
            if(USBUART_1_midi_out_ep == USBUART_1_EP8)
            {
                USBUART_1_MIDI_OUT_EP_Service();
            }
        #endif /*  USBUART_1_ISR_SERVICE_MIDI_OUT */

        /* `#START EP8_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_8_ISR_EXIT_CALLBACK
            USBUART_1_EP_8_ISR_ExitCallback();
        #endif /* USBUART_1_EP_8_ISR_EXIT_CALLBACK */

        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && !defined(USBUART_1_MAIN_SERVICE_MIDI_OUT) && \
                     USBUART_1_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & USBUART_1_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  USBUART_1_EP8_ISR_REMOVE */


/*******************************************************************************
* Function Name: USBUART_1_SOF_ISR
********************************************************************************
*
* Summary:
*  Start of Frame Interrupt Service Routine
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(USBUART_1_SOF_ISR)
{
    #ifdef USBUART_1_SOF_ISR_INTERRUPT_CALLBACK
        USBUART_1_SOF_ISR_InterruptCallback();
    #endif /* USBUART_1_SOF_ISR_INTERRUPT_CALLBACK */

    /* `#START SOF_USER_CODE` Place your code here */

    /* `#END` */
}


/*******************************************************************************
* Function Name: USBUART_1_BUS_RESET_ISR
********************************************************************************
*
* Summary:
*  USB Bus Reset Interrupt Service Routine.  Calls _Start with the same
*  parameters as the last USER call to _Start
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(USBUART_1_BUS_RESET_ISR)
{
    #ifdef USBUART_1_BUS_RESET_ISR_ENTRY_CALLBACK
        USBUART_1_BUS_RESET_ISR_EntryCallback();
    #endif /* USBUART_1_BUS_RESET_ISR_ENTRY_CALLBACK */

    /* `#START BUS_RESET_USER_CODE` Place your code here */

    /* `#END` */

    USBUART_1_ReInitComponent();

    #ifdef USBUART_1_BUS_RESET_ISR_EXIT_CALLBACK
        USBUART_1_BUS_RESET_ISR_ExitCallback();
    #endif /* USBUART_1_BUS_RESET_ISR_EXIT_CALLBACK */    
}


#if((USBUART_1_EP_MM != USBUART_1__EP_MANUAL) && (USBUART_1_ARB_ISR_REMOVE == 0u))


    /*******************************************************************************
    * Function Name: USBUART_1_ARB_ISR
    ********************************************************************************
    *
    * Summary:
    *  Arbiter Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side effect:
    *  Search for EP8 int_status will be much slower than search for EP1 int_status.
    *
    *******************************************************************************/
    CY_ISR(USBUART_1_ARB_ISR)
    {
        uint8 int_status;
        uint8 ep_status;
        uint8 ep = USBUART_1_EP1;
        uint8 ptr = 0u;

        #ifdef USBUART_1_ARB_ISR_ENTRY_CALLBACK
            USBUART_1_ARB_ISR_EntryCallback();
        #endif /* USBUART_1_ARB_ISR_ENTRY_CALLBACK */

        /* `#START ARB_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        int_status = USBUART_1_ARB_INT_SR_REG;                   /* read Arbiter Status Register */
        USBUART_1_ARB_INT_SR_REG = int_status;                   /* Clear Serviced Interrupts */

        while(int_status != 0u)
        {
            if((int_status & 1u) != 0u)  /* If EpX interrupt present */
            {   /* read Endpoint Status Register */
                ep_status  = CY_GET_REG8((reg8 *)(USBUART_1_ARB_EP1_SR_IND + ptr));
                /* If In Buffer Full */
                if((ep_status & USBUART_1_ARB_EPX_SR_IN_BUF_FULL) != 0u)
                {
                    if((USBUART_1_EP[ep].addr & USBUART_1_DIR_IN) != 0u)
                    {
                        /* Clear Data ready status */
                        *(reg8 *)(USBUART_1_ARB_EP1_CFG_IND + ptr) &=
                                                                    (uint8)~USBUART_1_ARB_EPX_CFG_IN_DATA_RDY;
                        #if((USBUART_1_EP_MM == USBUART_1__EP_DMAAUTO) && (USBUART_1_EP_DMA_AUTO_OPT == 0u))
                            /* Setup common area DMA with rest of the data */
                            if(USBUART_1_inLength[ep] > USBUART_1_DMA_BYTES_PER_BURST)
                            {
                                USBUART_1_LoadNextInEP(ep, 0u);
                            }
                            else
                            {
                                USBUART_1_inBufFull[ep] = 1u;
                            }
                        #endif /* ((USBUART_1_EP_MM == USBUART_1__EP_DMAAUTO) && (USBUART_1_EP_DMA_AUTO_OPT == 0u)) */
                        /* Write the Mode register */
                        CY_SET_REG8((reg8 *)(USBUART_1_SIE_EP1_CR0_IND + ptr), USBUART_1_EP[ep].epMode);
                        #if (defined(USBUART_1_ENABLE_MIDI_STREAMING) && USBUART_1_ISR_SERVICE_MIDI_IN)
                            if(ep == USBUART_1_midi_in_ep)
                            {   /* Clear MIDI input pointer */
                                USBUART_1_midiInPointer = 0u;
                            }
                        #endif /*  USBUART_1_ENABLE_MIDI_STREAMING*/
                    }
                }
                /* (re)arm Out EP only for mode2 */
                #if(USBUART_1_EP_MM != USBUART_1__EP_DMAAUTO)
                    /* If DMA Grant */
                    if((ep_status & USBUART_1_ARB_EPX_SR_DMA_GNT) != 0u)
                    {
                        if((USBUART_1_EP[ep].addr & USBUART_1_DIR_IN) == 0u)
                        {
                                USBUART_1_EP[ep].apiEpState = USBUART_1_NO_EVENT_PENDING;
                                /* Write the Mode register */
                                CY_SET_REG8((reg8 *)(USBUART_1_SIE_EP1_CR0_IND + ptr),
                                                                                    USBUART_1_EP[ep].epMode);
                        }
                    }
                #endif /*  USBUART_1_EP_MM */

                /* `#START ARB_USER_CODE` Place your code here for handle Buffer Underflow/Overflow */

                /* `#END` */

                #ifdef USBUART_1_ARB_ISR_CALLBACK
                    USBUART_1_ARB_ISR_Callback();
                #endif /* USBUART_1_ARB_ISR_CALLBACK */

                CY_SET_REG8((reg8 *)(USBUART_1_ARB_EP1_SR_IND + ptr), ep_status);   /* Clear Serviced events */
            }
            ptr += USBUART_1_EPX_CNTX_ADDR_OFFSET;               /* prepare pointer for next EP */
            ep++;
            int_status >>= 1u;
        }

        /* `#START ARB_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_ARB_ISR_EXIT_CALLBACK
            USBUART_1_ARB_ISR_ExitCallback();
        #endif /* USBUART_1_ARB_ISR_EXIT_CALLBACK */
    }

#endif /*  USBUART_1_EP_MM */

#if ((USBUART_1_EP_MM == USBUART_1__EP_DMAAUTO) && (USBUART_1_EP_DMA_AUTO_OPT == 0u))
    /******************************************************************************
    * Function Name: USBUART_1_EP_DMA_DONE_ISR
    *******************************************************************************
    *
    * Summary:
    *  Endpoint 1 DMA Done Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    ******************************************************************************/
    CY_ISR(USBUART_1_EP_DMA_DONE_ISR)
    {
        uint8 int8Status;
        uint8 int17Status;
        uint8 ep_status;
        uint8 ep = USBUART_1_EP1;
        uint8 ptr = 0u;

        #ifdef USBUART_1_EP_DMA_DONE_ISR_ENTRY_CALLBACK
            USBUART_1_EP_DMA_DONE_ISR_EntryCallback();
        #endif /* USBUART_1_EP_DMA_DONE_ISR_ENTRY_CALLBACK */

        /* `#START EP_DMA_DONE_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        /* Read clear on read status register with the EP source of interrupt */
        int17Status = USBUART_1_EP17_DMA_Done_SR_Read() & USBUART_1_EP17_SR_MASK;
        int8Status = USBUART_1_EP8_DMA_Done_SR_Read() & USBUART_1_EP8_SR_MASK;

        while(int8Status != 0u)
        {
            while(int17Status != 0u)
            {
                if((int17Status & 1u) != 0u)  /* If EpX interrupt present */
                {
                    /* Read Endpoint Status Register */
                    ep_status = CY_GET_REG8((reg8 *)(USBUART_1_ARB_EP1_SR_IND + ptr));
                    if( ((ep_status & USBUART_1_ARB_EPX_SR_IN_BUF_FULL) == 0u) &&
                        (USBUART_1_inBufFull[ep] == 0u))
                    {
                        /* `#START EP_DMA_DONE_USER_CODE` Place your code here */

                        /* `#END` */

                        #ifdef USBUART_1_EP_DMA_DONE_ISR_CALLBACK
                            USBUART_1_EP_DMA_DONE_ISR_Callback();
                        #endif /* USBUART_1_EP_DMA_DONE_ISR_CALLBACK */

                        CY_SET_REG8((reg8 *)(USBUART_1_ARB_RW1_WA_MSB_IND + ptr), 0x00u);
                        /* repeat 2 last bytes to prefetch endpoint area */
                        CY_SET_REG8((reg8 *)(USBUART_1_ARB_RW1_WA_IND + ptr),
                                    USBUART_1_DMA_BYTES_PER_BURST * ep - USBUART_1_DMA_BYTES_REPEAT);
                        USBUART_1_LoadNextInEP(ep, 1);
                        /* Set Data ready status, This will generate DMA request */
                        * (reg8 *)(USBUART_1_ARB_EP1_CFG_IND + ptr) |= USBUART_1_ARB_EPX_CFG_IN_DATA_RDY;
                    }
                }
                ptr += USBUART_1_EPX_CNTX_ADDR_OFFSET;               /* prepare pointer for next EP */
                ep++;
                int17Status >>= 1u;
            }
            int8Status >>= 1u;
            if(int8Status != 0u)
            {
                /* Prepare pointer for EP8 */
                ptr = ((USBUART_1_EP8 - USBUART_1_EP1) << USBUART_1_EPX_CNTX_ADDR_SHIFT);
                ep = USBUART_1_EP8;
                int17Status = int8Status & 0x01u;
            }
        }

        /* `#START EP_DMA_DONE_END_USER_CODE` Place your code here */

        /* `#END` */

        #ifdef USBUART_1_EP_DMA_DONE_ISR_EXIT_CALLBACK
            USBUART_1_EP_DMA_DONE_ISR_ExitCallback();
        #endif /* USBUART_1_EP_DMA_DONE_ISR_EXIT_CALLBACK */
    }
#endif /* ((USBUART_1_EP_MM == USBUART_1__EP_DMAAUTO) && (USBUART_1_EP_DMA_AUTO_OPT == 0u)) */


/* [] END OF FILE */
