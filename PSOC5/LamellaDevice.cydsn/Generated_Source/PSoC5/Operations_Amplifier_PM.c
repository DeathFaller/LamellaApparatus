/*******************************************************************************
* File Name: Operations_Amplifier_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Operations_Amplifier.h"

static Operations_Amplifier_BACKUP_STRUCT  Operations_Amplifier_backup;


/*******************************************************************************  
* Function Name: Operations_Amplifier_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void Operations_Amplifier_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: Operations_Amplifier_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Operations_Amplifier_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: Operations_Amplifier_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Operations_Amplifier_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Operations_Amplifier_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((Operations_Amplifier_PM_ACT_CFG_REG & Operations_Amplifier_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Operations_Amplifier_backup.enableState = 1u;
         /* Stops the component */
         Operations_Amplifier_Stop();
    }
    else
    {
        /* Component is disabled */
        Operations_Amplifier_backup.enableState = 0u;
    }
    /* Saves the configuration */
    Operations_Amplifier_SaveConfig();
}


/*******************************************************************************  
* Function Name: Operations_Amplifier_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Operations_Amplifier_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Operations_Amplifier_Wakeup(void) 
{
    /* Restore the user configuration */
    Operations_Amplifier_RestoreConfig();

    /* Enables the component operation */
    if(Operations_Amplifier_backup.enableState == 1u)
    {
        Operations_Amplifier_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
