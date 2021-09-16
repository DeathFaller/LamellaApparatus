/*******************************************************************************
* File Name: Interrupt_Debug.h
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
#if !defined(CY_ISR_Interrupt_Debug_H)
#define CY_ISR_Interrupt_Debug_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interrupt_Debug_Start(void);
void Interrupt_Debug_StartEx(cyisraddress address);
void Interrupt_Debug_Stop(void);

CY_ISR_PROTO(Interrupt_Debug_Interrupt);

void Interrupt_Debug_SetVector(cyisraddress address);
cyisraddress Interrupt_Debug_GetVector(void);

void Interrupt_Debug_SetPriority(uint8 priority);
uint8 Interrupt_Debug_GetPriority(void);

void Interrupt_Debug_Enable(void);
uint8 Interrupt_Debug_GetState(void);
void Interrupt_Debug_Disable(void);

void Interrupt_Debug_SetPending(void);
void Interrupt_Debug_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interrupt_Debug ISR. */
#define Interrupt_Debug_INTC_VECTOR            ((reg32 *) Interrupt_Debug__INTC_VECT)

/* Address of the Interrupt_Debug ISR priority. */
#define Interrupt_Debug_INTC_PRIOR             ((reg8 *) Interrupt_Debug__INTC_PRIOR_REG)

/* Priority of the Interrupt_Debug interrupt. */
#define Interrupt_Debug_INTC_PRIOR_NUMBER      Interrupt_Debug__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interrupt_Debug interrupt. */
#define Interrupt_Debug_INTC_SET_EN            ((reg32 *) Interrupt_Debug__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interrupt_Debug interrupt. */
#define Interrupt_Debug_INTC_CLR_EN            ((reg32 *) Interrupt_Debug__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interrupt_Debug interrupt state to pending. */
#define Interrupt_Debug_INTC_SET_PD            ((reg32 *) Interrupt_Debug__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interrupt_Debug interrupt. */
#define Interrupt_Debug_INTC_CLR_PD            ((reg32 *) Interrupt_Debug__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interrupt_Debug_H */


/* [] END OF FILE */
