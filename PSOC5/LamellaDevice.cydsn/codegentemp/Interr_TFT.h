/*******************************************************************************
* File Name: Interr_TFT.h
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
#if !defined(CY_ISR_Interr_TFT_H)
#define CY_ISR_Interr_TFT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interr_TFT_Start(void);
void Interr_TFT_StartEx(cyisraddress address);
void Interr_TFT_Stop(void);

CY_ISR_PROTO(Interr_TFT_Interrupt);

void Interr_TFT_SetVector(cyisraddress address);
cyisraddress Interr_TFT_GetVector(void);

void Interr_TFT_SetPriority(uint8 priority);
uint8 Interr_TFT_GetPriority(void);

void Interr_TFT_Enable(void);
uint8 Interr_TFT_GetState(void);
void Interr_TFT_Disable(void);

void Interr_TFT_SetPending(void);
void Interr_TFT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interr_TFT ISR. */
#define Interr_TFT_INTC_VECTOR            ((reg32 *) Interr_TFT__INTC_VECT)

/* Address of the Interr_TFT ISR priority. */
#define Interr_TFT_INTC_PRIOR             ((reg8 *) Interr_TFT__INTC_PRIOR_REG)

/* Priority of the Interr_TFT interrupt. */
#define Interr_TFT_INTC_PRIOR_NUMBER      Interr_TFT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interr_TFT interrupt. */
#define Interr_TFT_INTC_SET_EN            ((reg32 *) Interr_TFT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interr_TFT interrupt. */
#define Interr_TFT_INTC_CLR_EN            ((reg32 *) Interr_TFT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interr_TFT interrupt state to pending. */
#define Interr_TFT_INTC_SET_PD            ((reg32 *) Interr_TFT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interr_TFT interrupt. */
#define Interr_TFT_INTC_CLR_PD            ((reg32 *) Interr_TFT__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interr_TFT_H */


/* [] END OF FILE */
