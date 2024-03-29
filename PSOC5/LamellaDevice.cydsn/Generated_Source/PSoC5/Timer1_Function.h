/*******************************************************************************
* File Name: Timer1_Function.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Timer1_Function_H)
#define CY_ISR_Timer1_Function_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Timer1_Function_Start(void);
void Timer1_Function_StartEx(cyisraddress address);
void Timer1_Function_Stop(void);

CY_ISR_PROTO(Timer1_Function_Interrupt);

void Timer1_Function_SetVector(cyisraddress address);
cyisraddress Timer1_Function_GetVector(void);

void Timer1_Function_SetPriority(uint8 priority);
uint8 Timer1_Function_GetPriority(void);

void Timer1_Function_Enable(void);
uint8 Timer1_Function_GetState(void);
void Timer1_Function_Disable(void);

void Timer1_Function_SetPending(void);
void Timer1_Function_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Timer1_Function ISR. */
#define Timer1_Function_INTC_VECTOR            ((reg32 *) Timer1_Function__INTC_VECT)

/* Address of the Timer1_Function ISR priority. */
#define Timer1_Function_INTC_PRIOR             ((reg8 *) Timer1_Function__INTC_PRIOR_REG)

/* Priority of the Timer1_Function interrupt. */
#define Timer1_Function_INTC_PRIOR_NUMBER      Timer1_Function__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Timer1_Function interrupt. */
#define Timer1_Function_INTC_SET_EN            ((reg32 *) Timer1_Function__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Timer1_Function interrupt. */
#define Timer1_Function_INTC_CLR_EN            ((reg32 *) Timer1_Function__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Timer1_Function interrupt state to pending. */
#define Timer1_Function_INTC_SET_PD            ((reg32 *) Timer1_Function__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Timer1_Function interrupt. */
#define Timer1_Function_INTC_CLR_PD            ((reg32 *) Timer1_Function__INTC_CLR_PD_REG)


#endif /* CY_ISR_Timer1_Function_H */


/* [] END OF FILE */
