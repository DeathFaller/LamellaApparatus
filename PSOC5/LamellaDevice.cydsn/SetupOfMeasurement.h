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

#ifndef SETUPOFMEASUREMENT_H
    #define SETUPOFMEASUREMENT_H

    #include <GlobalVariables.h>
    #include <Nextion.h>
    #include <Nextion_PlotSetupData.h>
    #include <Laser.h>
    #include <ADC.h>
    #include <StepMotor.h>
    #include <Error.h>
    
    
    void switchLasers(char const symbol)
    {
        switch(symbol)
        {
            case BUTTON_LASER1:
                Laser1_Toggle();
                if (LaserState1)
                {
                    Nextion_SendBackgroundColorToButton("b_Laser1", NextionColor_Green);
                }
                else
                {
                    Nextion_SendBackgroundColorToButton("b_Laser1", NextionColor_Red);
                }
                break;
                
            case BUTTON_LASER2:
                Laser2_Toggle();
                if (LaserState2)
                {
                    Nextion_SendBackgroundColorToButton("b_Laser2", NextionColor_Green);
                }
                else
                {
                    Nextion_SendBackgroundColorToButton("b_Laser2", NextionColor_Red);
                }
                break;
                
            case BUTTON_LASER3:
                Laser3_Toggle();
                if (LaserState3)
                {
                    Nextion_SendBackgroundColorToButton("b_Laser3", NextionColor_Green);
                }
                else
                {
                    Nextion_SendBackgroundColorToButton("b_Laser3", NextionColor_Red);
                }
                break;
            default:
                break;
        }
    }
    
    void rotateStepMotor(char const symbol)
    {
        switch(symbol)
        {
            case BUTTON_1STEP_CW:
                MoveOneStepCW();
                break;
                
            case BUTTON_1STEP_CCW:
                MoveOneStepCCW();
                break;
                
            case BUTTON_10DEG_CW:
                Move10DegreeCW();
                break;
            case BUTTON_10DEG_CCW:
                Move10DegreeCCW();
                break;
                
            case BUTTON_90DEG_CW:
                Move90DegreeCW();
                break;
            case BUTTON_90DEG_CCW:
                Move90DegreeCCW();
                break;
                
            case BUTTON_CREATELAMELLA:
                Move90DegreeCW();
                CyDelay(g_FormationTime_ms);
                Move90DegreeCCW();
                break;
                
            default:
                break;
        }
    }
    
    int SetupOfMeasurement()
    {     
        Nextion_SendString("page Setup");
        g_NextionInterrupt = '0';
        // Init
        
        // Turn off all lasers for safety reasons.
        turnAllLasersOff();
        
        Nextion_SendBackgroundColorToButton("b_Laser1", NextionColor_Red);
        Nextion_SendBackgroundColorToButton("b_Laser2", NextionColor_Red);
        Nextion_SendBackgroundColorToButton("b_Laser3", NextionColor_Red);
        
        // Main 
        
        
        
        while (1)
        {
            // Plotting of current ADC value onto Nextion. 
            if (v_timerflag_100ms)
            {
                v_timerflag_100ms = 0;   
                
                int ADCValue = GetADCValue();
                
                Nextion_SendValueToValueBox("n_ADC", ADCValue);
                NextionPlot_PointsToSetupAxes((float)g_ThresholdValue_mV, 4095, (float)ADCValue);
            }
            // Reacting to Input-Buttons:
            switchLasers(g_NextionInterrupt);
            rotateStepMotor(g_NextionInterrupt);
            switch (g_NextionInterrupt)
            {
                case BUTTON_CONFIRM:                   // Confirm -> Messstart!
                    return 0;
                    break;
                case BUTTON_HOME:
                    return 1;
                    break;
                default:
                    break;
            }   
            g_NextionInterrupt = '0';
        }
    }
    
#endif

/* [] END OF FILE */
