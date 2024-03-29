/*******************************************************************************
* File Name: PGA_Photo_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for PGA 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PGA_Photo.h"

static PGA_Photo_BACKUP_STRUCT  PGA_Photo_backup;


/*******************************************************************************
* Function Name: PGA_Photo_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user register configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void PGA_Photo_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: PGA_Photo_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void PGA_Photo_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: PGA_Photo_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PGA_Photo_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void PGA_Photo_Sleep(void) 
{
    /* Save PGA enable state */
    if((PGA_Photo_PM_ACT_CFG_REG & PGA_Photo_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        PGA_Photo_backup.enableState = 1u;
        /* Stop the configuration */
        PGA_Photo_Stop();
    }
    else
    {
        /* Component is disabled */
        PGA_Photo_backup.enableState = 0u;
    }
    /* Save the configuration */
    PGA_Photo_SaveConfig();
}


/*******************************************************************************
* Function Name: PGA_Photo_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  void
*
* Global variables:
*  PGA_Photo_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void PGA_Photo_Wakeup(void) 
{
    /* Restore the configurations */
    PGA_Photo_RestoreConfig();
     /* Enables the component operation */
    if(PGA_Photo_backup.enableState == 1u)
    {
        PGA_Photo_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
