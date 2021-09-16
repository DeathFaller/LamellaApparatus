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

#ifndef LASERSELECT_H
    #define LASERSELECT_H

    #include <project.h>
    #include <GlobalVariables.h>
    #include <Nextion.h>
    
    
    const char MeasurementLaser[3][4] = {
        {BUTTON_L1_1, BUTTON_L1_2, BUTTON_L1_3, BUTTON_L1_4},
        {BUTTON_L2_1, BUTTON_L2_2, BUTTON_L2_3, BUTTON_L2_4},
        {BUTTON_L3_1, BUTTON_L3_2, BUTTON_L3_3, BUTTON_L3_4}
    };
    
    void Init_MeasurementLasers()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                g_measurementLasers[i][j] = 0;
                Nextion_SendBackgroundColorToButton((char*)MeasurementLaser[i][j], NextionColor_Red);
            }
        }
    }
    
    int ToggleLaser(char interrupt)
    {
        int returnValue = 0;
        
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {           
                if (MeasurementLaser[i][j] == interrupt)
                {
                    g_measurementLasers[i][j] = !g_measurementLasers[i][j];
                    if (g_measurementLasers[i][j])
                    {
                        Nextion_SendBackgroundColorToButton((char*)MeasurementLaser[i][j], NextionColor_Green);
                    }
                    else
                    {
                        Nextion_SendBackgroundColorToButton((char*)MeasurementLaser[i][j], NextionColor_Red);
                    }
                
                }
            }
        }
        
        return returnValue;
    }
    
    int Laserselect()
    {   
        Init_MeasurementLasers();
        
        g_NextionInterrupt = '0';
        Nextion_SendString("page LaserSelect");
        
        while (1)
        {
            switch (g_NextionInterrupt)
            {
                case '0':
                    // Do nothing
                    break;
                case BUTTON_CONFIRM:
                    return 0;
                    break;
                case 'H':
                    return 1;
                    break;
                default:
                    ToggleLaser(g_NextionInterrupt);
                    break;
            }
            g_NextionInterrupt = '0';
        }
    }
#endif

/* [] END OF FILE */
