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
#ifndef SWITCHINTERRUPTVARIABLES_H
    #define SWITCHINTERRUPTVARIABLES_H

    #include <Includes.h>
    
    char Protect_PCInterrupt = 0;
    
    void Switch_PCInterrupt(char New){
        if (Protect_PCInterrupt == 0){
            Protect_PCInterrupt = 1;
            g_PC_InterruptSignal = New;
            Protect_PCInterrupt = 0;
        }
        
    }
    
    char Protect_NextionInterrupt = 0;
    void Switch_NextionInterrupt(char New){
        if (Protect_NextionInterrupt == 0){
            Protect_NextionInterrupt = 1;
            g_Nextion_InterruptSignal = New;
            Protect_NextionInterrupt = 0;
        }
    }
    
#endif
/* [] END OF FILE */
