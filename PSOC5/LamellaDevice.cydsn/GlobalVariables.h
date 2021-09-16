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

#include <ProgramParts.h>

#ifndef GLOBALVARIABLES_H
    #define GLOBALVARIABLES_H
     // Newly prepared
    char g_NextionInterrupt = '0';
    
    #include <PAGES.h>
    #include <BUTTONS.h>
    #include <SLIDERS.h>
    #include <MODES.h>


    
    // Error - codes
    volatile int g_Error_Code = 0;

    // old
    
    
    char g_PCInterrupt = '0';
    
    char g_ActivePage = '0';
    
    // measurement parameter:
    int g_NumberOfMeasurements = 0;
    int g_SwitchPeriodOfLaser_ms = 0;
    int g_MaxMeasurementTime_min = 0;
    int g_FormationTime_ms = 0;
    int g_RelaxationTime_ms = 0;
    int g_ConfirmationTime_ms = 0;
    int g_ThresholdValue_mV = 0;
    
    char g_DataLogging = 0;
    
    #ifdef ChangeFileName
    // Filename for logging data
        #define LengthOfFileName 4
    char FileName[LengthOfFileName];               // Size of 8, because FAT only supports 8+3     
    #endif 
    // Parameters of step motor
  
    // maximum frequency

    
    // auxiliary constants

    #define NextionColor_Red 63488
    #define NextionColor_Green 34784
    
    // Should Laser be used?

    const int MAXMEASUREMENTSTEPS = 4;
    char g_measurementLasers[3][4];

    // State of Lasers
    
    char LaserState1 = 0;
    char LaserState2 = 0;
    char LaserState3 = 0;
    
    // State of Relais
    char OutputState1 = 0;
    char OutputState2 = 0;
    
    // Timer
    volatile int v_timer_100ms = 0;
    volatile char v_timerflag_100ms = 0;
    
    volatile int v_timer_waiting = 0;
    volatile char v_timerflag_waiting = 0;
    
    volatile double v_timer_Lifetime_ms = 0;
    
    volatile int v_timer_Measurement = 0;
    volatile int v_timerflag_Measurement = 0;
    
    volatile int v_timer_LaserSwitch = 0;
    volatile int v_timerflag_LaserSwitch = 0;
    
    volatile int v_timer_500ms = 0;
    volatile int v_timerflag_500ms = 0;
    

    
#endif
/* [] END OF FILE */
