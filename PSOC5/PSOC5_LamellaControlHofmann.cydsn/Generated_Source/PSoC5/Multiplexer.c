/*******************************************************************************
* File Name: Multiplexer.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "Multiplexer.h"

static uint8 Multiplexer_lastChannel = Multiplexer_NULL_CHANNEL;


/*******************************************************************************
* Function Name: Multiplexer_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Multiplexer_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < Multiplexer_CHANNELS ; chan++)
    {
#if (Multiplexer_MUXTYPE == Multiplexer_MUX_SINGLE)
        Multiplexer_Unset(chan);
#else
        Multiplexer_CYAMUXSIDE_A_Unset(chan);
        Multiplexer_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    Multiplexer_lastChannel = Multiplexer_NULL_CHANNEL;
}


#if (!Multiplexer_ATMOSTONE)
/*******************************************************************************
* Function Name: Multiplexer_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void Multiplexer_Select(uint8 channel) 
{
    Multiplexer_DisconnectAll();        /* Disconnect all previous connections */
    Multiplexer_Connect(channel);       /* Make the given selection */
    Multiplexer_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: Multiplexer_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void Multiplexer_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( Multiplexer_lastChannel != Multiplexer_NULL_CHANNEL)
    {
        Multiplexer_Disconnect(Multiplexer_lastChannel);
    }

    /* Make the new channel connection */
#if (Multiplexer_MUXTYPE == Multiplexer_MUX_SINGLE)
    Multiplexer_Set(channel);
#else
    Multiplexer_CYAMUXSIDE_A_Set(channel);
    Multiplexer_CYAMUXSIDE_B_Set(channel);
#endif


    Multiplexer_lastChannel = channel;   /* Update last channel */
}


#if (Multiplexer_MUXTYPE == Multiplexer_MUX_DIFF)
#if (!Multiplexer_ATMOSTONE)
/*******************************************************************************
* Function Name: Multiplexer_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void Multiplexer_Connect(uint8 channel) 
{
    Multiplexer_CYAMUXSIDE_A_Set(channel);
    Multiplexer_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: Multiplexer_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void Multiplexer_Disconnect(uint8 channel) 
{
    Multiplexer_CYAMUXSIDE_A_Unset(channel);
    Multiplexer_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (Multiplexer_ATMOSTONE)
/*******************************************************************************
* Function Name: Multiplexer_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Multiplexer_DisconnectAll(void) 
{
    if(Multiplexer_lastChannel != Multiplexer_NULL_CHANNEL) 
    {
        Multiplexer_Disconnect(Multiplexer_lastChannel);
        Multiplexer_lastChannel = Multiplexer_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
