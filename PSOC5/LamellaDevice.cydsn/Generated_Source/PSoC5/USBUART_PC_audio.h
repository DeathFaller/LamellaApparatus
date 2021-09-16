/***************************************************************************//**
* \file USBUART_PC_audio.h
* \version 3.20
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  Audio class.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USBUART_PC_audio_H)
#define CY_USBFS_USBUART_PC_audio_H

#include "USBUART_PC.h"


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_CONSTANTS` Place your declaration here */

/* `#END` */


/***************************************
*  Constants for USBUART_PC_audio API.
***************************************/

/* Audio Class-Specific Request Codes (AUDIO Table A-9) */
#define USBUART_PC_REQUEST_CODE_UNDEFINED     (0x00u)
#define USBUART_PC_SET_CUR                    (0x01u)
#define USBUART_PC_GET_CUR                    (0x81u)
#define USBUART_PC_SET_MIN                    (0x02u)
#define USBUART_PC_GET_MIN                    (0x82u)
#define USBUART_PC_SET_MAX                    (0x03u)
#define USBUART_PC_GET_MAX                    (0x83u)
#define USBUART_PC_SET_RES                    (0x04u)
#define USBUART_PC_GET_RES                    (0x84u)
#define USBUART_PC_SET_MEM                    (0x05u)
#define USBUART_PC_GET_MEM                    (0x85u)
#define USBUART_PC_GET_STAT                   (0xFFu)

/* point Control Selectors (AUDIO Table A-19) */
#define USBUART_PC_EP_CONTROL_UNDEFINED       (0x00u)
#define USBUART_PC_SAMPLING_FREQ_CONTROL      (0x01u)
#define USBUART_PC_PITCH_CONTROL              (0x02u)

/* Feature Unit Control Selectors (AUDIO Table A-11) */
#define USBUART_PC_FU_CONTROL_UNDEFINED       (0x00u)
#define USBUART_PC_MUTE_CONTROL               (0x01u)
#define USBUART_PC_VOLUME_CONTROL             (0x02u)
#define USBUART_PC_BASS_CONTROL               (0x03u)
#define USBUART_PC_MID_CONTROL                (0x04u)
#define USBUART_PC_TREBLE_CONTROL             (0x05u)
#define USBUART_PC_GRAPHIC_EQUALIZER_CONTROL  (0x06u)
#define USBUART_PC_AUTOMATIC_GAIN_CONTROL     (0x07u)
#define USBUART_PC_DELAY_CONTROL              (0x08u)
#define USBUART_PC_BASS_BOOST_CONTROL         (0x09u)
#define USBUART_PC_LOUDNESS_CONTROL           (0x0Au)

#define USBUART_PC_SAMPLE_FREQ_LEN            (3u)
#define USBUART_PC_VOLUME_LEN                 (2u)

#if !defined(USER_SUPPLIED_DEFAULT_VOLUME_VALUE)
    #define USBUART_PC_VOL_MIN_MSB            (0x80u)
    #define USBUART_PC_VOL_MIN_LSB            (0x01u)
    #define USBUART_PC_VOL_MAX_MSB            (0x7Fu)
    #define USBUART_PC_VOL_MAX_LSB            (0xFFu)
    #define USBUART_PC_VOL_RES_MSB            (0x00u)
    #define USBUART_PC_VOL_RES_LSB            (0x01u)
#endif /* USER_SUPPLIED_DEFAULT_VOLUME_VALUE */


/***************************************
* External data references
***************************************/
/**
* \addtogroup group_audio
* @{
*/
extern volatile uint8 USBUART_PC_currentSampleFrequency[USBUART_PC_MAX_EP][USBUART_PC_SAMPLE_FREQ_LEN];
extern volatile uint8 USBUART_PC_frequencyChanged;
extern volatile uint8 USBUART_PC_currentMute;
extern volatile uint8 USBUART_PC_currentVolume[USBUART_PC_VOLUME_LEN];
/** @} audio */

extern volatile uint8 USBUART_PC_minimumVolume[USBUART_PC_VOLUME_LEN];
extern volatile uint8 USBUART_PC_maximumVolume[USBUART_PC_VOLUME_LEN];
extern volatile uint8 USBUART_PC_resolutionVolume[USBUART_PC_VOLUME_LEN];

#endif /*  CY_USBFS_USBUART_PC_audio_H */


/* [] END OF FILE */
