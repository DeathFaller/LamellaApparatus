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

#ifndef FINISHED_H
    #define FINISHED_H
    
    #include <project.h>
    #include <GlobalVariables.h>
    #include <Nextion.h>
    #include <Laser.h>
    
    
    void Finished(char* string)
    {
        turnAllLasersOff();
        Nextion_SendString("page Finished");
        Nextion_SendTextToTextBox("t_Message", string);
        while(g_NextionInterrupt != BUTTON_HOME)
        {
            CyDelay(1);
        }
    }
    
    #endif

/* [] END OF FILE */
