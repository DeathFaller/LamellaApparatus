/*******************************************************************************
* File Name: Analog_Digital_Converter_PM.c
* Version 3.10
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

#include "Analog_Digital_Converter.h"


/***************************************
* Local data allocation
***************************************/

static Analog_Digital_Converter_BACKUP_STRUCT  Analog_Digital_Converter_backup =
{
    Analog_Digital_Converter_DISABLED
};


/*******************************************************************************
* Function Name: Analog_Digital_Converter_SaveConfig
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
void Analog_Digital_Converter_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Analog_Digital_Converter_RestoreConfig
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
void Analog_Digital_Converter_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Analog_Digital_Converter_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The Analog_Digital_Converter_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Analog_Digital_Converter_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Analog_Digital_Converter_Sleep(void)
{
    if((Analog_Digital_Converter_PWRMGR_SAR_REG  & Analog_Digital_Converter_ACT_PWR_SAR_EN) != 0u)
    {
        if((Analog_Digital_Converter_SAR_CSR0_REG & Analog_Digital_Converter_SAR_SOF_START_CONV) != 0u)
        {
            Analog_Digital_Converter_backup.enableState = Analog_Digital_Converter_ENABLED | Analog_Digital_Converter_STARTED;
        }
        else
        {
            Analog_Digital_Converter_backup.enableState = Analog_Digital_Converter_ENABLED;
        }
        Analog_Digital_Converter_Stop();
    }
    else
    {
        Analog_Digital_Converter_backup.enableState = Analog_Digital_Converter_DISABLED;
    }
}


/*******************************************************************************
* Function Name: Analog_Digital_Converter_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  Analog_Digital_Converter_Sleep() was called. If the component was enabled before the
*  Analog_Digital_Converter_Sleep() function was called, the
*  Analog_Digital_Converter_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Analog_Digital_Converter_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Analog_Digital_Converter_Wakeup(void)
{
    if(Analog_Digital_Converter_backup.enableState != Analog_Digital_Converter_DISABLED)
    {
        Analog_Digital_Converter_Enable();
        #if(Analog_Digital_Converter_DEFAULT_CONV_MODE != Analog_Digital_Converter__HARDWARE_TRIGGER)
            if((Analog_Digital_Converter_backup.enableState & Analog_Digital_Converter_STARTED) != 0u)
            {
                Analog_Digital_Converter_StartConvert();
            }
        #endif /* End Analog_Digital_Converter_DEFAULT_CONV_MODE != Analog_Digital_Converter__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
