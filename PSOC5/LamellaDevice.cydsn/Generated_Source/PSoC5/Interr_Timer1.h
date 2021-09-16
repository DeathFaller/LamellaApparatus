/*******************************************************************************
* File Name: Interr_Timer1.h
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
#if !defined(CY_ISR_Interr_Timer1_H)
#define CY_ISR_Interr_Timer1_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interr_Timer1_Start(void);
void Interr_Timer1_StartEx(cyisraddress address);
void Interr_Timer1_Stop(void);

CY_ISR_PROTO(Interr_Timer1_Interrupt);

void Interr_Timer1_SetVector(cyisraddress address);
cyisraddress Interr_Timer1_GetVector(void);

void Interr_Timer1_SetPriority(uint8 priority);
uint8 Interr_Timer1_GetPriority(void);

void Interr_Timer1_Enable(void);
uint8 Interr_Timer1_GetState(void);
void Interr_Timer1_Disable(void);

void Interr_Timer1_SetPending(void);
void Interr_Timer1_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interr_Timer1 ISR. */
#define Interr_Timer1_INTC_VECTOR            ((reg32 *) Interr_Timer1__INTC_VECT)

/* Address of the Interr_Timer1 ISR priority. */
#define Interr_Timer1_INTC_PRIOR             ((reg8 *) Interr_Timer1__INTC_PRIOR_REG)

/* Priority of the Interr_Timer1 interrupt. */
#define Interr_Timer1_INTC_PRIOR_NUMBER      Interr_Timer1__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interr_Timer1 interrupt. */
#define Interr_Timer1_INTC_SET_EN            ((reg32 *) Interr_Timer1__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interr_Timer1 interrupt. */
#define Interr_Timer1_INTC_CLR_EN            ((reg32 *) Interr_Timer1__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interr_Timer1 interrupt state to pending. */
#define Interr_Timer1_INTC_SET_PD            ((reg32 *) Interr_Timer1__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interr_Timer1 interrupt. */
#define Interr_Timer1_INTC_CLR_PD            ((reg32 *) Interr_Timer1__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interr_Timer1_H */


/* [] END OF FILE */
