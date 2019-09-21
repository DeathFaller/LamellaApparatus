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
#ifndef GLOBALVARIABLES_H
    #define GLOBALVARIABLES_H

    #include <Includes.h>
    
    // PC Interrupt (UART)
    char g_PC_InterruptSignal;             // 
    
    // Nextion Interrupt (UART)
    char g_Nextion_InterruptSignal;
    
    // Nextion Pages
    char g_ActivePage = 'H';                                // initialisiert auf Home-Bildschirm
    
    // Timer and TimerInterrupt
    volatile int t_timer_LaserSwitch = 0;           // Timer, counting for Laser Switch
    volatile char f_timer_LaserSwitch = 0;          // Timer flag, indicating the necessity of Laser Switch 
    int p_LaserSwitchPeriod = 100;                        // Period, with which the lasers get switched, in ms

    volatile int t_timer_LamellaLifetime = 0;
    volatile int f_timer_LamellaLifetime_Measuring = 0;


#endif
/* [] END OF FILE */
