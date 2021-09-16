/*******************************************************************************
* File Name: LED_slider_val_received.h  
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

#if !defined(CY_PINS_LED_slider_val_received_H) /* Pins LED_slider_val_received_H */
#define CY_PINS_LED_slider_val_received_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_slider_val_received_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED_slider_val_received__PORT == 15 && ((LED_slider_val_received__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LED_slider_val_received_Write(uint8 value);
void    LED_slider_val_received_SetDriveMode(uint8 mode);
uint8   LED_slider_val_received_ReadDataReg(void);
uint8   LED_slider_val_received_Read(void);
void    LED_slider_val_received_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED_slider_val_received_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LED_slider_val_received_SetDriveMode() function.
     *  @{
     */
        #define LED_slider_val_received_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LED_slider_val_received_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LED_slider_val_received_DM_RES_UP          PIN_DM_RES_UP
        #define LED_slider_val_received_DM_RES_DWN         PIN_DM_RES_DWN
        #define LED_slider_val_received_DM_OD_LO           PIN_DM_OD_LO
        #define LED_slider_val_received_DM_OD_HI           PIN_DM_OD_HI
        #define LED_slider_val_received_DM_STRONG          PIN_DM_STRONG
        #define LED_slider_val_received_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LED_slider_val_received_MASK               LED_slider_val_received__MASK
#define LED_slider_val_received_SHIFT              LED_slider_val_received__SHIFT
#define LED_slider_val_received_WIDTH              1u

/* Interrupt constants */
#if defined(LED_slider_val_received__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED_slider_val_received_SetInterruptMode() function.
     *  @{
     */
        #define LED_slider_val_received_INTR_NONE      (uint16)(0x0000u)
        #define LED_slider_val_received_INTR_RISING    (uint16)(0x0001u)
        #define LED_slider_val_received_INTR_FALLING   (uint16)(0x0002u)
        #define LED_slider_val_received_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LED_slider_val_received_INTR_MASK      (0x01u) 
#endif /* (LED_slider_val_received__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_slider_val_received_PS                     (* (reg8 *) LED_slider_val_received__PS)
/* Data Register */
#define LED_slider_val_received_DR                     (* (reg8 *) LED_slider_val_received__DR)
/* Port Number */
#define LED_slider_val_received_PRT_NUM                (* (reg8 *) LED_slider_val_received__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_slider_val_received_AG                     (* (reg8 *) LED_slider_val_received__AG)                       
/* Analog MUX bux enable */
#define LED_slider_val_received_AMUX                   (* (reg8 *) LED_slider_val_received__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_slider_val_received_BIE                    (* (reg8 *) LED_slider_val_received__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_slider_val_received_BIT_MASK               (* (reg8 *) LED_slider_val_received__BIT_MASK)
/* Bypass Enable */
#define LED_slider_val_received_BYP                    (* (reg8 *) LED_slider_val_received__BYP)
/* Port wide control signals */                                                   
#define LED_slider_val_received_CTL                    (* (reg8 *) LED_slider_val_received__CTL)
/* Drive Modes */
#define LED_slider_val_received_DM0                    (* (reg8 *) LED_slider_val_received__DM0) 
#define LED_slider_val_received_DM1                    (* (reg8 *) LED_slider_val_received__DM1)
#define LED_slider_val_received_DM2                    (* (reg8 *) LED_slider_val_received__DM2) 
/* Input Buffer Disable Override */
#define LED_slider_val_received_INP_DIS                (* (reg8 *) LED_slider_val_received__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_slider_val_received_LCD_COM_SEG            (* (reg8 *) LED_slider_val_received__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_slider_val_received_LCD_EN                 (* (reg8 *) LED_slider_val_received__LCD_EN)
/* Slew Rate Control */
#define LED_slider_val_received_SLW                    (* (reg8 *) LED_slider_val_received__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_slider_val_received_PRTDSI__CAPS_SEL       (* (reg8 *) LED_slider_val_received__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_slider_val_received_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_slider_val_received__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_slider_val_received_PRTDSI__OE_SEL0        (* (reg8 *) LED_slider_val_received__PRTDSI__OE_SEL0) 
#define LED_slider_val_received_PRTDSI__OE_SEL1        (* (reg8 *) LED_slider_val_received__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_slider_val_received_PRTDSI__OUT_SEL0       (* (reg8 *) LED_slider_val_received__PRTDSI__OUT_SEL0) 
#define LED_slider_val_received_PRTDSI__OUT_SEL1       (* (reg8 *) LED_slider_val_received__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_slider_val_received_PRTDSI__SYNC_OUT       (* (reg8 *) LED_slider_val_received__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LED_slider_val_received__SIO_CFG)
    #define LED_slider_val_received_SIO_HYST_EN        (* (reg8 *) LED_slider_val_received__SIO_HYST_EN)
    #define LED_slider_val_received_SIO_REG_HIFREQ     (* (reg8 *) LED_slider_val_received__SIO_REG_HIFREQ)
    #define LED_slider_val_received_SIO_CFG            (* (reg8 *) LED_slider_val_received__SIO_CFG)
    #define LED_slider_val_received_SIO_DIFF           (* (reg8 *) LED_slider_val_received__SIO_DIFF)
#endif /* (LED_slider_val_received__SIO_CFG) */

/* Interrupt Registers */
#if defined(LED_slider_val_received__INTSTAT)
    #define LED_slider_val_received_INTSTAT            (* (reg8 *) LED_slider_val_received__INTSTAT)
    #define LED_slider_val_received_SNAP               (* (reg8 *) LED_slider_val_received__SNAP)
    
	#define LED_slider_val_received_0_INTTYPE_REG 		(* (reg8 *) LED_slider_val_received__0__INTTYPE)
#endif /* (LED_slider_val_received__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED_slider_val_received_H */


/* [] END OF FILE */
