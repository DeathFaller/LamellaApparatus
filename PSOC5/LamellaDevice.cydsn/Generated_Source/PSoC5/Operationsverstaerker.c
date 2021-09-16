/*******************************************************************************
* File Name: Operationsverstaerker.c
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

#include "Operationsverstaerker.h"

uint8 Operationsverstaerker_initVar = 0u;


/*******************************************************************************   
* Function Name: Operationsverstaerker_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Operationsverstaerker_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Operationsverstaerker_Init(void) 
{
    Operationsverstaerker_SetPower(Operationsverstaerker_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: Operationsverstaerker_Enable
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
void Operationsverstaerker_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    Operationsverstaerker_PUMP_CR1_REG  |= (Operationsverstaerker_PUMP_CR1_CLKSEL | Operationsverstaerker_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    Operationsverstaerker_PM_ACT_CFG_REG |= Operationsverstaerker_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    Operationsverstaerker_PM_STBY_CFG_REG |= Operationsverstaerker_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   Operationsverstaerker_Start
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
*  Operationsverstaerker_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void Operationsverstaerker_Start(void) 
{
    if(Operationsverstaerker_initVar == 0u)
    {
        Operationsverstaerker_initVar = 1u;
        Operationsverstaerker_Init();
    }

    Operationsverstaerker_Enable();
}


/*******************************************************************************
* Function Name: Operationsverstaerker_Stop
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
void Operationsverstaerker_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    Operationsverstaerker_PM_ACT_CFG_REG &= (uint8)(~Operationsverstaerker_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    Operationsverstaerker_PM_STBY_CFG_REG &= (uint8)(~Operationsverstaerker_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(Operationsverstaerker_PM_ACT_CFG_REG == 0u)
    {
        Operationsverstaerker_PUMP_CR1_REG &= (uint8)(~(Operationsverstaerker_PUMP_CR1_CLKSEL | Operationsverstaerker_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: Operationsverstaerker_SetPower
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
void Operationsverstaerker_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        Operationsverstaerker_CR_REG &= (uint8)(~Operationsverstaerker_PWR_MASK);
        Operationsverstaerker_CR_REG |= power & Operationsverstaerker_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(Operationsverstaerker_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
