/*******************************************************************************
* File Name: V_Amplified.h  
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

#if !defined(CY_PINS_V_Amplified_H) /* Pins V_Amplified_H */
#define CY_PINS_V_Amplified_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "V_Amplified_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 V_Amplified__PORT == 15 && ((V_Amplified__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    V_Amplified_Write(uint8 value);
void    V_Amplified_SetDriveMode(uint8 mode);
uint8   V_Amplified_ReadDataReg(void);
uint8   V_Amplified_Read(void);
void    V_Amplified_SetInterruptMode(uint16 position, uint16 mode);
uint8   V_Amplified_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the V_Amplified_SetDriveMode() function.
     *  @{
     */
        #define V_Amplified_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define V_Amplified_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define V_Amplified_DM_RES_UP          PIN_DM_RES_UP
        #define V_Amplified_DM_RES_DWN         PIN_DM_RES_DWN
        #define V_Amplified_DM_OD_LO           PIN_DM_OD_LO
        #define V_Amplified_DM_OD_HI           PIN_DM_OD_HI
        #define V_Amplified_DM_STRONG          PIN_DM_STRONG
        #define V_Amplified_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define V_Amplified_MASK               V_Amplified__MASK
#define V_Amplified_SHIFT              V_Amplified__SHIFT
#define V_Amplified_WIDTH              1u

/* Interrupt constants */
#if defined(V_Amplified__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in V_Amplified_SetInterruptMode() function.
     *  @{
     */
        #define V_Amplified_INTR_NONE      (uint16)(0x0000u)
        #define V_Amplified_INTR_RISING    (uint16)(0x0001u)
        #define V_Amplified_INTR_FALLING   (uint16)(0x0002u)
        #define V_Amplified_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define V_Amplified_INTR_MASK      (0x01u) 
#endif /* (V_Amplified__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_Amplified_PS                     (* (reg8 *) V_Amplified__PS)
/* Data Register */
#define V_Amplified_DR                     (* (reg8 *) V_Amplified__DR)
/* Port Number */
#define V_Amplified_PRT_NUM                (* (reg8 *) V_Amplified__PRT) 
/* Connect to Analog Globals */                                                  
#define V_Amplified_AG                     (* (reg8 *) V_Amplified__AG)                       
/* Analog MUX bux enable */
#define V_Amplified_AMUX                   (* (reg8 *) V_Amplified__AMUX) 
/* Bidirectional Enable */                                                        
#define V_Amplified_BIE                    (* (reg8 *) V_Amplified__BIE)
/* Bit-mask for Aliased Register Access */
#define V_Amplified_BIT_MASK               (* (reg8 *) V_Amplified__BIT_MASK)
/* Bypass Enable */
#define V_Amplified_BYP                    (* (reg8 *) V_Amplified__BYP)
/* Port wide control signals */                                                   
#define V_Amplified_CTL                    (* (reg8 *) V_Amplified__CTL)
/* Drive Modes */
#define V_Amplified_DM0                    (* (reg8 *) V_Amplified__DM0) 
#define V_Amplified_DM1                    (* (reg8 *) V_Amplified__DM1)
#define V_Amplified_DM2                    (* (reg8 *) V_Amplified__DM2) 
/* Input Buffer Disable Override */
#define V_Amplified_INP_DIS                (* (reg8 *) V_Amplified__INP_DIS)
/* LCD Common or Segment Drive */
#define V_Amplified_LCD_COM_SEG            (* (reg8 *) V_Amplified__LCD_COM_SEG)
/* Enable Segment LCD */
#define V_Amplified_LCD_EN                 (* (reg8 *) V_Amplified__LCD_EN)
/* Slew Rate Control */
#define V_Amplified_SLW                    (* (reg8 *) V_Amplified__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define V_Amplified_PRTDSI__CAPS_SEL       (* (reg8 *) V_Amplified__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define V_Amplified_PRTDSI__DBL_SYNC_IN    (* (reg8 *) V_Amplified__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define V_Amplified_PRTDSI__OE_SEL0        (* (reg8 *) V_Amplified__PRTDSI__OE_SEL0) 
#define V_Amplified_PRTDSI__OE_SEL1        (* (reg8 *) V_Amplified__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define V_Amplified_PRTDSI__OUT_SEL0       (* (reg8 *) V_Amplified__PRTDSI__OUT_SEL0) 
#define V_Amplified_PRTDSI__OUT_SEL1       (* (reg8 *) V_Amplified__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define V_Amplified_PRTDSI__SYNC_OUT       (* (reg8 *) V_Amplified__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(V_Amplified__SIO_CFG)
    #define V_Amplified_SIO_HYST_EN        (* (reg8 *) V_Amplified__SIO_HYST_EN)
    #define V_Amplified_SIO_REG_HIFREQ     (* (reg8 *) V_Amplified__SIO_REG_HIFREQ)
    #define V_Amplified_SIO_CFG            (* (reg8 *) V_Amplified__SIO_CFG)
    #define V_Amplified_SIO_DIFF           (* (reg8 *) V_Amplified__SIO_DIFF)
#endif /* (V_Amplified__SIO_CFG) */

/* Interrupt Registers */
#if defined(V_Amplified__INTSTAT)
    #define V_Amplified_INTSTAT            (* (reg8 *) V_Amplified__INTSTAT)
    #define V_Amplified_SNAP               (* (reg8 *) V_Amplified__SNAP)
    
	#define V_Amplified_0_INTTYPE_REG 		(* (reg8 *) V_Amplified__0__INTTYPE)
#endif /* (V_Amplified__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_V_Amplified_H */


/* [] END OF FILE */
