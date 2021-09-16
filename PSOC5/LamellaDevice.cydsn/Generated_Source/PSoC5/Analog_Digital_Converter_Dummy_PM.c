/*******************************************************************************
* File Name: Analog_Digital_Converter_Dummy_PM.c
* Version 3.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Analog_Digital_Converter_Dummy.h"


/***************************************
* Local data allocation
***************************************/

static Analog_Digital_Converter_Dummy_BACKUP_STRUCT  Analog_Digital_Converter_Dummy_backup =
{
    Analog_Digital_Converter_Dummy_DISABLED
};


/*******************************************************************************
* Function Name: Analog_Digital_Converter_Dummy_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Analog_Digital_Converter_Dummy_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Analog_Digital_Converter_Dummy_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Analog_Digital_Converter_Dummy_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Analog_Digital_Converter_Dummy_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The Analog_Digital_Converter_Dummy_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Analog_Digital_Converter_Dummy_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Analog_Digital_Converter_Dummy_Sleep(void)
{
    if((Analog_Digital_Converter_Dummy_PWRMGR_SAR_REG  & Analog_Digital_Converter_Dummy_ACT_PWR_SAR_EN) != 0u)
    {
        if((Analog_Digital_Converter_Dummy_SAR_CSR0_REG & Analog_Digital_Converter_Dummy_SAR_SOF_START_CONV) != 0u)
        {
            Analog_Digital_Converter_Dummy_backup.enableState = Analog_Digital_Converter_Dummy_ENABLED | Analog_Digital_Converter_Dummy_STARTED;
        }
        else
        {
            Analog_Digital_Converter_Dummy_backup.enableState = Analog_Digital_Converter_Dummy_ENABLED;
        }
        Analog_Digital_Converter_Dummy_Stop();
    }
    else
    {
        Analog_Digital_Converter_Dummy_backup.enableState = Analog_Digital_Converter_Dummy_DISABLED;
    }
}


/*******************************************************************************
* Function Name: Analog_Digital_Converter_Dummy_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  Analog_Digital_Converter_Dummy_Sleep() was called. If the component was enabled before the
*  Analog_Digital_Converter_Dummy_Sleep() function was called, the
*  Analog_Digital_Converter_Dummy_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Analog_Digital_Converter_Dummy_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Analog_Digital_Converter_Dummy_Wakeup(void)
{
    if(Analog_Digital_Converter_Dummy_backup.enableState != Analog_Digital_Converter_Dummy_DISABLED)
    {
        Analog_Digital_Converter_Dummy_Enable();
        #if(Analog_Digital_Converter_Dummy_DEFAULT_CONV_MODE != Analog_Digital_Converter_Dummy__HARDWARE_TRIGGER)
            if((Analog_Digital_Converter_Dummy_backup.enableState & Analog_Digital_Converter_Dummy_STARTED) != 0u)
            {
                Analog_Digital_Converter_Dummy_StartConvert();
            }
        #endif /* End Analog_Digital_Converter_Dummy_DEFAULT_CONV_MODE != Analog_Digital_Converter_Dummy__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
