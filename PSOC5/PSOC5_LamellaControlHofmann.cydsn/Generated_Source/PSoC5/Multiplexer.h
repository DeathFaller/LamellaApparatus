/*******************************************************************************
* File Name: Multiplexer.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_Multiplexer_H)
#define CY_AMUX_Multiplexer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void Multiplexer_Start(void) ;
#define Multiplexer_Init() Multiplexer_Start()
void Multiplexer_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void Multiplexer_Stop(void); */
/* void Multiplexer_Select(uint8 channel); */
/* void Multiplexer_Connect(uint8 channel); */
/* void Multiplexer_Disconnect(uint8 channel); */
/* void Multiplexer_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define Multiplexer_CHANNELS  4u
#define Multiplexer_MUXTYPE   1
#define Multiplexer_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define Multiplexer_NULL_CHANNEL 0xFFu
#define Multiplexer_MUX_SINGLE   1
#define Multiplexer_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if Multiplexer_MUXTYPE == Multiplexer_MUX_SINGLE
# if !Multiplexer_ATMOSTONE
#  define Multiplexer_Connect(channel) Multiplexer_Set(channel)
# endif
# define Multiplexer_Disconnect(channel) Multiplexer_Unset(channel)
#else
# if !Multiplexer_ATMOSTONE
void Multiplexer_Connect(uint8 channel) ;
# endif
void Multiplexer_Disconnect(uint8 channel) ;
#endif

#if Multiplexer_ATMOSTONE
# define Multiplexer_Stop() Multiplexer_DisconnectAll()
# define Multiplexer_Select(channel) Multiplexer_FastSelect(channel)
void Multiplexer_DisconnectAll(void) ;
#else
# define Multiplexer_Stop() Multiplexer_Start()
void Multiplexer_Select(uint8 channel) ;
# define Multiplexer_DisconnectAll() Multiplexer_Start()
#endif

#endif /* CY_AMUX_Multiplexer_H */


/* [] END OF FILE */
