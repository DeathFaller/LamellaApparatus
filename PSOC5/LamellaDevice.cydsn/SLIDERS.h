/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef SLIDERS_H
    #define SLIDERS_H
    
    char g_SliderValueReceiving = 0;            // Indicates whether slider values are received (1) or already received (2)
    char g_SliderValueBuffer[4];                // Saves received slider values
    
    #define SliderFactor_NumberOfMeasurements 10
    #define SliderFactor_SwitchPeriodOfLaser 10
    #define SliderFactor_MaxMeasurementTime 15
    #define SliderFactor_FormationTime 500
    #define SliderFactor_RelaxationTime 250
    #define SliderFactor_ConfirmationTime 500 
    #define SliderFactor_ThresholdValue 1
    
    #define SLIDER_NUMBER 'N'
    #define SLIDER_PERIOD 'P'
    #define SLIDER_MAXTIME 'M'
    #define SLIDER_FORMATION 'F'
    #define SLIDER_RELAXATION 'R'
    #define SLIDER_CONFIRMATION 'C'
    #define SLIDER_THRESHOLD 'T'
    
    #define SLIDER_GETNUMBER '&'
#endif

/* [] END OF FILE */
