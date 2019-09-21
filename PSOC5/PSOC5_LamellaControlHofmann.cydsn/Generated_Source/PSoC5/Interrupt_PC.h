/*******************************************************************************
* File Name: Interrupt_PC.h
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
#if !defined(CY_ISR_Interrupt_PC_H)
#define CY_ISR_Interrupt_PC_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interrupt_PC_Start(void);
void Interrupt_PC_StartEx(cyisraddress address);
void Interrupt_PC_Stop(void);

CY_ISR_PROTO(Interrupt_PC_Interrupt);

void Interrupt_PC_SetVector(cyisraddress address);
cyisraddress Interrupt_PC_GetVector(void);

void Interrupt_PC_SetPriority(uint8 priority);
uint8 Interrupt_PC_GetPriority(void);

void Interrupt_PC_Enable(void);
uint8 Interrupt_PC_GetState(void);
void Interrupt_PC_Disable(void);

void Interrupt_PC_SetPending(void);
void Interrupt_PC_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interrupt_PC ISR. */
#define Interrupt_PC_INTC_VECTOR            ((reg32 *) Interrupt_PC__INTC_VECT)

/* Address of the Interrupt_PC ISR priority. */
#define Interrupt_PC_INTC_PRIOR             ((reg8 *) Interrupt_PC__INTC_PRIOR_REG)

/* Priority of the Interrupt_PC interrupt. */
#define Interrupt_PC_INTC_PRIOR_NUMBER      Interrupt_PC__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interrupt_PC interrupt. */
#define Interrupt_PC_INTC_SET_EN            ((reg32 *) Interrupt_PC__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interrupt_PC interrupt. */
#define Interrupt_PC_INTC_CLR_EN            ((reg32 *) Interrupt_PC__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interrupt_PC interrupt state to pending. */
#define Interrupt_PC_INTC_SET_PD            ((reg32 *) Interrupt_PC__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interrupt_PC interrupt. */
#define Interrupt_PC_INTC_CLR_PD            ((reg32 *) Interrupt_PC__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interrupt_PC_H */


/* [] END OF FILE */
