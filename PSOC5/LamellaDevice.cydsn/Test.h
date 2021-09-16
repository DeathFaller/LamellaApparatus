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

#ifndef TEST_H
    #define TEST_H
    
    #include <project.h>
    #include <Laser.h>
    #include <GlobalVariables.h>
    #include <StepMotor.h>
    #include <SDCard.h>
    
    
    void Test()
    {
        // INIT
        g_ActivePage = 'Z';
        Nextion_SendString("page Test");
        
        CyDelay(100);
        
        Laser1(0);
        Laser2(0);
        Laser3(0);

        // Set Pictures to orange color
        
        Nextion_SendString("p_StepMotor.pic=1");
        Nextion_SendString("p_SD.pic=1");
        Nextion_SendString("p_L1.pic=1");
        Nextion_SendString("p_L2.pic=1");
        Nextion_SendString("p_L3.pic=1");
        Nextion_SendString("p_SDSpeed.pic=1");
        
        
        // MAIN
        
        while (g_ActivePage == 'Z')
        {
            switch(g_NextionInterrupt)
            {
                case '0':
                    CyDelay(1);
                    break;
                case 'M':       // Stepper
                    Nextion_SendString("p_StepMotor.pic=2");
                    Move90DegreeCCW();
                    CyDelay(1000);
                    Move90DegreeCW();
                    CyDelay(1000);
                    Nextion_SendString("p_StepMotor.pic=0");
                    break;
                case 'C':       // SD-Card (normal)
                    Nextion_SendString("p_SD.pic=2");
                    for (int i = 0; i < 10; i++)
                    {
                        LogLifetime("Test.txt", i, i*25, 0);
                        CyDelay(100);
                    }
                    for (int i = 0; i < 10; i++)
                    {
                        LogIntensity(i, 0, 0, 0, v_timer_Lifetime_ms, 123);   
                        CyDelay(100);
                    }
                    Nextion_SendString("p_SD.pic=0");
                    break;
                case '1':       // Laser 1
                    Laser1_Toggle();
                    if (LaserState3)
                    {
                        Nextion_SendString("p_L1.pic=0");   
                    }
                    else
                    {
                        Nextion_SendString("p_L1.pic=2"); 
                    }
                    break;
                case '2':       // Laser 2
                    Laser2_Toggle();
                    if (LaserState2)
                    {
                        Nextion_SendString("p_L2.pic=0");   
                    }
                    else
                    {
                        Nextion_SendString("p_L2.pic=2"); 
                    }
                    break;
                case '3':       // Laser 3
                    Laser3_Toggle();
                    if(LaserState3)
                    {
                        Nextion_SendString("p_L3.pic=0");   
                    }
                    else
                    {
                        Nextion_SendString("p_L3.pic=2"); 
                    }
                    break;
                case 'S':       // SD-Card (Speed)
                    Nextion_SendString("p_SDSpeed.pic=2");
                    WriteSpeedTest();
                    Nextion_SendString("p_SDSpeed.pic=0");
                    break;
            }
            g_NextionInterrupt = '0';
            
        }
        
    }



#endif

/* [] END OF FILE */
