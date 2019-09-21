/*******************************************************************************
* File Name: Operations_Amplifier.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
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

#include "Operations_Amplifier.h"

uint8 Operations_Amplifier_initVar = 0u;


/*******************************************************************************   
* Function Name: Operations_Amplifier_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Operations_Amplifier_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Operations_Amplifier_Init(void) 
{
    Operations_Amplifier_SetPower(Operations_Amplifier_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: Operations_Amplifier_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Operations_Amplifier_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    Operations_Amplifier_PUMP_CR1_REG  |= (Operations_Amplifier_PUMP_CR1_CLKSEL | Operations_Amplifier_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    Operations_Amplifier_PM_ACT_CFG_REG |= Operations_Amplifier_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    Operations_Amplifier_PM_STBY_CFG_REG |= Operations_Amplifier_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   Operations_Amplifier_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Operations_Amplifier_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void Operations_Amplifier_Start(void) 
{
    if(Operations_Amplifier_initVar == 0u)
    {
        Operations_Amplifier_initVar = 1u;
        Operations_Amplifier_Init();
    }

    Operations_Amplifier_Enable();
}


/*******************************************************************************
* Function Name: Operations_Amplifier_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Operations_Amplifier_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    Operations_Amplifier_PM_ACT_CFG_REG &= (uint8)(~Operations_Amplifier_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    Operations_Amplifier_PM_STBY_CFG_REG &= (uint8)(~Operations_Amplifier_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(Operations_Amplifier_PM_ACT_CFG_REG == 0u)
    {
        Operations_Amplifier_PUMP_CR1_REG &= (uint8)(~(Operations_Amplifier_PUMP_CR1_CLKSEL | Operations_Amplifier_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: Operations_Amplifier_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void Operations_Amplifier_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        Operations_Amplifier_CR_REG &= (uint8)(~Operations_Amplifier_PWR_MASK);
        Operations_Amplifier_CR_REG |= power & Operations_Amplifier_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(Operations_Amplifier_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
