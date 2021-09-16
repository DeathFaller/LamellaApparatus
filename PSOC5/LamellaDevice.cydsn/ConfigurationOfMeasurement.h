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

#ifndef CONFIGURATIONOFMEASUREMENT_H
    #define CONFIGURATIONOFMEASUREMENT_H
    
    #include <Nextion.h>
    #include <GlobalVariables.h>
    #include <Error.h>
    #include <ProgramParts.h>
    
    #ifdef ChangeFileName
    #include <FileName.h>    
    #endif
    
    int ConfigurationOfMeasurement(const char measurementMode)
    {
        // Init
        g_NextionInterrupt = '0';
        Nextion_SendString("page Parameters");
        
        int number = 0;
        char ActivePage = '1';
        char UpdateNecessary = 1;
        
        switch (measurementMode)
        {
            case MODE_LIFETIME:
                g_NumberOfMeasurements = 300;
                g_SwitchPeriodOfLaser_ms = 50;
                g_MaxMeasurementTime_min = 300;
                break;
            case MODE_THICKNESS:
                g_NumberOfMeasurements = 50;
                g_SwitchPeriodOfLaser_ms = 500;
                g_MaxMeasurementTime_min = 60;
                break;
            case MODE_LIFETIMEANDTHICKNESS:
                g_NumberOfMeasurements = 300;
                g_SwitchPeriodOfLaser_ms = 500;
                g_MaxMeasurementTime_min = 300;
                break;
            default:
                setError(1);
                return 1;
                break;
        }
        g_FormationTime_ms = 5000;
        g_RelaxationTime_ms = 5000;
        g_ConfirmationTime_ms = 5000;
        g_ThresholdValue_mV = 55; 
        
        while (1)
        {
            if (UpdateNecessary)
            {
                UpdateNecessary = 0;   
                // send the most recent values to the sliders
                if (ActivePage == '1')                  // First parameter page
                {
                    Nextion_SendValueToValueBox("n_Number", g_NumberOfMeasurements);
                    Nextion_SendValueToValueBox("h_Number", g_NumberOfMeasurements/SliderFactor_NumberOfMeasurements);
                    Nextion_SendValueToValueBox("n_Period", g_SwitchPeriodOfLaser_ms);
                    Nextion_SendValueToValueBox("h_Period", g_SwitchPeriodOfLaser_ms/SliderFactor_SwitchPeriodOfLaser);
                    Nextion_SendValueToValueBox("n_MaxTime", g_MaxMeasurementTime_min);
                    Nextion_SendValueToValueBox("h_MaxTime", g_MaxMeasurementTime_min/SliderFactor_MaxMeasurementTime);
                    }
                else                                    // Additional parameter page
                {
                    Nextion_SendValueToValueBox("n_Formation", g_FormationTime_ms);
                    Nextion_SendValueToValueBox("h_Formation", g_FormationTime_ms/SliderFactor_FormationTime);
                    Nextion_SendValueToValueBox("n_Relaxation", g_RelaxationTime_ms);
                    Nextion_SendValueToValueBox("h_Relaxation", g_RelaxationTime_ms/SliderFactor_RelaxationTime);
                    Nextion_SendValueToValueBox("n_Confirmation", g_ConfirmationTime_ms);
                    Nextion_SendValueToValueBox("h_Confirmation", g_ConfirmationTime_ms/SliderFactor_ConfirmationTime);
                    Nextion_SendValueToValueBox("n_Threshold", g_ThresholdValue_mV);
                    Nextion_SendValueToValueBox("h_Threshold", g_ThresholdValue_mV/SliderFactor_ThresholdValue);
                }
            }
            

            if (g_NextionInterrupt != '0')
            {
                // Get Number from slider
               number = Nextion_GetSliderValue();
            }
            switch (g_NextionInterrupt)
            {
                case '0':
                    // Do nothing
                    break;
                
                case SLIDER_NUMBER:
                    if (number == 0)
                    {
                        number = 1;             // minimum value: 10 lamellas
                    }
                    g_NumberOfMeasurements = number * SliderFactor_NumberOfMeasurements;
                    Nextion_SendValueToValueBox("n_Number", g_NumberOfMeasurements);
                    break;
                
                case SLIDER_PERIOD:
                    if (measurementMode != MODE_LIFETIME)
                    {
                        if (number <= 50)
                        {
                            number = 50;             // minimum value: 500 ms, less is not possible, because of the SD-Card
                        }
                    }
                    else
                    {
                        if (number == 0)
                        {
                            number = 1;             // minimum value: 10 ms
                        }
                    }
                    g_SwitchPeriodOfLaser_ms = number * SliderFactor_SwitchPeriodOfLaser;
                    Nextion_SendValueToValueBox("n_Period", g_SwitchPeriodOfLaser_ms);
                    break;
                
                case SLIDER_MAXTIME:
                    if (number == 0)
                    {
                        number = 1;             // minimum value: 15 min
                    }
                    g_MaxMeasurementTime_min = number * SliderFactor_MaxMeasurementTime;
                    Nextion_SendValueToValueBox("n_MaxTime", g_MaxMeasurementTime_min);
                    
                    break;
                
                case SLIDER_FORMATION:
                    if (number == 0)
                    {
                        number = 1;             // minimum value: 500 ms
                    }
                    g_FormationTime_ms = number * SliderFactor_FormationTime;
                    Nextion_SendValueToValueBox("n_Formation", g_FormationTime_ms);
                    
                    break;
                
                case SLIDER_RELAXATION:
                    if (number == 0)
                    {
                        number = 1;             // minimum value: 250 ms
                    }
                    g_RelaxationTime_ms = number * SliderFactor_RelaxationTime;
                    Nextion_SendValueToValueBox("n_Relaxation", g_RelaxationTime_ms);
                    
                    break;
                
                case SLIDER_CONFIRMATION:
                    if (number == 0)
                    {
                        number = 1;             // minimum value: 500 ms
                    }
                    g_ConfirmationTime_ms = number * SliderFactor_ConfirmationTime;
                    Nextion_SendValueToValueBox("n_Confirmation", g_ConfirmationTime_ms);
                    
                    break;
                
                case SLIDER_THRESHOLD:
                    if (number == 0)
                    {
                        number = 1;             // minimum value: 1 mV
                    }
                    g_ThresholdValue_mV = number * SliderFactor_ThresholdValue;
                    Nextion_SendValueToValueBox("n_Threshold", g_ThresholdValue_mV);
                    
                    break;
                case BUTTON_ADDITIONALSETTINGS:
                    if (ActivePage == '1')
                    {
                        ActivePage = '2';
                        Nextion_SendString("page AddParameters");
                    }
                    else
                    {
                        ActivePage = '1';  
                        Nextion_SendString("page Parameters");
                    }
                    UpdateNecessary = 1;
                    break;
                
                case BUTTON_CONFIRM:           // Confirmation of parameters 
                    return 0;
                    break;
                    
                case BUTTON_HOME:
                    return 1;
                    break;

                #ifdef ChangeFileName    
                case 'D':
                    Filename();
                    Nextion_SendString("page AddParameters");
                    ActivePage = '2';
                    UpdateNecessary = 1;
                    CyDelay(200);
                    SendFileNameToNextion();
                    break;
                #endif
                    
                default:
                    setError(1);
                    return 2;
                    break;
            }
            
            g_NextionInterrupt = '0';
            CyDelay(5);                     // Maybe useful, maybe not. Will see it.
        }
        
    }

#endif

/* [] END OF FILE */
