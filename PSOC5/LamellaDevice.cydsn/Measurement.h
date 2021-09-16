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

#ifndef MEASUREMENT_H
    #define MEASUREMENT_H

    #include <project.h>
    #include <ADC.h>
    #include <GlobalVariables.h>
    #include <StepMotor.h>
    #include <Laser.h>
    #include <SDCard.h>
    #include <Nextion.h>
    #include <Nextion_PlotLifetimeData.h>
    #include <Finished.h>
    
    void Measurement(char const measurementMode)
    {
        // INIT
        Nextion_SendString("page Measurement");
        
        char LamellaPresent = 0;
        char LamellaRuptured = 1;           // For indication if Lamella is over max. Lifetime
        int CounterMeasurements = 0;
        
        int recentMeasurementStep = 0;          // Used for determining which lasers should be turned on
       
        Nextion_SendValueToValueBox("n_MaxLamellas", g_NumberOfMeasurements);

        int ADC_Value;
        char Rupture_ConfirmationStarted = 0;
       
        double RuptureStart_ms = 0;
        
        double timeOfADCValue = 0;
        
        // MAIN

        double MaxLifetime_ms = g_MaxMeasurementTime_min * 60 * 1000;
        Nextion_SendValueToValueBox("n_ScalingPlot", g_MaxMeasurementTime_min);
        
        while (1)
        {
            // Messung starten
            if (g_NextionInterrupt == '0')
            {
                if (CounterMeasurements < g_NumberOfMeasurements)
                {
    
                    if (LamellaPresent)
                    {
                        if (v_timerflag_Measurement)
                        {
                            v_timerflag_Measurement = 0;
                            
                            // Messung durchführen
                             if (v_timer_Lifetime_ms > MaxLifetime_ms)
                            {
                                LamellaPresent = 0;             // Arbitrary rupture of lamella
                                LamellaRuptured = 0;
                            }
                            else
                            {
                                LamellaRuptured = 1;
                                ADC_Value = GetADCValue();
                                timeOfADCValue = v_timer_Lifetime_ms;
                                
                                if (ADC_Value < g_ThresholdValue_mV)
                                {
                                    Rupture_ConfirmationStarted = 1;   
                                }
                                else
                                {
                                    Rupture_ConfirmationStarted = 0;
                                }
                                
                                if (v_timer_Lifetime_ms < g_RelaxationTime_ms)
                                {
                                    Rupture_ConfirmationStarted = 0;
                                } 
                                if (Rupture_ConfirmationStarted)
                                {
                                    double DiffMeasurementRupture = v_timer_Lifetime_ms - RuptureStart_ms;
                                    if (RuptureStart_ms == 0)   
                                    {
                                        RuptureStart_ms = v_timer_Lifetime_ms;
                                    }
                                    else if (DiffMeasurementRupture > g_ConfirmationTime_ms){
                                        LamellaPresent = 0;
                                        // Lamella ruptured
                                    }
                                }
                                else
                                {
                                    RuptureStart_ms = 0; // Reset of Timer necessary   
                                }
                                
                            }
                            // Datenpunkt speichern -> SD Karte
                            
                            if (g_DataLogging)
                            {
                                LogIntensity(CounterMeasurements, LaserState1, LaserState2, LaserState3, timeOfADCValue, ADC_Value);
                            }
                            
                            if (LamellaPresent == 0)
                            {
                                // Only happens if lamella ruptures (normally or arbitrary)
                             
                                if (measurementMode != 'T')
                                {
                                    LogLifetime("Life.LAM", CounterMeasurements, v_timer_Lifetime_ms, LamellaRuptured);   
                                }
                                Nextion_PlotLifetime(CounterMeasurements, v_timer_Lifetime_ms);
                                ++CounterMeasurements;
                            }
                        }
                        
                        if (v_timerflag_500ms)
                        {
                            v_timerflag_500ms = 0;
                            Nextion_SendValueToValueBox("n_Timer", v_timer_Lifetime_ms);
                            Nextion_SendValueToValueBox("n_Intensity", ADC_Value);
                        }
                        
                        if (v_timerflag_LaserSwitch)
                        {
                            v_timerflag_LaserSwitch = 0;
                            
                            v_timer_Measurement = 0;
                            v_timerflag_Measurement = 0;
                            
                            Laser1(g_measurementLasers[0][recentMeasurementStep]);
                            Laser2(g_measurementLasers[1][recentMeasurementStep]);
                            Laser3(g_measurementLasers[2][recentMeasurementStep]);
                            ++recentMeasurementStep;
                            if (recentMeasurementStep >= MAXMEASUREMENTSTEPS)
                            {
                                recentMeasurementStep = 0;
                            } 
                        }
                    }
                    else
                    {
                        turnAllLasersOff();
                        
                        Nextion_SendValueToValueBox("n_Progress", CounterMeasurements); // Send recent lamella number to display
                        int ProgressInPercent = (int)(100 * CounterMeasurements / g_NumberOfMeasurements);
                        Nextion_SendValueToValueBox("j_Progress", ProgressInPercent);
                        Move90DegreeCW();           
                        v_timer_waiting = 0;
                        while (v_timer_waiting < g_FormationTime_ms)
                        {
                            CyDelay(10);
                        }
                        Move90DegreeCCW();
                        LamellaPresent = 1;
                        v_timer_Lifetime_ms = 0;
                        v_timer_LaserSwitch = 0;
                        v_timer_Measurement = 0;
                        recentMeasurementStep = 0;
                        
                    }
                }
                else
                {
                    g_NextionInterrupt = '0';
                    Finished("Measurement finished!");
                    break;
                }
            }  
            
            if (g_NextionInterrupt == BUTTON_STOP)
            {
                //Messstop
                g_NextionInterrupt = '0';
                Finished("Measurement stopped");
                break;
            }
        }
    }
    

#endif



/* [] END OF FILE */
