/*******************************************************************************
* File Name: Interr_PC.h
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
#if !defined(CY_ISR_Interr_PC_H)
#define CY_ISR_Interr_PC_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interr_PC_Start(void);
void Interr_PC_StartEx(cyisraddress address);
void Interr_PC_Stop(void);

CY_ISR_PROTO(Interr_PC_Interrupt);

void Interr_PC_SetVector(cyisraddress address);
cyisraddress Interr_PC_GetVector(void);

void Interr_PC_SetPriority(uint8 priority);
uint8 Interr_PC_GetPriority(void);

void Interr_PC_Enable(void);
uint8 Interr_PC_GetState(void);
void Interr_PC_Disable(void);

void Interr_PC_SetPending(void);
void Interr_PC_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interr_PC ISR. */
#define Interr_PC_INTC_VECTOR            ((reg32 *) Interr_PC__INTC_VECT)

/* Address of the Interr_PC ISR priority. */
#define Interr_PC_INTC_PRIOR             ((reg8 *) Interr_PC__INTC_PRIOR_REG)

/* Priority of the Interr_PC interrupt. */
#define Interr_PC_INTC_PRIOR_NUMBER      Interr_PC__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interr_PC interrupt. */
#define Interr_PC_INTC_SET_EN            ((reg32 *) Interr_PC__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interr_PC interrupt. */
#define Interr_PC_INTC_CLR_EN            ((reg32 *) Interr_PC__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interr_PC interrupt state to pending. */
#define Interr_PC_INTC_SET_PD            ((reg32 *) Interr_PC__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interr_PC interrupt. */
#define Interr_PC_INTC_CLR_PD            ((reg32 *) Interr_PC__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interr_PC_H */


/* [] END OF FILE */
