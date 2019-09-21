/*******************************************************************************
* File Name: Resistor_1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Resistor_1_H) /* Pins Resistor_1_H */
#define CY_PINS_Resistor_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Resistor_1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Resistor_1__PORT == 15 && ((Resistor_1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Resistor_1_Write(uint8 value);
void    Resistor_1_SetDriveMode(uint8 mode);
uint8   Resistor_1_ReadDataReg(void);
uint8   Resistor_1_Read(void);
void    Resistor_1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Resistor_1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Resistor_1_SetDriveMode() function.
     *  @{
     */
        #define Resistor_1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Resistor_1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Resistor_1_DM_RES_UP          PIN_DM_RES_UP
        #define Resistor_1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Resistor_1_DM_OD_LO           PIN_DM_OD_LO
        #define Resistor_1_DM_OD_HI           PIN_DM_OD_HI
        #define Resistor_1_DM_STRONG          PIN_DM_STRONG
        #define Resistor_1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Resistor_1_MASK               Resistor_1__MASK
#define Resistor_1_SHIFT              Resistor_1__SHIFT
#define Resistor_1_WIDTH              1u

/* Interrupt constants */
#if defined(Resistor_1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Resistor_1_SetInterruptMode() function.
     *  @{
     */
        #define Resistor_1_INTR_NONE      (uint16)(0x0000u)
        #define Resistor_1_INTR_RISING    (uint16)(0x0001u)
        #define Resistor_1_INTR_FALLING   (uint16)(0x0002u)
        #define Resistor_1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Resistor_1_INTR_MASK      (0x01u) 
#endif /* (Resistor_1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Resistor_1_PS                     (* (reg8 *) Resistor_1__PS)
/* Data Register */
#define Resistor_1_DR                     (* (reg8 *) Resistor_1__DR)
/* Port Number */
#define Resistor_1_PRT_NUM                (* (reg8 *) Resistor_1__PRT) 
/* Connect to Analog Globals */                                                  
#define Resistor_1_AG                     (* (reg8 *) Resistor_1__AG)                       
/* Analog MUX bux enable */
#define Resistor_1_AMUX                   (* (reg8 *) Resistor_1__AMUX) 
/* Bidirectional Enable */                                                        
#define Resistor_1_BIE                    (* (reg8 *) Resistor_1__BIE)
/* Bit-mask for Aliased Register Access */
#define Resistor_1_BIT_MASK               (* (reg8 *) Resistor_1__BIT_MASK)
/* Bypass Enable */
#define Resistor_1_BYP                    (* (reg8 *) Resistor_1__BYP)
/* Port wide control signals */                                                   
#define Resistor_1_CTL                    (* (reg8 *) Resistor_1__CTL)
/* Drive Modes */
#define Resistor_1_DM0                    (* (reg8 *) Resistor_1__DM0) 
#define Resistor_1_DM1                    (* (reg8 *) Resistor_1__DM1)
#define Resistor_1_DM2                    (* (reg8 *) Resistor_1__DM2) 
/* Input Buffer Disable Override */
#define Resistor_1_INP_DIS                (* (reg8 *) Resistor_1__INP_DIS)
/* LCD Common or Segment Drive */
#define Resistor_1_LCD_COM_SEG            (* (reg8 *) Resistor_1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Resistor_1_LCD_EN                 (* (reg8 *) Resistor_1__LCD_EN)
/* Slew Rate Control */
#define Resistor_1_SLW                    (* (reg8 *) Resistor_1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Resistor_1_PRTDSI__CAPS_SEL       (* (reg8 *) Resistor_1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Resistor_1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Resistor_1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Resistor_1_PRTDSI__OE_SEL0        (* (reg8 *) Resistor_1__PRTDSI__OE_SEL0) 
#define Resistor_1_PRTDSI__OE_SEL1        (* (reg8 *) Resistor_1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Resistor_1_PRTDSI__OUT_SEL0       (* (reg8 *) Resistor_1__PRTDSI__OUT_SEL0) 
#define Resistor_1_PRTDSI__OUT_SEL1       (* (reg8 *) Resistor_1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Resistor_1_PRTDSI__SYNC_OUT       (* (reg8 *) Resistor_1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Resistor_1__SIO_CFG)
    #define Resistor_1_SIO_HYST_EN        (* (reg8 *) Resistor_1__SIO_HYST_EN)
    #define Resistor_1_SIO_REG_HIFREQ     (* (reg8 *) Resistor_1__SIO_REG_HIFREQ)
    #define Resistor_1_SIO_CFG            (* (reg8 *) Resistor_1__SIO_CFG)
    #define Resistor_1_SIO_DIFF           (* (reg8 *) Resistor_1__SIO_DIFF)
#endif /* (Resistor_1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Resistor_1__INTSTAT)
    #define Resistor_1_INTSTAT            (* (reg8 *) Resistor_1__INTSTAT)
    #define Resistor_1_SNAP               (* (reg8 *) Resistor_1__SNAP)
    
	#define Resistor_1_0_INTTYPE_REG 		(* (reg8 *) Resistor_1__0__INTTYPE)
#endif /* (Resistor_1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Resistor_1_H */


/* [] END OF FILE */
